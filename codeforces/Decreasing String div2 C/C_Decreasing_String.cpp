// https://codeforces.com/problemset/problem/1886/C

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

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        ll pos; cin >> pos;
        pos--;
        int N = s.size();

        int oper = 0;
        while (pos >= N - oper) {
            pos -= N - oper;
            oper++;
        }

        stack<int> st;
        vector<bool> rem(N, false);
        for (int i = 0; i < N; i++) {
            if (oper == 0) break;
            while (!st.empty() && s[i] - s[st.top()] < 0 && oper > 0) {
                rem[st.top()] = true;
                oper--;
                st.pop();
            }

            st.push(i);
        }

        while (oper > 0) {
            rem[st.top()] = true;
            st.pop();
            oper--;
        }

        int i = 0;
        for (; i < N; i++) {
            pos--;
            if (rem[i]) pos++;
            if (pos < 0) break;
        }

        cout << s[i];
    }
}