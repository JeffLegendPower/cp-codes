// https://codeforces.com/contest/1858/problem/D

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
const int Nmax = 7e3;  // limit for array size
int N;  // array size
int t[2 * Nmax];

string s;

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

    int T;
    cin >> T;

    while (T--) {
        int N, k;
        cin >> N >> k;
        string s;
        cin >> s;

        ll most1s = 0, most0s = 0;
        ll ones = 0, zeros = 0;
        for (int i = 0; i < N; i++) {
            if (s[i] == '1') {
                ones++;
                zeros = 0;
            } else {
                zeros++;
                ones = 0;
            }
            // cout << ones << " " << zeros << endl;
            most1s = max(most1s, ones);
            most0s = max(most0s, zeros);
            // cout << most1s << " " << most0s << endl;
        }

        // cout << most1s << " " << most0s << endl;

        // how many 1's can we get if we have i 0's
        ll most0[N + 1], most1[N + 1];
        for (int i = 0; i <= N; i++) {
            most0[i] = -1;
            most1[i] = -1;
        }

        // set stuff to 0
        for (int l = 0; l < N; l++) {
            int best1 = 0;
            int streak1 = 0;
            for (int i = 0; i < l; i++) {
                if (s[i] == '1') streak1++;
                else streak1 = 0;
                best1 = max(best1, streak1);
            }

            vector<int> back;
            map<int, int> cnts;

            int streak2 = 0;
            for (int i = N - 1; i >= l; i--) {
                if (s[i] == '1') streak2++;
                else streak2 = 0;
                cnts[streak2]++;
                back.push_back(streak2);
            }

            int cost = 0;
            int cnt = 0;
            // for (int j = l - 1; j >= 0; j--) {
            //     if (s[j] == '0') cnt++;
            //     else break;
            // }
            for (int r = l; r < N; r++) {
                cnt++;
                if (s[r] == '1') cost++;
                if (cost > k) break;

                cnts[back.back()]--;
                if (cnts[back.back()] == 0) cnts.erase(back.back());
                ll streak1s = best1;
                if (cnts.size() > 0) streak1s = max(streak1s, (ll) cnts.rbegin()->first);
                back.pop_back();

                most0[cnt] = max(most0[cnt], streak1s);
            }
        } // set stuff to 1
        for (int l = 0; l < N; l++) {
            int best0 = 0;
            int streak0 = 0;
            for (int i = 0; i < l; i++) {
                if (s[i] == '0') streak0++;
                else streak0 = 0;
                best0 = max(best0, streak0);
            }

            vector<int> back;
            map<int, int> cnts;

            int streak2 = 0;
            for (int i = N - 1; i >= l; i--) {
                if (s[i] == '0') streak2++;
                else streak2 = 0;
                cnts[streak2]++;
                back.push_back(streak2);
            }

            int cost = 0;
            int cnt = 0;
            // for (int j = l - 1; j >= 0; j--) {
            //     if (s[j] == '1') cnt++;
            //     else break;
            // }
            for (int r = l; r < N; r++) {
                cnt++;
                if (s[r] == '0') cost++;
                if (cost > k) break;

                cnts[back.back()]--;
                if (cnts[back.back()] == 0) cnts.erase(back.back());
                ll streak0s = best0;
                if (cnts.size() > 0) streak0s = max(streak0s, (ll) cnts.rbegin()->first);
                back.pop_back();

                most1[cnt] = max(most1[cnt], streak0s);
            }
        }

        for (ll j = 1; j <= N; j++) {
            ll best = most1s + j * most0s;
            for (ll i = 0; i <= N; i++) {
                if (most0[i] != -1) best = max(best, j * i + most0[i]);
                if (most1[i] != -1) best = max(best, j * most1[i] + i);
            }
            cout << best << " ";
        }
        cout << endl;
    }
}