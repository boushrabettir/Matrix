#include <iostream>
#include <vector>

#include "matrix.cpp"


int main() {

/* testing it so far */

    Matrix newMatrix; 



    newMatrix.SetRows(3);
    newMatrix.SetColumns(6);

    newMatrix.GetValues();
    newMatrix.Print();
    std::cout << "\n\n";
    newMatrix.REF(newMatrix);
    newMatrix.Print();
    // newMatrix.REF(newMatrix);
    // std::cout << "Here is your REF matrix" << std::endl;


    // std::cout << "Transposed: " << "\n";
    // newMatrix.Transpose(newMatrix);
    // newMatrix.Print();

    //  std::cout << "!Transposed: " << "\n";
    //  newMatrix.Transpose(newMatrix);
    // newMatrix.Print();

    /* Weird bug here if I try to add [6, 10]^T to matrix b*/
    // newMatrix.ScalarMultiplication(newMatrix, 2);
    //  newMatrix.Print();


   /* Multiplying Matrix */ 

  

    // Matrix b;
    // b.SetRows(2);
    // b.SetColumns(2);
    // b.GetValues();

    // bool match;
    
    // // newMatrix.MultiplyMatrix(newMatrix, b, match);

   
    // // newMatrix.Print();


    // newMatrix.Arithmetic(newMatrix, b, true);
    // newMatrix.Print();
    

    return 0;
}
