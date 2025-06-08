#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

#define ll long long

inline int partition(int arr[], int arr2[], int arr3[], int start, int end) {
    int pivot = arr[start];
    int count = 0;
    
    for (int i = start + 1; i <= end; i++) {
        if (arr[i] <= pivot)
            count++;
    }

    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
    swap(arr2[pivotIndex], arr2[start]);
    swap(arr3[pivotIndex], arr3[start]);

    int i = start + 1, j = end;
    while (i <= j) {
        while (i <= end && arr[i] <= pivot) i++;
        while (arr[j] > pivot) j--;
        
        if (i < j) {
            swap(arr[i], arr[j]);
            swap(arr2[i], arr2[j]);
            swap(arr3[i], arr3[j]);
        }
    }

    swap(arr[start], arr[j]);
    swap(arr2[start], arr2[j]);
    swap(arr3[start], arr3[j]);

    return j;
}

inline void quickSort(int arr[], int arr2[], int arr3[], int start, int end) {
    if (start >= end)
        return;

    int p = partition(arr, arr2, arr3, start, end);
    quickSort(arr, arr2, arr3, start, p - 1);
    quickSort(arr, arr2, arr3, p + 1, end);
}

void reverseArray(int arr[], int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        // Swap elements at start and end indices
        std::swap(arr[start], arr[end]);

        // Move indices towards the center
        start++;
        end--;
    }
}

inline bool equalValues(bool arr1[], bool arr2[], int length) {
    bool equal = true;
    for (int i = 0; i < length; i++)
        equal = equal && arr1[i] == arr2[i];

    return equal;
}



int main() {
    freopen("tracing.in", "r", stdin);
    freopen("tracing.out", "w", stdout);

    int N, T;
    string finalCows;

    cin >> N >> T;
    cin >> finalCows;

    int shaketimes[T], firstShakeCows[T], secondShakeCows[T];

    for (int i = 0; i < T; i++) {
        cin >> shaketimes[i] >> firstShakeCows[i] >> secondShakeCows[i];
    }

    quickSort(shaketimes, firstShakeCows, secondShakeCows, 0, T); // Sort in descending order (cant make it work in ascending for some reason)
    // Flip arrays to make them ascending
    reverseArray(shaketimes, T);
    reverseArray(firstShakeCows, T);
    reverseArray(secondShakeCows, T);

    // Convert the final cow string into a bool array
    bool finalCowArr[N];
    for (int i = 0; i < N; i++)
        finalCowArr[i] = finalCows[i] == '1';

    // Now simulate every cow doing this at every K to find the number of cows who could've done it and the bounds for K
    int lowerKBound = -9999999;
    int upperKBound = 9999999;
    int numPossibleCows = 0;

    for (int infected = 0; infected < N; infected++) {
        bool setLowerBound = false;
        bool incrementedPossibleCows = false;

        for (int K = 0; K <= T; K++) {
            bool initPopulation[N];
            int KCountPerCow[N];
            for (int i = 0; i < N; i++) {
                initPopulation[i] = i == infected;
                KCountPerCow[i] = 0;
            }
            
            // Simulate cow activity
            for (int t = 0; t < T; t++) {
                int firstShakeCow = firstShakeCows[t], secondShakeCow = secondShakeCows[t],
                firstShakeK = KCountPerCow[firstShakeCow - 1], secondShakeK = KCountPerCow[secondShakeCow - 1];

                if (initPopulation[firstShakeCow - 1] && firstShakeK < K) {
                    KCountPerCow[firstShakeCow - 1]++;
                    initPopulation[secondShakeCow - 1] = true;
                }
                if (initPopulation[secondShakeCow - 1] && secondShakeK < K) {
                    KCountPerCow[secondShakeCow - 1]++;
                    initPopulation[firstShakeCow - 1] = true;
                }

                // if (infected == 0 && K == 0) {
                //     cout << firstShakeCow << " " << secondShakeCow << " ";
                //     for (int l = 0; l < N; l++) {
                //         cout << initPopulation[l] << " ";
                //     }
                //     cout << endl;
                // }
            }
            // cout << endl;

            bool works = equalValues(initPopulation, finalCowArr, N);
            // cout << works << " " << infected + 1 << " " << K << endl;

            if (works) {
                if (!setLowerBound) {
                    lowerKBound = max(lowerKBound, K);
                    setLowerBound = true;
                }
                if (!incrementedPossibleCows) {
                    incrementedPossibleCows = true;
                    numPossibleCows++;
                }
            } else if (setLowerBound) {
                upperKBound = min(upperKBound, K - 1);
            }
        }
    }

    cout << numPossibleCows << " " << lowerKBound << " ";
    if (upperKBound == 9999999)
        cout << "Infinity";
    else cout << upperKBound;
}