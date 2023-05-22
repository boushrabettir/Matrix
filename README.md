# Matrix V.1. Library

## Integrating this into your Project

First, git clone this into any folder of your repository. Preferably, the root of your project.

```
git clone https://github.com/boushrabettir/Matrix.git
```

<br />

If you're using macOS, you can use this command to clone it into your project.

```
sudo git clone https://github.com/boushrabettir/Matrix.git
```

<br />

## Examples

Similar to any matrix that can do matrix functions, you can do and apply the same logic here. In other words, what you can do on paper, you can do in this library,
or even better. There exists several member functions that are easy to work with for `V.1.` of this library.

### GETTING STARTED

- Define the `matrix.h` file in your header. A `main.cpp` file already exists with this header in `src/main.cpp`

```cpp
#include "matrix.h"
```

- Create your new matrix

```cpp
Matrix myMatrix;
```

- Set your rows and columns

```cpp
myMatrix.SetSize(3, 3);
```

- Set your values. You will be prompted in the command line to input your values for each row/column element

```cpp
myMatrix.GetValues();
```

- Print your matrix

```cpp
myMatrix.Print();
```

### Now, you are free to do ANY matrix function for V.1.! Here is the current list of functions to use for your matrix.

1. Scalar Multiplication

```cpp
myMatrix.ScalarMultiplication(3);
```

2. Multiply Matrix

```cpp
Matrix mySecondMatrix;

// After doing SetSize() and GetValues() member functions...

myMatrix.MultiplyMatrix(mySecondMatrix);
```

3. Arithmetic

The last argument is whether or not you want to subtract or add your matrices. `true` means you want to subtract, and `false` means you want to add.

```cpp
myMatrix.Arithmetic(mySecondMatrix, true);
```

4. Transpose

```cpp
myMatrix.Transpose();
```

5. REF/RREF

The last argument is type boolean. If you want your matrix to be REF (Reduced Row Form) input `false`, else if you want it to be in RREF (Reduced Row Echelon Form), input `true`

```cpp
myMatrix.REF(true);
```

6. Rank

Please note that this function will automatically put your matrix into RREF (Reduced Row Echelon Form), and return the rank.

```cpp
myMatrix.Rank();
```

7. Trace

Please note that this function returns the trace, so if you would like to verify the number or use this number in another operation, make sure to hold it into a variable.

```cpp
auto trace = myMatrix.Trace();
std::cout << trace << std::endl;
```

8. Exponentiation

```cpp
myMatrix.Exponentiate(2);
```

9. Inverse (strictly, 2x2 Matrices only)

```cpp
myMatrix.Inverse();
```

10. Dot Product

```cpp
myMatrix.DotProduct(mySecondMatrix);
```

11. Orthogonal Test

```cpp
myMatrix.Orthogonal(mySecondMatrix, myThirdMatrix);
```

In upcoming `V.2.`, there will exist more member functions to implement into your project!
<br />

### Created with 💙 by Boushra
