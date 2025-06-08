#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

// (x1, y1) will be > than (x2, y2) if they dont intersect
vector<int> inter_rect(vector<int> s1, vector<int> s2) {
	int bl_a_x = s1[0], bl_a_y = s1[1], tr_a_x = s1[2], tr_a_y = s1[3];
	int bl_b_x = s2[0], bl_b_y = s2[1], tr_b_x = s2[2], tr_b_y = s2[3];

    vector<int> inter_rect(4);
    inter_rect[0] = max(bl_a_x, bl_b_x);
    inter_rect[1] = max(bl_a_y, bl_b_y);
    inter_rect[2] = min(tr_a_x, tr_b_x);
    inter_rect[3] = min(tr_a_y, tr_b_y);
    return inter_rect;
}

int main() {
    freopen("billboard.in", "r", stdin);
    freopen("billboard.out", "w", stdout);

    int ax1, ay1, ax2, ay2, bx1, by1, bx2, by2;

    cin >> ax1 >> ay1 >> ax2 >> ay2 >> bx1 >> by1 >> bx2 >> by2;
    vector<int> lawnmower;
    lawnmower.push_back(ax1);
    lawnmower.push_back(ay1);
    lawnmower.push_back(ax2);
    lawnmower.push_back(ay2);

    vector<int> cowfeed;
    cowfeed.push_back(bx1);
    cowfeed.push_back(by1);
    cowfeed.push_back(bx2);
    cowfeed.push_back(by2);

    vector<int> intersection_area = inter_rect(lawnmower, cowfeed);

    int area = (lawnmower[2] - lawnmower[0]) * (lawnmower[3] - lawnmower[1]);

    // if (intersection_area[0] == lawnmower[0] && intersection_area[2] == lawnmower[2] && 
    // (intersection_area[1] == lawnmower[1] || intersection_area[3] == lawnmower[3])) {
    //     area -= (intersection_area[2] - intersection_area[0]) * (intersection_area[3] - intersection_area[1]);
    // } else if (intersection_area[1] == lawnmower[1] && intersection_area[3] == lawnmower[3] &&
    // (intersection_area[0] == lawnmower[0] || intersection_area[2] == lawnmower[2])) {
    //     area -= (intersection_area[2] - intersection_area[0]) * (intersection_area[3] - intersection_area[1]);
    // }
    int num_side_touched = 0;
    int sides = 4;
    while (sides--) {
        if (intersection_area[sides] == lawnmower[sides]) {
            num_side_touched++;
        }
    }
    if (num_side_touched >= 3) {
        area -= (intersection_area[2] - intersection_area[0]) * (intersection_area[3] - intersection_area[1]);
    }

    cout << area;
    return 0;
}