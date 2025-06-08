// https://codeforces.com/problemset/problem/2003/D2

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

struct node {
    ll mexin, mexout;
    vector<int> next;
};
vector<node> graph;

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        graph.clear();

        int N;
        ll M;
        cin >> N >> M;

        map<int, int> mexins;
        for (int i = 0; i < N; i++) {
            int l; cin >> l;
            set<ll> a;
            int mexin = 0;
            for (int j = 0; j < l; j++) {
                ll ai; cin >> ai;
                a.insert(ai);
            } while (a.find(mexin) != a.end()) mexin++;

            int mexout = mexin + 1;
            while (a.find(mexout) != a.end()) mexout++;

            mexins[mexin]++;
            graph.push_back({mexin, mexout});
        }
        sort(graph.begin(), graph.end(), [](node one, node two) {
            return one.mexin > two.mexin;
        });

        // best outcome mex if coming in from x=i
        map<ll, ll> bestmexout;
        ll best = 0;
        for (int i = 0; i < N; i++) {
            ll mexin = graph[i].mexin, mexout = graph[i].mexout;
            bestmexout[mexin] = max({bestmexout[mexin], mexout, bestmexout[mexout]});

            best = max(best, mexin);
            if (mexins[mexin] > 1) best = max(best, bestmexout[mexin]);
        }

        ll total = best * (best + 1);
        total += (M - best) * (best + 1 + M) / 2;
        if (M < best) total = best * (M + 1);

        for (auto itr = bestmexout.begin(); itr != bestmexout.end(); itr++) {
            ll mexin = itr->first, mexout = itr->second;
            if (mexin > M) continue;

            if (mexout > max(best, mexin)) {
                total -= max(best, mexin);
                total += mexout;
            }
        }

        cout << total << endl;
    }
}