// https://cses.fi/problemset/task/1140

// Naively, we'd solve this in O(2^n) by testing every subset of projects
// However, we can solve this in O(n^2) by using dp. We will first sort the
// projects in descending order by their start times and for each project we
// will solve for the total reward achievable if we start by working on that project
// For the leftmost (latest) project, that total reward would just be the reward of that project
// For every next project, we'd iterate through all the projects before it and find the one with
// the highest total reward and has a start time strictly after the current project's end time

// However, O(n^2) is still too slow. But this can be sped up by using prefix maximums and binary search
// We can store the maximum total reward achievable if we start with project i using prefix maximums
// and use binary search to find the rightmost project before the current project whos start time is strictly
// after the current project's end time. Because the projects are sorted in descending order of their start
// time, there is no project[j] before project[i] such that the start time of project j is before the start
// time of project i. By using prefix maximums and binary search, we can drop the time complexity from O(n^2)
// to O(nlogn)

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


struct project {
    ll start, end, reward;
    // Optimal reward if you start with this project
    ll dpreward;
};

int main() {
    int N;
    cin >> N;

    project projects[N];
    for (int i = 0; i < N; i++) cin >> projects[i].start >> projects[i].end >> projects[i].reward;

    sort(projects, projects + N, [](project one, project two) {
        return one.start > two.start;
    });

    // Store max reward we can get if we start from this project
    ll prefixreward[N + 1];
    prefixreward[0] = 0;
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            projects[i].dpreward = projects[i].reward;
            prefixreward[i + 1] = max(prefixreward[i], projects[i].dpreward);
            continue;
        }

        int low = 0, high = i - 1;
        int best = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (projects[mid].start <= projects[i].end) high = mid - 1;
            else {
                low = mid + 1;
                best = mid;
            }
        }

        if (best == -1) {
            projects[i].dpreward = projects[i].reward;
        } else {
            projects[i].dpreward = projects[i].reward + prefixreward[best + 1];
        }
        prefixreward[i + 1] = max(prefixreward[i], projects[i].dpreward);
    }

    cout << prefixreward[N];
}