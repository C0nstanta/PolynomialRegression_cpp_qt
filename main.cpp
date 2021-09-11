#include <QCoreApplication>
#include <QDebug>

#include <polynomregression.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //X - Our square meters for every flat in dataset
    QVector<double> X{58.0, 42.0, 45.0, 44.0, 70.0,
                      60.0, 32.0, 46.0, 51.0, 58.0, 59.4, 48.0,
                      68.0, 64.0, 34.8, 60.06, 36.0, 43.0};
    //Y - Price in 1000 usd (Ground Truth)
    QVector<double> Y{80.0, 67.999, 70.0, 75.0, 83.0, 68.0, 57.0,
                      63.0, 80.0, 75.5, 73.5, 74.0, 79.0, 120.0, 68.0,
                      72.0, 58.0, 76.0};
    const double alpha = 0.01;
    const int num_steps = 501;
    double square_meters = 80.0;
    int show_every = 100;

    PolynomRegression pol2(X, Y);


    pol2.model_weights = {0.01, 0.01, 0.01};

    pol2.compPolinomGrad(X, Y);


    pol2.polynomRegression(alpha, num_steps, square_meters, show_every);


    return a.exec();
}
