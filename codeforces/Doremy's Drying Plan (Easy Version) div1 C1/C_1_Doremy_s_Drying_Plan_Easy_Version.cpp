// https://codeforces.com/contest/1889/problem/C1

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
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, k;
        cin >> N >> M >> k;

        vector<int> citiespre[N];
        vector<pii> days(M);
        for (int i = 0; i < M; i++) {
            int l, r;
            cin >> l >> r;
            days[i] = {l - 1, r - 1};

            citiespre[l - 1].push_back(i + 1);
            if (r < N) citiespre[r].push_back(-(i + 1));
        }

        vector<pii> day2s(N, {-1, -1});
        vector<int> day1spre(N + 1);
        vector<int> day2spre(N + 2);
        ordered_set curdays;
        day1spre[0] = 0;
        day2spre[0] = 0;

        ll dry = 0;

        for (int i = 0; i < N; i++) {
            for (int day : citiespre[i]) {
                if (day > 0) curdays.insert(day);
                else curdays.erase(-day);
            }

            day1spre[i + 1] = day1spre[i];
            day2spre[i + 1] = day2spre[i];

            if (curdays.size() == 2) {
                day2s[i] = {*curdays.find_by_order(0), *curdays.find_by_order(1)};
                day2spre[i + 1]++;
            } else if (curdays.size() == 1) day1spre[i + 1]++;
            else if (curdays.size() == 0) dry++;
        }

        ll mostdry = 0;
        ll nextmostdry = 0;
        for (int i = 0; i < M; i++) {
            ll numdry = day1spre[days[i].second + 1] - day1spre[days[i].first];
            if (numdry >= mostdry) {
                nextmostdry = mostdry;
                mostdry = numdry;
            } else if (numdry > nextmostdry) nextmostdry = numdry;
        }

        ll best = mostdry + nextmostdry;
        for (int i = 0; i < N; i++) {
            if (day2s[i].first == -1) continue;
            int one = day2s[i].first - 1;
            int two = day2s[i].second - 1;
            
            ll numdry = 0;
            numdry += day1spre[days[one].second + 1] - day1spre[days[one].first];
            numdry += day1spre[days[two].second + 1] - day1spre[days[two].first];
            numdry += day2spre[min(days[one].second, days[two].second) + 1] - day2spre[max(days[one].first, days[two].first)];
            best = max(best, numdry);
        }

        cout << best + dry << endl;
    }
}