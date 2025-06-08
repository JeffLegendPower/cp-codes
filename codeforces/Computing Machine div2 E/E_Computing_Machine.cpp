// https://codeforces.com/contest/1978/problem/E

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define ll long long
#define plli pair<ll, int>
#define pll pair<ll, ll>
#define pii pair<int, int>
// Usage: FOR(i, 0, N) {...}
#define FOR(i, start, end) for(int i = start; i < end; i++)


struct comp {
    bool operator() (plli a, plli b) {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


// Segtree start
const int Nmax = 2e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];
pii range[2 * Nmax];

string a, b;

int oper(int a, int b) {
    return a + b;
}

int combine(int leftidx, int rightidx) {
    int num = t[leftidx] + t[rightidx];

    // if (range[i].second - range[i].first < 2) return num;

    if (range[leftidx].second - range[leftidx].first > 0 && a[range[leftidx].second] != '1') {
        // bool condition = b[range[leftidx].second - 1] == '1' && b[range[rightidx].first] == '1';
        bool conditionleft = b[range[leftidx].second - 1] == '1';
        bool conditionright = b[range[rightidx].first] == '1';
        if (range[leftidx].second - range[leftidx].first > 1 && a[range[leftidx].second - 2] == '0') conditionleft = true;
        if (range[rightidx].second - range[rightidx].first > 0 && a[range[rightidx].first + 1] == '0') conditionright = true;

        if (conditionleft && conditionright) num++;
    } if (range[rightidx].second - range[rightidx].first > 0 && a[range[rightidx].first] != '1') {
        // bool condition = b[range[leftidx].second - 1] == '1' && b[range[rightidx].first] == '1';
        bool conditionright = b[range[rightidx].first + 1] == '1';
        bool conditionleft = b[range[leftidx].second] == '1';
        if (range[rightidx].second - range[rightidx].first > 1 && a[range[rightidx].first + 2] == '0') conditionright = true;
        if (range[leftidx].second - range[leftidx].first > 0 && a[range[leftidx].second - 1] == '0') conditionleft = true;

        if (conditionleft && conditionright) num++;
    }

    return num;
}

int combineadd(int leftstart, int leftend, int rightstart, int rightend) {
    // cout << leftstart << " " << leftend << " " << rightstart << " " << rightend << endl;
    // int num = t[leftidx] + t[rightidx];

    // if (range[i].second - range[i].first < 2) return num;

    int num = 0;

    if (leftend - leftstart > 0 && a[leftend] != '1') {
        // bool condition = b[range[leftidx].second - 1] == '1' && b[range[rightidx].first] == '1';
        bool conditionleft = b[leftend - 1] == '1';
        bool conditionright = b[rightstart] == '1';
        // // cout << leftstart << " " << leftend << " " << rightstart << " " << rightend << endl;
        // cout << conditionright << " " << conditionleft << endl;
        // cout << b << endl;
        if (leftend - leftstart > 1 && a[leftend - 2] == '0') conditionleft = true;
        if (rightend - rightstart > 0 && a[rightstart + 1] == '0') conditionright = true;

        if (conditionleft && conditionright) {
            num++;
            if (rightend - rightstart > 1 && a[rightstart + 1] == '0') {
                bool condition1 = b[rightstart + 2] == '1';
                if (rightend - rightstart > 2 && a[rightstart + 3] == '0') condition1 = true;
                if (condition1) num++;
            }
        }
    } if (rightend - rightstart > 0 && a[rightstart] != '1') {
        // bool condition = b[range[leftidx].second - 1] == '1' && b[range[rightidx].first] == '1';
        bool conditionright = b[rightstart + 1] == '1';
        bool conditionleft = b[leftend] == '1';
        // cout << leftstart << " " << leftend << " " << rightstart << " " << rightend << endl;
        // cout << conditionright << " " << conditionleft << endl;
        if (rightend - rightstart > 1 && a[rightstart + 2] == '0') conditionright = true;
        if (leftend - leftstart > 0 && a[leftend - 1] == '0') conditionleft = true;

        if (conditionleft && conditionright) {
            num++;
            if (leftend - leftstart > 1 && a[leftend - 1] == '0') {
                bool condition1 = b[leftend - 2] == '1';
                if (leftend - leftstart > 2 && a[leftend - 3] == '0') condition1 = true;
                if (condition1) num++;
            }
        }
    } 
    if (leftend - leftstart > 1 && a[leftend - 1] == '0') {
        bool condition1 = b[leftend - 2] == '1';
        if (leftend - leftstart > 2 && a[leftend - 3] == '0') condition1 = true;
        if (condition1) {
            
        }
    }

    return num;
}

void build() {  // build the tree
    for (int i = N - 1; i > 0; --i) {
        t[i] = t[i<<1] + t[i<<1|1];

        int leftidx = i<<1;
        int rightidx = i<<1|1;
        if (range[i<<1|1].first < range[leftidx].first) {
            leftidx = i<<1|1;
            rightidx = i<<1;
        }

        range[i] = {
            range[leftidx].first,
            range[rightidx].second
        };

        // t[i] = combine(leftidx, rightidx);
        t[i] += combineadd(range[leftidx].first, range[leftidx].second, range[rightidx].first, range[rightidx].second);

        // if (range[i].second - range[i].first < 2) continue;

        // if (range[leftidx].second - range[leftidx].first > 0 && a[range[leftidx].second] != '1') {
        //     // bool condition = b[range[leftidx].second - 1] == '1' && b[range[rightidx].first] == '1';
        //     bool conditionleft = b[range[leftidx].second - 1] == '1';
        //     bool conditionright = b[range[rightidx].first] == '1';
        //     if (range[leftidx].second - range[leftidx].first > 1 && a[range[leftidx].second - 2] == '0') conditionleft = true;
        //     if (range[rightidx].second - range[rightidx].first > 0 && a[range[rightidx].first + 1] == '0') conditionright = true;

        //     if (conditionleft && conditionright) t[i]++;
        // } if (range[rightidx].second - range[rightidx].first > 0 && a[range[rightidx].first] != '1') {
        //     // bool condition = b[range[leftidx].second - 1] == '1' && b[range[rightidx].first] == '1';
        //     bool conditionright = b[range[rightidx].first + 1] == '1';
        //     bool conditionleft = b[range[leftidx].second] == '1';
        //     if (range[rightidx].second - range[rightidx].first > 1 && a[range[rightidx].first + 2] == '0') conditionright = true;
        //     if (range[leftidx].second - range[leftidx].first > 0 && a[range[leftidx].second - 1] == '0') conditionleft = true;

        //     if (conditionleft && conditionright) t[i]++;
        // }
    }
}

void modify(int p, int value) {  // set value at position p
    for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

int query(int l, int r) {  // on interval [l, r)
    int res = 0;
    int low = -1, high = -1;
    // {low, high, val}
    vector<vector<int>> blocks;

    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l&1) {
            cout << "1 " << range[l].first << " " << range[l].second << " " << t[l] << endl;
            blocks.push_back({range[l].first, range[l].second, t[l]});
            l++;
        } if (r&1) {
            // cout << r << endl;
            r--;
            blocks.push_back({range[r].first, range[r].second, t[r]});
            cout << "2 " << range[r].first << " " << range[r].second << " " << t[r] << endl;
        }
    }

    sort(blocks.begin(), blocks.end(), [](vector<int> one, vector<int> two) {
        return one[0] < two[0];
        // return true;
    });
    res = blocks[0][2];
    for (int i = 1; i < blocks.size(); i++) {
        res += blocks[i][2];
        res += combineadd(l, blocks[i - 1][1], blocks[i][0], blocks[i][1]);
    }
    return res;
}
// Segtree end


int main() {
    int T;
    cin >> T;

    while (T--) {
        cin >> N;

        cin >> a >> b;


        for (int i = N; i < 2 * N; i++) {
            t[i] = a[i - N] - '0'; // temp
            range[i] = {i - N, i - N};
            // cout << i << endl;
            // cout << range[i].first << " " << range[i].second << endl;
        }

        // cout << t[4] << endl;
        build();

        // cout << range[1].first << " " << range[1].second << endl;

        int Q;
        cin >> Q;

        // cout << t[1] << endl;
        
        // cout << query(0, 16);

        while (Q--) {
            int l, r;
            cin >> l >> r;

            cout << query(l - 1, r) << endl;
        }
    }
}