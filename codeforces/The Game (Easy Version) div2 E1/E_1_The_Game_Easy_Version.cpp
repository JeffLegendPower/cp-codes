// https://codeforces.com/contest/2062/problem/E1

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

vector<vector<int>> graph;
vector<int> subtree;
vector<int> pos;

int k =0;
int eulertour(int v, int p, int &i) {
    subtree[v] = 1;
    pos[v] = i++;

    for (int x : graph[v]) if (x != p) {
        subtree[v] += eulertour(x, v, i);
    }

    return subtree[v];
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int T; cin >> T;
    while (T--) {
        int N;
        cin >> N;
        graph.clear();
        subtree.clear();
        pos.clear();

        graph.resize(N);
        subtree.resize(N);
        pos.resize(N);

        pii w[N];
        for (int i = 0; i < N; i++) {
            cin >> w[i].first;
            w[i].second = i;
        }

        for (int i = 0; i < N-1; i++) {
            int u, v; cin >> u >> v;
            u--, v--;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        int t = 0;
        eulertour(0, -1, t);

        sort(w, w+N, greater<pii>());

        // min and max pos of every node
        int minpos[N+1], maxpos[N+1];
        minpos[0] = 1e6;
        maxpos[0] = -1;

        // min and max pos of every node thats a win
        int minpos2[N+1], maxpos2[N+1];
        minpos2[0] = 1e6;
        maxpos2[0] = -1;

        vector<bool> win(N, false);
        int nodewin = -1;
        for (int i = 0; i < N; i++) {
            int v = w[i].second;
            int l = pos[v], r = l+subtree[v]-1;

            int i2 = 0;
            int low = 0, high = i-1;
            while (low <= high) {
                int mid = low+(high-low)/2;
                if (w[mid].first <= w[i].first) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                    i2 = mid+1;
                }
            }

            minpos[i+1] = min(minpos[i], pos[v]);
            maxpos[i+1] = max(maxpos[i], pos[v]);
            minpos2[i+1] = minpos2[i];
            maxpos2[i+1] = maxpos2[i];

            if (minpos[i2] >= l && maxpos[i2] <= r) {
                win[i] = false;
            }

            else if (minpos2[i2] >= l && maxpos2[i2] <= r) {
                win[i] = true;
                nodewin = v;
                break;

                minpos2[i+1] = min(minpos2[i], pos[v]);
                maxpos2[i+1] = max(maxpos2[i], pos[v]);
            }

            else win[i] = false;
        }

        cout << nodewin+1 << endl;
    }
}