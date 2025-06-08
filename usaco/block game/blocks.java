/*
ID: ishaangoyal12
LANG: JAVA
TASK: blocks
*/

import java.io.*;
import java.util.*;

public class blocks {

    final static String alphabet = "abcdefghijklmnopqrstuvwxyz";

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("blocks.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("blocks.out")));

        int N = Integer.parseInt(in.readLine());

        int[] numLetters = new int[26];

        for (int i = 0; i < N; i++) {
            String[] words = in.readLine().split(" ");

            int[] addLetters = new int[26];

            for (int j = 0; j < words[0].length(); j++) {
                char[] word = words[0].toCharArray();
                addLetters[alphabet.indexOf(word[j])]++;
            }

            int[] addLetters2 = new int[26];

            for (int j = 0; j < words[1].length(); j++) {
                char[] word = words[1].toCharArray();
                addLetters2[alphabet.indexOf(word[j])]++;
            }

            for (int j = 0; j < 26; j++) {
                numLetters[j] += Math.max(addLetters[j], addLetters2[j]);
            }
        }

        for (int i = 0; i < 26; i++) {
            out.println(numLetters[i]);
        }

        out.flush();
    }
}