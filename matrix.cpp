#include <iostream>

#include "matrix.h"
#include <algorithm>
#include <array>
#include <iomanip>
#include <iterator>
#include <cmath>
#include <utility>

Matrix::Matrix()
    : rows_(0), colums_(0),
      matrix_(std::make_shared<std::vector<std::vector<long long> > >(
          0, std::vector<long long>(0))) {}

Matrix::Matrix(long long rows, long long columns)
    : rows_(rows), colums_(columns),
      matrix_(std::make_shared<std::vector<std::vector<long long> > >(
          rows, std::vector<long long>(columns))) {}

Matrix::Matrix(std::vector<std::vector<long long> > set_values) 
     : matrix_(std::make_shared<std::vector<std::vector<long long> > >(set_values)) {}

// ooo inheritience in the HOUSE
long long Matrix::GetRows() const { return rows_; }
long long Matrix::GetColumns() const { return colums_; }

std::shared_ptr<std::vector<std::vector<long long> > > Matrix::GetMatrix() const {
  return matrix_;
}

std::vector<std::vector<long long> > Matrix::GetValues() {
  std::cout << "Please input your values accordingly!\n";
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < colums_; ++j) {
      std::cout << "Enter element at (Row: " << i << ", Column: " << j << "): ";
      // if (!(std::cin >> (*matrix_)[i][j])) {
      //   std::cin.clear(); // clear error flags
      //   std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
      //                   '\n'); // discard invalid input
      //   throw std::runtime_error("Your input is not valid. Please try again.");
      // }
      std::cin >> (*matrix_)[i][j];
    }
  }
  return *matrix_;
};

void Matrix::SetRows(const long long rows) {
  rows_ = rows;
  matrix_->resize(rows_);
  for (std::vector<long long> &row : *matrix_) {
    row.resize(rows_);
  }
}

void Matrix::SetColumns(const long long columns) {
  colums_ = columns;
  for (std::vector<long long> &columns : *matrix_) {
    columns.resize(colums_);
  }
}

void Matrix::SetSize(const long long rows, const long long columns) {
  // Video link about string buffers -> https://youtu.be/yMwA4u7eXEY

  SetRows(rows);
  SetColumns(columns);
}

void Matrix::SetNewValues(
    const std::vector<std::vector<long long> > new_values) {
  *matrix_ = new_values;
}

void Matrix::Print() const {

  for (const std::vector<long long> &row : *matrix_) {
    std::cout << "[ ";
    for (const long long &elem : row) {
      if (std::abs(elem - (int)elem) >= 0.01)
        std::cout << std::setprecision(2) << elem << " ";
      else
        std::cout << std::setprecision(0) << elem << " ";
    }
    std::cout << "]\n";
  }
}

Matrix Matrix::ScalarMultiplication(Matrix &matrix, long long scalar) const {
  long long rows = matrix.GetRows();
  long long columns = matrix.GetColumns();
  std::vector<std::vector<long long> > &DEF = *matrix.GetMatrix();

  if (!std::isdigit(scalar)) {
    throw std::runtime_error("Scalar is a not a digit. Please try again.");
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      DEF[i][j] *= scalar;
    }
  }

  matrix.SetNewValues(DEF);
  return matrix;
}

Matrix Matrix::Arithmetic(Matrix &a, Matrix &b, bool negative) {
  long long row_a = a.GetRows();
  long long column_a = a.GetColumns();

  long long row_b = b.GetRows();
  long long column_b = b.GetColumns();

  if (row_a != row_b || column_a != column_b)
    throw std::invalid_argument("Matrices have different dimensions");

  std::vector<std::vector<long long> > &DEREFERNCED_A = *a.GetMatrix();
  std::vector<std::vector<long long> > &DEREFERNCED_B = *b.GetMatrix();

  /* weird bug */

  for (int i = 0; i < row_a; i++) {
    for (int j = 0; j < column_a; j++) {
      if (negative)
        DEREFERNCED_A[i][j] -= DEREFERNCED_A[i][j];
      else
        DEREFERNCED_A[i][j] += DEREFERNCED_B[i][j];
    }
  }

  a.SetNewValues(DEREFERNCED_A);
  return a;
}

Matrix Matrix::MultiplyMatrix(Matrix &a, Matrix &b) {
  bool not_a_match = true;
  Matrix results;
  results.SetSize(a.GetRows(), b.GetColumns());

  std::vector<std::vector<long long> > &DEREFERNCED_FIRST = *a.GetMatrix();
  std::vector<std::vector<long long> > &DEREFERNCED_SECOND = *b.GetMatrix();
  std::vector<std::vector<long long> > &DEREFERNCED_RESULT =
      *results.GetMatrix();

  long long first_matrix_column = a.GetColumns();
  long long first_matrix_row = a.GetRows();

  long long second_matrix_column = b.GetColumns();
  long long second_matrix_row = b.GetRows();

  if (first_matrix_column != second_matrix_row ||
      second_matrix_column != first_matrix_row) {
    throw std::runtime_error("These matrices cannot be multiplied. Please "
                             "check your dimensions before proceeding again.");
  }
  if (first_matrix_column == second_matrix_row ||
      second_matrix_column == first_matrix_row) {

    /* Multiply them together */

    for (int i = 0; i < first_matrix_row; i++) {
      for (int j = 0; j < second_matrix_column; j++) {
        long long sum = 0.0;
        for (int k = 0; k < second_matrix_row; k++) {
          sum += DEREFERNCED_FIRST[i][k] * DEREFERNCED_SECOND[k][j];
        }
        DEREFERNCED_RESULT[i][j] = sum;
      }
    }
  }

  results.SetNewValues(DEREFERNCED_RESULT);
  a = results;
  a.SetSize(a.GetRows(), b.GetColumns());

  return a;
}

void Matrix::RowOperations(long long rows, long long columns,
                           std::vector<std::vector<long long> > &DEF, bool is_rref) {

  int lead = 0;
  is_rref = false;
  // if cpp reference guide, stackoverflow didnt exist i would not have finish
  // this holy cow
 while (lead < rows) {
  float leading, multiplier;

  for (int row = 0; row < rows; row++) {
    leading = DEF[lead][lead];
    multiplier = DEF[row][lead] / DEF[lead][lead];
    for (int column = 0; column < columns; column++) {
      if (row == lead && is_rref == false) {
        continue; // skip the division step for the leading row
      } else if (row == lead && is_rref == true) {
        DEF[row][column] -= DEF[lead][column] * multiplier;
      } else {
        DEF[row][column] -= DEF[lead][column] * multiplier;
      }
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

Matrix Matrix::REF(Matrix &a, bool is_rref) {
  long long rows = a.GetRows();
  long long columns = a.GetColumns();
  auto &DEF = *a.GetMatrix();

  int increase_counter = 0;

  for (long long i = 0; i < rows; i++) {
    for (long long j = 0; j < columns; j++) {
      if (DEF[increase_counter][increase_counter] >= columns) {
        break;
      } else {
        if (DEF[increase_counter][increase_counter] == 0) {
          long long row_to_swap = increase_counter + 1; // 1
          while (row_to_swap < rows &&
                 DEF[row_to_swap][increase_counter] == 0) {
            row_to_swap++;
            // 2 need to check to see if it goes outta bounds and if its STILL 0
            // we continue
          }
          if (row_to_swap < rows) {
            // Swap the rows
            std::swap_ranges(DEF[increase_counter].begin(),
                             DEF[increase_counter].end(),
                             DEF[row_to_swap].begin());
            // link -> https://en.cppreference.com/w/cpp/algorithm/swap_ranges
          }
        }
      }
    }
    a.RowOperations(rows, columns, DEF, is_rref);
    a.SetNewValues(DEF);
  }
  return a;
}

int Matrix::Rank(Matrix &a) {
  long long rows = a.GetRows();
  long long columns = a.GetColumns();

  auto &DEF = *a.GetMatrix();
  int number_of_ranks = 0;

  for (long long i = 0; i < rows; i++) {
    bool all_zeros = true;
    for (long long j = 0; j < columns; j++) {
      if (DEF[i][j] == 1) {
        all_zeros = false;
        break;
      }
    }
    if (!all_zeros) {
      number_of_ranks += 1;
    }
  }

  return number_of_ranks;
}

long long Matrix::Trace(Matrix& a) {
  long long rows = a.GetRows();
  long long columns = a.GetColumns();
  auto &DEF = *a.GetMatrix();
  int increase_counter = 0;
  long long trace = 0;
  while(increase_counter < rows) {
    trace += DEF[increase_counter][increase_counter];
    increase_counter++;
  }

  return trace;
}

Matrix Matrix::Inverse(Matrix &a) {
  auto &DEF = *a.GetMatrix();

  long long scalar = DEF[0][0] * DEF[1][1] - DEF[1][0] * DEF[0][1];

  if (scalar == 0)
    throw std::runtime_error("2x2 Matrix is not invertible!");

  DEF[1][0] = (DEF[1][0] * -1) / scalar;
  DEF[0][1] = (DEF[0][1] * -1) / scalar;
  DEF[0][0] = DEF[0][0] / scalar;
  DEF[1][1] = DEF[1][1] / scalar;
  std::swap(DEF[0][0], DEF[1][1]);

  a.SetNewValues(DEF);

  return a;
}

Matrix Matrix::Transpose(Matrix &a) {
  long long rows = a.GetRows();
  long long columns = a.GetColumns();
  auto &DEREFERNCED = *a.GetMatrix();

  std::vector<std::vector<long long> > transposed(columns,
                                                 std::vector<long long>(rows));

  for (long long i = 0; i < rows; i++) {
    for (long long j = 0; j < columns; j++) {
      transposed[j][i] = DEREFERNCED[i][j];
    }
  }

  a.SetNewValues(transposed);
  return a;
}

Matrix Matrix::Exponentiation(Matrix& a, double exponent) {
  long long rows = a.GetRows();
  long long columns = a.GetColumns();
  auto &DEREFERNCED = *a.GetMatrix();

  
  int counter = 0;
  while(exponent > counter) {
    a.MultiplyMatrix(a, a);
    exponent-=1;
  }

  return a;
}

double Matrix::DotProduct(Matrix& a, Matrix& b) {
  long long row_a = a.GetRows();
  long long column_a = a.GetColumns();

  long long row_b = b.GetRows();
  long long column_b = b.GetColumns();

  if(row_a != row_b || (column_a != 1 || column_b != 1) || column_a != column_b) {
    throw std::runtime_error("Please check to see if your matrices are valid");
  }

  auto &DEREFERENCED_A = *a.GetMatrix();
  auto &DEREFERENCED_B = *b.GetMatrix();

 double scalar = 0;

 for(long long row = 0; row < row_a; row++) {
     scalar += DEREFERENCED_A[row][0] * DEREFERENCED_B[row][0];
  
 }

  return scalar;
}

std::string Matrix::Orthogonal(Matrix& a, Matrix& b, Matrix& c) {
  long long row_a = a.GetRows();
  long long column_a = a.GetColumns();

  long long row_b = b.GetRows();
  long long column_b = b.GetColumns();

  long long row_c = c.GetRows();
  long long column_c = c.GetColumns();

  auto &DEREFERENCED_A = *a.GetMatrix();
  auto &DEREFERENCED_B = *b.GetMatrix();
  auto &DEREFERENCED_C = *c.GetMatrix();

  if(row_a != row_b || (column_a != 1 || column_b != 1 || column_c != 1) || column_a != column_b || row_a) {
    throw std::runtime_error("Please check to see if your matrices are valid");
}

  double m_one, m_two, m_three = 0;
  for(long long row = 0; row < row_a; row++) {
    m_one += DEREFERENCED_A[row][0] * DEREFERENCED_B[row][0];
    m_two += DEREFERENCED_A[row][0] * DEREFERENCED_C[row][0];
    m_three += DEREFERENCED_B[row][0] * DEREFERENCED_C[row][0];
  }

  if(m_one == m_two == m_three) {
    return "These matrices are orthogonal to one another";
  }

  return "These matrices are not orthogonal to one another";
}