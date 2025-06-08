#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

#define ll long long

int main() {
    int n;
    cin >> n;
    int x[n];
    for (int i = 0; i < n; i++)
        cin >> x[i];

    sort(x, x + n);

    // since sorted, all the numbers will appear in groups next to eachother so we only gotta hold and check them once
    int distinctNumbers = 0;
    
    int currentNumber = -1;
    for (int i = 0; i < n; i++) {
        if (x[i] != currentNumber) {
            distinctNumbers++;
            currentNumber = x[i];
        }
    }

    cout << distinctNumbers;
}