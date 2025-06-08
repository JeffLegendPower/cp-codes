#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

inline int indexOf(char arr[], char element, int count, int size) {
    int count2 = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == element) {
            if (count2 == count) return i;
            count2++;
        }
    }
    return -1;
}

int main() {

    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);

    char points[52];

    for (int i = 0; i < 52; i++) {
        cin >> points[i];
    }

    int pairs = 0;
    for (int i = 0; i < 26; i++) {
        char currentLetter = i + 65;
        int index = indexOf(points, currentLetter, 0, 52);
        int followingLetters[26];

        for (int i = 0; i < 26; i++) {
            followingLetters[i] = 0;
        } 

        for (int j = index + 1; j < 52; j++) {
            char letter = points[j];
            if (letter == currentLetter) break;

            if (followingLetters[letter - 65] == 0) {
                // cout << currentLetter;
                // cout << " ";
                // cout << letter;
                // cout << "\n";
                followingLetters[letter - 65] = 1;
            }
        }
        // cout << "\n";

        int index2 = indexOf(points, currentLetter, 1, 52);
        // cout << index;
        // cout << " ";
        // cout << index2;
        // cout << "\n";

        for (int j = index2 + 1; j < 52; j++) {
            char letter = points[j];

            if (followingLetters[letter - 65] == 1) {
                // cout << currentLetter;
                // cout << " ";
                // cout << letter;
                // cout << "\n";
                followingLetters[letter - 65] = 2;
            }
        }

        for (int j = 0; j < 26; j++) {
            if (followingLetters[j] == 2) {
                pairs++;
            }
        }
    }

    cout << pairs;
}