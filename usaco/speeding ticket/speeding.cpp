#include <iostream>
#include <fstream>

using namespace std;

#define ll long long

int main() {
    std::ifstream in("speeding.in");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    std::ofstream out("speeding.out");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    ll N;
    ll M;
    cin >> N >> M;

    short speedLimits[100] = {};
    short currentIndex = 0;
    while (N--) {
        short segmentLength;
        short speedLimit;
        cin >> segmentLength >> speedLimit;
        for (short i = currentIndex; i < segmentLength + currentIndex; i++) {
            speedLimits[i] = speedLimit;
        }
        currentIndex += segmentLength;
    }

    short greatestInfraction = 0;
    currentIndex = 0;
    while (M--) {
        short segmentLength;
        short speed;
        cin >> segmentLength >> speed;
        for (short i = currentIndex; i < segmentLength + currentIndex; i++) {
            short infraction = speed - speedLimits[i];
            if (infraction > greatestInfraction) {
                greatestInfraction = infraction;
            }
        }
        currentIndex += segmentLength;
    }

    cout << greatestInfraction;

    return 0;
}