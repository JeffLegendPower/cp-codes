// https://codeforces.com/problemset/problem/1838/D

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    string s;
    cin >> s;

    set<int> loww;
    set<int, greater<int>> highh;
    for (int i = 0; i < N; i++) {
        if ((i&1) && s[i] == '(') {
            loww.insert(i);
            highh.insert(i);
        } else if (((i^1)&1) && s[i] == ')') {
            loww.insert(i);
            highh.insert(i);
        }
    }

    while (Q--) {
        int i;
        cin >> i;
        i--;

        if (N % 2 == 1) {
            cout << "NO" << endl;
            continue;
        }

        s[i] = (s[i] == '(') ? ')' : '(';
        if (i&1) {
            if (s[i] == '(') {
                loww.insert(i);
                highh.insert(i);   
            } else {
                loww.erase(i);
                highh.erase(i);
            }
        } else {
            if (s[i] == ')') {
                loww.insert(i);
                highh.insert(i);
            } else {
                loww.erase(i);
                highh.erase(i);
            }
        }

        int minn = (loww.begin() == loww.end() ? 1e6 : *loww.begin());
        int maxx = (highh.begin() == highh.end() ? (1e6 + 1) : *highh.begin());

        if (minn == 1e6 && maxx == 1e6 + 1) {
            cout << "YES" << endl;
            continue;
        }

        bool works = (minn&1) && ((maxx^1)&1);
        cout << (works ? "YES" : "NO") << endl;
    }
}