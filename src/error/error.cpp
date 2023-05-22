  #include "error.h"


    void ValidMatrices::ThrowError() const {
        throw std::runtime_error("Your input is not valid, please try again.");
    }

    void ValidMatrices::ScalarError() const {
        throw std::runtime_error("Scalar is a not a digit or it is a value of 0. Please try again.");
    }

    void ValidMatrices::DimensionError() const {
      throw std::runtime_error("Matrices have different dimensions");
    }

    void ValidMatrices::MultiplicationError() const {
        throw std::runtime_error("These matrices cannot be multiplied. Please "
                             "check your dimensions before proceeding again.");
    }

    void ValidMatrices::InvertibleError() const {
         throw std::runtime_error("2x2 Matrix is not invertible!");
    }

    void ValidMatrices::DotProductError() const {
         throw std::runtime_error("Please check to see if your matrices are valid. Inconsistencies in column/row length.");
    }

    void ValidMatrices::OrthogonalError() const {
         throw std::runtime_error("Please check to see if your matrices are valid");
    }

