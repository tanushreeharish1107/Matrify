#include <iostream>
using namespace std;
#include <cstring>

void printMatrix(int rows, int cols , int** arr){
      for (int i=0;i<rows;i++)
      {
        for(int j=0;j<cols;j++)
        {
        cout<<arr[i][j]<<" ";
        }
       
     cout<<endl;
     
        }

}

//---------------------------------------------------------------------------------------------------

void cofactor(int rows,int cols, int** arr ,int** temp, int p , int q){
   int i=0,j=0;
   

   for(int row=0;row<rows;row++)
   {
    for(int col=0;col<cols;col++)
    {
        if (row!=p && col!=q)
        {

            temp[i][j]=arr[row][col];
            j++;

            if(j==cols-1)
            { //if j reaches the end of the row , move to the new row 
                j=0;
                i++;
            }
        }
    }
   
   }
   //we get a cofactor matrix out of this function in temp

}

//---------------------------------------------------------------------------------------------------

int det(int n , int** arr){

    if (n==1){
       return arr[0][0];
    }

    if(n==2){
        return (arr[0][0]*arr[1][1])-(arr[0][1]*arr[1][0]);
    }

    int sol=0;
    
    int sign=1;

    int** temp = new int*[n-1];
    for(int i=0;i<n-1;i++){
        temp[i]= new int[n-1];
    }
   

   
    for (int j=0;j<n;j++){
       cofactor(n,n,arr,temp,0,j);
       sol= sol+ (sign)*(arr[0][j])*(det(n-1,temp)); //recursive call
       sign=-sign; //alternate the sign
    }

    // Deallocate memory for temp matrix
    for (int i = 0; i < n - 1; i++) {
        delete[] temp[i];
    }
    delete[] temp;

    return sol;

}

//-----------------------------------------------------------------------------------

int trace(int n, int** arr){
    int sol=0;

    for(int i=0;i<n;i++){
       sol=sol+arr[i][i];
    }

    return sol;

}

//-----------------------------------------------------------------------------------
void transpose(int rows ,int cols, int** arr, int** temp){
    
     for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            temp[j][i]=arr[i][j];
        }
    }
    
}

//-----------------------------------------------------------------------------------


void adjoint(int rows, int cols, int** arr, int** temp) {
    if (rows != cols) {
        std::cout << "Adjoint is only defined for square matrices." << std::endl;
        return;
    }
    
    // Dynamically allocate space for the cofactor matrix (size (rows-1)x(cols-1))
    int** cofactorm = new int*[rows - 1];
    for (int i = 0; i < rows - 1; i++) {
        cofactorm[i] = new int[cols - 1];
    }

    // Calculate the cofactor matrix and the determinant of each minor
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cofactor(rows, cols, arr, cofactorm, i, j);  // Get the cofactor matrix
            temp[j][i] = ((i + j) % 2 == 0 ? 1 : -1) * det(rows - 1, cofactorm);  // Compute the determinant and apply sign (-1)^(i+j)
        }
    }

    // Deallocate memory for the cofactor matrix
    for (int i = 0; i < rows - 1; i++) {
        delete[] cofactorm[i];
    }
    delete[] cofactorm;
}

//---------------------------------------------------------------------------

void addition(int rows,int cols , int** arr1 , int** arr2){

    int** arrsol;
     for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
         arrsol[i][j]=arr1[i][j]+arr2[i][j];  
        }
    
    }

    printMatrix(rows,cols,arrsol);

   

}

//---------------------------------------------------------------------------

void multiply(int rows1,int cols1, int** arr1,int rows2,int cols2, int** arr2) {
    if (cols1 != rows2) {
        cout << "Matrix multiplication not possible: number of columns in arr1 must equal number of rows in arr2." << endl;
        return;
    }
    
    // Dynamically allocate memory for the solution matrix
    int** arrsoln = new int*[rows1];
    for (int i = 0; i < rows1; i++) {
        arrsoln[i] = new int[cols2]();
    }

    // Perform matrix multiplication
    for (int i = 0; i < rows1; i++) {
        for (int j = 0; j < cols2; j++) {
            for (int k = 0; k < cols1; k++) {
                arrsoln[i][j] += arr1[i][k] * arr2[k][j];  // Multiply and accumulate
            }
        }
    }

    // Print the result matrix
    printMatrix(rows1,cols2 ,arrsoln);

    // Deallocate the memory for the result matrix
    for (int i = 0; i < rows1; i++) {
        delete[] arrsoln[i];
    }
    delete[] arrsoln;
}

//----------------------------------------------------------------------------------------------
bool inverse(int** mat, int** inv, int n) {
    // Find determinant of the matrix
    int D = det(n,mat);
    if (det == 0) {
        cout << "Singular matrix, can't find its inverse";
        return false;
    }

    // Find adjoint
    int** adj = new int*[n];
    for (int i = 0; i < n; i++) adj[i] = new int[n];
    adjoint(n,n,mat, adj);

    // Find inverse using formula: inv(A) = adj(A) / det(A)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv[i][j] = adj[i][j] / float(D);
        }
    }

    for (int i = 0; i < n; i++) delete[] adj[i];
    delete[] adj;

    return true;
}

int main() {
    int rows, cols;
    cout << "Is it a single(s) or multi(m) matrix operation? " << endl;
    char o;
    cin >> o;

    if (o == 's') {
        cout << "Enter number of rows: ";
        cin >> rows;
        cout << "Enter number of cols: ";
        cin >> cols;

        // Dynamically allocate memory for matrix
        int** mat = new int*[rows];
        for (int i = 0; i < rows; i++) {
            mat[i] = new int[cols];
        }

        cout << "Enter your matrix: " << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> mat[i][j];
            }
        }

        cout << "Enter your operation number: \n1. Determinant \n2. Trace \n3. Transpose \n4. Adjoint \n5. Inverse" << endl;
        int op;
        cin >> op;

        // Dynamically allocate memory for temp matrix
        int** temp = new int*[rows];
        for (int i = 0; i < rows; i++) {
            temp[i] = new int[cols];
        }

        switch (op) {
            case 1:
                if (rows != cols) {
                    cout << "The Determinant is not possible for non-square matrices.\n";
                } else {
                    cout << "Determinant: " << det(rows, mat) << endl;
                }
                break;
            case 2:
                if (rows != cols) {
                    cout << "The Trace is not possible for non-square matrices.\n";
                } else {
                    cout << "Trace: " << trace(rows, mat) << endl;
                }
                break;
            case 3:
                transpose(rows, cols, mat, temp);
                cout << "Transpose: \n";
                printMatrix(cols, rows, temp); // Transpose flips the dimensions
                break;
            case 4:
                if (rows != cols) {
                    cout << "Adjoint is not possible for non-square matrices.\n";
                } else {
                    adjoint(rows, cols, mat, temp);
                    cout << "Adjoint: \n";
                    printMatrix(rows, cols, temp);
                }
                break;
            case 5:
                if (rows != cols) {
                    cout << "Inverse is not possible for non-square matrices.\n";
                } else {
                    if (inverse(mat, temp, rows)) {
                        cout << "Inverse: \n";
                        printMatrix(rows, cols, temp);
                    } else {
                        cout << "Inverse is not possible (determinant is 0).\n";
                    }
                }
                break;
            default:
                cout << "Invalid operation." << endl;
        }

        // Free dynamically allocated memory
        for (int i = 0; i < rows; i++) {
            delete[] mat[i];
            delete[] temp[i];
        }
        delete[] mat;
        delete[] temp;

    } else if (o == 'm') {
        cout << "Enter number of rows for first matrix: ";
        cin >> rows;
        cout << "Enter number of cols for first matrix: ";
        cin >> cols;

        int** mat = new int*[rows];
        for (int i = 0; i < rows; i++) {
            mat[i] = new int[cols];
        }

        cout << "Enter the first matrix: " << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cin >> mat[i][j];
            }
        }

        int rows2, cols2;
        cout << "Enter number of rows for second matrix: ";
        cin >> rows2;
        cout << "Enter number of cols for second matrix: ";
        cin >> cols2;

        int** mat2 = new int*[rows2];
        for (int i = 0; i < rows2; i++) {
            mat2[i] = new int[cols2];
        }

        cout << "Enter the second matrix: " << endl;
        for (int i = 0; i < rows2; i++) {
            for (int j = 0; j < cols2; j++) {
                cin >> mat2[i][j];
            }
        }

        cout << "Enter your operation number: \n1. Addition \n2. Multiplication" << endl;
        int op;
        cin >> op;

        switch (op) {
            case 1:
                if (rows == rows2 && cols == cols2) {
                    addition(rows, cols, mat, mat2);
                } else {
                    cout << "Addition is not possible (matrices must have the same dimensions).\n";
                }
                break;
            case 2:
                if (cols == rows2) {
                    multiply(rows, cols, mat, rows2, cols2, mat2);
                } else {
                    cout << "Multiplication is not possible (number of columns of the first matrix must equal the number of rows of the second matrix).\n";
                }
                break;
            default:
                cout << "Invalid operation.\n";
        }

        // Free dynamically allocated memory
        for (int i = 0; i < rows; i++) {
            delete[] mat[i];
        }
        delete[] mat;

        for (int i = 0; i < rows2; i++) {
            delete[] mat2[i];
        }
        delete[] mat2;
    }

    return 0;
}




   
   

    

   