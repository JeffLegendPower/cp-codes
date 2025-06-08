#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

#define ll long long

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int N;
        cin >> N;
        ll boxes[N];
        for (int n = 0; n < N; n++)
            cin >> boxes[n];

        if (N == 1) {
            cout << 0 << endl;
            continue;
        }

        // sort boxes by size in ascending order
        // sort(boxes, boxes + (sizeof(boxes) / sizeof(boxes[0])));
        // cout << boxes[0] << endl;
        int maxdiff = 0;

        // test for all values of k (maybe will work good men)
        for (int k = 1; k <= N; k++) { // can ignore k = N because maxdiff will just be 0 then
            // if N isn't divisble by k we skip this one
            if (N % k != 0) continue;

            // group them into trucks
            int truckweights[N / k];
            for (int i = 0; i < N / k; i++)
                truckweights[i] = 0; // set to 0 default
            
            for (int i = 0; i < N; i++)
                truckweights[i / k] += boxes[i];

            int smallest = 9999999999, largest = -1;
            for (int i = 0; i < N / k; i++) {
                smallest = min(smallest, truckweights[i]);
                largest = max(largest, truckweights[i]);
            }

            // cout << largest << " " << smallest << endl;
            maxdiff = max(maxdiff, largest - smallest);
        }

        cout << maxdiff << endl;
    }
}