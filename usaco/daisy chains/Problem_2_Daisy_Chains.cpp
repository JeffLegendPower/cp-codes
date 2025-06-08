#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

#define ll long long

// returns -1 if avg is a decimal
// inclusive
inline int avgFromRange(int arr[], int start, int end) {
    int num = 0;
    for (int i = start; i <= end; i++) {
        num += arr[i];
    }
    double avg = num / double(end - start + 1);
    return avg == int(avg) ? int(avg) : -1;
}

// inclusive
inline bool contains(int arr[], int start, int end, int target) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == target) return true;
    }
    return false;
}

int main() {
    int N;
    cin >> N;

    int flowers[N];
    for (int i = 0; i < N; i++) {
        cin >> flowers[i];
    }

    int photosWithAvgFlower = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            int avg = avgFromRange(flowers, i, j);
            if (contains(flowers, i, j, avg)) photosWithAvgFlower++;
        }
    }
    cout << photosWithAvgFlower;
}