#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

using namespace std;

#define ll long long

int main() {
    // freopen("bcs.in", "r", stdin);
    // freopen("bcs.out", "w", stdout);

    int N, K;

    cin >> N >> K;

    char origFigure[N][N];

    for (int i = 0; i < N; i++) {
        string line;
        cin >> line;
        for (int j = 0; j < N; j++) {
            origFigure[i][j] = line[j];
        }
    }

    char pieces[K][N][N];

    for (int k = 0; k < K; k++) {
        for (int i = 0; i < N; i++) {
            string line;
            cin >> line;
            for (int j = 0; j < N; j++) {
                pieces[k][i][j] = line[j];
            }
        }
    }

    for (int piece1 = 0; piece1 < K - 1; piece1++) {
        for (int piece2 = piece1 + 1; piece2 < K; piece2++) {
            int piece1HshiftMin, piece1HShiftMax, piece1VShiftMin, piece1VShiftMax;
            int piece2HshiftMin, piece2HShiftMax, piece2VShiftMin, piece2VShiftMax;

            for (int HShift1 = -N + 1; HShift1 < N; HShift1++) {
                for (int VShift1 = -N + 1; VShift1 < N; VShift1++) {
                    for (int HShift2 = -N + 1; HShift2 < N; HShift2++) {
                        for (int VShift2 = -N + 1; VShift2 < N; VShift2++) {
                            char newFigure[N][N];
                            bool skip = false;
                            for (int y = 0; y < N; y++) {
                                for (int x = 0; x < N; x++) {
                                    int piece1x = x + HShift1,
                                    piece1y = y + VShift1,
                                    piece2x = x + HShift2,
                                    piece2y = y = VShift2;

                                    char piece1Char = pieces[piece1][piece1x][piece1y];
                                    char piece2Char = pieces[piece2][piece2x][piece2y];

                                    bool piece1InBounds = piece1x < 0 || piece1x >= N || piece1y < 0 || piece1y >= N,
                                    piece2InBounds = piece2x < 0 || piece2x >= N || piece2y < 0 || piece2y >= N;

                                    if (!piece1InBounds && !piece1InBounds)
                                        newFigure[y][x] = '.';
                                    else if (piece1InBounds)
                                        newFigure[y][x] = piece1Char;
                                    else if (piece2InBounds)
                                        newFigure[y][x] = piece2Char;
                                    else { // both in bounds
                                        if (piece1Char == '#' && piece1Char == piece2Char) { 
                                            // both are yes and that means that this combination is bad and we will skip it now
                                            skip = true;
                                            newFigure[0][0] = 'X'; // Just to make sure that it doesn't accidentally count as a valid combo
                                            break;
                                        }
                                        if (piece1Char == '#')
                                            newFigure[y][x] = piece1Char;
                                        else if (piece2Char == '#')
                                            newFigure[y][x] = piece2Char;
                                    }
                                }
                                if (skip)
                                    break;
                            }

                            // now compare the constructed figure to the original
                            bool valid = true;
                            for (int y = 0; y < N; y++) {
                                for (int x = 0; x < N; x++) {
                                    valid = valid && newFigure[y][x] == origFigure[y][x];
                                }
                            }
                            if (valid) {
                                cout << piece1 << " " << piece2;
                            }
                        }
                    }
                }
            }
        }
    }
}