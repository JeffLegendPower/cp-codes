// https://usaco.org/index.php?page=viewproblem2&cpid=1377&lang=en

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

struct qry {
    ll x, y, d;
    int hidx, vidx;
};

vector<ll> hors, verts;
// num parity flips from 0 to i
vector<ll> pre_h, pre_v;
int h = 0, v = 0;

qry verti(ll x, ll y, ll d, int hidx, int vidx) {
    int low = hidx + 1, high = h - 1;
    int best = hidx;

    qry bestq = {x, y, d, hidx, vidx};
    while (low <= high) {
        int mid = low + (high - low) / 2;

        ll hflip = pre_h[mid - 1] - pre_h[hidx];

        int lowv = vidx, highv = v - 1;
        int bestv = -1;
        while (lowv <= highv) {
            int midv = lowv + (highv - lowv) / 2;
            if (pre_v[midv] - pre_v[vidx] < hflip) {
                lowv = midv + 1;
            } else {
                highv = midv - 1;
                bestv = midv;
            }
        }

        if (bestv == -1) {
            high = mid - 1;
            continue;
        }
        ll dist = hors[mid] - y + verts[bestv] - x;
        if (dist <= d) {
            low = mid + 1;
            best = mid;
            bestq = {verts[bestv], hors[mid], d - dist, mid, bestv};
        } else high = mid - 1;
    }

    return bestq;
} qry hori(ll x, ll y, ll d, int hidx, int vidx) {
    int low = vidx + 1, high = v - 1;
    int best = vidx;

    qry bestq = {x, y, d, hidx, vidx};
    while (low <= high) {
        int mid = low + (high - low) / 2;

        ll vflip = pre_v[mid - 1] - pre_v[hidx];

        int lowh = hidx, highh = h - 1;
        int besth = -1;
        while (lowh <= highh) {
            int midh = lowh + (highh - lowh) / 2;
            if (pre_h[midh] - pre_h[hidx] < vflip) {
                lowh = midh + 1;
            } else {
                highh = midh - 1;
                besth = midh;
            }
        }

        if (besth == -1) {
            high = mid - 1;
            continue;
        }
        ll dist = verts[mid] - y + hors[besth] - x;
        if (dist <= d) {
            low = mid + 1;
            best = mid;
            bestq = {verts[mid], hors[besth], d - dist, besth, mid};
        } else high = mid - 1;
    }

    return bestq;
}


int main() {
    // Comment out for interactive problems
    ios::sync_with_stdio(false);
	cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    for (int i = 0; i < N; i++) {
        char c;
        ll ci;
        cin >> c >> ci;
        if (c == 'H') {
            hors.push_back(ci);
            h++;
        } else {
            verts.push_back(ci);
            v++;
        }
    }
    sort(hors.begin(), hors.end());
    sort(verts.begin(), verts.end());

    pre_h.push_back(0);
    pre_v.push_back(0);
    for (int i = 1; i < h; i++) pre_h.push_back(pre_h.back() + ((hors[i] - hors[i - 1])&1));
    for (int i = 1; i < v; i++) pre_v.push_back(pre_v.back() + ((verts[i] - verts[i - 1])&1));

    while (Q--) {
        ll x, y, d;
        cin >> x >> y >> d;

        int low = 0, high = h - 1, hidx = -1, vidx = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (hors[mid] >= y) {
                high = mid - 1;
                hidx = mid;
            } else low = mid + 1;
        }
        low = 0, high = v - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (verts[mid] >= x) {
                high = mid - 1;
                vidx = mid;
            } else low = mid + 1;
        }

        if (hidx == -1) {
            cout << x << " " << (y+d) << endl;
            continue;
        } if (vidx == -1) {
            cout << (x+d) << " " << y << endl;
            continue;
        }

        bool even = true;
        if (hors[hidx] > y) {
            d -= hors[hidx] - y;
            if ((hors[hidx] - y)&1) even = false;
            y = hors[hidx];
            if (d <= 0) {
                y += d;
                cout << x << " " << y << endl;
                continue;
            }
        } if (verts[vidx] > x) {
            d -= verts[vidx] - x;
            if ((verts[vidx] - x)&1) even = false;
            x = verts[vidx];
            if (d <= 0) {
                x += d;
                cout << x << " " << y << endl;
                continue;
            }
        }

        if (even) {
            qry next = verti(x, y, d, hidx, vidx);
            if ((d - next.d)&1) {
                next = hori(next.x, next.y, next.d, next.hidx, next.vidx);
                if ((d - next.d)&1) cout << (next.x + next.d) << " " << next.y << endl;
                else cout << next.x << " " << (next.y + next.d) << endl;
            } else cout << next.x << " " << (next.y + next.d) << endl;
        } else {
            qry next = hori(x, y, d, hidx, vidx);
            if ((d - next.d)&1) {
                // cout << next.x << " " << next.y << " " << next.d << " " << d << endl;
                next = verti(next.x, next.y, next.d, next.hidx, next.vidx);
                if (1^((d - next.d)&1)) cout << (next.x + next.d) << " " << next.y << endl;
                else cout << next.x << " " << (next.y + next.d) << endl;
            } else cout << next.x << " " << (next.y + next.d) << endl;
        }
    }
}