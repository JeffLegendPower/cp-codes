#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

#define ll long long

inline int maxCows(int xcoords[], int ycoords[], int N, int a, int b) {

    int firstQuad = 0;
    int secondQuad = 0;
    int thirdQuad = 0;
    int fourthQuad = 0;

    for (int i = 0; i < N; i++) {
        int x = xcoords[i];
        int y = ycoords[i];
        if (x > a) {
            if (y > b) {
                firstQuad++;
            }
            else {
                fourthQuad++;
            }
        } else {
            if (y > b) {
                secondQuad++;
            } else {
                thirdQuad++;
            }
        }
    }

    return max(max(firstQuad, secondQuad), max(thirdQuad, fourthQuad));
}

int main() {
    // freopen("balancing.in", "r", stdin);
    // freopen("balancing.out", "w", stdout);

    int N, B;
    cin >> N >> B;

    int xcoords[N];
    int ycoords[N];

    for (int i = 0; i < N; i++) {
        cin >> xcoords[i] >> ycoords[i];
    }

    int minMaxCows = 99999999;
    // a is the x wall, b is the y wall

    // int a_guess = avg(xcoords, N);
    // int b_guess = avg(ycoords, N);

    // if (a_guess % 2 == 1)
    //     a_guess--;
    // if (b_guess % 2 == 1)
    //     b_guess--;

    int minX = 999999999, maxX = -999999999, minY = 999999999, maxY = -999999999;
    
    for (int i = 0; i < N; i++) {
        minX = min(minX, xcoords[i]);
        minY = min(minY, ycoords[i]);
        maxX = max(maxX, xcoords[i]);
        maxY = max(maxY, ycoords[i]);
    }

    int avgX = (minX + maxX) / 2, avgY = (minY + maxY) / 2;
    if (avgX % 2 == 1) avgX--;
    if (avgY % 2 == 1) avgY--;

    int lastMaxCows = -1;
    // for (int a = minX; a < maxX; a += 2) {
    for (int i = 0; i < N; i++) {
        int a = xcoords[i] - 1;
        for (int j = 0; j < N; j++) {
            int b = ycoords[j] - 1;
            int maxCow = maxCows(xcoords, ycoords, N, a, b);
            minMaxCows = min(minMaxCows, maxCow);
            lastMaxCows = maxCow;
        }
    }

    cout << minMaxCows;
}