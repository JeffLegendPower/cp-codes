#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

#define ll long long

int main() {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    int N, M;
    cin >> N >> M;
    string spotty_genomes[N];
    string plain_genomes[N];
    
    for (int i = 0; i < N; i++) {
        cin >> spotty_genomes[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> plain_genomes[i];
    }

    int num_good = 0;

    // // get all combinations of 3 in a set of length M (from 1, 2, 3... M)
    for (int pos1 = 0; pos1 < M - 2; pos1++) {
        for (int pos2 = pos1 + 1; pos2 < M - 1; pos2++) {
            for (int pos3 = pos2 + 1; pos3 < M; pos3++) {

                // get the N amount of 3-letter sequences for plain cows
                string plain_sequences[N];
                for (int i = 0; i < N; i++) {
                    plain_sequences[i] += plain_genomes[i][pos1];
                    plain_sequences[i] += plain_genomes[i][pos2];
                    plain_sequences[i] += plain_genomes[i][pos3];
                }

                // // do the same for spotty cows
                // string spotty_sequences[N];
                // for (int i = 0; i < N; i++) {
                //     spotty_sequences[i] += spotty_genomes[i][pos1];
                //     spotty_sequences[i] += spotty_genomes[i][pos2];
                //     spotty_sequences[i] += spotty_genomes[i][pos3];
                // }

                // compare all the spotty sequences to plain sequences, if any match then this one wont work
                bool badsequence = false;
                for (int i = 0; i < N; i++) {
                    string spotty_sequence;
                    spotty_sequence += spotty_genomes[i][pos1];
                    spotty_sequence += spotty_genomes[i][pos2];
                    spotty_sequence += spotty_genomes[i][pos3];
                    for (int j = 0; j < N; j++) {
                        if (spotty_sequence == plain_sequences[j]) {
                            badsequence = true;
                            break;
                        }
                    }
                    if (badsequence) {
                        break;
                    }
                }

                if (!badsequence) {
                    num_good += 1;
                }
            }
        }
    }

    cout << num_good;
}