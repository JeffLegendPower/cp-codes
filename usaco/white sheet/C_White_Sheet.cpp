#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

#define ll unsigned long long

vector<ll> inter_area(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4) {
    vector<ll> inter_rect;
    inter_rect.push_back(max(x3, x1));
    inter_rect.push_back(max(y3, y1));
    inter_rect.push_back(min(x4, x2));
    inter_rect.push_back(min(y4, y2));
    // ll x = min(x4, x2) - max(x3, x1);
    // ll y = min(y4, y2) - max(y3, y1);
    // if (x < 0 || y < 0) return 0;
    // return 1ll* x * y;
    return inter_rect;
}

bool isValidRect(vector<ll> rect) {
    if (rect[2] >= rect[0] && rect[3] >= rect[1]) return true;
    return false;
}

int main() {
    ll x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;

    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5 >> x6 >> y6;

    ll area = (x2-x1)*(y2-y1);

    vector<ll> inter_area_1 = inter_area(x1, y1, x2, y2, x3, y3, x4, y4);
    vector<ll> inter_area_2 = inter_area(x1, y1, x2, y2, x5, y5, x6, y6);

    if (isValidRect(inter_area_1)) {
        area -= (inter_area_1[2] - inter_area_1[0]) * (inter_area_1[3] - inter_area_1[1]);
        vector<ll> black_inter = inter_area(inter_area_1[0], inter_area_1[1], inter_area_1[2], inter_area_1[3], x5, y5, x6, y6);
        if (isValidRect(black_inter)) area += (black_inter[2] - black_inter[0]) * (black_inter[3] - black_inter[1]);
    } if (isValidRect(inter_area_2)) {
        area -= (inter_area_2[2] - inter_area_2[0]) * (inter_area_2[3] - inter_area_2[1]);
    }
    // area -= inter_area_1;
    // area -= inter_area_2;
    cout << (area > 0 ? "YES" : "NO");
}