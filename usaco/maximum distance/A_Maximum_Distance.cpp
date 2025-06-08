#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

#define ll long long

inline ll lengthSquared(pair<int, int> one, pair<int, int> two) {
    return (two.first - one.first)*(two.first - one.first) + (two.second - one.second)*(two.second - one.second);
}

int main() {
    int N;
    cin >> N;

    vector<pair<int, int> > coordinates;

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        coordinates.push_back(make_pair(x, 0));
    }
    for (int i = 0; i < N; i++) {
        int y;
        cin >> y;
        coordinates[i].second = y;
    }

    ll longest = 0;
    for (int first = 0; first < N; first++) {
        for (int second = first + 1; second < N; second++) {
            ll length = lengthSquared(coordinates[first], coordinates[second]);
            // cout << length;
            // cout << "\n";
            longest = max(longest, length);
        }
    }
    cout << longest;
}