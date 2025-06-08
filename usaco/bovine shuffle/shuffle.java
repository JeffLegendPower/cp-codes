/*
ID: ishaangoyal12
LANG: JAVA
TASK: shuffle
*/

import java.io.*;
import java.util.*;

public class shuffle {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("shuffle.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("shuffle.out")));

        int N = Integer.parseInt(in.readLine());

        Mapping[] mappings = new Mapping[N];

        String[] mappingStrings = in.readLine().split(" ");
        for (int i = 0; i < N; i++) {
            mappings[i] = new Mapping(i + 1, Integer.parseInt(mappingStrings[i]));
        }

        sort(mappings, 0, N - 1);
        int[] reverseMappings = new int[N];
        for (int i = 0; i < N; i++) {
            reverseMappings[i] = mappings[i].one;
        }

        String[] cowStrings = in.readLine().split(" ");
        Cow[] cows = new Cow[N];
        for (int i = 0; i < N; i++) {
            cows[i] = new Cow(Integer.parseInt(cowStrings[i]));
        }

        // now for the reverse mapping
        for (int i = 0; i < 3; i++) {
            Cow[] cows2 = new Cow[N];
            for (int j = 0; j < N; j++) {
                cows2[reverseMappings[j] - 1] = cows[j];
            }
            cows = cows2;
        }

        for (int i = 0; i < N; i++) {
            out.println(cows[i].ID);
        }
        out.flush();
    }

    private static class Cow {
        int ID;

        public Cow(int ID) {
            this.ID = ID;
        }
    }

    private static class Mapping {
        int one;
        int two;

        public Mapping(int one, int two) {
            this.one = one;
            this.two = two;
        }
    }

    static int partition(Mapping arr[], int low, int high) {
        int pivot = arr[high].two;
        int i = (low-1); // index of smaller element
        for (int j=low; j<high; j++) {
            // If current element is smaller than or
            // equal to pivot
            if (arr[j].two <= pivot) {
                i++;
    
                // swap arr[i] and arr[j]
                Mapping temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    
        // swap arr[i+1] and arr[high] (or pivot)
        Mapping temp = arr[i+1];
        arr[i+1] = arr[high];
        arr[high] = temp;
    
        return i+1;
    }
    
    static void sort(Mapping arr[], int low, int high) {
        if (low < high) {
            /* pi is partitioning index, arr[pi] is
                now at right place */
            int pi = partition(arr, low, high);
    
            // Recursively sort elements before
            // partition and after partition
            sort(arr, low, pi-1);
            sort(arr, pi+1, high);
        }
    }
}