// https://cses.fi/problemset/task/1097

// I'm feeling quite proud that I managed to solve this problem very quickly

// Naively, this could be solved in O(2^n) by just testing all the possible ways
// the first player could make their moves. However, this is a DP problem that
// needs to be faster than O(2^n). Let's try to solve this with subarrays [l, r]
// Since both players are trying to maximize their score, for each subarray we will store
// the maximum score of the first and second person to access that subarray
// This will be denoted as {x, y} where x is the score increase of the first person to access the subarray
// and y is the score increase of the second person to access the subarray
// For subarrays [l, l], we can tell that the scores will look like {a[l], 0}
// For subarrays [l, l + 1], the first person to access it has 2 choices, take the first or last element
// and the score {x, y} of said subarray will be determined by the maximum score x achievable
// So if the first element is taken, {x, y} will look like {a[l] + scores[l + 1][l + 1].y, scores[l + 1][l + 1].x}
// As the second person to access subarray [l, l + 1] will be the first person to access the smaller subarray
// So they can maximize their score. The other option is to take the last element, and the score of [l, l + 1]
// will be determined by the max of x. We can keep doing this for all subarrays [l, l], then [l, l + 1]... [l, l + k]
// Until we have calculated {x, y} it for [0, N - 1]
// Our answer will be x, as player 1 are the first person to access [0, N - 1]

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


int main() {
    int N;
    cin >> N;

    ll a[N];
    for (int i = 0; i < N; i++) cin >> a[i];

    // pair<ll, ll>: score of first person to access subarray, score of second person to access subarray
    // Indices: Left bound of subarray, right bound of subarray (inclusive) [l, r]
    pll score[N][N];
    for (int len = 0; len < N; len++) {
        for (int left = 0; left < N; left++) {
            if (left + len >= N) break;
            if (len == 0) {
                score[left][left + len] = {a[left], 0};
                continue;
            }

            score[left][left + len] = {
                a[left] + score[left + 1][left + len].second,
                score[left + 1][left + len].first
            };

            if (a[left + len] + score[left][left + len - 1].second > score[left][left + len].first) {
                score[left][left + len] = {
                    a[left + len] + score[left][left + len - 1].second,
                    score[left][left + len - 1].first
                };
            }
        }
    }

    cout << score[0][N - 1].first;
}