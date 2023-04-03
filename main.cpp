#include <iostream>
#include <vector>

#include "matrix.cpp"


int main() {

/* testing it so far */

    Matrix newMatrix; 

    int rows, cols;
    std::cout << "Enter number of rows and columns: ";
    std::cin >> rows >> cols;

    newMatrix.SetRows(rows);
    newMatrix.SetColumns(cols);

    newMatrix.GetValues();

    newMatrix.Print();

    /* Weird bug here if I try to add [6, 10]^T to matrix b*/
    // newMatrix.ScalarMultiplication(newMatrix, 2);
    // newMatrix.Print();


   /* Multiplying Matrix */ 

  

    Matrix b;
    b.SetRows(2);
    b.SetColumns(1);
    b.GetValues();

    b.GetMatrix();


    bool match;
    
    newMatrix.MultiplyMatrix(newMatrix, b, match);

   
    newMatrix.Print();


    // newMatrix.AddMatrix(newMatrix, b, match);
    // newMatrix.Print();
    

    return 0;
}