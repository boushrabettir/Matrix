#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <vector>
#include <memory>

class Matrix {
public:
    Matrix();
    Matrix(size_t rows, size_t columns);
    double GetRows() const;
    double GetColumns() const;
    std::shared_ptr<std::vector<std::vector<double> > > GetMatrix() const;

    std::vector<std::vector<double> > GetValues();

    void SetRows(const size_t rows);
    void SetColumns(const size_t columns);

    void SetNewValues(const std::vector<std::vector<double> > new_values);

    Matrix ScalarMultiplication(Matrix& matrix, double scalar) const;
    Matrix MultiplyMatrix(Matrix& a, Matrix& b, bool not_a_match);
    Matrix Arithmetic(Matrix& a, Matrix& b, bool negative);
    Matrix Transpose(Matrix& a);
    Matrix Lamda(Matrix& a);
    Matrix REF(Matrix& a);


    void Print() const;

private:
    size_t rows_, colums_;
    // std::vector<std::vector<double> > matrix_;
    std::shared_ptr<std::vector<std::vector<double> > > matrix_;
    
};

#endif
