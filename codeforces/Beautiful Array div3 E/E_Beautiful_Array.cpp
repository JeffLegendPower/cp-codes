// https://codeforces.com/contest/1986/problem/E

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

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

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}
// Segtree end


struct ai {
    ll modk;
    ll divk;
};

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int N;
        ll k;
        cin >> N >> k;

        ai a[N];
        for (int i = 0; i < N; i++) {
            ll num;
            cin >> num;
            a[i].modk = num % k;
            a[i].divk = num / k;
        }

        sort(a, a + N, [](ai one, ai two) {
            if (one.modk == two.modk) return one.divk < two.divk;
            return one.modk < two.modk;
        });

        // for (int i = 0; i < N; i++) {
        //     cout << a[i].modk << " " << a[i].divk << endl;
        // }

        ll oper = 0;

        bool works = true;
        bool canrem = N % 2 == 1;

        for (int i = 0; i < N; i++) {
            int nummod = 0;
            for (int j = i; j < N; j++) {
                if (a[j].modk == a[i].modk) nummod++;
                else break;
            }

            if (nummod % 2 == 1) {
                if (!canrem) {
                    works = false;
                    break;
                }
                canrem = false;

                vector<ll> diff;
                vector<ll> oddpre;
                vector<ll> evenpre;
                oddpre.push_back(0);
                evenpre.push_back(0);
                for (int j = 0; j < nummod - 1; j++) {
                    diff.push_back(a[i + j + 1].divk - a[i + j].divk);

                    oddpre.push_back(oddpre[oddpre.size() - 1]);
                    evenpre.push_back(evenpre[evenpre.size() - 1]);

                    if (j % 2 == 0) oddpre[oddpre.size() - 1] += diff[j];
                    else evenpre[evenpre.size() - 1] += diff[j];
                }

                ll mincost = 1e18;
                for (int j = 0; j < nummod; j++) {
                    ll curcost = oddpre[j] + evenpre[nummod - 1] - evenpre[j];
                    mincost = min(mincost, curcost);
                }
                oper += mincost;
                // cout << nummod << endl;

                // for (ll di : oddpre) cout << di << " ";
                // cout << endl;

                i += nummod - 1;
                continue;
            }

            for (int j = 0; j < nummod; j += 2) {
                oper += a[i + j + 1].divk - a[i + j].divk;
            }
            i += nummod - 1;
            continue;
        }

        // for (int i = 0; i < N / 2; i++) {
        //     ll ai = a[i];
        //     ll bi = a[N - i - 1];

        //     if (ai % k != bi % k) {
        //         works = false;
        //         break;
        //     }

        //     ai = ai / k;
        //     bi = bi / k;
        //     oper += abs(ai - bi);
        // }

        cout << (works ? oper : -1) << endl;
    }
}