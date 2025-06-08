/*
ID: ishaangoyal12
LANG: JAVA
TASK: speeding
*/

import java.io.*;
import java.util.*;

public class speeding {

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("speeding.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("speeding.out")));

        String[] NandM = in.readLine().split(" ");
        int N = Integer.parseInt(NandM[0]);
        int M = Integer.parseInt(NandM[1]);

        Segment[] roadSegments = new Segment[N];
        int point = 0;
        for (int i = 0; i < N; i++) {
            int[] nums = numbersFromStringPair(in.readLine());
            roadSegments[i] = new Segment(point + 1, point + nums[0], nums[1]);
            point = roadSegments[i].end;
        }

        Segment[] driveSegments = new Segment[M];
        point = 0;
        for (int i = 0; i < M; i++) {
            int[] nums = numbersFromStringPair(in.readLine());
            driveSegments[i] = new Segment(point + 1, point + nums[0], nums[1]);
            point = driveSegments[i].end;
        }

        int amountOverLimit = 0;
        for (int i = 1; i <= 100; i++) {
            int amountOverLimitTemp = speedAtPoint(driveSegments, i) - speedAtPoint( roadSegments, i);
            if (amountOverLimitTemp > amountOverLimit) amountOverLimit = amountOverLimitTemp;
            
        }
        out.println(amountOverLimit);
        out.flush();
    }

    public static class Segment {
        int start;
        int end;
        int speed;

        public Segment(int start, int end, int speed) {
            this.start = start;
            this.end = end;
            this.speed = speed;
        }
    }

    private static int speedAtPoint(Segment[] segments, int point) {
        if (point < 1) return -1;
        for (int i = 0; i < segments.length; i++) {
            Segment segment = segments[i];
            if (point > segment.end) continue;
            return segment.speed;
        }
        return -1;
    }

    private static int[] numbersFromStringPair(String pair) {
        String[] numsString = pair.split(" ");
        int[] nums = new int[]{Integer.parseInt(numsString[0]), Integer.parseInt(numsString[1])};
        return nums;
    }
}