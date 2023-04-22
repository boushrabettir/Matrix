#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <memory>
#include <vector>


class BaseMatrix {
    /*
    TODO:
        1. Implement Parent class 
        2. Child class inherits from Base
        3. Optimize the code where it does not slow down
        4. Deconstructors possibly to free up any space? 
            -> Automatically given?
        5. Do some more c++ research
    */

    /*
        -> A Matrix has the following
            1. Rows
            2. Columns
                - Getting / Setting

        -> POSSIBLE FUNCTIONS TO MOVE IN
            double GetRows() const;
            double GetColumns() const;
            std::shared_ptr<std::vector<std::vector<double> > > GetMatrix() const;

            std::vector<std::vector<double> > GetValues();

            void SetRows(const size_t rows);
            void SetColumns(const size_t columns);
            void SetSize(const size_t rows, const size_t columns);
            void SetNewValues(const std::vector<std::vector<double> > new_values);
    */

  public:
    BaseMatrix() {}
    BaseMatrix(size_t rows, size_t columns) : rows_(rows), columns_(columns) {}
    double GetRows() const { return rows_; }
    double GetColumns() const { return columns_; }

    std::vector<std::vector<double> > GetValues() {
      std::cout << "Please input your values accordingly!\n";
       for (int i = 0; i < rows_; ++i) {
         for (int j = 0; j < columns_; ++j) {
           std::cout << "Enter element at (Row: " << i << ", Column: " << j << "): ";
            std::cin >> (*matrix_)[i][j];
        }
    }
     return *matrix_;
    };

    void SetRows(const size_t rows) {
      rows_ = rows;
      matrix_->resize(rows_);
      for (std::vector<double>& row : *matrix_) {
        row.resize(rows_);
      }
    }

    void SetColumns(const size_t columns) {
      columns_ = columns;
      for (std::vector<double>& columns : *matrix_) {
        columns.resize(columns_);
      }
    }

    void SetSize(const size_t rows, const size_t columns) {
      SetRows(rows);
      SetColumns(columns);
    }
    // implement ^

    void SetNewValues(const std::vector<std::vector<double> > new_values) { *matrix_ = new_values; }

  private:
    size_t rows_, columns_;
    std::shared_ptr<std::vector<std::vector<double> > > matrix_;
};

#endif 