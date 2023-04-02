#include <iostream>

#include "matrix.cpp"

#include <array>

int main() {

    Matrix matrix_a;
    std::array<double, 2> matrix_a_top_row = {1, 1};
    matrix_a.TwoXTwoSetTopRow(matrix_a_top_row);
    std::array<double, 2> matrix_a_bottom_row = {1, 1};
    matrix_a.TwoXTwoSetBottomRow(matrix_a_bottom_row);

    matrix_a.CombinedTwoXTwo(matrix_a_top_row, matrix_a_bottom_row);
    std::cout << "\n=== FIRST TRY ===\n";
    matrix_a.Print();

    matrix_a.Multiplication2X2Scalar(2);
    std::cout << "\n=== SECOND TRY ===\n";
    matrix_a.Print();

    Matrix matrix_b;
    
    std::array<double, 2> matrix_b_top_row = {1, 1};
    matrix_b.TwoXTwoSetTopRow(matrix_b_top_row);
    std::array<double, 2> matrix_b_bottom_row = {1, 1};
    matrix_b.TwoXTwoSetBottomRow(matrix_b_bottom_row);

    matrix_b.CombinedTwoXTwo(matrix_b_top_row, matrix_b_bottom_row);
            
    /* multiple matrix a and b */
    matrix_a = matrix_a.MultiplyMatrix(matrix_b);
    std::cout << "\n=== THIRD TRY ===\n";
    matrix_a.Print();
}