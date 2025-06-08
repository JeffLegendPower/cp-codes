// https://codeforces.com/contest/1847/problem/D

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
    bool operator() (int a, int b) {
        return a < b;
    }
};

typedef tree<int, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


// Segtree start
const int Nmax = 3e5;  // limit for array size
int N;  // array size
bool t[2 * Nmax];

int oper(int a, int b) {
    return a + b;
}

void build() {  // build the tree
  for (int i = N - 1; i > 0; --i) t[i] = t[i<<1] | t[i<<1|1];
}

void modify(int l, int r, bool value) {
  for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
    if (l&1) t[l++] |= value;
    if (r&1) t[--r] |= value;
  }
}

void push() {
  for (int i = 1; i < N; ++i) {
    t[i<<1] |= t[i];
    t[i<<1|1] |= t[i];
    t[i] = 0;
  }
}

int query(int p) {
  bool res = false;
  for (p += N; p > 0; p >>= 1) res |= t[p];
  return res;
}

// Segtree end


class DSU {
  private:
	vector<int> parents;
	vector<int> sizes;

  public:
    vector<int> next;
	DSU(int size) : parents(size), sizes(size, 1), next(size) {
		for (int i = 0; i < size; i++) { 
            parents[i] = i;
            next[i] = i;
        }
	}

	/** @return the "representative" node in x's component */
	int find(int x) {
		return parents[x] == x ? x : (parents[x] = find(parents[x]));
	}

	/** @return whether the merge changed connectivity */
	bool unite(int x, int y) {
		int x_root = find(x);
		int y_root = find(y);
		if (x_root == y_root) { return false; }

        // cant do rank optimization here, dsu will take logn time
		// if (sizes[x_root] < sizes[y_root]) { swap(x_root, y_root); }

		sizes[x_root] += sizes[y_root];
		parents[y_root] = x_root;
		return true;
	}

	/** @return whether x and y are in the same connected component */
	bool connected(int x, int y) { return find(x) == find(y); }
};


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, M, Q;
    cin >> N >> M >> Q;

    DSU dsu(N);

    string s;
    cin >> s;

    // order, idx
    vector<int> prior(N, -1);

    int curprior = 0;
    for (int i = 0; i < M; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;

        // int t = 0;
        for (int j = l; j <= r; j = dsu.next[dsu.find(j)]) {
            // if (t++ > 10) break;

            // int next = dsu.next[dsu.find(j)];
            // cout << j << " " << dsu.next[dsu.find(j)] << endl;
            if (prior[j] == -1) {
                prior[j] = curprior++;;

                if (j == N - 1) break;
                dsu.unite(j + 1, j);
            }

            // cout << j << " " << dsu.next[dsu.find(j)] << endl;
            if (j == N - 1) break;
            // j = next;
        }
    }

    ordered_set has;
    ordered_set nott;

    for (int i = 0; i < N; i++) {
        // cout << prior[i] << endl;
        if (prior[i] != -1) {
            if (s[i] == '1') {
                has.insert(prior[i]);
                // cout << "a " << prior[i] << endl;
            } else {
                nott.insert(prior[i]);
                // cout << "b " << prior[i] << endl;
            }
        }
    }

    // cout << cost << endl;
    // sort(prior.begin(), prior.end(), [](pii one, pii two) {
    //     return one
    // });

    // int low = 0, high = min(has.size(), nott.size()) - 1;
    //     int best = -1;
    //     while (low <= high) {
    //         int mid = low + (high - low) / 2;
    //         int val1 = *nott.find_by_order(nott.size() - 1 - mid);
    //         int val2 = *has.find_by_order(mid);
    //         // cout << mid << " " << val1 << " " << val2 << endl;

    //         if (val1 <= val2) {
    //             best = mid;
    //             low = mid + 1;
    //         } else high = mid - 1;
    //     }

    //     cout << best + 1 << endl;


    // edit 3=> prior[3] = 3

    while (Q--) {
        int x;
        cin >> x;

        if (s[x - 1] == '1') {
            s[x - 1] = '0';
            int priori = prior[x - 1];
            if (priori == -1) continue;
            has.erase(priori);
            nott.insert(priori);
        } else {
            s[x - 1] = '1';
            int priori = prior[x - 1];
            if (priori == -1) continue;
            nott.erase(priori);
            has.insert(priori);
        }

        // cout << has.size() << " " << nott.size() << endl;

        int low = 0, high = min(has.size(), nott.size()) - 1;
        int best = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int val1 = *nott.find_by_order(nott.size() - 1 - mid);
            int val2 = *has.find_by_order(mid);
            cout << mid << " " << val1 << " " << val2 << endl;

            if (val1 >= val2) {
                best = mid;
                low = mid + 1;
            } else high = mid - 1;
        }

        cout << best + 1 << endl;
    }

    // while (Q--) {
    //     int x;
    //     cin >> x;
    //     if (s[x - 1] == '1') {
    //         s[x - 1] = '0';
    //         if (query(x - 1)) cost++;
    //     } else {
    //         s[x - 1] = '1';
    //         if (query(x - 1)) cost--;
    //     }
    //     cout << cost << endl;
    // }
}