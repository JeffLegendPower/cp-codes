/*
ID: ishaangoyal12
LANG: JAVA
TASK: measurement
*/

import java.io.*;
import java.util.*;

public class measurement {

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("measurement.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("measurement.out")));

        int N = Integer.parseInt(in.readLine());

        Map<String, Integer> cows = new HashMap<>();
        cows.put("Bessie", 7);
        cows.put("Elsie", 7);
        cows.put("Mildred", 7);

        Entry[] entries = new Entry[N];

        for (int i = 0; i < N; i++) {
            String[] entryData = in.readLine().split(" ");
            int day = Integer.parseInt(entryData[0]);
            String cowName = entryData[1];
            int change = Integer.parseInt(entryData[2]);
            entries[i] = new Entry(day, cowName, change);
        }

        sort(entries, 0, N - 1);

        int numAdjustments = 0;
        int entryIndex = 0;
        String[] cowsInLead = new String[]{"Bessie", "Elsie", "Mildred"};
        for (int i = 1; i <= 100; i++) {
            // first process changes in cow production (if any)
            if (entryIndex < N) {
                Entry currentEntry = entries[entryIndex];
                if (currentEntry.day == i) {
                    cows.compute(currentEntry.cow, (key, value) -> 
                        value += currentEntry.change
                    );
                    entryIndex++;
                }
            }

            // now get the current cows in lead then compare them to the old cows in lead, if different increment numAdjustments and set cowsInLead to currentCowsInLead
            String[] currentCowsInLead = new String[3];
            for (int j = 0; j < 3; j++) currentCowsInLead[j] = "";
            int highestMilkProd = 0;
            
            int bessieProd = cows.get("Bessie");
            int elsieProd = cows.get("Elsie");
            int mildredProd = cows.get("Mildred");

            highestMilkProd = bessieProd > elsieProd ? 
            (bessieProd > mildredProd ? bessieProd : mildredProd) : 
            (elsieProd > mildredProd ? elsieProd : mildredProd);

            if (bessieProd == highestMilkProd) currentCowsInLead[0] = "Bessie";
            if (elsieProd == highestMilkProd) currentCowsInLead[1] = "Elsie";
            if (mildredProd == highestMilkProd) currentCowsInLead[2] = "Mildred";

            if (!compare(cowsInLead, currentCowsInLead)) {
                cowsInLead = currentCowsInLead;
                numAdjustments++;
            }
        }

        out.println(numAdjustments);
        out.flush();
    }

    // assumes both strings are same length
    private static boolean compare(String[] one, String[] two) {
        for (int i = 0; i < one.length; i++) {
            if (!one[i].equals(two[i])) return false;
        }
        return true;
    }

    private static int partition(Entry arr[], int low, int high) {
        int pivot = arr[high].day;
        int i = (low - 1); // index of smaller element
        for (int j = low; j < high; j++) {
            // If current element's day is smaller than or equal to pivot
            if (arr[j].day <= pivot) {
                i++;

                // swap arr[i] and arr[j]
                Entry temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }

        // swap arr[i+1] and arr[high] (or pivot)
        Entry temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        return i + 1;
    }

    private static void sort(Entry arr[], int low, int high) {
        if (low < high) {
            /* pi is partitioning index, arr[pi] is
              now at the right place */
            int pi = partition(arr, low, high);

            // Recursively sort elements before
            // partition and after partition
            sort(arr, low, pi - 1);
            sort(arr, pi + 1, high);
        }
    }

    private static class Entry {
        int day;
        String cow;
        int change;

        public Entry(int day, String cow, int change) {
            this.day = day;
            this.cow = cow;
            this.change = change;
        }
    }
}
