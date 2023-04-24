#include <iostream>

#include "matrix.h"
#include <algorithm>
#include <utility>
#include <iterator>
#include <array>
#include <iomanip>

Matrix::Matrix() : rows_(0), colums_(0), matrix_(std::make_shared<std::vector<std::vector<long long> > >(0, std::vector<long long>(0))){}
Matrix::Matrix(long long rows, long long columns) : rows_(rows), colums_(columns), matrix_(std::make_shared<std::vector<std::vector<long long> > >(rows, std::vector<long long>(columns))) {}

// ooo inheritience in the HOUSE
    long long Matrix::GetRows() const { return rows_; }
    long long Matrix::GetColumns() const { return colums_; }

    std::vector<std::vector<long long> > Matrix::GetValues() {
      std::cout << "Please input your values accordingly!\n";
       for (int i = 0; i < rows_; ++i) {
         for (int j = 0; j < colums_; ++j) {
           std::cout << "Enter element at (Row: " << i << ", Column: " << j << "): ";
            std::cin >> (*matrix_)[i][j];
        }
    }
     return *matrix_;
    };

    void Matrix::SetRows(const long long rows) {
      rows_ = rows;
      matrix_->resize(rows_);
      for (std::vector<long long>& row : *matrix_) {
        row.resize(rows_);
      }
    }

    void Matrix::SetColumns(const long long columns) {
      colums_ = columns;
      for (std::vector<long long>& columns : *matrix_) {
        columns.resize(colums_);
      }
    }

    void Matrix::SetSize(const long long rows, const long long columns) {
      SetRows(rows);
      SetColumns(columns);
    }
    // implement ^

    void Matrix::SetNewValues(const std::vector<std::vector<long long> > new_values) { *matrix_ = new_values; }

std::shared_ptr<std::vector<std::vector<long long> > > Matrix::GetMatrix() const { return matrix_; }
void Matrix::Print() const {

    for (const std::vector<long long>& row : *matrix_) {
        std::cout << "[ ";
        for (const long long& elem : row) {
            if(std::abs(elem - (int)elem) >= 0.01) std::cout << std::setprecision(2) << elem << " ";
            else std::cout << std::setprecision(0) << elem << " ";
        }
        std::cout << "]\n";
    }
}


Matrix Matrix::ScalarMultiplication(Matrix& matrix, long long scalar) const {
    long long rows = matrix.GetRows();
    long long columns = matrix.GetColumns();
    std::vector<std::vector<long long> >& DEF = *matrix.GetMatrix();

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            DEF[i][j] *= scalar;
        }
    }


    matrix.SetNewValues(DEF);
    return matrix;
}

Matrix Matrix::Arithmetic(Matrix& a, Matrix& b, bool negative) {
    long long row_a = a.GetRows();
    long long column_a = a.GetColumns();

    long long row_b = b.GetRows();
    long long column_b = b.GetColumns();

    if (row_a != row_b || column_a != column_b) throw std::invalid_argument("Matrices have different dimensions");
    
    std::vector<std::vector<long long> >& DEREFERNCED_A = *a.GetMatrix();
    std::vector<std::vector<long long> >& DEREFERNCED_B = *b.GetMatrix();

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

Matrix Matrix::MultiplyMatrix(Matrix& a, Matrix& b) {
    bool not_a_match = true;
    Matrix results;
    results.SetSize(a.GetRows(), b.GetColumns());
 
    std::vector<std::vector<long long> >& DEREFERNCED_FIRST = *a.GetMatrix();
    std::vector<std::vector<long long> >& DEREFERNCED_SECOND = *b.GetMatrix();
    std::vector<std::vector<long long> >& DEREFERNCED_RESULT = *results.GetMatrix();
    // 2 x 3 - A ROW/COLUMN
    // 4 x 2 - B ROW/COLUMN
    /*
    for(i=0;i<r;i++)    
        {    
            for(j=0;j<c;j++) {    
             mul[i][j]=0;    
        for(k=0;k<c;k++)    {    
         mul[i][j]+=a[i][k]*b[k][j];    
        }    
    }    
}    
    */

    long long first_matrix_column = a.GetColumns();
    long long first_matrix_row = a.GetRows();

    long long second_matrix_column = b.GetColumns();
    long long second_matrix_row = b.GetRows();

    if(first_matrix_column == second_matrix_row || second_matrix_column == first_matrix_row) {
         
        /* Multiply them together */

       for(int i = 0; i < first_matrix_row; i++) {
    for(int j = 0; j < second_matrix_column; j++) {
        long long sum = 0.0;
        for(int k = 0; k < second_matrix_row; k++) {
            sum += DEREFERNCED_FIRST[i][k] * DEREFERNCED_SECOND[k][j];
        }
        DEREFERNCED_RESULT[i][j] = sum;
    }
}

    } else {
        std::cout << "\n\t\t\t====== THE MATRICES CANNOT BE MULTIPLIED DUE TO THE FOLLOWING. ======\t\t\t\n";
        std::string response = first_matrix_column != second_matrix_row ?  "First Matrix Column do not equal to the Second Matrix Row" : second_matrix_column != first_matrix_row ? "Second Matrix Column do not equal to the First Matrix Row" : "NULL";
        std::cout << "\n\t\t\t" << response << "\t\t\t\n";
     
    }

results.SetNewValues(DEREFERNCED_RESULT);
 a = results;
 a.SetSize(a.GetRows(), b.GetColumns());

return a;

} 



void Matrix::RowOperations(long long rows, long long columns, std::vector<std::vector<long long> >& DEF) {

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
  long long rows = a.GetRows();
  long long columns = a.GetColumns();
  auto& DEF = *a.GetMatrix();

  int increase_counter = 0;
 

  for (long long i = 0; i < rows; i++) {
    for (long long j = 0; j < columns; j++) {
      if (DEF[increase_counter][increase_counter] >= columns) {
        break;
      } else {
        if (DEF[increase_counter][increase_counter] == 0) {
          long long row_to_swap = increase_counter + 1; //1
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

    long long scalar = DEF[0][0] * DEF[1][1] - DEF[1][0] * DEF[0][1];

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
    long long rows = a.GetRows();
    long long columns = a.GetColumns();
    auto& DEREFERNCED = *a.GetMatrix();
 
    std::vector<std::vector<long long> > transposed(columns, std::vector<long long>(rows));

    for (long long i = 0; i < rows; i++) {
        for (long long j = 0; j < columns; j++) {
            transposed[j][i] = DEREFERNCED[i][j];
        }
    }

    a.SetNewValues(transposed);
    return a;
}
