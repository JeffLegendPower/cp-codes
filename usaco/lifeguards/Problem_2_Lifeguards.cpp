#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

pii subtractRanges(const pii& range1, const pii& range2) {
    // Check if range2 fully encompasses range1
    if (range1.first >= range2.first && range1.second <= range2.second) {
        return make_pair(-1, -1); // Return {-1, -1}
    }

    // Check for intersection
    if (range1.second < range2.first || range1.first > range2.second) {
        return range1; // No intersection, return range1 as is
    }

    // Calculate the remaining ranges after subtracting the intersection
    pii result;
    if (range1.first < range2.first) {
        result.first = range1.first;
        result.second = range2.first - 1;
    } else {
        result.first = range2.second + 1;
        result.second = range1.second;
    }

    return result;
}

int main() {
    freopen("lifeguards.in", "r", stdin);
    freopen("lifeguards.out", "w", stdout);

    int N;
    cin >> N;

    pii lifeguards[N];

    for (int i = 0; i < N; i++) {
        cin >> lifeguards[i].first >> lifeguards[i].second;
    }

    int maxLength = 0;
    // lifeguard to exclude
    for (int i = 0; i < N; i++) {
        vector<pii> ranges;

        int length = 0;

        for (int j = 0; j < N; j++) {
            if (j == i) continue;
            pii lifeguard = pii(lifeguards[j].first, lifeguards[j].second);


            for (int k = 0; k < ranges.size(); k++) {
                pii range = ranges[k];
                lifeguard = subtractRanges(lifeguard, range);
                if (lifeguard.first == -1) continue;
            }

            ranges.push_back(lifeguard);
            length += lifeguard.second - lifeguard.first;
        }
        maxLength = max(maxLength, length);
    }

    cout << maxLength;
}