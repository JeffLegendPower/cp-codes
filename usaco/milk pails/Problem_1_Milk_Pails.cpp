#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

#define ll long long

int main() {
    freopen("pails.in", "r", stdin);
	freopen("pails.out", "w", stdout);
    int X, Y, M;
    cin >> X >> Y >> M;

    int combinations = M / X;
    
    int mostPoured = 0;
    int current = M;
    for (int i = 1; i <= combinations; i++) {
        current -= X * i;
        int remainder = current % Y;
        mostPoured = max(mostPoured, M - remainder);
        current = M;
    }
    cout << mostPoured;
}