// https://codeforces.com/problemset/problem/1991/E

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

struct node {
    int color = -1;
    vector<int> next;  
};
vector<node> graph;

// returns whether possible
bool color() {
    graph[0].color = 0;

    deque<int> todo;
    todo.push_back(0);
    while (!todo.empty()) {
        int cur = todo.front();
        todo.pop_front();

        for (int next : graph[cur].next) {
            if (graph[next].color != -1) {
                if (graph[next].color != !graph[cur].color) return false;
                continue;
            }
            graph[next].color = !graph[cur].color;
            todo.push_back(next);
        }
    }
    
    return true;
}

int main() {
    // Comment out for interactive problems
    // ios::sync_with_stdio(false);
	// cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        graph.clear();

        for (int i = 0; i < N; i++) graph.push_back({});
        for (int i = 0; i < M; i++) {
            int u, v; cin >> u >> v;
            u--, v--;
            graph[u].next.push_back(v);
            graph[v].next.push_back(u);
        }

        bool bob = color();
        if (bob) {
            cout << "Bob" << endl;

            vector<int> ones, zeros;
            for (int i = 0; i < N; i++) {
                if (graph[i].color == 1) ones.push_back(i);
                else zeros.push_back(i);
            }

            for (int i = 0; i < N; i++) {
                int a, b; cin >> a >> b;
                if (a > b) swap(a, b);
                if (a == 1) {
                    if (ones.empty()) {
                        cout << (zeros.back() + 1) << " " << b << endl;
                        zeros.pop_back();
                    } else {
                        cout << (ones.back() + 1) << " " << a << endl;
                        ones.pop_back();
                    }
                } else if (a == 2) {
                    if (zeros.empty()) {
                        cout << (ones.back() + 1) << " " << b << endl;
                        ones.pop_back();
                    } else {
                        cout << (zeros.back() + 1) << " " << a << endl;
                        zeros.pop_back();
                    }
                }
            }
        } else {
            cout << "Alice" << endl;

            for (int i = 0; i < N; i++) {
                cout << "1 2" << endl;
                int a, b; cin >> a >> b;
            }
        }
    }
}