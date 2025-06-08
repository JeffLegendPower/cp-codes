// https://atcoder.jp/contests/abc363/tasks/abc363_c

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

int K;
string s = "";
ll countt = 0;

bool valid() {
    if (K % 2 == 1) {
        for (int i = K / 2; i < N - K / 2; i++) {
            bool validhere = false;
            for (int j = 0; j <= K / 2; j++) {
                if (s[i - j] != s[i + j]) {
                    validhere = true;
                    break;
                }
            }
            if (!validhere) return false;
        }
    } else {
        for (int i = K / 2 - 1; i < N - K / 2; i++) {
            bool validhere = false;
            for (int j = 0; j < K / 2; j++) {
                if (s[i - j] != s[i + j + 1]) {
                    validhere = true;
                    break;
                }
            }
            if (!validhere) return false;
        }
    }

    return true;
}

int freq[26];
void test(int idx) {
    if (idx == N) {
        countt += valid();
        return;
    }
    for (int i = 0; i < 26; i++) {
        if (freq[i] == 0) continue;
        freq[i]--;
        s += 'a' + i;
        test(idx + 1);
        s.pop_back();
        freq[i]++;
    }
}

int main() {
    cin >> N >> K;

    string S;
    cin >> S;

    // N = 3;
    // K = 2;
    // s = "aab";

    // cout << valid();

    for (int i = 0; i < 26; i++) freq[i] = 0;
    for (int i = 0; i < N; i++) freq[S[i] - 'a']++;

    test(0);
    cout << countt;

    // ll total = 1;
    // ll fact[11];
    // fact[0] = 1;
    // fact[1] = 1;
    // for (ll i = 2 ; i <= N; i++) {
    //     total *= i;
    //     fact[i] = fact[i - 1] * i;
    // }

    // int freq[26];

    // ll remove = 0;
    // for (int i = 0; i < 26; i++) {
    //     total /= fact[freq[i]];
        
    // } 
}