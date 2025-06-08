// https://codeforces.com/contest/1921/problem/G

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


int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, M, k;
        cin >> N >> M >> k;

        bool field[N][M];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char c;
                cin >> c;
                field[i][j] = c == '#';
            }
        }

        int pre[N + 1][M + 1];
        int rightuppre[N][M];
        int rightdownpre[N][M];
        for (int i = 0; i < N + 1; i++) {
            pre[i][0] = 0;
        } for (int j = 0; j < M + 1; j++) {
            pre[0][j] = 0;
        }

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + field[i - 1][j - 1];
            }
        }

        for (int j = 0; j < M; j++) {
            for (int i = 0; i < N; i++) {
                rightuppre[i][j] = field[i][j];
                if (i > 0) {
                    rightuppre[i][j] += rightuppre[i - 1][j];
                    if (j > 0) rightuppre[i][j] -= rightuppre[i][j - 1];
                } if (j > 0) rightuppre[i][j] += rightuppre[min(i + 1, N - 1)][j - 1];
            }
        }

        for (int j = 0; j < M; j++) {
            for (int i = N - 1; i >= 0; i--) {
                rightdownpre[i][j] = field[i][j];
                // cout << i << " " << j << endl;
                if (i < N - 1) {
                    rightdownpre[i][j] += rightdownpre[i + 1][j];
                    if (j > 0) rightdownpre[i][j] -= rightdownpre[i][j - 1];
                } if (j > 0) rightdownpre[i][j] += rightdownpre[max(i - 1, 0)][j - 1];
            }
        }


        int most = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // Try right-down
                int num = rightuppre[min(i + max(j + k - (M - 1), 0), N - 1)][min(j + k, M - 1)];
                if (j > 0) num -= rightuppre[min(i + k + 1, N - 1)][j - 1];
                num -= pre[i][min(j + k + 1, M)] - pre[i][j];
                most = max(most, num);

                // Try left-down
                num = pre[N][j + 1] - pre[i][j + 1] - pre[N][max(j - k, 0)] + pre[i][max(j - k, 0)];
                // cout << i << " " << j << " " << num << endl;
                if (j - max(i + k + 1 - (N - 1), 0) >= 0) num -= rightdownpre[min(i + k + 1, N - 1)][min(j - max(i + k + 1 - (N - 1), 0), M - 1)];
                // cout << i << " " << j << " " << num << endl;
                if (j - k > 0) num += rightdownpre[i][j - k - 1];
                most = max(most, num);

                // Try left-up
                num = pre[i + 1][j + 1] - pre[i + 1][max(j - k, 0)];
                if (j + min(0, i - k - 1) >= 0) num -= rightuppre[max(i - k - 1, 0)][j + min(0, i - k - 1)];
                if (j - k > 0) num += rightuppre[i][j - k - 1];
                most = max(most, num);

                // Try right-up
                num = rightdownpre[max(i - max(j + k - (M - 1), 0), 0)][min(j + k, M - 1)];
                // cout << i << " " << j << " " << num << endl;
                // cout << i << " " << j << " " << num << endl;
                if (j > 0) num -= rightdownpre[max(i - k - 1, 0)][j - 1];
                // cout << i << " " << j << " " << num << endl;
                // cout << i << " " << j << " " << num << endl;
                // if (i < N - 1) num -= pre[i + 2][min(j + k + 1, M)]
                num -= pre[N][min(j + k + 1, M)] - pre[i + 1][min(j + k + 1, M)] - pre[N][j] + pre[i + 1][j];
                most = max(most, num);

                // cout << i << " " << j << " " << num << endl;
                // cout << pre[N][min(j + k + 1, M)] << " " << pre[i + 1][min(j + k + 1, M)] << " " << pre[N][j] << " " << pre[i + 1][j] << endl;
            }
        }

        cout << most << endl;

        // cout << rightuppre[2][1] << " " << rightuppre[1][1] << " " << rightuppre[2][0] << endl;
    }
}