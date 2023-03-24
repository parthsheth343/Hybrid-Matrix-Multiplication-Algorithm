#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;
#define ll long long

//Variables for maximum, minimum, and average runtime
int minimum = 1e9;
int maximum = 0;
double average = 0;

//The current matrice size (squares matrices only)
const int n = 180; 

//A and B are input matrices, C is the product
ll C[n][n];
int A[n][n];
int B[n][n];

//Algorithm for multiplying two matrices the standard way
void naive_mutliply(int A[n][n], int B[n][n], int q) {
    //Starts the timer
    auto start = high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    //Stops the timer
    auto stop = high_resolution_clock::now();
    //Calculates time elapsed
    auto duration = duration_cast<microseconds>(stop-start);
    cout << "Test Case " << q << " - Time elapsed: " << duration.count() << " microseconds"<< endl;
    maximum = max(maximum, (int) duration.count());
    minimum = min(minimum, (int) duration.count());
    average += (int) duration.count();
}

int main() {
    
    //Input file with matrices
    freopen("180x180.in", "r", stdin); 
    //Output file with results
    freopen("Naive180.out", "w", stdout);

    int testcases = 100;

    //Looping through testcases
    for (int i = 0; i < testcases; i++) { 

        //Reading matrix A
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cin >> A[j][k];
            }
        }
        //Reading matrix B
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cin >> B[j][k];
            }
        }
        //Resetting matrix C after each test case
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[j][k] = 0;
            }
        }
        //Multiplying matrices A and B
        naive_mutliply(A, B, i+1);
    }

    //Printing statistics
    cout << endl;
    cout << "Minimum time: " << minimum << " microseconds"<< endl;
    cout << "Maximum time: " << maximum << " microseconds"<< endl;
    cout << "Average time: " << average/testcases << " microseconds"<< endl;

    return 0;
}