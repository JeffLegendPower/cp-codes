// https://codeforces.com/contest/1956/problem/D

// For any segment [l, r], we can make the value of each element in the array
// equal to the number of elements in the segment via a little recursion
// So by operating on [l, r], we set the total value of that segment to (r - l + 1) * (r - l + 1)
// This also means that if we are operating on segments [l, r], [r, k]
// It's always better to operate on the segment [l, k]
// As the value of each element will be greater
// Since N <= 18, we can brute force every combination of elements which are worked on as there's
// only 2^18 combinations
// By doing that we can find which elements to operate on and therefore which segments to operate on
// Then we can generate the sequence of operations via recursion

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
const int Nmax = 1e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

int oper(int a, int b) {
    return a + b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = oper(t[i<<1], t[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = oper(t[p], t[p^1]);
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t[l++]);
    if (r&1) res = oper(res, t[--r]);
  }
  return res;
}
// Segtree end
vector<bool> best;
vector<bool> last;
vector<ll> a2;
ll maxSum = 0;

void bestSet(int N) {
    if (last.size() == N) {
        ll sum = 0;
        int first1 = -1;
        for (int i = 0; i < N; i++) {
            if (!last[i]) {
                sum += a2[i];
                if (first1 != -1) {
                    sum += (i - first1) * (i - first1);
                    first1 = -1;
                }
            } else if (first1 == -1) first1 = i;
        }
        if (first1 != -1) sum += (N - first1) * (N - first1);
        if (sum > maxSum) {
            maxSum = sum;
            best.clear();
            for (int i = 0; i < N; i++) best.push_back(last[i]);
        }
        return;
    }

    last.push_back(true);
    bestSet(N);
    last.pop_back();
    last.push_back(false);
    bestSet(N);
    last.pop_back();
}

// Always true: h - l >= 1
void writemexrange(int l, int h, vector<pii> &opers, vector<ll> &a) {
    vector<pii> prevopers;
    // if (a[l - 1] == 0) opers.push_back({l, l});
    for (int i = l; i <= h; i++) if (a[i - 1] == i - l) opers.push_back({i, i});
    // for (int i = l; i <= h; i++)

    prevopers.push_back({l, l});
    // if (a[l] != 1) {
        // prevopers.push_back({l, l + 1});
        // prevopers.push_back({l, l});
    // } 
    for (int i = l + 1; i <= h; i++) {
        // if (a[i - 1] != i - l) {
            prevopers.push_back({l, i});
            int size = prevopers.size();
            for (int j = 0; j < size - 1; j++) prevopers.push_back(prevopers[j]);
        // }
    }

    prevopers.push_back({l, h});
    for (pii oper : prevopers) opers.push_back(oper);
}

int main() {
    int N;
    cin >> N;

    vector<ll> a;
    ll pre[N + 1];
    pre[0] = 0;
    for (int i = 0; i < N; i++) {
        ll ai;
        cin >> ai;
        a.push_back(ai);
        a2.push_back(ai);
        pre[i + 1] = pre[i] + a[i];
    }

    vector<pii> mexoper;

    // for (int i = 0; i < N; i++) {
    //     ll biggestdiff = 0;
    //     ll jidx = -1;
    //     for (int j = i; j < N; j++) {
    //         ll len = j - i + 1;
    //         ll diff = len * len - pre[j + 1] + pre[i];
    //         if (diff > biggestdiff) {
    //             biggestdiff = diff;
    //             jidx = j;
    //         }
    //     }

    //     if (jidx == -1) continue;

    //     mexoper.push_back({i + 1, jidx + 1});

    //     for (int k = i; k <= jidx; k++) {
    //         a[k] = jidx - i + 1;
    //     } for (int k = i; k < N; k++) pre[k + 1] = pre[k] + a[k];

    //     i = jidx;

    //     // for (int j = N - 1; j >= i; j--) {
    //     //     int len = j - i + 1;
    //     //     if (pre[j + 1] - pre[i] >= len * len) continue;
    //     //     mexoper.push_back({i + 1, j + 1});

    //     //     for (int k = i; k <= j; k++) {
    //     //         a[k] = len;
    //     //     } for (int k = i; k < N; k++) pre[k + 1] = pre[k] + a[k];
    //     // }
    // }

    bestSet(N);
    vector<pii> opers;
    for (int i = 0; i < N; i++) {
        if (best[i] == 0) continue;
        int j = i;
        for (; j < N; j++) if (best[j] == 0) break;
        writemexrange(i + 1, j, opers, a2);
        i = j - 1;
    }

    // for (pii oper : mexoper) writemexrange(oper.first, oper.second, opers, a2);
    cout << maxSum << " " << opers.size() << endl;
    // // cout << mexoper[0].first << " " << mexoper[0].second << endl;
    for (pii oper : opers) cout << oper.first << " " << oper.second << endl;
    
}