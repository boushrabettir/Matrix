#include <iostream>

#include "matrix.h"
#include <algorithm>
#include <utility>
#include <array>
#include <iomanip>

Matrix::Matrix() : rows_(0), colums_(0), matrix_(std::make_shared<std::vector<std::vector<double> > >(0, std::vector<double>(0))){}
Matrix::Matrix(size_t rows, size_t columns) : rows_(rows), colums_(columns), matrix_(std::make_shared<std::vector<std::vector<double> > >(rows, std::vector<double>(columns))) {}


double Matrix::GetRows() const { return rows_; }

double Matrix::GetColumns() const { return colums_; }

std::shared_ptr<std::vector<std::vector<double> > > Matrix::GetMatrix() const { return matrix_; }

void Matrix::SetRows(const size_t rows) {
    rows_ = rows;
    matrix_->resize(rows_);
    for (std::vector<double>& row : *matrix_) {
        row.resize(rows_);
    }
}

void Matrix::SetColumns(const size_t columns) {
    colums_ = columns;
    for (std::vector<double>& columns : *matrix_) {
        columns.resize(colums_);
    }
}

void Matrix::SetNewValues(const std::vector<std::vector<double> > new_values) {
    *matrix_ = new_values;
};

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
     std::cout << "Pointers pointing to matrix_: " <<  m.use_count() << "\n";

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            DEREFERNCED[i][j] *= scalar;
        }
    }


    matrix.SetNewValues(DEREFERNCED);
    return matrix;
}

Matrix Matrix::Arithmetic(Matrix& a, Matrix& b, bool negative) {
    double row_a = a.GetRows();
    double column_a = a.GetColumns();

    double row_b = b.GetRows();
    double column_b = b.GetColumns();

    if (row_a != row_b || column_a != column_b) throw std::invalid_argument("Matrices have different dimensions");
    

    std::shared_ptr<std::vector<std::vector<double> > > matrix_a = a.GetMatrix();
    std::shared_ptr<std::vector<std::vector<double> > > matrix_b = b.GetMatrix();
    auto DEREFERNCED_A = *matrix_a;
    auto DEREFERNCED_B = *matrix_b;

    /* weird bug */

       for (int i = 0; i < row_a; i++) {
        for (int j = 0; j < column_a; j++) {
            if(negative) DEREFERNCED_A[i][j] -= DEREFERNCED_B[i][j];
            else DEREFERNCED_A[i][j] += DEREFERNCED_B[i][j];
        }
    }
    
    
    a.SetNewValues(DEREFERNCED_A);    
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

    
    a.SetNewValues(DEREFERNCED_FIRST); 
    return a;
}

std::vector<std::shared_ptr<double> > Matrix::MiddleElements(Matrix& a) const {
    /*
        Here we get the matrix, we loop through the values and push in the middle elemnts
        11
        22
        33
        44 etc. 
        until theres no more
    */

    size_t rows = a.GetRows();
    size_t columns = a.GetColumns();
    std::shared_ptr<std::vector<std::vector<double> > > m = a.GetMatrix();
    auto DEF = *m;

    std::vector<std::shared_ptr<double> > middle_elements;

     for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if(DEF[i] == DEF[j]) {
                middle_elements.push_back(std::make_shared<double>(DEF[i][j]));
            }
        }
     }

    return middle_elements;
}

/* Very ugly implementation. I am just getting an idea of how to go about this. Will use 
help from other functions since this is quite impossible IMO to do for me in one member function. 
i think instead of considering all cases, i could generally just have two main cases
*/

Matrix Matrix::REF(Matrix& a) {
    size_t rows = a.GetRows();
    size_t columns = a.GetColumns();
    std::shared_ptr<std::vector<std::vector<double> > > m = a.GetMatrix();
    auto& DEF = *m;

    std::vector<std::shared_ptr<double> > middle_elements = this->MiddleElements(a);
    // [4 2; 3 4]; ===> 4 4
    // for(auto thisone : middle_elements) {
    //     std::cout << *thisone << "\n";
    // }

    int increase_counter = 0;
    std::vector<int> index_in_memory;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {

            if(DEF[increase_counter][increase_counter] >= columns) {
                break;
            } else if(DEF[increase_counter][increase_counter] == 0) {
                for(int k = 1; k < rows; k++) {
                    if(DEF[k][j] == 1 || DEF[k][j] > 1 || DEF[k][j] < 1) {
                        index_in_memory.push_back(k);
                    }
                }

                /* Change this */
                for(int m = 0; m < columns; m++) {
                     std::swap(DEF[increase_counter][m], DEF[index_in_memory[increase_counter]][m]);
                }
                increase_counter+=1;

                if(DEF[increase_counter][j] == 0) {
                    for(int m = 0; m < columns; m++) {
                        std::swap(DEF[increase_counter][m], DEF[index_in_memory[increase_counter]][m]);
                    }
                }
               

                      
            }

            increase_counter = 0;
        double diag_element = DEF[increase_counter][increase_counter];
        for(int l = 0; l < columns; l++) {
            DEF[increase_counter][l] /= diag_element;
        }

        increase_counter +=1;
                
            
            // } else {
            //     if(DEF[increase_counter][increase_counter] == 0) {
            //         std::swap(DEF[increase_counter][j], DEF[increase_counter + 1][j]);
            //     }
            //     DEF[increase_counter][j] = DEF[increase_counter][j] / *middle_elements[increase_counter];
            // }

            
            // DEF[increase_counter + 1][j] = (DEF[increase_counter][increase_counter] * DEF[increase_counter + 1][increase_counter]) - DEF[increase_counter][increase_counter];
            // increase_counter += 1;
           
            
        }
    }
    
    //     int counter = 0;
    //     for (int i = 0; i < rows  - 1; i++) {
    //         for (int j = 0; j < columns; j++) {
    //             if(*middle_elements[counter] != 1) {
    //                 DEF[i][j] /= *middle_elements[counter];
    //             }

    //               DEF[i][j] *= DEF[i + 1][j];

    //             if(DEF[i + 1][j] < 0) {
    //                 DEF[i + 1][j] = DEF[i][j] + DEF[i + 1][j];
    //             } else if (DEF[i + 1][j] > 0) {
    //                  DEF[i + 1][j] = DEF[i][j] - DEF[i + 1][j];
    //             }

    //             if(*middle_elements[counter] != 1) DEF[i][j] /= DEF[i][j];
              
             
    //         }
    //          counter += 1;    
    //     }

       

    a.SetNewValues(DEF);
    return a;
}


Matrix Matrix::Inverse(Matrix& a) {
    std::shared_ptr<std::vector<std::vector<double> > > m = a.GetMatrix();
    auto DEF = *m;

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
    std::shared_ptr<std::vector<std::vector<double> > > m = a.GetMatrix();
    std::cout << "Pointers pointing to matrix_: " <<  m.use_count() << "\n";
    auto DEREFERNCED = *m;
    std::vector<std::vector<double> > transposed(columns, std::vector<double>(rows));

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < columns; j++) {
            transposed[j][i] = DEREFERNCED[i][j];
        }
    }

    a.SetNewValues(transposed);
    return a;
}