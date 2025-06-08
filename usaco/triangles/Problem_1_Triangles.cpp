#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

// inline int largestArea() {

// }

int main() {
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    int N;

    cin >> N;

    pair<int, int> points[N];

    for (int i = 0; i < N; i++) {
        cin >> points[i].first >> points[i].second;
    }

    int greatestArea = 0;

    for (int i = 0; i < N; i++) {
        pair<int, int> point = points[i];
        int greatestDistanceX = 0;
        int greatestDistanceY = 0;

        for (int j = 0; j < N; j++) {
            pair<int, int> point2 = points[j];
            // same x
            if (point.first == point2.first) {
                greatestDistanceY = max(greatestDistanceY, abs(point2.second - point.second));
            }
            // same y
            if (point.second == point2.second) {
                greatestDistanceX = max(greatestDistanceX, abs(point2.first - point.first));
            }
        }
        
        greatestArea = max(greatestArea, greatestDistanceX * greatestDistanceY);
    }

    cout << greatestArea;
}