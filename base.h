#ifndef BASE_H
#define BASE_H

class Base {
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
};

#endif 