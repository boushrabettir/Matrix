#ifndef MATRIX_H
#define MATRIX_H

#include <array>


class Matrix {
public:
    Matrix();
    
    std::array<double, 2> TwoXTwoTopRow() const;
    std::array<double, 2> TwoXTwoBottomRow() const;

    std::array<std::array<double, 2>, 2> TwoXTwoMatrix() const;

    void TwoXTwoSetTopRow(const std::array<double, 2>& top_row);
    void TwoXTwoSetBottomRow(const std::array<double, 2>& bottom_row);


    std::array<std::array<double, 2>, 2> CombinedTwoXTwo(const std::array<double, 2>& top_row, const std::array<double, 2>& bottom_row);
    std::array<std::array<double, 2>, 2> Multiplication2X2Scalar(double number);
    Matrix MultiplyMatrix(Matrix& a) const;

    void Print() const;

private:
    std::array<double, 2> top_row_;
    std::array<double, 2> bottom_row_;
    std::array<std::array<double, 2>, 2> matrix_;
};

#endif
