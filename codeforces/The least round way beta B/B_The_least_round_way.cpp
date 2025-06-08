// https://codeforces.com/contest/2/problem/B

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;
typedef pair<int, int> pii;

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


// Number of times a number is divisible by 2 and 5
int numdiv2(ll num) {
    int div = 0;
    while (num % 2 == 0) {
        div++;
        num /= 2;
    }
    return div;
} int numdiv5(ll num) {
    int div = 0;
    while (num % 5 == 0) {
        div++;
        num /= 5;
    }
    return div;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    cin >> N;

    // pii diva[N][N];
    int diva2[N][N], diva5[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ll ai;
            cin >> ai;
            diva2[i][j] = numdiv2(ai);
            diva5[i][j] = numdiv5(ai);
        }
    }

    int dp2[N][N], dp5[N][N];
    char backtrack2[N][N], backtrack5[N][N];
    dp2[0][0] = diva2[0][0];
    dp5[0][0] = diva5[0][0];
    backtrack2[0][0] = '.';
    backtrack5[0][0] = '.';

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0 && j == 0) continue;
            if (i == 0) {
                backtrack2[i][j] = 'R';
                backtrack5[i][j] = 'R';
                dp2[i][j] = dp2[i][j - 1] + diva2[i][j];
                dp5[i][j] = dp5[i][j - 1] + diva5[i][j];
            } else if (j == 0) {
                backtrack2[i][j] = 'D';
                backtrack5[i][j] = 'D';
                dp2[i][j] = dp2[i - 1][j] + diva2[i][j];
                dp5[i][j] = dp5[i - 1][j] + diva5[i][j];
            } else {
                int right2 = dp2[i][j - 1], down2 = dp2[i - 1][j];
                int right5 = dp5[i][j - 1], down5 = dp5[i - 1][j];

                if (right2 <= down2) {
                    dp2[i][j] = right2 + diva2[i][j];
                    backtrack2[i][j] = 'R';
                } else {
                    dp2[i][j] = down2 + diva2[i][j];
                    backtrack2[i][j] = 'D';
                } if (right5 <= down5) {
                    dp5[i][j] = right5 + diva5[i][j];
                    backtrack5[i][j] = 'R';
                } else {
                    dp5[i][j] = down5 + diva5[i][j];
                    backtrack5[i][j] = 'D';
                }
            }
        }
    }

    vector<char> seq;

    if (dp2[N - 1][N - 1] <= dp5[N - 1][N - 1]) {
        cout << dp2[N - 1][N - 1] << endl;
        int i = N - 1, j = N - 1;
        while (i > 0 || j > 0) {
            char back = backtrack2[i][j];
            seq.push_back(back);
            if (back == 'R') j--;
            else i--;
        }
    } else {
        cout << dp5[N - 1][N - 1] << endl;
        int i = N - 1, j = N - 1;
        while (i > 0 || j > 0) {
            char back = backtrack5[i][j];
            seq.push_back(back);
            if (back == 'R') j--;
            else i--;
        }
    }
    for (int i = seq.size() - 1; i >= 0; i--) cout << seq[i];
}