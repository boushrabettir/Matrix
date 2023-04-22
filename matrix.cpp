#include <iostream>

#include "matrix.h"
#include <algorithm>
#include <utility>
#include <iterator>
#include <array>
#include <iomanip>

Matrix::Matrix() : rows_(0), colums_(0), matrix_(std::make_shared<std::vector<std::vector<double> > >(0, std::vector<double>(0))){}
Matrix::Matrix(size_t rows, size_t columns) : rows_(rows), colums_(columns), matrix_(std::make_shared<std::vector<std::vector<double> > >(rows, std::vector<double>(columns))) {}


std::shared_ptr<std::vector<std::vector<double> > > Matrix::GetMatrix() const { return matrix_; }
void Matrix::Print() const {

    for (const std::vector<double>& row : *matrix_) {
        std::cout << "[ ";
        for (const double& elem : row) {
            if(std::abs(elem - (int)elem) >= 0.01) std::cout << std::setprecision(2) << elem << " ";
            else std::cout << std::setprecision(0) << elem << " ";
        }
        std::cout << "]\n";
    }
}


Matrix Matrix::ScalarMultiplication(Matrix& matrix, double scalar) const {
    double rows = matrix.GetRows();
    double columns = matrix.GetColumns();
    std::vector<std::vector<double> >& DEF = *matrix.GetMatrix();

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            DEF[i][j] *= scalar;
        }
    }


    matrix.SetNewValues(DEF);
    return matrix;
}

Matrix Matrix::Arithmetic(Matrix& a, Matrix& b, bool negative) {
    double row_a = a.GetRows();
    double column_a = a.GetColumns();

    double row_b = b.GetRows();
    double column_b = b.GetColumns();

    if (row_a != row_b || column_a != column_b) throw std::invalid_argument("Matrices have different dimensions");
    
    std::vector<std::vector<double> >& DEREFERNCED_A = *a.GetMatrix();
    std::vector<std::vector<double> >& DEREFERNCED_B = *b.GetMatrix();

    /* weird bug */

       for (int i = 0; i < row_a; i++) {
        for (int j = 0; j < column_a; j++) {
            if(negative) DEREFERNCED_A[i][j] -= DEREFERNCED_A[i][j];
            else DEREFERNCED_A[i][j] += DEREFERNCED_B[i][j];
        }
    }
    
    a.SetNewValues(DEREFERNCED_A);    
    return a;
}

Matrix Matrix::MultiplyMatrix(Matrix& a, Matrix& b, bool not_a_match) {
    std::vector<std::vector<double> >& DEREFERNCED_FIRST = *a.GetMatrix();
    std::vector<std::vector<double> >& DEREFERNCED_SECOND = *b.GetMatrix();
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

    a.SetNewValues(DEREFERNCED_FIRST); 
    return a;
}


void Matrix::RowOperations(size_t rows, size_t columns, std::vector<std::vector<double> >& DEF) {

    int lead = 0;
    // if cpp reference guide, stackoverflow didnt exist i would not have finish this holy cow
    while(lead < rows) {
        float leading, multiplier;

        for(int row = 0; row < rows; row++) {
           leading = DEF[lead][lead]; // 0 0 element
            multiplier = DEF[row][lead] / DEF[lead][lead]; // row increase , lead = 0 , multiplier
            for(int column = 0; column < columns; column++) {
                if(row == lead) // row = 0 -> lead = 0 
                    DEF[row][column] /= leading;
                 else 
                    DEF[row][column] -= DEF[lead][column] * multiplier;
                    // 0  0 --> 1 0 * m  
            }   
        }
        lead++;
    }
}

/* Change this */
                // i did this wrong we want to loop the entire row nto the eelement itself
                // pivot can remove elements below > 0 
                // if 0 in pivot find a non zero swap it then do the removeing 
// why did i get RREF bruh!!

Matrix Matrix::REF(Matrix& a) {
  size_t rows = a.GetRows();
  size_t columns = a.GetColumns();
  auto& DEF = *a.GetMatrix();

  int increase_counter = 0;
 

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      if (DEF[increase_counter][increase_counter] >= columns) {
        break;
      } else {
        if (DEF[increase_counter][increase_counter] == 0) {
          size_t row_to_swap = increase_counter + 1; //1
          while (row_to_swap < rows && DEF[row_to_swap][increase_counter] == 0) {
            row_to_swap++; 
            // 2 need to check to see if it goes outta bounds and if its STILL 0 we continue 
          }
          if (row_to_swap < rows) {
            // Swap the rows
            std::swap_ranges(DEF[increase_counter].begin(), DEF[increase_counter].end(), DEF[row_to_swap].begin());
            // link -> https://en.cppreference.com/w/cpp/algorithm/swap_ranges
          }
        }
      }
    }
    a.RowOperations(rows, columns, DEF);
    a.SetNewValues(DEF);
  }
  return a;
}

Matrix Matrix::Inverse(Matrix& a) {
    auto& DEF = *a.GetMatrix();
    
    double scalar = DEF[0][0] * DEF[1][1] - DEF[1][0] * DEF[0][1];

    if(scalar == 0)  throw std::runtime_error("2x2 Matrix is not invertible!");

    DEF[1][0] = (DEF[1][0] * -1) / scalar;
    DEF[0][1] = (DEF[0][1] * -1) / scalar;
    DEF[0][0] = DEF[0][0] / scalar;
    DEF[1][1] = DEF[1][1] / scalar;
    std::swap(DEF[0][0], DEF[1][1]);
    
    a.SetNewValues(DEF);

    return a;
}

Matrix Matrix::Transpose(Matrix& a) {
    size_t rows = a.GetRows();
    size_t columns = a.GetColumns();
    auto& DEREFERNCED = *a.GetMatrix();
 
    std::vector<std::vector<double> > transposed(columns, std::vector<double>(rows));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            transposed[j][i] = DEREFERNCED[i][j];
        }
    }

    a.SetNewValues(transposed);
    return a;
}