#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    freopen("guess.in", "r", stdin);
    freopen("guess.out", "w", stdout);

    int N;
    cin >> N;

    unordered_map<string, int> properties;

    while (N--) {
        string name;
        int animalProperties;
        cin >> name >> animalProperties;

        while (animalProperties--) {
            string property;
            cin >> property;
            properties[property]++;
        }
    }

    int numShared = 0;

    for (unordered_map<string, int>::iterator i = properties.begin(); i != properties.end(); i++) {
        if (i->second > 1) {
            numShared++;
        }
    }
    
    cout << numShared + 1;
}