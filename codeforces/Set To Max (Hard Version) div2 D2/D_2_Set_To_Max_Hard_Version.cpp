// https://codeforces.com/contest/1904/problem/D2

// We can check for each index to see if we can satisfy the condition
// For the obvious case if a[i] > b[i] it won't work
// Now, we will look to the left and to the right

// If we find our desired max, that's good
// However, in the direction we are going if we find an element a[j] too big then we can't use that direction
// As it will make the number too big
// Same if we cross another b[j] that's smaller than what we are looking for, we would be setting a[j] to
// a number too big, which would make that direction not work

// We do the above in O(N * log^2(N)) instead of O(N^2) by using a segtree which stores 
// the maximum a over an interval and the minimum b over an interval

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


// Segtree begin
const int Nmax = 2 * 1e5;  // limit for array size
pii t[2 * Nmax]; // { max a, min b }
int N;  // array size

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) {
    t[i].first = max(t[i<<1].first, t[i<<1|1].first);
    t[i].second = min(t[i<<1].second, t[i<<1|1].second);
  }
}

void modify(int p, pii value) {  // set value at position p
  for (t[p += N] = value; p > 1; p >>= 1) {
    t[p>>1].first = max(t[p].first, t[p^1].first);
    t[p>>1].second = min(t[p].second, t[p^1].second);
  }
}

pii query(int l, int r) {  // on interval [l, r)
  pii res = {0, 1e6};
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) {
        res.first = max(res.first, t[l].first);
        res.second = min(res.second, t[l++].second);
    } if (r&1) {
        res.first = max(res.first, t[--r].first);
        res.second = min(res.second, t[r].second);
    }
  }
  return res;
}
// Segtree end


int main() {
    int T;
    cin >> T;

    while (T--) {
        cin >> N;

        int a[N];
        int b[N];
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            t[N + i].first = a[i];
        } for (int i = 0; i < N; i++) {
            cin >> b[i];
            t[N + i].second = b[i];
        }

        build();

        bool works = true;

        for (int i = 0; i < N; i++) {
            if (a[i] == b[i]) continue;

            if (a[i] > b[i]) {
                works = false;
                break;
            }

            // Try for both directions
            // If both directions fail then it's not possible
            // Go through the segtree and find the smallest interval [x, i - 1] where max(a) over this interval = b[i]
            // Do this via binary search
            // If we can't find one, we fail this direction
            // If min(b) over this interval < b[i] then this also fails
            // Otherwise this direction works

            // First to the left
            int low = 0, high = i - 1;
            pii best = { -1, -1 };

            while (low <= high) {
                int mid = low + (high - low) / 2;
                pii res = query(mid, i);

                if (res.first == b[i]) best = res;
                if (res.first >= b[i]) {
                    low = mid + 1;
                } else high = mid - 1;
            }

            // This direction works!
            if (best.first == b[i] && best.second >= b[i]) {
                continue;
            }

            // If not, try to the right
            low = i + 1, high = N - 1;
            best = { -1, -1 };

            while (low <= high) {
                int mid = low + (high - low) / 2;
                pii res = query(i + 1, mid + 1);

                if (res.first == b[i]) best = res;
                if (res.first >= b[i]) {
                    high = mid - 1;
                } else low = mid + 1;
            }

            // If this direction doesn't work... fail it
            if (best.first != b[i] || best.second < b[i]) {
                works = false;
                break;
            }
        }

        cout << (works ? "YES" : "NO") << endl;
    }
}