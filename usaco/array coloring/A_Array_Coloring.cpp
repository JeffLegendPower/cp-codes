#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    
    int n;

    cin >> n;

    while (n--) {
        int t;

        cin >> t;

        int arr[t];
        int numOdd = 0;
        while (t--) {
            int num;
            cin >> num;
            if (num % 2 == 1) numOdd++;
        }

        cout << (numOdd % 2 == 0 ? "YES" : "NO");
        cout << "\n";
    }
}