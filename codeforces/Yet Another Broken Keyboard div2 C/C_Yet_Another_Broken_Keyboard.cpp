// https://codeforces.com/problemset/problem/1272/C

// To get the number of contiguous substrings in a given string, we use the arithmetic sum (N*(N+1)/2)
// As there is only 1 substring of length N, 2 of length N - 1... N of length 1
// Since a substring can only contain letters given to us, we can split s into substrings that satisfy it
// And then take the sum of the number of substrings for each one

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


int main() {
    int N, K;
    cin >> N >> K;

    string s;
    cin >> s;

    set<char> allowed;
    for (int i = 0; i < K; i++) {
        char c;
        cin >> c;
        allowed.insert(c);
    }

    // Split into substrings
    vector<string> substrs;
    substrs.push_back("");
    for (int i = 0; i < N; i++) {
        char c = s[i];

        // If allowed, add to the current substring
        if (allowed.find(c) != allowed.end())
            substrs[substrs.size() - 1] += c;
        // Otherwise create a new substring
        else substrs.push_back("");
    }

    ll total = 0;
    for (string substr : substrs) {
        ll size = substr.size();
        total += size * (size + 1) / 2;
    }

    cout << total << endl;
}