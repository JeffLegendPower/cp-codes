// https://codeforces.com/contest/1986/problem/D

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

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

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) res += t[l++];
    if (r&1) res += t[--r];
  }
  return res;
}
// Segtree end


ll least;
string s;

// string expr;
vector<ll> expr;
void dfs(int idx, int tens) {
    if (idx == N) {
        ll res = 0;

        for (int i = 0; i < expr.size(); i++) {
            res += expr[i];
        }

        least = min(least, res);

        // cout << res << endl;

        // cout << expr << endl;
        return;
    }

    // if (idx > 0) expr += '+';
    if (idx > 0) expr.push_back(1);

    // expr += s[idx];
    ll num = s[idx] - '0';
    // expr[expr.size() - 1] *= num;

    if (idx == tens) {
        num *= 10;
        num += s[idx + 1] - '0';
        expr[expr.size() - 1] *= num;

        dfs(idx + 2, tens);

        expr[expr.size() - 1] /= num;

    } else {
        expr[expr.size() - 1] *= num;

        dfs(idx + 1, tens);

        expr[expr.size() - 1] /= num;
    }

    if (idx > 0) expr.pop_back();


    // expr += s[idx];
    expr[expr.size() - 1] *= num;

    if (idx == tens) {
        // expr += s[idx + 1];
        dfs(idx + 2, tens);
        // expr.pop_back();

    } else dfs(idx + 1, tens);

    expr[expr.size() - 1] /= num;

    // expr.pop_back();

    // if (idx > 0) expr.pop_back();
}


int main() {
    int T;
    cin >> T;

    while (T--) {
        cin >> N;
        cin >> s;
        // expr = "";

        // if (N < 4) {
        // expr.clear();
        // expr.push_back(1);

        // least = 1e18;

        // // brute force

        // // which number is  2 digit
        // for (int i = 0; i < N - 1; i++) {
        //     dfs(0, i);
        // }

        // // cout << most << endl;

        // // dfs(0, 0);
        // cout << least << endl;
        // continue;
        // }

        if (N == 2) {
            ll num = s[0] - '0';
            num *= 10;
            num += s[1] - '0';
            cout << num << endl;
            continue;
        }

        if (N == 3) {
            if (s[0] == '0' || s[2] == '0') {
                cout << 0 << endl;
                continue;
            }

            if (s[1] == '0') {
            ll num = s[2] - '0';

            if (num == 1) {
                cout << s[0] << endl;
                continue;
            }

            if (s[0] != '1') num += s[0] - '0';

            cout << num << endl;
            continue;
            }

            // ll num1 = (s[0] - '0') * 10 + s[1] - '0';
            // if (s[2] != '1') num1 += s[2] - '0';

            // ll num2 = (s[1] - '0') * 10 + s[2] - '0';
            // if (s[0] != '1') num1 += s[0] - '0';

            // cout << min(num1, num2) << endl;
            // continue;
        }

        bool has0 = false;
        for (char c : s) if (c == '0') has0 = true;

        if (has0) {
            cout << 0 << endl;
            continue;
        }

        ll mintotal = 1e18;

        for (int i = 0; i < N - 1; i++) {
            ll total = 0;
            for (int j = 0; j < N; j++) {
                ll num = s[j] - '0';
                if (j == i) {
                    j++;
                    num *= 10;
                    num += s[j] - '0';
                }

                if (num > 1) total += num;
            }
            mintotal = min(mintotal, total);
        }

        cout << mintotal << endl;
    }
}