#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main() {
    freopen("diamond.in", "r", stdin);
	freopen("diamond.out", "w", stdout);

    int N, K;
    cin >> N >> K;

    int diamonds[N];

    int maxDia = 0;
    for (int i = 0; i < N; i++) {
        cin >> diamonds[i];
        maxDia = max(maxDia, diamonds[i]);
    }

    int maxDiamonds = 0;
    for (int diamond = 0; diamond < maxDia; diamond++) {
        int numDiamonds = 0;
        for (int j = 0; j < N; j++) {
            if (diamonds[j] - diamond <= K && diamonds[j] - diamond >= 0) {
                numDiamonds++;
            }
        }
        maxDiamonds = max(maxDiamonds, numDiamonds);
    }

    cout << maxDiamonds;
}