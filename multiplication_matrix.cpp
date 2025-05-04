// Write a program to implement Parallel matrix-matrix multiplication using OpenMP.
#include <iostream>
#include <omp.h>
#include <chrono>
using namespace std;

#define MAX 100

void sequentialMatrixMultiply(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n, int m, int p) 
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < p; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

void parallelMatrixMultiply(int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX], int n, int m, int p) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < p; ++k)
                C[i][j] += A[i][k] * B[k][j];
}

void printMatrix(int M[MAX][MAX], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << M[i][j] << " ";
        cout << endl;
    }
}

int main() {
    int n, m, p;
    int A[MAX][MAX], B[MAX][MAX], C_seq[MAX][MAX] = {}, C_par[MAX][MAX] = {};

    cout << "Enter dimensions (A: n x p, B: p x m)\n";
    cout << "Enter n: ";
    cin >> n;
    cout << "Enter p: ";
    cin >> p;
    cout << "Enter m: ";
    cin >> m;

    cout << "Enter matrix A elements:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < p; ++j) {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }

    cout << "Enter matrix B elements:\n";
    for (int i = 0; i < p; ++i)
        for (int j = 0; j < m; ++j) {
            cout << "B[" << i << "][" << j << "]: ";
            cin >> B[i][j];
        }

    auto startSeq = chrono::high_resolution_clock::now();
    sequentialMatrixMultiply(A, B, C_seq, n, m, p);
    auto endSeq = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationSeq = endSeq - startSeq;

    auto startPar = chrono::high_resolution_clock::now();
    parallelMatrixMultiply(A, B, C_par, n, m, p);
    auto endPar = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationPar = endPar - startPar;

    cout << "\n----- Sequential Matrix-Matrix Multiplication Output -----\n";
    printMatrix(C_seq, n, m);
    cout << "Time Taken: " << durationSeq.count() << " milliseconds\n";

    cout << "\n----- Parallel Matrix-Matrix Multiplication Output -----\n";
    printMatrix(C_par, n, m);
    cout << "Time Taken: " << durationPar.count() << " milliseconds\n";

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <chrono>
// #include <omp.h>

// using namespace std;
// using namespace chrono;

// // Sequential Matrix Multiplication
// void sequentialMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++) {
//             C[i][j] = 0;
//             for (int k = 0; k < n; k++)
//                 C[i][j] += A[i][k] * B[k][j];
//         }
// }

// // Parallel Matrix Multiplication using OpenMP
// void parallelMultiply(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
//     #pragma omp parallel for collapse(2)
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++) {
//             C[i][j] = 0;
//             for (int k = 0; k < n; k++)
//                 C[i][j] += A[i][k] * B[k][j];
//         }
// }

// // Function to display a matrix
// void displayMatrix(const vector<vector<int>>& M, int n, const string& name) {
//     cout << "\n" << name << ":\n";
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++)
//             cout << M[i][j] << " ";
//         cout << endl;
//     }
// }

// int main() {
//     int n;
//     cout << "Enter size of square matrices (n): ";
//     cin >> n;

//     vector<vector<int>> A(n, vector<int>(n));
//     vector<vector<int>> B(n, vector<int>(n));
//     vector<vector<int>> C_seq(n, vector<int>(n));
//     vector<vector<int>> C_par(n, vector<int>(n));

//     // Take input for Matrix A
//     cout << "\nEnter elements for Matrix A (" << n << "x" << n << "):\n";
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++)
//             cin >> A[i][j];

//     // Take input for Matrix B
//     cout << "\nEnter elements for Matrix B (" << n << "x" << n << "):\n";
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < n; j++)
//             cin >> B[i][j];

//     // Sequential Multiplication
//     auto start_seq = high_resolution_clock::now();
//     sequentialMultiply(A, B, C_seq, n);
//     auto end_seq = high_resolution_clock::now();
//     auto duration_seq = duration_cast<milliseconds>(end_seq - start_seq);

//     // Parallel Multiplication
//     auto start_par = high_resolution_clock::now();
//     parallelMultiply(A, B, C_par, n);
//     auto end_par = high_resolution_clock::now();
//     auto duration_par = duration_cast<milliseconds>(end_par - start_par);

//     // Display Results
//     cout << "\nTime taken by Sequential Multiplication: " << duration_seq.count() << " ms";
//     cout << "\nTime taken by Parallel Multiplication:   " << duration_par.count() << " ms\n";

//     // Optional: Display result matrices
//     char show;
//     cout << "\nDo you want to display the result matrices? (y/n): ";
//     cin >> show;

//     if (show == 'y' || show == 'Y') {
//         displayMatrix(C_seq, n, "Result (Sequential)");
//         displayMatrix(C_par, n, "Result (Parallel)");
//     }

//     return 0;
// }

