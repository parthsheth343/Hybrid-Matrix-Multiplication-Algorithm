#include <bits/stdc++.h>
#include <chrono>

#define ll long long
using namespace std;
using namespace std::chrono;

//making code easier to read
#define vi vector<int>
#define vii vector<vi>

//statistics
ll minimum = 1e16;
ll maximum = 0;
long double average = 0;

//size of matrix
const int p = 17;

//crossover point tested
const int crossover = 16;

//smaller power of 2 greater than p (to pad matrices with 0s until its sides are of form 2^n)
const int r = pow(2, ceil(log2(p)));

//2 input matrixes and their product matrix
vii First(r, vi (r, 0));
vii Second(r, vi (r, 0));
vii Result(r, vi (r, 0));

//function to add two matrices
vii add(vii A, vii B) {
    int n = A.size();
    vii C(n, vi (n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

//function to substract two matrices
vii substract(vii A, vii B) {
    int n = A.size();
    vii C(n, vi (n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

//naive algorithm, for when the matrix size is less than the crossover point
vii naive(vii A, vii B) {
    int n = A.size();
    vii C(n, vi (n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return C;
}

//main function
vii strassen(vii A, vii B) {

    //size length of the matrix
    int n = A.size();

    //compare size with crossover point
    if (n <= crossover) {
        return naive(A, B);
    }

    //product matrix
    vii C(n, vi (n, 0));

    //base case where divide and conquer ends
    if (n == 1) {
        C[0][0] = A[0][0]*B[0][0];
        return C;
    }

    //splitting the input matrices into 4 quadrants each
    int half = n/2;
    vii a11(half, vi (half, 0));
    vii a12(half, vi (half, 0));
    vii a21(half, vi (half, 0));
    vii a22(half, vi (half, 0));
    vii b11(half, vi (half, 0));
    vii b12(half, vi (half, 0));
    vii b21(half, vi (half, 0));
    vii b22(half, vi (half, 0));

    //initializing these matrices
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + half];
            a21[i][j] = A[i + half][j];
            a22[i][j] = A[i + half][j + half];
            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + half];
            b21[i][j] = B[i + half][j];
            b22[i][j] = B[i + half][j + half];
        }
    }

    //divide and conquer
    vii p1 = strassen(a11, substract(b12, b22));
    vii p2 = strassen(add(a11, a12), b22);
    vii p3 = strassen(add(a21, a22), b11);
    vii p4 = strassen(a22, substract(b21, b11));
    vii p5 = strassen(add(a11, a22), add(b11, b22));
    vii p6 = strassen(substract(a12, a22), add(b21, b22));
    vii p7 = strassen(substract(a11, a21), add(b11, b12));

    //calculating the 4 quadrants of the resultant matrix
    vii c11 = add(substract(add(p5, p4), p2), p6);
    vii c12 = add(p1, p2);
    vii c21 = add(p3, p4);
    vii c22 = substract(substract(add(p1, p5), p3), p7);

    //combining the 4 resultant matrices
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = c11[i][j];
            C[i][j + half] = c12[i][j];
            C[i + half][j] = c21[i][j];
            C[i + half][j + half] = c22[i][j];
        }
    }

    return C;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //reads input file
    freopen("17x17.in", "r", stdin);
    //reads output file
    freopen("C16-17.out", "w", stdout);

    //number of testcases
    int testcases = 3;

    //looping through testcases
    for (int i = 0; i < testcases; i++) {

        //reading the first matrix
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < p; k++) {
                cin >> First[j][k];
            }
        }

        //reading the second matrix
        for (int j = 0; j < p; j++) {
            for (int k = 0; k < p; k++) {
                cin >> Second[j][k];
            }
        }

        //resets the resultant matrix after each testcase
        for (int j = 0; j < r; j++) {
            for (int k = 0; k < r; k++) {
                Result[j][k]=0;
            }
        }

        //starting the timer
        auto start = high_resolution_clock::now();

        //padding the matrix with 0s if needed
        for (int j = p; j < r; j++) {
            for (int k = 0; k < r; k++) {
                First[j][k] = 0;
                First[k][j] = 0;
                Second[k][j] = 0;
                Second[j][k] = 0;
            }
        }

        //calculating the product of the input matrices
        Result = strassen(First, Second);

        //stopping the timer
        auto stop = high_resolution_clock::now();

        //calculating time elapsed
        auto duration = duration_cast<microseconds>(stop-start);

        //printing test case results
        cout << "Test Case " << i+1 << " - Time elapsed: " << duration.count() << " microseconds"<< endl;
        maximum = max(maximum, (ll) duration.count());
        minimum = min(minimum, (ll) duration.count());
        average += (ll) duration.count();
    }

    //printing statistics
    cout << endl;
    cout << "Minimum time: " << minimum << " microseconds"<< endl;
    cout << "Maximum time: " << maximum << " microseconds"<< endl;
    cout << "Average time: " << average/testcases << " microseconds"<< endl;

}