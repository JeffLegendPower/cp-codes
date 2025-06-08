// https://usaco.org/index.php?page=viewproblem2&cpid=648

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (const plli& a, const plli& b) const {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

int solve(stack<pii> &shape) {
    vector<int> left(101, 0), right(101, 0);
    int last = -1;
    while (!shape.empty()) {
        auto [num, len] = shape.top();
        shape.pop();
        if (num > last) right[num] += len;
        else left[num] += len;

        last = num;
    }

    int maxleft = 0, maxright = 0;
    for (int i = 0; i <= 100; i++) if (left[i]) maxleft = i;
    for (int i = 0; i <= 100; i++) if (right[i]) maxright = i;

    for (int i = 0; i < maxleft; i++) left[i+1] += left[i]/2;
    for (int i = 0; i < maxright; i++) right[i+1] += right[i]/2;
    
    vector<int> endd(101, 0);
    endd[maxleft] += left[maxleft];
    endd[maxright] += right[maxright];

    int most = 0;
    for (int i = 0; i < 100; i++) {
        endd[i+1] += endd[i]/2;
        if (endd[i+1]) most = i+1;
    }

    return most;
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    setIO("262144");

    int N; cin >> N;

    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];

    vector<pii> b;
    b.push_back({a[0], 1});
    for (int i = 1; i < N; i++) {
        if (a[i] == a[i-1]) b[b.size()-1].second++;
        else b.push_back({a[i], 1});
    }

    int M = b.size();

    stack<pii> shape;
    int best = 0;
    int t = 0;
    for (int i = 0; i < M; i++) {
        while (!shape.empty() && b[i].first > shape.top().first) {
            auto [num, len] = shape.top();
            if (len&1) {
                best = max(best, solve(shape));

                if (len/2 > 0) shape.push({num+1, len/2});
            } else {
                shape.pop();
                if (!shape.empty() && shape.top().first == num+1) {
                    pii bck = shape.top();
                    shape.pop();
                    shape.push({bck.first, bck.second + len/2});
                } else shape.push({num+1, len/2});
            }
        }

        if (!shape.empty() && shape.top().first == b[i].first) {
            pii bck = shape.top();
            shape.pop();
            shape.push({bck.first, bck.second + b[i].second});
        } else shape.push(b[i]);
    }

    best = max(best, solve(shape));

    cout << best;
}