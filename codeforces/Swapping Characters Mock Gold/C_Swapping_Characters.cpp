// https://codeforces.com/gym/588594/problem/C

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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int uid(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }
ll uld(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

void setIO(string s) {
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

struct comp {
    bool operator() (const plli& a, const plli& b) const {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;


vector<string> ss;
int K, N;

string test4(vector<int> &idxs, bool dup) {
    for (int a = 0; a < 4; a++) {
        for (int b = 0; b < 4; b++) {
            if (b == a) continue;
            for (int c = 0; c < 4; c++) {
                if (c == b || c == a) continue;
                for (int d = 0; d < 4; d++) {
                    if (d == c || d == b || d == a) continue;

                    string cur = ss[0];
                    cur[idxs[a]] = ss[0][idxs[0]];
                    cur[idxs[b]] = ss[0][idxs[1]];
                    cur[idxs[c]] = ss[0][idxs[2]];
                    cur[idxs[d]] = ss[0][idxs[3]];

                    int num = 0;
                    for (int i = 0; i < K; i++) {
                        int diff = N;
                        for (int j = 0; j < N; j++) {
                            if (ss[i][j] == cur[j]) diff--;
                        }

                        if (diff == 2 || (diff == 0 && dup)) num++;
                    }

                    if (num == K) return cur;
                }
            }
        }
    }

    return "";
}

string test3(vector<int> &idxs, bool dup) {
    for (int a = 0; a < 3; a++) {
        for (int b = 0; b < 3; b++) {
            if (b == a) continue;
            for (int c = 0; c < 3; c++) {
                if (c == b || c == a) continue;

                string cur = ss[0];
                cur[idxs[a]] = ss[0][idxs[0]];
                cur[idxs[b]] = ss[0][idxs[1]];
                cur[idxs[c]] = ss[0][idxs[2]];

                int num = 0;
                for (int i = 0; i < K; i++) {
                    int diff = N;
                    for (int j = 0; j < N; j++) {
                        if (ss[i][j] == cur[j]) diff--;
                    }

                    if (diff == 2 || (diff == 0 && dup)) num++;
                }

                if (num == K) return cur;
            }
        }
    }

    return "";
}

int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    cin >> K >> N;

    // if valid string exists, every string will have matching chars for all but at most 4
    // if 0 not match (all identical), then swap any 2 indices of one of the strings and done
    // if 1 unmatch, i dont think possible
    // if 2 unmatch, iterate through all other match chars and try permutations of that and these 2 chars
    // if 3 unmatch, try permutations of the 3 chars
    // if 4 unmatch, try all permutations of the 4 chars

    ss.resize(K);
    for (int i = 0; i < K; i++) cin >> ss[i];

    vector<int> charcnt(26, 0);
    for (int i = 0; i < N; i++) charcnt[ss[0][i] - 'a']++;
    for (int k = 1; k < K; k++) {
        vector<int> charcnt2(26, 0);
        for (int i = 0; i < N; i++) {
            charcnt2[ss[k][i] - 'a']++;
        }
        
        for (int i = 0; i < 26; i++) if (charcnt2[i] != charcnt[i]) {
            cout << -1;
            return 0;
        }
    }

    bool dup = false;
    for (int i = 0; i < 26; i++) if (charcnt[i] >= 2) dup = true;

    vector<int> same(N, 0);

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) if (ss[i][j] == ss[0][j]) same[j]++;
    }

    int numdiff = N;
    vector<int> diffs;
    for (int i = 0; i < N; i++) {
        if (same[i] == K) numdiff--;
        else diffs.push_back(i);
    }

    if (numdiff == 0) {
        swap(ss[0][0], ss[0][1]);
        cout << ss[0];
        return 0;
    }

    if (numdiff == 4) {
        string s = test4(diffs, dup);
        if (s.empty()) cout << -1;
        else cout << s;
        return 0;
    } if (numdiff == 3) {
        string s = test3(diffs, dup);
        if (s.empty()) cout << -1;
        else cout << s;
        return 0;
    } if (numdiff == 2) {
        for (int i = 0; i < N; i++) {
            if (same[i] == K) continue;

            diffs.push_back(i);

            string s = test3(diffs, dup);
            if (!s.empty()) {
                cout << s;
                return 0;
            }

            diffs.pop_back();
        }

        cout << -1;
    }
}