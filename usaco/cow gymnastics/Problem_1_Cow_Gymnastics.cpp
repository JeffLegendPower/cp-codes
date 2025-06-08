#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

// assumes both elements are in the array
inline int firstInArr(int one, int two, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == (one + 1)) {
            return 1;
        } else if (arr[i] == (two + 1)) {
            return 2;
        }
    }
    return -1;
}

int main() {

    freopen("gymnastics.in", "r", stdin);
    freopen("gymnastics.out", "w", stdout);

    int K, N;
    cin >> K >> N;

    int cows[K][N];

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            cin >> cows[i][j];
        }
    }

    int numConsistent = 0;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int cow1 = i;
            int cow2 = j;
            int betterCow = -1;
            for (int k = 0; k < K; k++) {
                int first = firstInArr(cow1, cow2, cows[k], N);

                if (betterCow == -1) {
                    betterCow = first;
                } else if (betterCow != first) {
                    betterCow = -1;
                    break;
                }
            }
            if (betterCow != -1) {
                numConsistent++;
            }
        }
    }

    cout << numConsistent;
}