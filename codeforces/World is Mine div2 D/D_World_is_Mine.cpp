// https://codeforces.com/contest/1987/problem/D

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
        int N;
        cin >> N;

        // number of each cake tastiness, size of group of cake with same tastiness
        int freq[N + 1], freq2[N + 1];
        for (int i = 0; i <= N; i++) {
            freq[i] = 0;
            freq2[i] = 0;
        }
        
        for (int i = 0; i < N; i++) {
            int ai;
            cin >> ai;
            freq[ai]++;
        }
        for (int i = 1; i <= N; i++) {
            cout << freq[i] << " ";
        }
        cout << endl;

        int num = 0;
        int last = 0;
        bool alice = false;
        while (true) {
            alice = !alice;

            if (alice) {
                bool found = false;
                for (int i = last + 1; i <= N; i++) {
                    if (freq[i] > 0) {
                        freq[i]--;
                        last = i;
                        num++;
                        found = true;
                        // cout << i << endl;
                        break;
                    }
                }
                if (!found) break;
            } else {
                // tastiness, number of cake
                vector<pii> possible; 
                int dist = 0;
                for (int i = last + 1; i < N; i++) {
                    if (freq[i] > 0) dist++;
                    if (freq[i] > 0 && freq[i] >= dist) possible.push_back({i, freq[i]});
                }
                sort(possible.begin(), possible.end(), [](pii one, pii two) {
                    return one.second < two.second;
                });
                vector<pii> plan;
                int totalnum = 0;
                for (pii cur : possible) {
                    if (totalnum + cur.second < )
                }


                int lookingforsize = 1e6;
                for (int i = last + 1; i <= N; i++) {
                    if (freq[i] > 0) {
                        lookingforsize = min(lookingforsize, freq[i]);
                    }
                }

                if (lookingforsize == 1e6) break;
                bool found = false;
                int dist = 0;
                for (int i = last + 1; i <= N; i++) {
                    if (freq[i] > 0) dist++;
                    if (freq[i] == lookingforsize && dist >= lookingforsize) {
                        freq[i]--;
                        cout << i << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    for (int i = N; i >= last + 1; i--) {
                        if (freq[i] == lookingforsize) {
                            freq[i]--;
                            found = true;
                            break;
                        }
                    }
                }

                if (!found) break;
            }
        }

        cout << num << endl;
    }
}