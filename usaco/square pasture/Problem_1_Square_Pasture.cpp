#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct Rect {
	int x1, y1, x2, y2;
	int area() { return (y2 - y1) * (x2 - x1); }
};

int main() {
    freopen("square.in", "r", stdin);
	freopen("square.out", "w", stdout);

    Rect a, b;
    cin >> a.x1 >> a.y1 >> a.x2 >> a.y2 >> b.x1 >> b.y1 >> b.x2 >> b.y2;

    int length = max(max(a.x2, b.x2) - min(a.x1, b.x1), max(a.y2, b.y2) - min(a.y1, b.y1));
    cout << pow(length, 2);
    return 0;
}