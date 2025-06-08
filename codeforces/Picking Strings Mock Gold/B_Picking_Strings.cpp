// https://codeforces.com/gym/588594/problem/B

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


// problem go to hell
// motherfucker problems
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string a, b;
    cin >> a >> b;
    int N = a.size(), M = b.size();

    int bca[N+1], bcb[M+1];
    bca[0] = 0, bcb[0] = 0;

    int lastbca[N+1], lastbcb[M+1];
    lastbca[0] = -1, lastbcb[0] = -1;
    
    for (int i = 0; i < N; i++) {
        bca[i+1] = bca[i];
        lastbca[i+1] = lastbca[i];
        if (a[i] == 'B' || a[i] == 'C') {
            bca[i+1]++;
            lastbca[i+1] = i+1;
        }
    }
    
    for (int i = 0; i < M; i++) {
        bcb[i+1] = bcb[i];
        lastbcb[i+1] = lastbcb[i];
        if (b[i] == 'B' || b[i] == 'C') {
            bcb[i+1]++;
            lastbcb[i+1] = i+1;
        }
    }
    
    int Q; 
    cin >> Q;
    
    while (Q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        
        if (lastbca[r1] < l1) {
            if (lastbcb[r2] < l2 && (r1-l1 == r2-l2)) cout << 1;
            else {
                int tailb = r2 - lastbcb[r2];
                int bcheadb = bcb[r2] - bcb[l2-1];

                if (lastbcb[r2] == -1) tailb = r2 - l2 + 1;

                if (bcheadb&1) {
                    cout << 0;
                    continue;
                }

                int taila = r1 - l1 + 1;
                if (bcheadb == 0) {
                    if (taila >= tailb && (taila - tailb)%3 == 0) cout << 1;
                    else cout << 0;
                } else {
                    if (taila > tailb) cout << 1;
                    else cout << 0;
                }
            }
            continue;
        } if (lastbcb[r2] < l2) {
            if (lastbca[r1] < l1 && (r1-l1 >= r2-l2) && (r1-l1 - r2+l2)%3 == 0) cout << 1;
            else cout << 0;
            continue;
        }

        int taila = r1 - lastbca[r1];
        int tailb = r2 - lastbcb[r2];

        int bcheada = bca[r1] - bca[l1 - 1];
        int bcheadb = bcb[r2] - bcb[l2 - 1];

        if (bcheada > bcheadb) {
            cout << 0;
            continue;
        }

        if ((bcheadb - bcheada)%2 == 1) {
            cout << 0;
            continue;
        }

        if (taila >= tailb && (taila - tailb)%3 == 0) cout << 1;
        else if (taila > tailb && (bcheada < bcheadb || (taila - tailb)%3 == 0)) cout << 1;
        else cout << 0;
    }
    
    return 0;
}