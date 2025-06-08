#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

#define ll string

ll roundup(ll input, int digit) {
    cout << input;
    cout << "\n";
    // ll shifted = input / (pow(10, digit - 1));
    ll shifted = input.substr(0, input.length() - digit + 1);
    cout << shifted;
    cout << "\n";
    // ll atDigit = shifted % 10;
    int atDigit = stoi(shifted.substr(shifted.length() - 1, shifted.length()));

    // ll output = shifted / 10;
    ll output = shifted.substr(0, shifted.length() - 1);
    if (atDigit >= 5) {
        // // ll output = shifted - atDigit + 10;
        // output += 1;
        output = output.substr(0, shifted.length() - 1) + to_string(stoi(output.substr(output.length() - 1, output.length())) + 1);
        // return output * (pow(10, digit));
    } else {
        // return output * (pow(10, digit));
    }
    while (digit--) {
        output += "0";
    }
    return output;
}

int firstDigitGreaterThanFive(ll input) {
    // int numDigits = int(log10(input) + 1);
    int numDigits = input.length();
    while (numDigits--) {
        // ll pruned = input / pow(10, numDigits);
        ll pruned = input.substr(0, input.length() - numDigits);
        // int currentDigit = pruned % 10;
        int currentDigit = stoi(pruned.substr(pruned.length() - 1, pruned.length()));
        if (currentDigit >= 5) return numDigits;
    }
    return -1;
}

int main() {
    int t;
    cin >> t;
    cout << unitbuf; 
    while (t--) {
        ll num;
        cin >> num;
        int digit = firstDigitGreaterThanFive(num);
        int a = 100;
        while (a-- && digit >= 0) {
            digit++;
            ll newNum = roundup(num, digit);
            if (newNum < num) break;
            num = newNum;
        }
        cout << num;
        cout << "\n";
    }
}