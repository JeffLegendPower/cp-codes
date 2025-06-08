/*
ID: ishaangoyal12
LANG: JAVA
TASK: traffic
*/

import java.io.*;
import java.util.*;

public class traffic {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("traffic.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("traffic.out")));

        int N = Integer.parseInt(in.readLine());

        Road[] roads = new Road[N];
        for (int i = 0; i < N; i++) {
            String[] roadString = in.readLine().split(" ");
            roads[i] = new Road(Ramp.valueOf(roadString[0]), Integer.parseInt(roadString[1]), Integer.parseInt(roadString[2]));
        }

        getStartingRange(roads, N, out);
        getEndingRange(roads, N, out);
        out.flush();
    }

    private static void getEndingRange(Road[] roads, int N, PrintWriter out) {
        int startingRoad = 0;
        for (int i = 0; i < N; i++) {
            if (roads[i].ramp == Ramp.none) {
                startingRoad = i;
                break;
            }
        }

        int lowerBound = roads[startingRoad].lower;
        int upperBound = roads[startingRoad].upper;

        // now go backwards from here
        // if startingRoad + 1 doesnt work then remove the + 1 because it might cause error if the startingroad is the last road
        for (int i = startingRoad + 1; i < N; i++) {
            Road currentRoad = roads[i];
            switch (currentRoad.ramp) {
                case on: {
                    lowerBound += currentRoad.lower;
                    upperBound += currentRoad.upper;
                    break;
                }
                case off: {
                    lowerBound -= currentRoad.upper;
                    upperBound -= currentRoad.lower;
                    if (lowerBound < 0) lowerBound = 0;
                    break;
                }
                case none: {
                    lowerBound = currentRoad.lower > lowerBound ? currentRoad.lower : lowerBound;
                    upperBound = currentRoad.upper < upperBound ? currentRoad.upper : upperBound;
                    break;
                }
            }
        }
        out.println(lowerBound + " " + upperBound);
    }

    private static void getStartingRange(Road[] roads, int N, PrintWriter out) {
        int startingRoad = 0;
        // might cause error because in line 106 i can be -1 if i here is 0
        for (int i = N - 1; i >= 0; i--) {
            if (roads[i].ramp == Ramp.none) {
                startingRoad = i;
                break;
            }
        }

        int lowerBound = roads[startingRoad].lower;
        int upperBound = roads[startingRoad].upper;
        
        // now go backwards from here
        for (int i = startingRoad - 1; i >= 0; i--) {
            Road currentRoad = roads[i];
            switch (currentRoad.ramp) {
                case on: {
                    lowerBound -= currentRoad.upper;
                    upperBound -= currentRoad.lower;
                    if (lowerBound < 0) lowerBound = 0;
                    break;
                }
                case off: {
                    lowerBound += currentRoad.lower;
                    upperBound += currentRoad.upper;
                    break;
                }
                case none: {
                    lowerBound = currentRoad.lower > lowerBound ? currentRoad.lower : lowerBound;
                    upperBound = currentRoad.upper < upperBound ? currentRoad.upper : upperBound;
                    break;
                }
            }
        }
        out.println(lowerBound + " " + upperBound);
    }

    static class Road {
        Ramp ramp;
        int lower;
        int upper;

        public Road(Ramp ramp, int lower, int upper) {
            this.ramp = ramp;
            this.lower = lower;
            this.upper = upper;
        }
    }
}

enum Ramp {
    on,
    off,
    none
}