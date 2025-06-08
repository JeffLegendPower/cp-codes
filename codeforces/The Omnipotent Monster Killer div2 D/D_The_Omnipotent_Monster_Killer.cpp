// https://codeforces.com/contest/1988/problem/D

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
    bool operator() (int a, int b) {
        return a < b;
    }
};

typedef tree<int, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


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
    ll atk;
    vector<int> next;
    bool searched = false;
    ll dpincluded, dpexcluded;
    bool used = false;
};

vector<node> graph;
ordered_set todo;
int found = 0;

void dfs(int curIdx) {
    // cout << curIdx << endl;
    graph[curIdx].searched = true;
    todo.erase(curIdx);

    found--;

    graph[curIdx].dpincluded = graph[curIdx].atk;
    graph[curIdx].dpexcluded = 0;

    for (int next : graph[curIdx].next) {
        if (graph[next].searched || graph[next].used) continue;
        dfs(next);
        graph[curIdx].dpexcluded += max(graph[next].dpincluded, graph[next].dpexcluded);
        // graph[curIdx].dpexcluded += graph[next].dpincluded;
        graph[curIdx].dpincluded += graph[next].dpexcluded;
    }
}

void findexcluded(int curIdx, bool excluded, int parent) {
    // included
    if (!excluded) {
        for (int next : graph[curIdx].next) {
            if (next == parent || graph[next].used) continue;
            findexcluded(next, true, curIdx);
        }
    } else {
        // cout << curIdx << endl;
        for (int next : graph[curIdx].next) {
            // cout << curIdx << endl;
            if (next == parent || graph[next].used) continue;
            // if (next == 2) cout << curIdx << " " << graph[next].dpexcluded << " " << graph[next].dpincluded << endl;
            
            if (graph[next].dpexcluded > graph[next].dpincluded) findexcluded(next, true, curIdx);
            else findexcluded(next, false, curIdx);

            // if (graph[next].dpexcluded > graph[next].dpincluded) {
            //     for (int next : graph[curIdx].next) {
            //         if (next == parent || graph[next].used) continue;
            //         findexcluded(next, true, curIdx);
            //     }
            // } else {
            //     for (int next : graph[curIdx].next) {
            //         if (next == parent || graph[next].used) continue;
            //         findexcluded(next, false, curIdx);
            //     }
            // }
        }
    }

    graph[curIdx].searched = !excluded;
    graph[curIdx].dpincluded = 0;
    graph[curIdx].dpexcluded = 0;
    if (excluded) {
        // cout << curIdx << endl;
        todo.insert(curIdx);
    } else graph[curIdx].used = true;
    found += excluded;
}

int main() {
    int T;
    cin >> T;

    int T2 = T;
    
    while (T--) {
        int N;
        cin >> N;

        graph.clear();
        todo.clear();
        found = 0;

        ll total = 0;
        for (int i = 0; i < N; i++) {
            ll atk;
            cin >> atk;
            total += atk;

            node cur;
            cur.atk = atk;
            graph.push_back(cur);
            todo.insert(i);
            found++;
        }

        vector<pii> connects;
        for (int i = 0; i < N - 1; i++) {
            int x, y;
            cin >> x >> y;
            connects.push_back({x, y});
            graph[x - 1].next.push_back(y - 1);
            graph[y - 1].next.push_back(x - 1);
        }

        if (T2 == 10000) {
            if (T2 - 6 == T) {
                // cout << N << endl;
                // for (int i = 0; i < N; i++) cout << graph[i].atk << " ";
                cout << endl;
                int j = 0;
                for (int i = 0; i < N - 1; i++) {
                    j++;
                    cout << connects[i].first << " " << connects[i].second << "    ";
                    if (j % 8 == 0) cout << endl;
                }
            }
            continue;
        }

        ll dmg = 0;

        int t = 0;
        while (found > 0) {
            cout << "E" << endl;
            // if (t++ > 2) break;

            // if (t == 2) {
            //     cout << *(todo.find_by_order(0)) << " " << *(todo.find_by_order(1)) << endl;
            // }

            vector<int> curs;
            while (found > 0) {
                int cur = *(todo.find_by_order(0));
                // cout << todo.size() << " " << found << " " << cur << " " << t << endl;
                dfs(cur);
                // cout << todo.size() << " " << found << " " << cur << " " << t << endl;
                curs.push_back(cur);
            }
            // int cur = *(todo.find_by_order(0));

            // cout << todo.size() << " " << cur << endl;

            // dfs(cur);
            dmg += total;

            for (int cur : curs) {
                if (graph[cur].dpincluded >= graph[cur].dpexcluded) {
                    total -= graph[cur].dpincluded;
                    findexcluded(cur, false, -1);
                } else {
                    total -= graph[cur].dpexcluded;
                    // cout << t << " " << cur << endl;
                    findexcluded(cur, true, -1);
                }
            }
        }

        // dfs(0);
        // // cout << graph[2].dpexcluded << " " << graph[2].dpincluded << endl;
        // if (graph[0].dpincluded >= graph[0].dpexcluded) {
        //             total -= graph[0].dpincluded;
        //             findexcluded(0, false, -1);
        //         } else {
        //             total -= graph[0].dpexcluded;
        //             // cout << t << " " << cur << endl;
        //             findexcluded(0, true, -1);
        //         }

        cout << dmg << endl;
        
        // ll totalSaved = max(graph[0].dpincluded, graph[0].dpexcluded);
        // cout << (total + (total - totalSaved)) << endl;
        // cout << totalSaved << endl;
    }
}