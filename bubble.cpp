// Write a program to implement Parallel Bubble Sort using OpenMP. Use existing
// algorithms and measure the performance of sequential and parallel algorithms.


#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <chrono>

using namespace std;

void sequentialBubbleSort(vector<int>& arr) 
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void parallelBubbleSort(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n; i++) 
    {
        #pragma omp parallel for
        for (int j = i % 2; j < n - 1; j += 2)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
    }
}

void printArray(const vector<int>& arr) 
{
    for (auto x : arr)
        cout << x << " ";
    cout << endl;
}

int main() 
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    
    vector<int> arr(n), arr_copy(n);
    
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Element " << i+1 << ": ";
        cin >> arr[i];
        arr_copy[i] = arr[i];
    }
    
    auto startSeq = chrono::high_resolution_clock::now();
    sequentialBubbleSort(arr);
    auto endSeq = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationSeq = endSeq - startSeq;
    
    auto startPar = chrono::high_resolution_clock::now();
    parallelBubbleSort(arr_copy);
    auto endPar = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationPar = endPar - startPar;
    
    cout << "\n----- Sequential Bubble Sort Output -----\n";
    cout << "Sorted Array: ";
    printArray(arr);
    cout << "Time Taken: " << durationSeq.count() << " milliseconds\n";

    cout << "\n----- Parallel Bubble Sort Output -----\n";
    cout << "Sorted Array: ";
    printArray(arr_copy);
    cout << "Time Taken: " << durationPar.count() << " milliseconds\n";
    
    return 0;
}


// #include <iostream>
// #include <vector>
// #include <omp.h>
// #include <chrono>

// using namespace std;

// void sequentialBubbleSort(vector<int>& arr) {
//     int n = arr.size();
//     for (int i = 0; i < n - 1; ++i)
//         for (int j = 0; j < n - i - 1; ++j)
//             if (arr[j] > arr[j + 1])
//                 swap(arr[j], arr[j + 1]);
// }

// // Parallel Odd-Even Bubble Sort
// void parallelBubbleSortOddEven(vector<int>& arr) {
//     int n = arr.size();
//     for (int i = 0; i < n; ++i) {
//         if (i % 2 == 0) {
//             #pragma omp parallel for
//             for (int j = 0; j < n - 1; j += 2)
//                 if (arr[j] > arr[j + 1])
//                     swap(arr[j], arr[j + 1]);
//         } else {
//             #pragma omp parallel for
//             for (int j = 1; j < n - 1; j += 2)
//                 if (arr[j] > arr[j + 1])
//                     swap(arr[j], arr[j + 1]);
//         }
//     }
// }

// void printArray(const vector<int>& arr) {
//     for (int val : arr)
//         cout << val << " ";
//     cout << "\n";
// }

// int main() {
//     int n;
//     cout << "Enter number of elements: ";
//     cin >> n;

//     if (n <= 0) {
//         cout << "Invalid size.\n";
//         return 1;
//     }

//     vector<int> original(n);
//     cout << "Enter elements:\n";
//     for (int i = 0; i < n; ++i) {
//         cout << "Element " << i + 1 << ": ";
//         cin >> original[i];
//     }

//     vector<int> seqArr = original;
//     vector<int> parArr = original;

//     // Sequential sort timing
//     auto startSeq = chrono::high_resolution_clock::now();
//     sequentialBubbleSort(seqArr);
//     auto endSeq = chrono::high_resolution_clock::now();

//     // Parallel sort timing
//     auto startPar = chrono::high_resolution_clock::now();
//     parallelBubbleSortOddEven(parArr);
//     auto endPar = chrono::high_resolution_clock::now();

//     chrono::duration<double, milli> timeSeq = endSeq - startSeq;
//     chrono::duration<double, milli> timePar = endPar - startPar;

//     cout << "\n=== Sequential Bubble Sort ===\n";
//     printArray(seqArr);
//     cout << "Time Taken: " << timeSeq.count() << " ms\n";

//     cout << "\n=== Parallel Odd-Even Bubble Sort ===\n";
//     printArray(parArr);
//     cout << "Time Taken: " << timePar.count() << " ms\n";

//     return 0;
// }
