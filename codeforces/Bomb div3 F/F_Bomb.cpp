// https://codeforces.com/contest/1996/problem/F

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
    int T;
    cin >> T;

    while (T--) {
        int N, k;
        cin >> N >> k;

        pll ab[N];
        for (int i = 0; i < N; i++) cin >> ab[i].first;
        for (int i = 0; i < N; i++) cin >> ab[i].second;

        // First, get the # moves to use up all a and the score achievable from that
        ll totala = 0;
        ll moves = 0;
        for (int i = 0; i < N; i++) {
            ll time = ab[i].first / ab[i].second - 1ll;
            if (ab[i].first % ab[i].second > 0) time++;

            // time++;
            // cout << time << endl;

            moves += time;
            totala += (time + 1) * (ab[i].first + ab[i].first - time * ab[i].second) / 2;
        }

        cout << totala << endl;

        ll extra = 0;
        ll remextra = max(0ll, moves - k);

        pll ab2[N];
        for (int i = 0; i < N; i++) ab2[i] = ab[i];

        sort(ab, ab + N, [](pll one, pll two) {
            // ll diff1 = one.second, diff2 = two.second;
            // if (one.first < one.second) diff1 = one.first;
            // if (two.first < two.second) diff2 = two.first;

            // if (diff1 == diff2) return one.first < one.second;

            // return diff1 < diff2;

            return (one.first % one.second) < (two.first % two.second);
        });

        sort(ab2, ab2 + N, [](pll one, pll two) {
            // ll diff1 = one.second, diff2 = two.second;
            // if (one.first < one.second) diff1 = one.first;
            // if (two.first < two.second) diff2 = two.first;

            // if (diff1 == diff2) return one.first < one.second;

            // return diff1 < diff2;

            return one.second < two.second;
        });

        int left1 = 0, left2 = 0;
        while (remextra > 0) {
            if (left1 >= N) {
                // TODO
                continue;
            } if (left2 >= N) {
                // TODO
                continue;
            }

            ll diff1 = ab[left1].first % ab[left1].second;
            ll diff2 = ab2[left2].second;

            if (diff1 <= diff2) {
                if (diff1 == 0) {
                    left1++;
                    continue;
                } remextra--;
                extra += diff1;
                left1++;
                continue;
            }
            
            ll cnt = ab2[left2].first / ab2[left2].second;

            if (cnt <= remextra) {
                remextra -= cnt;
                extra += ab2[left2].second * cnt;
            }
        }
    }
}