#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

#define ll long long

// Make some checks to see if a branch is impossible to get a value out of and we should cut it
inline bool tooBigNum(int entries[], int length) {
    int max_entry = -1;
    int max_index = -1;
    for (int i = 1; i < length - 1; i++) { // Ignore corners
        if (entries[i] > max_entry) {
            max_entry = entries[i];
            max_index = i;
        }
        // max_entry = max(max_entry, entries[i]);
        // max_index = i;
    }

    // If this max number is > than the sum of numbers on either side, then it's impossible to get a set of equal numbers on this branch and we should cut it
    int leftSum = 0;
    int rightSum = 0;
    for (int i = 0; i < length; i++) {
        if (i < max_index)
            leftSum += entries[i];
        if (i > max_index)
            rightSum += entries[i];
    }

    // if (leftSum < max_entry || rightSum < max_entry) {
    //     cout << "MAX ENTRY CHECK: ";
    //     for (int i = 0; i < length; i++) {
    //         cout << entries[i] << " ";
    //     }
    //     cout << endl << max_entry << " " << max_index << endl;
        
    //     return true;
    // }
    return leftSum < max_entry || rightSum < max_entry;
}

inline bool equalEntries(int input[], int length) {
    int num = input[0];
    for (int i = 1; i < length; i++)
        if (input[i] != num) return false;
    return true;
}

// returns minimum ply to combine to get equal
inline int combine(int entries[], int length, int ply) {
    int minPly = 99999999;
    for (int i = 0; i < length - 1; i++) {

        // Combine entries with the start point
        int combinedEntries[length - 1];
        for (int j = 0; j < length; j++) {
            if (j - 1 == i) continue; // Skip the entry coming after the first one we combined
            int newJ = j <= i ? j : j - 1;
            combinedEntries[newJ] = entries[j];
            if (j == i) combinedEntries[newJ] += entries[j + 1]; // Add the next entry onto the new combined one
        }

        if (length - 1 == 1 || equalEntries(combinedEntries, length - 1)) return ply + 1;
        
        // int combined = combine(combinedEntries, length - 1, ply + 1);
        // if (combined < minPly) {
        //     minPly = combined;
        //     if (true) {
        //         for (int p = 0; p < length - 1; p++) {
        //             cout << combinedEntries[p] << " ";
        //         }
        //         cout << i << endl;
        //     }
        // }
        if (tooBigNum(combinedEntries, length - 1)) continue;
        minPly = min(minPly, combine(combinedEntries, length - 1, ply + 1));
    }

    return minPly;
}

int main() {

    int T;
    cin >> T;
    for (int j = 0; j < T; j++) {
        int N;
        cin >> N;
        int numsleeps[N];
        for (int i = 0; i < N; i++)
            cin >> numsleeps[i];

        // int min_modifications = N - 1;
        // if (equalEntries(numsleeps, N)) return 0;
        // combine(numsleeps, N, 0);
        if (equalEntries(numsleeps, N)) cout << 0 << endl;
        else {
            cout << combine(numsleeps, N, 0) << endl;
        }
    }
}