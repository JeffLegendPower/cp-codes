// https://mirror.codeforces.com/contest/2001/problem/D

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
const int N2max = 1e6;  // limit for array size
int N2;  // array size
int t2[2 * N2max];

int oper2(int a, int b) {
    return max(a, b);
}

void build2() {  // build the tree
  for (int i = N2 - 1; i > 0; --i) t2[i] = oper2(t2[i<<1], t2[i<<1|1]);
}

void modify2(int p, int value) {  // set value at position p
  for (t2[p += N2] = value; p > 1; p >>= 1) t2[p>>1] = oper2(t2[p], t2[p^1]);
}

int query2(int l, int r) {  // on interval [l, r)
  int res = 0;
  for (l += N2, r += N2; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper2(res, t2[l++]);
    if (r&1) res = oper2(res, t2[--r]);
  }
  return res;
}

const int N3max = 1e6;  // limit for array size
int N3;  // array size
int t3[2 * N3max];

int oper3(int a, int b) {
    return min(a, b);
}

void build3() {  // build the tree
  for (int i = N3 - 1; i > 0; --i) t3[i] = oper3(t3[i<<1], t3[i<<1|1]);
}

void modify3(int p, int value) {  // set value at position p
  for (t3[p += N3] = value; p > 1; p >>= 1) t3[p>>1] = oper3(t3[p], t3[p^1]);
}

int query3(int l, int r) {  // on interval [l, r)
  int res = 1e6;
  for (l += N3, r += N3; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = oper3(res, t3[l++]);
    if (r&1) res = oper3(res, t3[--r]);
  }
  return res;
}


const int Nmax = 1e6;  // limit for array size
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

    int T;
    cin >> T;

    while (T--) {
        cin >> N;
        N2 = N;
        N3 = N;

        for (int i = 0; i < N; i++) t[N + i] = 0;
        build();

        int a[N];
        for (int i = 0; i < N; i++) {
            cin >> a[i];
            t2[N + i] = a[i];
            t3[N + i] = a[i];
        }
        build2();
        build3();

        int uniquesuff[N];
        uniquesuff[N - 1] = 1;
        set<int> unique;
        unique.insert(a[N - 1]);
        for (int i = N - 2; i >= 0; i--) {
            unique.insert(a[i]);
            uniquesuff[i] = unique.size();
        }
        int numunique = unique.size();

        // int maxpre[N];
        // int minpre[N];
        // maxpre[0] = a[0];
        // minpre[0] = a[0];
        // for (int i = 1; i < N; i++) {
        //     maxpre[i] = max(maxpre[i - 1], a[i]);
        //     minpre[i] = min(minpre[i - 1], a[i]);
        // }

        vector<int> lastidxs(N + 1, -1);
        for (int i = N - 1; i >= 0; i--) {
            if (lastidxs[a[i]] == -1) lastidxs[a[i]] = i;
        }

        vector<vector<int>> idxs(N + 1);
        for (int i = 0; i < N; i++) {
            idxs[a[i]].push_back(i);
        }

        vector<int> S;
        int target = numunique;
        int idx = 0;
        for (int i = 0; i < numunique; i++) {

            // which num to use
            int low = 1, high = N;
            int best = -1;
            int endidx = -1;
            // if (i == 3) {
            //     low = 7;
            //     high = 7;
            // }
            while (low <= high) {
                int mid = low + (high - low) / 2;

                // first idx >= this num if (i % 2 == 0) else first idx <= this num
                int lowidx = idx, highidx = N - 1;
                int bestidx = -1;
                while (lowidx <= highidx) {
                    int mididx = lowidx + (highidx - lowidx) / 2;
                    // if ((i % 2 == 0 && maxpre[mididx] >= mid) || (i % 2 == 1 && minpre[mididx] <= mid)) {
                    if ((i % 2 == 0 && query2(idx, mididx + 1) >= mid) || (i % 2 == 1 && query3(idx, mididx + 1) <= mid)) {
                        highidx = mididx - 1;
                        bestidx = mididx;
                    } else lowidx = mididx + 1;
                }

                if (bestidx == -1) {
                    if (i % 2 == 0) high = mid - 1;
                    else low = mid + 1;
                    continue;
                } if ((uniquesuff[bestidx] - query(bestidx, N)) < target) {
                    if (i % 2 == 0) high = mid - 1;
                    else low = mid + 1;
                }  else {
                    if (i % 2 == 0) low = mid + 1;
                    else high = mid - 1;
                    best = mid;
                    endidx = bestidx;
                    // if (i == 3) cout << mid << " " << bestidx << " " << query3(0, bestidx + 1) << endl;
                }
            }

            // cout << idx << " " << best << " " << endidx << endl;
            idx = endidx + 1;
            S.push_back(best);
            modify(lastidxs[best], 1);
            // cout << lastidxs[best] << " " << best << endl;
            target--;

            for (int cur : idxs[best]) {
                modify2(cur, 0);
                modify3(cur, 1e6);
            }
        }

        cout << S.size() << endl;
        for (int i = 0; i < S.size(); i++) cout << S[i] << " ";
        cout << endl;
    }
}