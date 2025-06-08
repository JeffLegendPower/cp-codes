/*
ID: ishaangoyal12
LANG: JAVA
TASK: blocks
*/

import java.io.*;
import java.util.*;

public class tttt {

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("tttt.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("tttt.out")));

        char[][] tttBoard = new char[3][3];

        for (int i = 0; i < 3; i++) {
            char[] row = in.readLine().toCharArray();
            tttBoard[i] = row;
        }

        // now go through all 8 ways to get 3 in a row in tictactoe
        HashSet<String> solo = new HashSet<>();
        HashSet<String> teams = new HashSet<>();
        // Counter teams = new Counter(0);

        updatePossibleWins(solo, teams, tttBoard[0][0], tttBoard[0][1], tttBoard[0][2]);
        updatePossibleWins(solo, teams, tttBoard[1][0], tttBoard[1][1], tttBoard[1][2]);
        updatePossibleWins(solo, teams, tttBoard[2][0], tttBoard[2][1], tttBoard[2][2]);

        updatePossibleWins(solo, teams, tttBoard[0][0], tttBoard[1][0], tttBoard[2][0]);
        updatePossibleWins(solo, teams, tttBoard[0][1], tttBoard[1][1], tttBoard[2][1]);
        updatePossibleWins(solo, teams, tttBoard[0][2], tttBoard[1][2], tttBoard[2][2]);

        updatePossibleWins(solo, teams, tttBoard[0][0], tttBoard[1][1], tttBoard[2][2]);
        updatePossibleWins(solo, teams, tttBoard[0][2], tttBoard[1][1], tttBoard[2][0]);

        out.println(solo.size());
        out.println(teams.size());
        out.flush();
    }

    public static void updatePossibleWins(HashSet<String> solo, HashSet<String> teams, char char1, char char2, char char3) {
        if (char1 == char2 && char2 == char3) {
            solo.add(new String(new char[]{char1}));
        }
        else if (char1 == char2 || char2 == char3 || char1 == char3) {
            char uniqueChar1 = char1;
            char uniqueChar2 = char2 == uniqueChar1 ? char3 : char2;
            String team = new String(uniqueChar1 > uniqueChar2 ? new char[]{uniqueChar2, uniqueChar1} : new char[]{uniqueChar1, uniqueChar2});

            teams.add(team);
        }
    }

    public static class Counter {
        int count;

        public Counter(int count) {
            this.count = count;
        }
    }
}