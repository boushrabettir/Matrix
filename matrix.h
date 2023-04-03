#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <vector>

class Matrix {
public:
    Matrix();
    Matrix(double rows, double columns);
    
    double GetRows() const;
    double GetColumns() const;
    std::vector<std::vector<double> > GetMatrix() const;

    std::vector<std::vector<double> > GetValues();

    void SetRows(const double rows);
    void SetColumns(const double columns);

    void SetNewValues(const std::vector<std::vector<double> > new_values);

    Matrix ScalarMultiplication(Matrix& matrix, double scalar) const;
    Matrix MultiplyMatrix(Matrix& a, Matrix& b, bool not_a_match);
    Matrix AddMatrix(Matrix& a, Matrix& b, bool not_a_match);


    void Print() const;

private:
    double rows_, colums_;
    std::vector<std::vector<double> > matrix_;
};

#endif
