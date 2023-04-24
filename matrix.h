#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <vector>
#include <memory>


class Matrix {
public:
    Matrix();
    Matrix(long long rows, long long columns);
    Matrix(std::vector<std::vector<long long> > set_values);
    long long GetRows() const;
    long long GetColumns() const;
    std::shared_ptr<std::vector<std::vector<long long> > > GetMatrix() const;

    std::vector<std::vector<long long> > GetValues();

    void SetRows(const long long rows);
    void SetColumns(const long long columns);
    void SetSize(const long long rows, const long long columns); 
    // implement ^

    void SetNewValues(const std::vector<std::vector<long long> > new_values);
    void RowOperations(long long rows, long long column, std::vector<std::vector<long long> >& DEF);

    Matrix ScalarMultiplication(Matrix& matrix, long long scalar) const;
    Matrix MultiplyMatrix(Matrix& a, Matrix& b);
    Matrix Arithmetic(Matrix& a, Matrix& b, bool negative);
    Matrix Transpose(Matrix& a);
    Matrix REF(Matrix& a);
    Matrix Inverse(Matrix& a);


    void Print() const;

private:
    long long rows_, colums_;
    std::shared_ptr<std::vector<std::vector<long long> > > matrix_;
    
};

#endif
