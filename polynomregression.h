#ifndef POLYNOMREGRESSION_H
#define POLYNOMREGRESSION_H

#include "normalization.h"
#include <QVector>


class PolynomRegression: public Normalization
{
public:
    PolynomRegression(const QVector<double>, const QVector<double>);

    QVector<double> polynomFunction(const QVector<double>&);
    QVector<double> compPolinomGrad(QVector<double>&, QVector<double>&);

    QVector<double> polynomRegression(const double alpha, const int num_steps,
                                      double sq_meters, int show_every);

    QVector<double> model_weights;

private:
    const QVector<double> X_;
    const QVector<double> Y_;
};

#endif // POLYNOMREGRESSION_H
