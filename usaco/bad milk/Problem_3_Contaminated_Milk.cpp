#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define ll unsigned long long

// return a vector because there might be multiple possible bad milks
inline vector<int> commonElements(vector<int> lists[], int length) {
    vector<int> commonElements = lists[0];

    for (int i = 0; i < length; i++) {
        vector<int> list = lists[i];
        vector<int> tempCommonElements;
        for (int element : list) {
            if (find(commonElements.begin(), commonElements.end(), element) != commonElements.end()) {
                tempCommonElements.push_back(element);
            }
        }
        if (list.size() > 0)
            commonElements = tempCommonElements;
    }

    return commonElements;
}

int main() {
    freopen("badmilk.in", "r", stdin);
    freopen("badmilk.out", "w", stdout);

    int N, M, D, S;
    cin >> N >> M >> D >> S;

    int drinkpeople[D], drinkmilks[D], drinktimes[D],
    sickpeople[S], sicktimes[S];

    for (int i = 0; i < D; i++) {
        cin >> drinkpeople[i] >> drinkmilks[i] >> drinktimes[i];
    }
    for (int i = 0; i < S; i++) {
        cin >> sickpeople[i] >> sicktimes[i];
    }

    vector<int> sickmilks[N];

    for (int t = 0; t < D; t++) {
        int drinkperson = drinkpeople[t], drinkmilk = drinkmilks[t], drinktime = drinktimes[t];

        int sicktime = -1;
        for (int i = 0; i < S; i++)
            if (sickpeople[i] == drinkperson && sicktimes[i] > drinktime) sicktime = sicktimes[i];

        if (sicktime == -1) continue; // ignore if didnt get sick before this moment because this case wont help in the investigation
        
        sickmilks[drinkperson - 1].push_back(drinkmilk);
    }

    vector<int> possibleSickMilks = commonElements(sickmilks, N);

    // cout << drinkmilks[5];

    int maxDoses = 0;
    for (int sickmilk : possibleSickMilks) {
        int doses = 0;
        bool personSick[N];
        for (int i = 0; i < N; i++)
            personSick[i] = false;
        
        for (int t = 0; t < D; t++) {
            int drinkperson = drinkpeople[t], drinkmilk = drinkmilks[t];
            if (personSick[drinkperson - 1]) continue;
            // if (sickmilk == 1)
            //     cout << drinkmilk << " " << sickmilk << " " << personSick[1] << endl;
            if (drinkmilk == sickmilk) {
                // cout << "e " << drinkperson << " " << drinkmilk << " " << drinktimes[t] << endl;
                doses++;
                personSick[drinkperson - 1] = true;
            }
        }

        maxDoses = max(maxDoses, doses);
    }

    cout << maxDoses;
}