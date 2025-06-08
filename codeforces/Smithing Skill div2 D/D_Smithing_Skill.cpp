// https://codeforces.com/contest/1989/problem/D

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

struct weap {
    ll a, b;
    ll diff;
};

ll ceil2(ll a, ll b) {
    ll c=a/b;
    if(a % b != 0) c++;
    return c;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    weap weaps[N];
    for (int i = 0; i < N; i++) {
        cin >> weaps[i].a;
    } for (int i = 0; i < N; i++) {
        cin >> weaps[i].b;
        weaps[i].diff = weaps[i].a - weaps[i].b;
    }

    ll metals[M];
    for (int i = 0; i < M; i++) cin >> metals[i];

    sort(weaps, weaps + N, [](weap one, weap two) {
        if (one.a == two.a) return one.diff > two.diff;
        return one.a < two.a;
    });

    ll smallestdiffs[weaps[N - 1].a];
    // ll smallestdiffs[1000000];
    ll exp[weaps[N - 1].a + 1];
    int aidx = 0;
    for (int i = 0; i < weaps[N - 1].a; i++) {
        while (weaps[aidx].a <= i + 1 && aidx < N - 1) {
            // smallestdiffs[i] = min
            aidx++;
        } if (aidx > 0 && weaps[aidx].a > i + 1) aidx--;
        if (weaps[aidx].a > i + 1) {
            smallestdiffs[i] = 1e18;
            continue;
        }
        smallestdiffs[i] = weaps[aidx].diff;
        // while (aidx < N - 1 && weaps[aidx + 1].a == weaps[aidx].a) {
        //     aidx++;
        //     smallestdiffs[i] = min(smallestdiffs[i], weaps[aidx].diff);
        // }
        if (i > 0) smallestdiffs[i] = min(smallestdiffs[i - 1], smallestdiffs[i]);
        // cout << smallestdiffs[i] << endl;
    }

    exp[0] = 0;
    for (int i = 1; i <= weaps[N - 1].a; i++) {
        ll diff = smallestdiffs[i - 1];
        if (diff > i) exp[i] = 0;
        else exp[i] = exp[i - diff] + 1;
        // cout << exp[i] << endl;
    }

    ll total = 0;
    // cout << weaps[N - 1].a << endl;
    for (ll metal : metals) {
        if (metal <= weaps[N - 1].a) {
            total += exp[metal] * 2;
            // cout << "E" << endl;
            continue;
        }
        ll more = metal - weaps[N - 1].a + 1;
        // cout << more << endl;
        ll xp = ceil2(more, smallestdiffs[weaps[N - 1].a - 1]);
        // cout << xp << endl;
        metal -= xp * smallestdiffs[weaps[N - 1].a - 1];
        total += xp * 2;
        total += exp[metal] * 2;
    }

    cout << total << endl;

    // for ()

    // for ()
}