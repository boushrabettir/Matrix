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
    void SetNewValues(const std::vector<std::vector<long long> > new_values);
    void SetRows(const long long rows);
    void SetColumns(const long long columns);
    void SetSize(const long long rows, const long long columns); 
    std::vector<std::vector<long long> > GetValues();
    Matrix ScalarMultiplication(Matrix& matrix, long long scalar) const;
    Matrix MultiplyMatrix(Matrix& a, Matrix& b);
    Matrix Arithmetic(Matrix& a, Matrix& b, bool negative);
    Matrix Transpose(Matrix& a);
    Matrix REF(Matrix& a, bool is_rref);
    Matrix Inverse(Matrix& a);
    Matrix LUFactorization(Matrix& a);
    int Rank(Matrix& a);

    void Print() const;
    
// protected:
    // wont work in unit tests. figure this out.

  
private:
    long long rows_, colums_;
    std::shared_ptr<std::vector<std::vector<long long> > > matrix_;


    void RowOperations(long long rows, 
          long long column, std::vector<std::vector<long long> >& DEF,
          bool is_rref);

};

#endif
