#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

int main() {
    //creating the testcase file
    freopen("180x180.in", "w", stdout);

    //size of the matrices to be generated
    int n = 180;    

    //number of testcases
    int testcases = 100;      

    //random number gen          
    srand(time(NULL));

    for (int i = 0; i < testcases; i++) {

        //makes two matrices for each testcase
        for (int j = 0; j < 2; j++) {

            //creating the matrix
            for (int p = 0; p < n; p++) {
                for (int q = 0; q < n; q++) {
                    int random_number = rand() % 1000 + 1;
                    cout << random_number << ' ';
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}