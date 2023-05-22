#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <array>
#include <iomanip>
#include <iterator>
#include <cmath>
#include <utility>
#include <limits>

class Matrix {
public:
    Matrix();
    Matrix(long long rows, long long columns);
    Matrix(std::vector<std::vector<long long> > set_values);

    std::size_t GetRows() const;
    std::size_t GetColumns() const;
    std::shared_ptr<std::vector<std::vector<long long> > > GetMatrix() const;
    void SetNewValues(const std::vector<std::vector<long long> > new_values);
    void SetRows(const std::size_t rows);
    void SetColumns(const std::size_t columns);
    void SetSize(const std::size_t rows, const std::size_t columns); 
    std::vector<std::vector<long long> > GetValues();
    Matrix ScalarMultiplication(long long scalar) const;
    Matrix MultiplyMatrix(Matrix& b);
    Matrix Arithmetic(Matrix& b, bool negative);
    Matrix Transpose();
    Matrix REF(bool is_rref);
    Matrix Inverse();
    Matrix Exponentiation(double exponent); 
    bool Orthogonal(Matrix& b, Matrix& c);
    double DotProduct(Matrix& b);
    long long Trace();
    int Rank();

    void Print() const;
  
private:
    std::size_t rows_, colums_;
    std::shared_ptr<std::vector<std::vector<long long> > > matrix_;


    void RowOperations(long long rows, 
          long long column, std::vector<std::vector<long long> >& DEF,
          bool is_rref);

};

#endif
