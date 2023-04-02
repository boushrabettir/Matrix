#include <iostream>

#include "matrix.h"
#include <array>

Matrix::Matrix() {};

std::array<double, 2> Matrix::TwoXTwoTopRow() const { return top_row_; }
std::array<double, 2> Matrix::TwoXTwoBottomRow() const { return bottom_row_; }
std::array<std::array<double, 2>, 2> Matrix::TwoXTwoMatrix() const { return matrix_; }

void Matrix::TwoXTwoSetTopRow(const std::array<double, 2>& top_row) { top_row_ = top_row; }
void Matrix::TwoXTwoSetBottomRow(const std::array<double, 2>& bottom_row) { bottom_row_ = bottom_row; }

std::array<std::array<double, 2>, 2> Matrix::CombinedTwoXTwo(const std::array<double, 2>& top_row, const std::array<double, 2>& bottom_row) {
    
    /* Row major order */
    matrix_[0][0] = top_row[0];
    matrix_[0][1] = top_row[1];
    matrix_[1][0] = bottom_row[0];
    matrix_[1][1] = bottom_row[1];

    return matrix_;
}

std::array<std::array<double, 2>, 2> Matrix::Multiplication2X2Scalar(double number) {
   matrix_[0][0] =  matrix_[0][0] * number;
   matrix_[0][1] =  matrix_[0][1] * number;
   matrix_[1][0] =  matrix_[1][0] * number;
   matrix_[1][1] =  matrix_[1][1] * number;

    return matrix_;
};

Matrix Matrix::MultiplyMatrix( Matrix& a) const {
    auto first = matrix_;
    auto second = a.TwoXTwoMatrix();
     
    std::array<std::array<double, 2>, 2> result;
    result[0][0] = first[0][0] * second[0][0] + first[0][1] * second[1][0];
    result[0][1] = first[0][0] * second[0][1] + first[0][1] * second[1][1];
    result[1][0] = first[1][0] * second[0][0] + first[1][1] * second[1][0];
    result[1][1] = first[1][0] * second[0][1] + first[1][1] * second[1][1];


    std::array<double, 2> newTopRow;
    newTopRow[0] = result[0][0];
    newTopRow[1] = result[0][1];

    std::array<double, 2> newBottomRow;
    newBottomRow[0] = result[1][0];
    newBottomRow[1] = result[1][1];

    a.TwoXTwoSetTopRow(newTopRow);
    a.TwoXTwoSetBottomRow(newBottomRow);
    
    a.CombinedTwoXTwo(newTopRow, newBottomRow);

    return a;
}


void Matrix::Print() const {
    std::cout << "This is your matrix: \n";
    for(int i = 0; i < matrix_.size(); i++){
        std::cout << "[ ";
        for(int j = 0; j < matrix_[i].size(); j++){
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << "]\n";

    }
}
