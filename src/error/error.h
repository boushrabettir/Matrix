#ifndef ERROR_H
#define ERROR_H

#include <iostream>

struct ValidMatrices {

    void ThrowError() const;

    void DimensionError() const;

    void ScalarError() const;

    void MultiplicationError() const;

    void InvertibleError() const;

    void DotProductError() const;

    void OrthogonalError() const;
};

#endif