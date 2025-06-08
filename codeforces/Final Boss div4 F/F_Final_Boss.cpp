// https://codeforces.com/contest/1985/problem/F

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


struct attk {
    ll cooldown;
    ll time;
    int dmg;
};

class Compare {
    public:
    bool operator() (attk one, attk two) {
        return one.time > two.time;
    }
};

int main() {
    int T;
    cin >> T;

    while (T--) {
        int h, N;
        cin >> h >> N;

        // time left, dmg
        attk atk[N];
        for (int i = 0; i < N; i++) cin >> atk[i].dmg;
        for (int i = 0; i < N; i++) cin >> atk[i].cooldown;

        priority_queue<attk, vector<attk>, Compare> atks;
        for (int i = 0; i < N; i++) {
            atks.push({atk[i].cooldown, 1, atk[i].dmg});
        }

        ll time = 0;
        while (h > 0) {
            attk cur = atks.top();
            atks.pop();

            time = max(time, cur.time);
            h -= cur.dmg;

            atks.push({cur.cooldown, cur.time + cur.cooldown, cur.dmg});
        }

        cout << time << endl;
    }
}