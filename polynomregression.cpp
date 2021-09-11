#include "polynomregression.h"
#include <QDebug>


PolynomRegression::PolynomRegression(QVector<double> X, QVector<double> Y):X_(X), Y_(Y)
{

}


QVector<double> PolynomRegression::polynomFunction(const QVector<double>& X)
{
    double y;
    QVector<double> y_predict;

    int num_x = X.size();
    int num_weights = model_weights.size();

    for (int c = 0; c < num_x; c++)
    {
        y = 0.0;
        for (int i = 0; i < num_weights; i++)
        {
            y += std::pow(X[c], i) * model_weights[i];
        }
        y_predict.push_back(y);
    }
    return y_predict;
}



QVector<double> PolynomRegression::compPolinomGrad(QVector<double>& X_norm, QVector<double>& Y_norm)
{
    int n_weights = model_weights.size();
    int n_x_norm = X_norm.size();

    QVector<double> y_predict;
    QVector<double> delta_y;
    QVector<double> delta_w;



    //y_predict = b + k * x
    y_predict = polynomFunction(X_norm);

    //delta_y = (y_pred - y_ground)
    std::transform(y_predict.begin(), y_predict.end(),
                   Y_norm.begin(),std::back_inserter(delta_y), std::minus<double>());


    for(int c = 0; c < n_weights; c++)
    {
        QVector<double> delta_pow;

        //X**0, X**1, ... X**(n_weihgts-1)
        for(int i = 0; i < n_x_norm; i++)
        {
            delta_pow.push_back(std::pow(X_norm[i], c));
        }

        QVector<double> delta_tmp;

        //(y_pred - y_ground) * [X**0, X**1, ... X**(n_weihgts-1)]
        std::transform(delta_y.begin(), delta_y.end(), delta_pow.begin(),
                       std::back_inserter(delta_tmp), std::multiplies<double>());

        //sum(delta_y * delta_pow) / n_x_norm
        delta_w.push_back(std::accumulate(delta_tmp.begin(), delta_tmp.end(), 0.0) / n_x_norm);

    }

    return delta_w;
}


QVector<double> PolynomRegression::polynomRegression(double alpha, int num_steps, double sq_meters = 0, int show_every = 100)
{
    NormData nDataX;
    NormData nDataY;

    nDataX = StandartScoreNorm(X_);
    nDataY = StandartScoreNorm(Y_);

    for(int c = 0; c < num_steps; c++)
    {
        QVector<double> deltaWeights;
        int n_weights = model_weights.size();

        deltaWeights = compPolinomGrad(nDataX.v_norm, nDataY.v_norm);

        std::transform(deltaWeights.begin(), deltaWeights.end(),
                       deltaWeights.begin(), [&alpha](double& x){
            return x * alpha;
        });

        for(int c = 0; c < n_weights; c++)
        {
            model_weights[c] -= deltaWeights[c];
        }

        if ((c % show_every == 0) & (sq_meters != 0))
        {
            double sq_meters_norm = (sq_meters - nDataX.v_mean) / nDataX.v_std;

            const QVector<double> sqMet{sq_meters_norm};

            QVector<double> predict_price = polynomFunction(sqMet);

            double predict_price_denorm = predict_price[0] * nDataY.v_std +nDataY.v_mean;

            qDebug() << "predict_price_denorm: $" << int(predict_price_denorm * 1000);
        }
    }

    return model_weights;
};

