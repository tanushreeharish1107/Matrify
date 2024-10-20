# Matrify
Complex Matrix Calculator


## Matrix Operations Program

This project implements a dynamic matrix operations program in C++. The program allows users to input matrices of any size and perform a variety of operations, including:

### Single Matrix Operations:
1. **Determinant** (only for square matrices)
2. **Trace** (only for square matrices)
3. **Transpose**
4. **Adjoint** (only for square matrices)
5. **Inverse** (only for square matrices)

### Multi-Matrix Operations:
1. **Addition** (only for matrices of the same dimensions)
2. **Multiplication** (valid when the number of columns in the first matrix equals the number of rows in the second matrix)

The program uses dynamic memory allocation for matrices and handles input sizes flexibly. It checks for valid operations based on matrix properties (e.g., ensuring the matrix is square for determinant and trace).


