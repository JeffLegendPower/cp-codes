/*
ID: ishaangoyal12
LANG: JAVA
TASK: rut
*/

import java.io.*;
import java.util.*;

public class rut {

    public static void main(String[] args) throws IOException {
        try {
            run();
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("aaaaaaa");
        }
    }

    public static void run() throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("rut.in"));
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);

        int N = Integer.parseInt(in.readLine());

        Cow[] cows = new Cow[N];

        int greatestX = 0;
        int greatestY = 0;

        // sometimes there might be a cow with coords greater than collide so if this is larger then we put this instead
        // we might not need this though we will see
        int altX = 0;
        int altY = 0;

        for (int i = 0; i < N; i++) {
            String[] cowData = in.readLine().split(" ");

            Direction direction = Direction.valueOf(cowData[0]);
            int x = Integer.parseInt(cowData[1]);
            int y = Integer.parseInt(cowData[2]);

            cows[i] = new Cow(
                direction, x, y, 0
            );

            if (x > greatestX && direction == Direction.N) greatestX = x;
            if (y > greatestY && direction == Direction.E) greatestY = y;

            if (x > altX) altX = x;
            if (y > altY) altY = y;
        }

        // whats going on here is we get the greatest initial x of north cows and y of east cows so we know the greatest point where they will intercept
        // anything past that means that they will go on forever
        // value 0 means untouched, 1 means being eaten, 2 means eaten
        // byte[][] cells = new byte[(greatestY > altY ? greatestY : altY) + 1][(greatestX > altX ? greatestX : altX) + 1];
        System.out.println(greatestX + " " + greatestY);
        byte[][] cells = new byte[greatestY + 1][greatestX + 2];

        // prune all north cows that have > y than greatestY and east cows that have > x than greatestX as we know that they will go on forever
        for (Cow cow : cows) {
            if (cow.direction == Direction.N) {
                if (cow.y > greatestY) {
                    cow.length = -1;
                    cow.stopped = true;
                }
            } else if (cow.x > greatestX) {
                cow.length = -1;
                cow.stopped = true;
            }
        }

        // System.out.println(greatestX + " " + greatestY);

        // now have a loop which keeps running until all the cows have stopped for whatever reason
        while (!haveCowsStopped(cows)) {
            ArrayList<Coordinate> cellsToEat = new ArrayList<>();
            for (int i = 0; i < N; i++) {
                Cow cow = cows[i];
                if (cow.stopped) continue;
                // check if current cell is already eaten
                int realX = realCellX(cow, cells);
                int realY = realCellY(cow, cells);
                byte cellStatus = -1;
                try {
                    cellStatus = cells[realY][realX];
                } catch (ArrayIndexOutOfBoundsException e) {
                    System.out.println("jjjjj");
                    System.out.println(realX + " " + cells[0].length);
                    System.out.println(realY + " " + cells.length);
                }
                if (cellStatus == 2) {
                    cow.stopped = true;
                    continue;
                }
                // now step the cow
                cells[realY][realX] = 1;
                cellsToEat.add(new Coordinate(realX, realY));
                if (cow.direction == Direction.N) cows[i].y++;
                else cows[i].x++;
                cows[i].length ++;
            }

            // now finish eating all the cells (this accounts for the case when multiple cows step on 1 cell)
            for (Coordinate coordinate : cellsToEat) {
                cells[coordinate.y][coordinate.x] = 2;
            }

            // recheck for cows that could be considered out of bounds and would eat forever
            for (Cow cow : cows) {
                if (willCowEatForever(cow, greatestX, greatestY)) {
                    cow.length = -1;
                    cow.stopped = true;
                }
                if (!cow.stopped && cow.x > greatestX && cow.y > greatestY) {
                    System.out.println((cow.x - greatestX) + " " + (cow.y - greatestY));
                }
            }
        }

        for (Cow cow : cows) {
            out.println(cow.length == -1 ? "Infinity" : cow.length);
        }
        out.flush();
    }

    private static boolean willCowEatForever(Cow cow, int greatestX, int greatestY) {
        if (cow.direction == Direction.N) {
            if (cow.y > greatestY) {
                return true;
            }
        } else if (cow.x > greatestX) {
            return true;
        }
        return false;
    }

    private static int realCellX(Cow cow, byte[][] cells) {
        return cow.x;
    }

    private static int realCellY(Cow cow, byte[][] cells) {
        return cells.length - cow.y - 1;
    }

    private static boolean haveCowsStopped(Cow[] cows) {
        for (Cow cow : cows) {
            if (!cow.stopped) return false;
        }
        return true;
    }

    private static class Cow {
        Direction direction;
        int x;
        int y;
        int length; // -1 means inf
        boolean stopped = false;

        public Cow(Direction direction, int x, int y, int length) {
            this.direction = direction;
            this.x = x;
            this.y = y;
            this.length = length;
        }
    }

    private static class Coordinate {
        int x;
        int y;

        public Coordinate(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    private enum Direction {
        N, E;
    }
}