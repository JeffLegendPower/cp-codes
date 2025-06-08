/*
ID: ishaangoyal12
LANG: JAVA
TASK: cbarn
*/

import java.io.*;
import java.util.*;

public class cbarn {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("cbarn.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cbarn.out")));

        int N = Integer.parseInt(in.readLine());

        int[] rooms2 = new int[N];
        for (int i = 0; i < N; i++) {
            rooms2[i] = Integer.parseInt(in.readLine());
        }

        int startingCows = Arrays.stream(rooms2).sum();

        int leastSteps = 999999999;
        int steps = startingCows * N;

        for (int j = 0; j < N; j++) {

            for (int i = 0; i < N; i++) {
                int i2 = i + j;
                if (i2 >= N) {
                    i2 -= N;
                }

                steps -= rooms2[i2] * (N - i);
            }
            if (steps < leastSteps) {
                leastSteps = steps;
            }
            steps = startingCows * N;
        }

        out.println(leastSteps);
        out.flush();
    }
}