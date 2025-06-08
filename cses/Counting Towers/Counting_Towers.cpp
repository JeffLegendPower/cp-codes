// https://cses.fi/problemset/task/2413

// This was definitely a hard one
// First, let's try to solve for any one tower of height i
// We can start with having a tower on top of height 1 and the bottom will be the tower of height i - 1
// A tower of height 1 has 2 combinations, so we can start off by saying that h[i] = 2 * h[i - 1]
// However, there's more combinations to be found
// Now what if the top was of height 2, and the bottom of height i - 2
// And let's find all the combinations of the top, and the combinations of the bottom can be retrieved from towers of
// previous heights

// If the top was to be split horizontally anywhere (in this case only possible in the middle)
// Then we end up overcounting the case when the top was of height 1 and bottom of height i - 1
// So now our top part can't be fully split horizontally, which means that we can't have any blocks
// of width 2 in our top, as otherwise we would have to have a horizontal split
// Now to find the number of combinations of our top part, we have to look at the areas which there can be a
// horizontal split. We can't have a full one, but we could split either the left, right, or neither.
// And remember that we must always have a vertical split since we can't have any blocks of width 2
// Notice that there's 3 choices we can make for each splittable area, so the number of combinations is
// 3^(t - 1), where t is the height of the top part
// BUT.... there's one more combination, as we can NOT have a vertical split on the top part and have the top part
// be one single block, so there's actually 1 + 3^(t - 1) combinations
// And for the number of combinations of the bottom part, we can just get that from our dp array
// Now we can do this for all top parts from size 2 to i to generate all of our combinations

// Now to construct our equation for the number of combinations for a tower of height i
// The first term will be that of a top part of height 1, so h[i] = 2 * h[i - 1]
// The second term will be the sum of all bottom parts from heights 0 to i - 2 and top parts of heights i to heights 2
// That will look like
// SUM from k=0 to i - 2 OF (h[k] * (1 + 3^(i - k - 1)))
// So our formula is h[i] = 2 * h[i - 1] + SUM from k=0 to i - 2 OF (h[k] * (1 + 3^(i - k - 1)))

// However this runs in O(N) time to calculate just one height, but we can use DP to calculate this in O(1)
// the 2 * h[i - 1] term runs in O(1), so we don't have to worry about that
// In the sum, we can multiply out h[k] so now the body of the sum looks like h[k] + h[k] * 3^(i - k - 1)
// We can split the sum into 2 h[k] and h[k] * 3^(i - k - 1), the first sum can be easily calculated using
// prefix sums. The second one will require some manipulation. To do this, we will need to create a recursive
// formula for that sum, so we can calculate the ith term from the i-1th term in O(1) time
// First, take out the last term from the sum and add it seperately, so now the sum looks like
// 3 * h[i - 2] + 3 * SUM from k=0 to i - 3 OF (h[k] * 3^(i - k - 2))
// Now, we can calculate the sum from multiplying the previous sum by 3 and adding that to 3 * h[i - 2]
// Now that we can calculate h[i] in O(1) as long as all h from 0 to i - 1 are calculated
// We can solve this problem

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
    ll MOD = 1e9 + 7;

    vector<ll> heights;
    vector<ll> heightsprefix;
    vector<ll> sumstore;

    heights.push_back(1);
    heightsprefix.push_back(1);
    sumstore.push_back(heights[0] * 3);

    for (int i = 1; i <= 1e6; i++) {
        heights.push_back((2 * heights[i - 1]) % MOD);
        if (i >= 2) {
            heights[i] += heightsprefix[i - 2];
            heights[i] %= MOD;
            heights[i] += sumstore[i - 2];
            heights[i] %= MOD;
        }
        heightsprefix.push_back((heights[i] + heightsprefix.back()) % MOD);

        ll sumstorenext = (3 * heights[i]) % MOD;
        sumstorenext += (3 * sumstore.back()) % MOD;
        sumstorenext %= MOD;
        sumstore.push_back(sumstorenext);
    }

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        cout << heights[n] << endl;
    }
}