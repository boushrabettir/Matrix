#include <iostream>

#include "matrix.h"
#include <array>

Matrix::Matrix() : rows_(0), colums_(0) {}

Matrix::Matrix(double rows, double columns) : rows_(rows), colums_(columns) {
    matrix_ = std::vector<std::vector<double> >(rows_, std::vector<double>(colums_, 0));
}

double Matrix::GetRows() const { return rows_; }

double Matrix::GetColumns() const { return colums_; }

std::vector<std::vector<double> > Matrix::GetMatrix() const { return matrix_; }

void Matrix::SetRows(const double rows) {
    rows_ = rows;
    matrix_.resize(rows_);
    for (std::vector<double>& row : matrix_) {
        row.resize(colums_);
    }
}

void Matrix::SetColumns(const double columns) {
    colums_ = columns;
    for (std::vector<double>& row : matrix_) {
        row.resize(colums_);
    }
}

void Matrix::SetNewValues(const std::vector<std::vector<double> > new_values) {
    matrix_ = new_values;
};

void Matrix::Print() const {
    for (const std::vector<double>& row : matrix_) {
        std::cout << "[ ";
        for (const double& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << "]\n";
    }
}

std::vector<std::vector<double> > Matrix::GetValues() {
    std::cout << "Please input your values accordingly!\n";
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < colums_; ++j) {
            std::cout << "Enter element at (Row: " << i << ", Column: " << j << "): ";
            std::cin >> matrix_[i][j];
        }
    }

    return matrix_;
}

Matrix Matrix::ScalarMultiplication(Matrix& matrix, double scalar) const {
    double rows = matrix.GetRows();
    double columns = matrix.GetColumns();
    std::vector<std::vector<double> > m = matrix.GetMatrix();


    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            m[i][j] *= scalar;
        }
    }

    Matrix a;
    a.SetNewValues(m);
    matrix = a;
    return matrix;
}

Matrix Matrix::AddMatrix(Matrix& a, Matrix& b, bool not_a_match) {
    double row_a = a.GetRows();
    double column_a = a.GetColumns();

    double row_b = b.GetRows();
    double column_b = b.GetColumns();

    if (row_a != row_b || column_a != column_b) {
        throw std::invalid_argument("Matrices have different dimensions");
    } 

    std::vector<std::vector<double> > matrix_a = a.GetMatrix();
    std::vector<std::vector<double> > matrix_b = b.GetMatrix();

       for (int i = 0; i < row_a; i++) {
        for (int j = 0; j < column_a; j++) {
            matrix_a[i][j] += matrix_b[i][j];
        }
    }
    
    Matrix final_matrix;
    final_matrix.SetNewValues(matrix_a);
    a = final_matrix;
    
    return a;
}

Matrix Matrix::MultiplyMatrix(Matrix& a, Matrix& b, bool not_a_match) {
    auto first = a.GetMatrix();
    auto second = b.GetMatrix();
    not_a_match = true;

    // 2 x 3 - A ROW/COLUMN
   // 4 x 2 - B ROW/COLUMN

    double first_matrix_column = a.GetColumns();
    double first_matrix_row = a.GetRows();

    double second_matrix_column = b.GetColumns();
    double second_matrix_row = b.GetRows();

    if(first_matrix_column == second_matrix_row || second_matrix_column == first_matrix_row) {
        not_a_match  = false;
        /* Multiply them together */
        
        
    } else {
        std::cout << "\n\t\t\t====== THE MATRICES CANNOT BE MULTIPLIED DUE TO THE FOLLOWING. ======\t\t\t\n";
        std::string response = first_matrix_column != second_matrix_row ?  "First Matrix Column do not equal to the Second Matrix Row" : second_matrix_column != first_matrix_row ? "Second Matrix Column do not equal to the First Matrix Row" : "NULL";
        std::cout << "\n\t\t\t" << response << "\t\t\t\n";
        not_a_match = true;
    }

    Matrix final_matrix;
    final_matrix.SetNewValues(first);
    a = final_matrix;
    
    return a;
}