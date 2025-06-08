// https://codeforces.com/contest/1792/problem/D

// The main observation needed to solve this is that for any permutation p
// if p[i] = k, then q[k] = i. Secondly, we need to remember that we can
// represent a permutation p of size M with an array a of size M where the value a[i] of
// each index i is the index of i in p
// We can use these together and now look at a single q
// First make an array a representing the indices of the values of q
// to get beauty of 1, p[0] = a[1]. For a beauty of 2, the previous must be true and
// p[1] = a[2]. This continues up to a beauty of k. Now notice that we can describe the beauty
// of p * q as how much of the prefix of p = the prefix of a. So for each q we can find the maximum prefix for all p
// and for each p update it's maximum prefix. I did this by using a segment tree with max range updates to update
// all p. A trie could've been used to find the maximum prefix between each p and q, however I don't know how to use
// a trie so I sorted the permutations and used binary search on repeatedly while increasing the prefix
// and constricting the bounds for the valid permutations

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

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = max(t[i<<1], t[i<<1|1]);
}

void modify(int l, int r, int value) {
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) {
        t[l] = max(t[l], value);
        l++;
    } if (r&1) {
        r--;
        t[r] = max(t[r], value);
    }
  }
}

int query(int p) {
  int res = 0;
  for (p += N; p > 0; p >>= 1) res = max(res, t[p]);
  return res;
}

void push() {
  for (int i = 1; i < N; ++i) {
    t[i<<1] = max(t[i<<1], t[i]);
    t[i<<1|1] = max(t[i<<1|1], t[i]);
    t[i] = 0;
  }
}

// Segtree end

struct perm {
    vector<int> eles;
    int idx;
};

int main() {
    int T;
    cin >> T;

    while (T--) {
        int M;
        cin >> N >> M;

        memset(t, 0, sizeof(t));

        vector<perm> permutations;
        for (int i = 0; i < N; i++) {
            perm cur;
            cur.idx = i;
            permutations.push_back(cur);
            for (int j = 0; j < M; j++) {
                int k;
                cin >> k;
                permutations[i].eles.push_back(k);
            }
        }

        sort(permutations.begin(), permutations.end(), [M](perm one, perm two) {
            for (int i = 0; i < M; i++) {
                if (one.eles[i] < two.eles[i]) return true;
                else if (two.eles[i] < one.eles[i]) return false;
            }
            return false;
        });

        for (int i = 0; i < N; i++) t[N + i] = 0;
        build();

        for (int i = 0; i < N; i++) {
            int freq[M + 1];
            freq[0] = -1;
            for (int j = 0; j < M; j++) {
                freq[permutations[i].eles[j]] = j + 1;
            }

            int start = 0, end = N - 1;
            for (int j = 0; j < M; j++) {
                int target = freq[j + 1];


                int low = start, high = end;
                int best = 1e6;
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    if (permutations[mid].eles[j] >= target) {
                        high = mid - 1;
                        if (permutations[mid].eles[j] == target) best = min(best, mid);
                    } else if (permutations[mid].eles[j] < target) {
                        low = mid + 1;
                    }
                }
                start = best;

                low = start, high = end;
                best = -1;
                while (low <= high) {
                    int mid = low + (high - low) / 2;
                    if (permutations[mid].eles[j] > target) {
                        high = mid - 1;
                    } else if (permutations[mid].eles[j] <= target) {
                        low = mid + 1;
                        if (permutations[mid].eles[j] == target) best = max(best, mid);
                    }
                }

                end = best;
                if (start == 1e6 || end == -1) break;

                modify(start, end + 1, j + 1);
            }
        }

        push();

        int best[N];
        for (int i = 0; i < N; i++) {
            int val = t[N + i];
            int idx = permutations[i].idx;
            best[idx] = val;
        }

        for (int i = 0; i < N; i++) cout << best[i] << " ";
        cout << endl;
    }
}