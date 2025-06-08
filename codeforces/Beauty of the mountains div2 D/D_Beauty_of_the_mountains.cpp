// https://codeforces.com/contest/1982/problem/D

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

        ll a[N][M];
        ll apre[N + 1][M + 1];
        bool b[N][M];
        ll sum = 0;

        for (int i = 0; i <= N; i++) apre[i][0] = 0;
        for (int i = 0; i <= M; i++) apre[0][i] = 0;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> a[i][j];
            }
        } for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char c;
                cin >> c;
                b[i][j] = c - '0';
                apre[i + 1][j + 1] = apre[i][j + 1] + apre[i + 1][j] - apre[i][j];

                if (b[i][j]) {
                    sum += a[i][j];
                    apre[i + 1][j + 1]++;
                } else {
                    sum -= a[i][j];
                    apre[i + 1][j + 1]--;
                }
            }
        }

        set<ll> diffs;
        for (int i = k; i <= N; i++) {
            for (int j = k; j <= M; j++) {
                diffs.insert(abs(apre[i][j] - apre[i - k][j] - apre[i][j - k] + apre[i - k][j - k]));
            }
        }

        // bitset<100000> test;

        sum = abs(sum);
        // cout << sum << " " << diffs.size() << endl;

        vector<ll> nums;
        for (auto itr = diffs.begin(); itr != diffs.end(); itr++) {
            nums.push_back(*itr);
        }

        ll gcdd = nums[nums.size() - 1];

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0)
                gcdd = gcd(gcdd, nums[i]);
        }

        if (gcdd == 0) {
            if (sum == 0) cout << "YES" << endl;
            else cout << "NO" << endl;
            continue;
        }
        if (sum % gcdd == 0) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
}