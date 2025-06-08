/*
ID: ishaangoyal12
LANG: JAVA
TASK: lostcow
*/

import java.io.*;
import java.util.*;

public class lostcow {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("lostcow.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lostcow.out")));

        String[] XandY = in.readLine().split(" ");
        Location x = new Location(Integer.parseInt(XandY[0]));
        Location y = new Location(Integer.parseInt(XandY[1]));

        int amount = 1;
        int moved = 0;

        int initialX = x.point;

        while (true) {
            moved += step(x, initialX + amount, y);
            if (x.point == y.point) {
                break;
            }
            amount *= -2;
        }
        out.println(moved);
        out.flush();
    }

    private static int step(Location x, int endLoc, Location y) {
        int steps = 0;
        boolean forward = endLoc > x.point;
        while (x.point != endLoc) {
            x.point += forward ? 1 : -1;
            steps++;
            if (x.point == y.point) return steps;
        }
        return steps;
    }

    private static class Location {
        int point;

        public Location(int point) {
            this.point = point;
        }
    }
}
