#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long

int main() {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int n, m;
        cin >> n >> m;
        int decks[n][m], deckSums[n];
        for (int N = 0; N < n; N++) {
            deckSums[N] = 0;
            for (int M = 0; M < m; M++) {
                cin >> decks[N][M];
                deckSums[N] += decks[N][M];
            }
        }

        int totalWinnings = 0;
        for (int first = 0; first < n; first++) {
            for (int second = first + 1; second < n; second++) {
                totalWinnings += abs(deckSums[first] - deckSums[second]);
                // for (int M = 0; M < m; M++) {
                //     totalWinnings += abs(decks[first][M] - decks[second][M]);
                // }
            }
        }

        cout << totalWinnings << endl;
    }
}