// https://codeforces.com/contest/1972/problem/D2

// b * gcd(a, b) is a multiple of a + b
// There's 4 cases, when a and b are coprime (gcd(a, b) = 1)
// when b = a*n (gcd(a, b) = a)
// when a = b*n (gcd(a, b) = b)
// when a and b share some prime factors (1 < gcd(a, b) < min(a, b))
// When they're coprime, gcd(a, b) = 1, so b * 1 is a multiple of a + b
// => (a + b) | b
// However, this is not possible as both a and b are positive integers, so a + b > b
// resulting in a contradiction as a + b can't divide b

// Now if b = a*n
// We can subtitute a*n in for b and a in for gcd(a, b)
// a*n * a is a multiple of a + a*n
// => a(n + 1) | a^2 * n => n + 1 | a * n
// We can subtitute b back in so we get n + 1 | b

// Now if a = b*n
// We will substitute b*n for a and b for gcd(a, b)
// b * b is a multiple of b*n + b
// => b(n + 1) | b^2 => n + 1 | b

// Now if 1 < gcd(a, b) < min(a, b)
// We will substitute gcd(a, b) = k
// Note that a = k * x and b = k * y for some integers x and y
// So we will say that k * y * k is a multiple of k * x + k * y
// => k * (x + y) | k^2 * y
// Divide out a k, so now we have x + y | k * y
// a + b | b*k
// Now we must notice that x must be a multiple of y
// So, a must be a multiple of b

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


int main() {

}