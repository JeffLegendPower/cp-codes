// https://atcoder.jp/contests/abc373/tasks/abc373_e

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

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (plli a, plli b) {
        return a > b;
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
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M;
    ll K;
    cin >> N >> M >> K;

    M--;

    vector<ll> votes(N, -1);

    plli a[N];
    ll extra = K;

    for (int i = 0; i < N; i++) {
        cin >> a[i].first;
        extra -= a[i].first;
        
        a[i].second = i;
    }

    // handle M=N or M = N - 1 case

    sort(a, a + N, [](plli one, plli two) {
        return one.first > two.first;
    });

    ll pres[N + 1];
    pres[0] = 0;
    for (int i = 0; i < N; i++) pres[i + 1] = pres[i] + a[i].first;

    for (int i = 0; i < N; i++) {
        ll next = a[i].first + extra;

        int low = 0, high = N - 1;
        int best = N - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (a[mid].first > next) {
                low = mid + 1;
            } else {
                high = mid - 1;
                best = mid;
            }
        }

        // cout << "E";
        if (best > M) continue;

        low = 0, high = extra;
        best = extra;
        while (low <= high) {
            ll mid = low + (high - low) / 2;

            int lowidx = 0, highidx = N - 1;
            int bestidx = N - 1;
            while (lowidx <= highidx) {
                int mididx = lowidx + (highidx - lowidx) / 2;

                if (a[mididx].first > a[i].first + mid) {
                    lowidx = mididx + 1;
                } else {
                    highidx = mididx - 1;
                    bestidx = mididx;
                }
            }

            // ll after = M - bestidx;

            // ll diff = pres[M + 1] - pres[bestidx];
            ll diff = (M + 1 - bestidx) * (a[i].first + mid + 1) - (pres[M + 1] - pres[bestidx]);
            if (bestidx <= i && i < M + 1) {
                diff = pres[M + 2] - pres[bestidx];
                diff -= a[i].first;

                // cout << "E";

                diff = (M + 1 - bestidx) * (a[i].first + mid + 1) - diff;
            }

            // cout << a[i].first << " " << bestidx << " " << diff << " " << mid << endl;


            if (diff <= extra - mid) {
                low = mid + 1;
            } else {
                high = mid - 1;
                best = mid;
            }
        }

        votes[a[i].second] = best;
    }
    
    for (int i = 0; i < N; i++) cout << votes[i] << " ";
}