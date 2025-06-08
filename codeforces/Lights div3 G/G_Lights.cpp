// https://codeforces.com/problemset/problem/1907/G

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


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;

        bool s[N];
        int a[N];
        vector<int> in(N, 0);
        for (int i = 0; i < N; i++) {
            char c; cin >> c;
            s[i] = c == '1';
        } for (int i = 0; i < N; i++) {
            cin >> a[i];
            a[i]--;
            in[a[i]]++;
        }

        vector<int> oper;

        vector<int> todo;
        vector<bool> done(N, false);
        for (int i = 0; i < N; i++) if (in[i] == 0) todo.push_back(i);
        while (!todo.empty()) {
            int i = todo.back();
            todo.pop_back();
            
            done[i] = true;

            if (s[i]) {
                s[i] = false;
                s[a[i]] ^= 1;
                oper.push_back(i + 1);
            }

            in[a[i]]--;
            if (in[a[i]] == 0) todo.push_back(a[i]);
        }

        // deal with cycles
        bool works = true;
        for (int i = 0; i < N; i++) {
            if (done[i]) continue;

            int x = i;
            vector<int> next1;

            bool stop = false;
            while (!done[x]) {
                done[x] = true;

                if (!stop) next1.push_back(x);

                x = a[x];
                if (s[x]) stop ^= 1;
                if (stop && done[x]) works = false;
            }

            stop = true;
            vector<int> next2;
            while (done[x]) {
                done[x] = false;

                if (!stop) next2.push_back(x);

                x = a[x];
                if (s[x]) stop ^= 1;
            }

            while (!done[x]) {
                done[x] = true;
                x = a[x];
            }

            if (next1.size() < next2.size()) {
                for (int x : next1) oper.push_back(x + 1);
            } else for (int x : next2) oper.push_back(x + 1);
        }

        if (!works) {
            cout << -1 << endl;
            continue;
        }

        cout << oper.size() << endl;
        for (int x : oper) cout << x << " ";
        cout << endl;
    }
}