#include <iostream>

#include "matrix.h"
#include <algorithm>
#include <array>

Matrix::Matrix() : rows_(0), colums_(0), matrix_(std::make_shared<std::vector<std::vector<double> > >(0, std::vector<double>(0))) {}

Matrix::Matrix(size_t rows, size_t columns) : rows_(rows), colums_(columns), matrix_(std::make_shared<std::vector<std::vector<double> > >(rows, std::vector<double>(columns))) {}


double Matrix::GetRows() const { return rows_; }

double Matrix::GetColumns() const { return colums_; }

std::shared_ptr<std::vector<std::vector<double> > > Matrix::GetMatrix() const { return matrix_; }

void Matrix::SetRows(const size_t rows) {
    rows_ = rows;
    matrix_->resize(rows_);
    for (std::vector<double>& row : *matrix_) {
        row.resize(colums_);
    }
}

void Matrix::SetColumns(const size_t columns) {
    colums_ = columns;
    for (std::vector<double>& row : *matrix_) {
        row.resize(colums_);
    }
}

void Matrix::SetNewValues(const std::vector<std::vector<double> > new_values) {
    *matrix_ = new_values;
};

void Matrix::Print() const {
    for (const std::vector<double>& row : *matrix_) {
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
            std::cin >> (*matrix_)[i][j];
        }
    }

    return *matrix_;
}

Matrix Matrix::ScalarMultiplication(Matrix& matrix, double scalar) const {
    double rows = matrix.GetRows();
    double columns = matrix.GetColumns();
    std::shared_ptr<std::vector<std::vector<double> > > m = matrix.GetMatrix();
    auto DEREFERNCED = *m;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            DEREFERNCED[i][j] *= scalar;
        }
    }

    Matrix a;
    a.SetNewValues(DEREFERNCED);
    matrix = a;
    return matrix;
}

Matrix Matrix::AddMatrix(Matrix& a, Matrix& b, bool not_a_match) {
    double row_a = a.GetRows();
    double column_a = a.GetColumns();

    double row_b = b.GetRows();
    double column_b = b.GetColumns();

    if (row_a != row_b || column_a != column_b) throw std::invalid_argument("Matrices have different dimensions");
    

    std::shared_ptr<std::vector<std::vector<double> > > matrix_a = a.GetMatrix();
    std::shared_ptr<std::vector<std::vector<double> > > matrix_b = b.GetMatrix();
    auto DEREFERNCED_A = *matrix_a;
    auto DEREFERNCED_B = *matrix_b;


       for (int i = 0; i < row_a; i++) {
        for (int j = 0; j < column_a; j++) {
            DEREFERNCED_A[i][j] += DEREFERNCED_B[i][j];
        }
    }
    
    Matrix final_matrix;
    final_matrix.SetNewValues(DEREFERNCED_A);
    a = final_matrix;
    
    return a;
}

Matrix Matrix::MultiplyMatrix(Matrix& a, Matrix& b, bool not_a_match) {
    std::shared_ptr<std::vector<std::vector<double> > > first = a.GetMatrix();
    std::shared_ptr<std::vector<std::vector<double> > > second = b.GetMatrix();
    auto DEREFERNCED_FIRST = *first;
    auto DEREFERNCED_SECOND = *second;
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
    final_matrix.SetNewValues(DEREFERNCED_FIRST);
    a = final_matrix;
    
    return a;
}

Matrix Matrix::Transpose(Matrix& a) {
    /*
         00   10
        [ 2 , 1 ]


        [ 2 ] 00
        [ 1 ] 01

        for every row it becomes a column
        for every column it becomes a row
    */
   
    double row_a = a.GetColumns();
    double column_a = a.GetRows();

    std::shared_ptr<std::vector<std::vector<double> > > first = a.GetMatrix();
    auto DEREFERNCED_FIRST = *first;   
    


   std::vector<std::vector<double> > trying(column_a, std::vector<double> (row_a));


   for (int i = 0; i < row_a; i++) {
        /* row becomes a column */
        for (int j = 0; j < column_a; j++) {
            /* columb becomes row */
            trying[j][i] = DEREFERNCED_FIRST[i][j];
             
        }
    }

    Matrix result_try;
    result_try.SetNewValues(trying);
    a = result_try;
    return a;
}