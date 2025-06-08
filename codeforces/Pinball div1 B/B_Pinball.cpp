// https://codeforces.com/contest/1936/problem/B

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#pragma GCC optimize("O3")
#pragma GCC target("avx2")

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
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;
        
        string s;
        cin >> s;

        ll numleft[N], numright[N];
        ll distsleft[N], distsright[N];

        numleft[0] = s[0] == '<';
        numright[N - 1] = s[N - 1] == '>';
        distsleft[0] = 0, distsright[N - 1] = 0;

        for (ll i = 1; i < N; i++) {
            numleft[i] = numleft[i - 1] + (s[i] == '<');
            distsleft[i] = distsleft[i - 1] + i * (s[i] == '<');
        } for (ll i = N - 2; i >= 0; i--) {
            numright[i] = numright[i + 1] + (s[i] == '>');
            distsright[i] = distsright[i + 1] + (N - i - 1) * (s[i] == '>');
        }

        for (ll i = 0; i < N; i++) {
            int lefts = numleft[N - 1] - ((i > 0) ? numleft[i - 1] : 0);
            int rights = numright[0] - ((i < N - 1) ? numright[i + 1] : 0);

            bool left;
            if (s[i] == '>') left = lefts >= rights;
            else left = lefts > rights;

            ll time = 0;
            if (left) {
                time = distsright[0] - ((i < N - 1) ? distsright[i + 1] : 0);
                time -= (N - i - 1) * rights;
                time *= 2;

                int targetleft = (s[i] == '>') ? rights : (rights + 1);

                int low = i, high = N - 1;
                int best = N - 1;
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    int num = numleft[mid] - ((i > 0) ? numleft[i - 1] : 0);
                    
                    if (num >= targetleft) {
                        high = mid - 1;
                        best = mid;
                    } else low = mid + 1;
                }

                ll time2 = distsleft[best] - ((i > 0) ? distsleft[i - 1] : 0);
                time2 -= i * targetleft;
                time2 *= 2;
                
                time += time2;
                time += i + 1;
            } else {
                time = distsleft[N - 1] - ((i > 0) ? distsleft[i - 1] : 0);
                time -= i * lefts;
                time *= 2;

                int targetright = (s[i] == '<') ? lefts : (lefts + 1);

                int low = 0, high = i;
                int best = 0;
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    int num = numright[mid] - ((i < N - 1) ? numright[i + 1] : 0);

                    if (num >= targetright) {
                        low = mid + 1;
                        best = mid;
                    } else high = mid - 1;
                }

                ll time2 = distsright[best] - ((i < N - 1) ? distsright[i + 1] : 0);
                time2 -= (N - i - 1) * targetright;
                time2 *= 2;
                time += time2;
                time += N - i;
            }

            cout << time << " ";
        }
        cout << endl;
    }
}