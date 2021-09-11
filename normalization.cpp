#include "normalization.h"

Normalization::Normalization()
{

}


NormData Normalization::StandartScoreNorm(const QVector<double>& v)
{
    int n = v.size();
    QVector<double> diff(n);
    QVector<double> v_norm(n);


    if (n == 0)
        return {v_norm, 0, 0 };
    else
    {
        double v_mean = std::accumulate(v.begin(), v.end(), 0.0) / n;

        std::transform(v.begin(), v.end(), diff.begin(), [v_mean](double x){
            return std::pow((x - v_mean),2);
        });

        double mean_square_dev = std::accumulate(diff.begin(), diff.end(), 0.0) / n;
        double v_std = std::sqrt(mean_square_dev);

        std::transform(v.begin(), v.end(), v_norm.begin(), [v_std, v_mean](double x){
            return (x - v_mean) / v_std;
        });

        return {v_norm, v_mean, v_std};
    }
}


QVector<double> Normalization::StandartScoreDeonorm(NormData& norm_data)
{
    int n = norm_data.v_norm.size();
    QVector<double> X(n);
    QVector<double>::iterator v_norm_b = norm_data.v_norm.begin();
    QVector<double>::iterator v_norm_e = norm_data.v_norm.end();

    double v_mean = norm_data.v_mean;
    double v_std = norm_data.v_std;

    std::transform(v_norm_b, v_norm_e, X.begin(), [v_mean, v_std](double x){
       return x * v_std + v_mean;
    });

    return X;
}


NormData Normalization::MinMaxNorm(const QVector<double>& v)
{
    int n = v.size();
    QVector<double> v_norm(n);

    double v_min;
    double v_max;

    v_min = *std::min_element(v.begin(), v.end());
    v_max = *std::max_element(v.begin(), v.end());


    std::transform(v.begin(), v.end(), v_norm.begin(), [v_min, v_max](double x){
        return (x - v_min)/(v_max - v_min);
    });

    return {v_norm, v_min, v_max};
}


QVector<double> Normalization::MinMaxDenorm(NormData& norm_data)
{
    int n = norm_data.v_norm.size();
    QVector<double>::iterator v_norm_b = norm_data.v_norm.begin();
    QVector<double>::iterator v_norm_e = norm_data.v_norm.end();
    QVector<double> X(n);


    double &v_min = norm_data.v_mean;
    double &v_max = norm_data.v_std;


    std::transform(v_norm_b, v_norm_e, X.begin(), [v_min, v_max](double x){
        return x * (v_max - v_min) + v_min;
    });

    return X;
}


NormData Normalization::DivMaxNorm(const QVector<double>& v)
{
    int n = v.size();
    QVector<double> v_norm(n);
    double v_max;

    v_max = *std::max_element(v.begin(), v.end());
    std::transform(v.begin(), v.end(), v_norm.begin(), [v_max](double x){
        return x / v_max;
    });

    return {v_norm, 0, v_max};
}


QVector<double> Normalization::DivMaxDenorm(NormData& norm_data)
{
    int n = norm_data.v_norm.size();
    QVector<double>::iterator v_norm_b = norm_data.v_norm.begin();
    QVector<double>::iterator v_norm_e = norm_data.v_norm.end();
    QVector<double> X(n);
    double& v_max = norm_data.v_std;


    std::transform(v_norm_b, v_norm_e, X.begin(), [v_max](double x){
        return x * v_max;
    });

    return X;
}
