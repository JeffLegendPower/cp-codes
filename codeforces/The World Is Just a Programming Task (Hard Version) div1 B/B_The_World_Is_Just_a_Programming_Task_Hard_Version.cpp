// https://codeforces.com/contest/1239/problem/B

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

int beauty(vector<char> &seq, int N) {
    int least = 0;
    int end = 0;
    for (int i = 0; i < N; i++) {
        if (seq[i] == '(') end++;
        else end--;
        least = min(least, end);
    }

    int total = least >= 0;
    // if (least >= 0) cout << N << endl;
    for (int i = N - 1; i > 0; i--) {
        if (seq[i] == '(') least++;
        else least--;
        total += least >= 0;
        // if (least >= 0) cout << i << endl;
    }
    return total;
}

int main() {
    int N;
    cin >> N;

    vector<char> seq;
    
    for (int i = 0; i < N; i++) {
        char c;
        cin >> c;
        seq.push_back(c);
    }

    cout << beauty(seq, N) << endl;

    int basebeauty = beauty(seq, N);
    int onebeauty = -1;
    pii oneidx;
    int twobeauty = -1;
    pii twoidx;


    for (int i = 0; i < N; i++) {
        if (seq[i] == '(' && i % 2 == 1) {
            oneidx.first = i + 1;
            for (int j = i + 1; j < N; j++) {
                if (seq[j] == ')' && j % 2 == 0) {
                    oneidx.second = j + 1;
                    swap(seq[i], seq[j]);
                    onebeauty = beauty(seq, N);
                    swap(seq[i], seq[j]);
                    break;
                }
            }
            break;
        } else if (seq[i] == ')' && i % 2 == 0) {
            oneidx.first = i + 1;
            for (int j = i + 1; j < N; j++) {
                if (seq[j] == '(' && j % 2 == 1) {
                    oneidx.second = j + 1;
                    swap(seq[i], seq[j]);
                    onebeauty = beauty(seq, N);
                    swap(seq[i], seq[j]);
                    break;
                }
            }
            break;
        }
    }

    for (int i = 0; i < N; i++) {
        if (seq[i] == '(' && i % 2 == 0) {
            twoidx.first = i + 1;
            for (int j = i + 1; j < N; j++) {
                if (seq[j] == ')' && j % 2 == 1) {
                    twoidx.second = j + 1;
                    swap(seq[i], seq[j]);
                    twobeauty = beauty(seq, N);
                    swap(seq[i], seq[j]);
                    break;
                }
            }
            break;
        } else if (seq[i] == ')' && i % 2 == 1) {
            twoidx.first = i + 1;
            for (int j = i + 1; j < N; j++) {
                if (seq[j] == '(' && j % 2 == 0) {
                    twoidx.second = j + 1;
                    swap(seq[i], seq[j]);
                    twobeauty = beauty(seq, N);
                    swap(seq[i], seq[j]);
                    break;
                }
            }
            break;
        }
    }

    if (basebeauty >= onebeauty && basebeauty >= twobeauty) {
        cout << basebeauty << endl;
        cout << "1 1";
    } else if (onebeauty >= basebeauty && onebeauty >= twobeauty) {
        cout << onebeauty << endl;
        cout << oneidx.first << " " << oneidx.second;
    } else {
        cout << twobeauty << endl;
        cout << twoidx.first << " " << twoidx.second;
    }
}