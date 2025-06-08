// https://codeforces.com/problemset/problem/1981/C
// rip i failed :(

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;

struct comp {
    bool operator() (plli a, plli b) {
        return a < b;
    }
};

typedef tree<plli, null_type, comp, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        ll a[N];
        for (int i = 0; i < N; i++) cin >> a[i];


        // Pad the end
        bool allneg = true;
        for (int i = N - 1; i >= 0; i--) {
            if (a[i] != -1) {
                for (int j = i + 1; j < N; j++) {
                    if (a[j - 1] >= 5) a[j] = a[j - 1] / 2;
                    else a[j] = a[j - 1] * 2;
                }
                allneg = false;
                break;
            }
        }

        // If all negative 1s then we can just put some generic array
        if (allneg) for (int i = 0; i < N; i++) a[i] = (i % 2) + 1;

        bool works = true;

        int last = -1;
        for (int i = 0; i < N; i++) {
            if (a[i] != -1) {
                // Pad the beginning
                if (last == -1) {
                    for (int j = i - 1; j >= 0; j--) {
                        if (a[j + 1] >= 5) a[j] = a[j + 1] / 2;
                        else a[j] = a[j + 1] * 2;
                    }
                    last = i;
                    continue;
                }

                // if (i - last == 1) {
                //     last = i;
                //     continue;
                // }

                ll a1 = a[last];
                ll a2 = a[i];
                vector<ll> startseq, endseq;
                while (a1 != a2) {
                    if (a1 > a2) {
                        a1 /= 2;
                        if (a1 != a[i]) startseq.push_back(a1);
                    } else {
                        a2 /= 2;
                        if (a2 != a[last]) endseq.push_back(a2);
                    }
                }

                // cout << i << " " << last << endl;
                vector<ll> total;
                for (int i = 0; i < startseq.size(); i++) total.push_back(startseq[i]);
                for (int i = endseq.size() - 1; i >= 0; i--) {
                    if (total.size() == 0 || total[total.size() - 1] != endseq[i])
                        total.push_back(endseq[i]);
                }
                int space = i - last - 1;

                if (a[i] == a[last]) total.push_back(a[i] * 2);

                // cout << total.size() << " " << i << " " << space << endl;
                // cout << space - total.size() << endl;

                if (space < total.size() || (space - total.size() % 2) == 1) {
                    works = false;
                    break;
                }
                // if (total.size() == 0 && space % 2 == 0) {
                //     works = false;
                //     break;
                // }

                for (int j = 0; j < total.size(); j++) {
                    a[j + last + 1] = total[j];
                }

                for (int j = 0; j < space - total.size(); j++) {
                    if (j % 2 == 0)
                        a[j + last + 1 + total.size()] = a[j + last + total.size()] * 2;
                    else a[j + last + 1 + total.size()] = a[j + last + total.size()] / 2;
                }

                last = i;
            }
        }

        if (!works) {
            cout << -1 << endl;
            continue;
        }

        for (int i = 0; i < N; i++) {
            cout << a[i] << " ";
        }

        cout << endl;
    }
}