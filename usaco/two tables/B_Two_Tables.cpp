#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

#define ll long long

int main() {
    cout << fixed << setprecision(9);
    int t;
    cin >> t;
    while (t--) {
        ll W, H, x1, y1, x2, y2, w, h;
        cin >> W >> H >> x1 >> y1 >> x2 >> y2 >> w >> h;

        ll tableWidth = x2 - x1;
        ll tableHeight = y2 - y1;

        bool enoughWidth = W - tableWidth >= w;
        bool enoughHeight = H - tableHeight >= h;

        if (!enoughWidth && !enoughHeight) {
            cout << -1;
            cout << "\n";
            continue;
        }

        double yDiff = enoughHeight ? h - max(y1, H - y2) : 0; // 2 - max(1, 5 - 4)
        double xDiff = enoughWidth ? w - max(x1, W - x2) : 0; // 4 - max(2, 8 - 7)
        
        if (yDiff < 0) yDiff = 0;
        if (xDiff < 0) xDiff = 0;

        // cout << yDiff;
        // cout << " ";
        // cout << xDiff;
        // cout << "\n";

        cout << (sqrt((xDiff*xDiff) + (yDiff*yDiff)));
        cout << "\n";
    }
}