#include "matrix.h"

// File which contains error handling functions
#include "error/error.cpp" 

// Globally defining to be used throughout all functions

ValidMatrices validater;

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

// ----------------- ACCESSORS ------------------------------
std::size_t Matrix::GetRows() const { return rows_; }
std::size_t Matrix::GetColumns() const { return colums_; }

std::shared_ptr<std::vector<std::vector<long long> > > Matrix::GetMatrix() const {
  return matrix_;
}

std::vector<std::vector<long long> > Matrix::GetValues() {
  std::cout << "Please input your values accordingly!\n";
  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < colums_; ++j) {
      std::cout << "Enter element at (Row: " << i << ", Column: " << j << "): ";
      std::cin >> (*matrix_)[i][j];
    }  
  }
  return *matrix_;
};


// ----------------- SETTERS --------------

void Matrix::SetRows(const std::size_t rows) {
  rows_ = rows;
  matrix_->resize(rows_);
  for (std::vector<long long> &row : *matrix_) {
    row.resize(rows_);
  }
}

void Matrix::SetColumns(const std::size_t columns) {
  colums_ = columns;
  for (std::vector<long long> &columns : *matrix_) {
    columns.resize(colums_);
  }
}

void Matrix::SetSize(const std::size_t rows, const std::size_t columns) {
  SetRows(rows);
  SetColumns(columns);
}

// Sets new values to the matrix
void Matrix::SetNewValues(const std::vector<std::vector<long long> > new_values) {
  *matrix_ = new_values;
}

// ---------------- HELPER FUNCTIONS ----------------
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

// Multiplies a scalar to the given matrix
Matrix Matrix::ScalarMultiplication(long long scalar) const {
  Matrix result(*this);  // Create a copy of the matrix
  std::vector<std::vector<long long>>& matrix_holder = *result.GetMatrix();

  if (scalar == 0) {
    validater.ScalarError(); // Throws runtime error
  }

  for (auto& row : matrix_holder) {
    for (auto& element : row) {
      element *= scalar;
    }
  }

  result.SetNewValues(matrix_holder);
  return result;
}

// Does both addition and subtraction to matrices dependent on value of boolean
Matrix Matrix::Arithmetic(Matrix &b, bool negative) {
 
  std::size_t row_a = this->GetRows();
  std::size_t column_a = this->GetColumns();

  std::size_t row_b = b.GetRows();
  std::size_t column_b = b.GetColumns();

  if (row_a != row_b || column_a != column_b)
     validater.DimensionError();

  std::vector<std::vector<long long> > &matrix_A = *this->GetMatrix();
  std::vector<std::vector<long long> > &matrix_B = *b.GetMatrix();

  for (int i = 0; i < row_a; i++) {
    for (int j = 0; j < column_a; j++) {
      if (negative)
        matrix_B[i][j] -= matrix_A[i][j];
      else
        matrix_A[i][j] += matrix_B[i][j];
    }
  }

  this->SetNewValues(matrix_A);
  return *this;
}

// Multiplies two matrices together
Matrix Matrix::MultiplyMatrix(Matrix &b) {
  bool not_a_match = true;
  Matrix results;
  results.SetSize(this->GetRows(), b.GetColumns());

  std::vector<std::vector<long long> > &matrix_FIRST = *this->GetMatrix();
  std::vector<std::vector<long long> > &matrix_SECOND = *b.GetMatrix();
  std::vector<std::vector<long long> > &matrix_RESULT =
      *results.GetMatrix();

  std::size_t first_matrix_column = this->GetColumns();
  std::size_t first_matrix_row = this->GetRows();

  std::size_t second_matrix_column = b.GetColumns();
  std::size_t second_matrix_row = b.GetRows();

  if (first_matrix_column == second_matrix_row) {

    for (int i = 0; i < first_matrix_row; i++) {
      for (int j = 0; j < second_matrix_column; j++) {
        long long sum = 0.0;
        for (int k = 0; k < second_matrix_row; k++) {
          sum += matrix_FIRST[i][k] * matrix_SECOND[k][j];
        }
        matrix_RESULT[i][j] = sum;
      }
    }
  } else {
    validater.MultiplicationError();
  }

  results.SetNewValues(matrix_RESULT);
  *this = results;
  this->SetSize(this->GetRows(), b.GetColumns());

  return *this;
}

void Matrix::RowOperations(long long rows, long long columns,
                           std::vector<std::vector<long long> > &matrix, bool is_rref) {

  int lead = 0;
  
 while (lead < rows) {
  float leading, multiplier;

  for (int row = 0; row < rows; row++) {
    leading = matrix[lead][lead];
    multiplier = matrix[row][lead] / matrix[lead][lead];
    for (int column = 0; column < columns; column++) {
      if (row == lead && is_rref == false) {
        continue; // skip the division step for the leading row
      } else if (row == lead && is_rref == true) {
        matrix[row][column] -= matrix[lead][column] * multiplier;
      } else {
        matrix[row][column] -= matrix[lead][column] * multiplier;
      }
    }
  }
  lead++;
}

}


Matrix Matrix::REF(bool is_rref) {
  std::size_t rows = this->GetRows();
  std::size_t columns = this->GetColumns();
  std::vector<std::vector<long long> > &matrix = *this->GetMatrix();

  for (long long i = 0; i < rows; i++) {
    for (long long j = 0; j < columns; j++) {
      if (matrix[i][i] >= columns) {
        break;
      } else {
        if (matrix[i][i] == 0) {
          long long row_to_swap = i + 1; // 1
          while (row_to_swap < rows &&
                 matrix[row_to_swap][i] == 0) {
            row_to_swap++;
          }
          if (row_to_swap < rows) {
            // Swap the rows
            std::swap_ranges(matrix[i].begin(),
                             matrix[i].end(),
                             matrix[row_to_swap].begin());
            // Link to view -> https://en.cppreference.com/w/cpp/algorithm/swap_ranges
          }
        }
      }
    }
    this->RowOperations(rows, columns, matrix, is_rref);
    this->SetNewValues(matrix);
  }
  return *this;
}

int Matrix::Rank() {
  std::size_t rows = this->GetRows();
  std::size_t columns = this->GetColumns();

  std::vector<std::vector<long long> > &matrix = *this->GetMatrix();
  int number_of_ranks = 0;

  for (long long i = 0; i < rows; i++) {
    bool all_zeros = true;
    for (long long j = 0; j < columns; j++) {
      if (matrix[i][j] == 1) {
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

long long Matrix::Trace() {
  std::size_t rows = this->GetRows();
  std::size_t columns = this->GetColumns();

  std::vector<std::vector<long long> > &matrix = *this->GetMatrix();

  int increase_counter = 0;
  long long trace = 0;
  while(increase_counter < rows) {
    trace += matrix[increase_counter][increase_counter];
    increase_counter++;
  }

  return trace;
}

Matrix Matrix::Inverse() {
  std::vector<std::vector<long long> > &matrix = *this->GetMatrix();

  long long scalar = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

  if (scalar == 0)
    validater.InvertibleError();

  matrix[1][0] = (matrix[1][0] * -1) / scalar;
  matrix[0][1] = (matrix[0][1] * -1) / scalar;
  matrix[0][0] = matrix[0][0] / scalar;
  matrix[1][1] = matrix[1][1] / scalar;
  std::swap(matrix[0][0], matrix[1][1]);

  this->SetNewValues(matrix);

  return *this;
}

Matrix Matrix::Transpose() {
  std::size_t rows = this->GetRows();
  std::size_t columns = this->GetColumns();
  std::vector<std::vector<long long> > &matrix = *this->GetMatrix();

  std::vector<std::vector<long long> > transposed(columns,
                                                 std::vector<long long>(rows));

  for (long long i = 0; i < rows; i++) {
    for (long long j = 0; j < columns; j++) {
      transposed[j][i] = matrix[i][j];
    }
  }

  this->SetNewValues(transposed);
  return *this;
}

Matrix Matrix::Exponentiation(double exponent) {
  std::size_t rows = this->GetRows();
  std::size_t columns = this->GetColumns();
  std::vector<std::vector<long long> > &matrix = *this->GetMatrix();


  while(exponent > 0) {
    this->MultiplyMatrix(*this);
    exponent-=1;
  }

  return *this;
}

double Matrix::DotProduct(Matrix& b) {
  std::size_t row_a = this->GetRows();
  std::size_t column_a = this->GetColumns();

  std::size_t row_b = b.GetRows();
  std::size_t column_b = b.GetColumns();

  if(row_a != row_b || (column_a != 1 || column_b != 1) || column_a != column_b) {
    validater.DotProductError();
  }

  auto &DEREFERENCED_A = *this->GetMatrix();
  auto &DEREFERENCED_B = *b.GetMatrix();

 double scalar = 0;

 for(long long row = 0; row < row_a; row++) {
     scalar += DEREFERENCED_A[row][0] * DEREFERENCED_B[row][0];
  
 }

  return scalar;
}

bool Matrix::Orthogonal(Matrix& b, Matrix& c) {
  std::size_t row_a = this->GetRows();
  std::size_t column_a = this->GetColumns();

  std::size_t row_b = b.GetRows();
  std::size_t column_b = b.GetColumns();

  std::size_t row_c = c.GetRows();
  std::size_t column_c = c.GetColumns();

  auto &DEREFERENCED_A = *this->GetMatrix();
  auto &DEREFERENCED_B = *b.GetMatrix();
  auto &DEREFERENCED_C = *c.GetMatrix();

  if(row_a != row_b || (column_a != 1 || column_b != 1 || column_c != 1) || column_a != column_b || row_a) {
    validater.OrthogonalError();
}

  double m_one, m_two, m_three = 0;

  for(long long row = 0; row < row_a; row++) {
    m_one += DEREFERENCED_A[row][0] * DEREFERENCED_B[row][0];
    m_two += DEREFERENCED_A[row][0] * DEREFERENCED_C[row][0];
    m_three += DEREFERENCED_B[row][0] * DEREFERENCED_C[row][0];
  }

  if(m_one == m_two && m_two == m_three) {
    return true;
  }

  return false;
}