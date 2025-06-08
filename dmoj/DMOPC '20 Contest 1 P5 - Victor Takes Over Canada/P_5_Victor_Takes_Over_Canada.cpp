// https://dmoj.ca/problem/dmopc20c1p5

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
const int Nmax = 5e5;  // limit for array size
int N;  // array size
int t[2 * Nmax];

void modify(int p, int value) {  // incr value at position p
  for (t[p += N] += value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}


const int N2max = 1e6;  // limit for array size
int N2;  // array size
pii t2[2 * N2max];

pii oper(pii a, pii b) {
    return (a.second < b.second ? a : b);
}

void build2() {  // build the tree
  for (int i = N2 - 1; i > 0; --i) t2[i] = oper(t2[i<<1], t2[i<<1|1]);
}

int query2(int l, int r) {  // on interval [l, r)
  pii res = {-1, 1e6};
  for (l += N2, r += N2; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper(res, t2[l++]);
    if (r&1) res = oper(res, t2[--r]);
  }
  return res.first;
}
// Segtree end

struct opr {
    int u;
    int idx;
    int pidx;
};
auto cmp1 = [](opr one, opr two) {
    return one.idx < two.idx;
}; auto cmp2 = [](opr one, opr two) {
    return one.idx > two.idx;
};
vector<set<opr, decltype(cmp1)>> opers1;
vector<set<opr, decltype(cmp2)>> opers2;

struct node {
    vector<int> next;

    int start, end;
    int time;
    int height;
};
node graph[500000];

int euler[1000000];
int timer = 0, timer2 = 0;
void euler_tour(int cur, int parent, int height) {
    graph[cur].start = timer++;
    graph[cur].height = height;
    graph[cur].time = timer2;
    euler[timer2++] = cur;

    for (int next : graph[cur].next) {
        if (next == parent) continue;
        euler_tour(next, cur, height + 1);
        euler[timer2++] = cur;
    }
    graph[cur].end = timer;
}

int lca(int u, int v) {
    int utime = graph[u].time, vtime = graph[v].time;
    return query2(min(utime, vtime), max(utime, vtime) + 1);
}

void updk(int k, int i) {
    auto itr1 = opers1[k].lower_bound({-1000000, graph[i].start, -1000000});
    auto itr2 = opers2[k].lower_bound({1000000, graph[i].start, 1000000});

    int p1height = (itr1 == opers1[k].end() ? 1e6 : graph[lca(itr1->u, i)].height);
    int p2height = (itr2 == opers2[k].end() ? 1e6 : graph[lca(itr2->u, i)].height);

    modify(graph[i].start, 1);
    int p = -1;
    if (p1height == p2height && p2height == 1e6) {
    } else if (p1height <= p2height) p = lca(itr1->u, i);
    else p = lca(itr2->u, i);

    int pstart = -1;
    if (p != -1) {
        modify(graph[p].start, -1);
        pstart = graph[p].start;
    }

    opers1[k].insert({i, graph[i].start, pstart});
    opers2[k].insert({i, graph[i].start, pstart});
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int K, M;
    cin >> N >> K >> M;

    int c[N];
    for (int i = 0; i < N; i++) cin >> c[i];
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].next.push_back(v);
        graph[v].next.push_back(u);
    }
    euler_tour(0, -1, 0);

    N2 = timer2;
    for (int i = 0; i < N2; i++) t2[N2 + i] = {euler[i], graph[euler[i]].height};
    build2();

    for (int i = 0; i <= K; i++) {
        opers1.push_back(set<opr, decltype(cmp1)>(cmp1));
        opers2.push_back(set<opr, decltype(cmp2)>(cmp2));
    }

    for (int i = 0; i < N; i++) {
        int k = c[i];
        updk(k, i);
    }

    cout << query(graph[0].start, graph[0].end) << endl;

    while (M--) {
        int t;
        cin >> t;

        if (t == 1) {
            int i, k;
            cin >> i >> k;
            i--;

            int oldk = c[i];
            auto itr1old = opers1[oldk].lower_bound({-1000000, graph[i].start, -1000000});
            auto itr2old = opers2[oldk].lower_bound({1000000, graph[i].start, 1000000});

            // cout << (itr1old == opers1[oldk].end()) << endl;

            if (itr1old->u == i) {
                modify(itr1old->idx, -1);
                if (itr1old->pidx != -1) modify(itr1old->pidx, 1);
                opers1[oldk].erase(*itr1old);
                opers2[oldk].erase(*itr2old);
            }

            c[i] = k;
            updk(k, i);

            cout << query(graph[0].start, graph[0].end) << endl;

        } else if (t == 2) {
            int u;
            cin >> u;
            u--;

            cout << u << " " << query(graph[u].start, graph[u].end) << endl;
        }
    }
}