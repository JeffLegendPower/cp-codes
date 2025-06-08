/*
ID: ishaangoyal12
LANG: JAVA
TASK: mowing
*/

import java.io.*;
import java.util.*;

public class mowing {

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("mowing.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("mowing.out")));

        int N = Integer.parseInt(in.readLine());

        int[][] cells = new int[2000][2000];

        int x = cells[0].length / 2;
        int y = cells.length / 2;
        cells[y][x] = 1;

        int time = 1;

        int maxTimeSinceCut = 9999999;

        for (int i = 0; i < N; i++) {
            String[] path = in.readLine().split(" ");
            char direction = path[0].charAt(0);
            int steps = Integer.parseInt(path[1]);

            for (int j = 0; j < steps; j++) {
                time++;
                switch (direction) {
                    case 'N': {
                        y--;
                        int timeSinceCut = timeSinceCut(cells, x, y, time);
                        if (timeSinceCut < maxTimeSinceCut && timeSinceCut != -1) {
                            maxTimeSinceCut = timeSinceCut;
                        }
                        cells[y][x] = time;
                        break;
                    }
                    case 'S': {
                        y++;
                        int timeSinceCut = timeSinceCut(cells, x, y, time);
                        if (timeSinceCut < maxTimeSinceCut && timeSinceCut != -1) {
                            maxTimeSinceCut = timeSinceCut;
                        }
                        cells[y][x] = time;
                        break;
                    }
                    case 'E': {
                        x++;
                        int timeSinceCut = timeSinceCut(cells, x, y, time);
                        if (timeSinceCut < maxTimeSinceCut && timeSinceCut != -1) {
                            maxTimeSinceCut = timeSinceCut;
                        }
                        cells[y][x] = time;
                        break;
                    }
                    case 'W': {
                        x--;
                        int timeSinceCut = timeSinceCut(cells, x, y, time);
                        if (timeSinceCut < maxTimeSinceCut && timeSinceCut != -1) {
                            maxTimeSinceCut = timeSinceCut;
                        }
                        cells[y][x] = time;
                        break;
                    }
                }
            }
        }

        out.println(maxTimeSinceCut == 9999999 ? -1 : maxTimeSinceCut);
        out.flush();
    }

    // returns -1 if not cut
    private static int timeSinceCut(int[][] cells, int x, int y, int time) {
        return cells[y][x] == 0 ? -1 : time - cells[y][x]/* + 1*/;
    }
}