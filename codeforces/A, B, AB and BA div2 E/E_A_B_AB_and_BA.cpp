// https://codeforces.com/problemset/problem/2069/E

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

struct comp {
    bool operator() (const plli& a, const plli& b) const {
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
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        string s; cin >> s;
        int N = s.size();

        int a, b, ab, ba;
        cin >> a >> b >> ab >> ba;

        int extra = 0;
        vector<int> ababs, babas;

        int l = -1;
        int numa = 0, numb = 0;
        for (int i = 0; i < N; i++) {
            if (s[i] == 'A') numa++;
            else numb++;

            if (l == -1) l = i;
            if (i == N-1 || s[i+1] == s[i]) {
                if (s[i] == s[l]) {
                    extra += (i-l+1)/2;
                } else if (s[l] == 'A') {
                    ababs.push_back((i-l+1)/2);
                } else {
                    babas.push_back((i-l+1)/2);
                }

                l = -1;
            }
        }

        sort(ababs.begin(), ababs.end(), greater<int>());
        sort(babas.begin(), babas.end(), greater<int>());
        while (!ababs.empty() && ab) {
            int num = ababs.back();
            ababs.pop_back();
            if (ab >= num) {
                ab -= num;
                numa -= num;
                numb -= num;
            } else {
                num -= ab;
                numa -= ab;
                numb -= ab;
                ab = 0;
                ababs.push_back(num);
            }
        } while (!babas.empty() && ba) {
            int num = babas.back();
            babas.pop_back();
            if (ba >= num) {
                ba -= num;
                numa -= num;
                numb -= num;
            } else {
                num -= ba;
                numa -= ba;
                numb -= ba;
                ba = 0;
                babas.push_back(num);
            }
        }

        while (!ababs.empty() && ba) {
            int num = ababs.back();
            ababs.pop_back();
            if (ba >= num-1) {
                ba -= num-1;
                numa -= num-1;
                numb -= num-1;
            } else {
                num -= ba;
                numa -= ba;
                numb -= ba;
                ba = 0;
                ababs.push_back(num);
            }
        } while (!babas.empty() && ab) {
            int num = babas.back();
            babas.pop_back();
            if (ab >= num-1) {
                ab -= num-1;
                numa -= num-1;
                numb -= num-1;
            } else {
                num -= ab;
                numa -= ab;
                numb -= ab;
                ab = 0;
                ababs.push_back(num);
            }
        }

        if (ab) {
            int rem = min(extra, ab);
            ab -= rem;
            extra -= rem;
            numa -= rem;
            numb -= rem;
        } if (ba) {
            int rem = min(extra, ba);
            ba -= rem;
            extra -= rem;
            numa -= rem;
            numb -= rem;
        }

        if (numa <= a && numb <= b) {
            cout << "YES";
        } else cout << "NO";
        cout << endl;
    }
}