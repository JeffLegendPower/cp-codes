// https://codeforces.com/contest/1979/problem/D

// This can just be solved by greedy
// From left to right I can iterate over the string and find the first sequence of 0s or 1s where
// the conditions aren't satisfied
// So I know I have to put p there to satisfy atleast those conditions
// And then I can just run through the string again and accounting the transformations by p
// If the new string is valid, I print p
// If not, then it's impossible and I print -1

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
        int N, k;
        cin >> N >> k;

        string s;
        cin >> s;

        int num = 0;
        char last = s[0];

        int p = 0;
        for (; p < N; p++) {
            if (s[p] == last) num++;
            else {
                last = s[p];
                if (num < k) {
                    p--;
                    break;
                } else if (num > k) {
                    p = p - k - 1;
                    break;
                }

                num = 1;
            }
        }
        
        num = 0;
        last = '.';

        bool works = true;
        for (int i = 0; i < N; i++) {
            int inew;
            if (i + p + 1 < N) inew = i + p + 1;
            else inew = p - (i + p + 1 - N);
            
            if (s[inew] == last) {
                num++;
                if (num > k) works = false;
            } else {
                last = s[inew];
                if (num != k && num > 0) {
                    works = false;
                }
                num = 1;
            }
        }

        if (num != k) works = false;
        cout << (works ? min(N, p + 1) : -1) << endl;
    }
}