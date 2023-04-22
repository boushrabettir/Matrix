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
 - Define the `matrix.h` file in your header
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

<br />
Now, you are free to do ANY matrix function for V.1.! Here is the current list of functions to use for your matrix. 

  1. Scalar Multiplication(YOUR SCALAR)
  2. Multiply Matrix(MATRIX 1, MATRIX 2)
  3. Arithmetic(MATRIX 1, MATRIX 2, bool) -> bool == true ? `SUBTRACTION` : `ADDITION`
  4. Transpose(MATRIX 1)
  5. REF and RREF(MATRIX 1)
  6. Inverse of a 2x2 ONLY(MATRIX 1)
  7. `MORE!`
 
In upcoming `V.2.`, there will exist more member functions to implement into your project!
<br />

### Created with 💙 by Boushra

