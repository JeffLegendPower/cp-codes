/*
ID: ishaangoyal12
LANG: JAVA
TASK: blist
*/

import java.io.*;
import java.util.*;

public class blist {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("blist.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("blist.out")));

        int N = Integer.parseInt(in.readLine());

        Cow[] cows = new Cow[N];
        for (int i = 0; i < N; i++) {
            String[] cowInfo = in.readLine().split(" ");
            cows[i] = new Cow(Integer.parseInt(cowInfo[0]), Integer.parseInt(cowInfo[1]), Integer.parseInt(cowInfo[2]));
        }

        sort(cows, 0, N - 1);

        int maxUsedBuckets = 0;
        // for (int i = cows[0].start; i <= cows[N - 1].end; i++) {
        for (int i = 1; i <= 1000; i++) {
            int usedBuckets = 0;
            for (int j = 0; j < N; j++) {
                if (cows[j].end <= i) {
                    continue;
                } else if (cows[j].start > i) {
                    continue;
                }
                usedBuckets += cows[j].buckets;
            }

            if (usedBuckets > maxUsedBuckets) maxUsedBuckets = usedBuckets;
        }

        out.println(maxUsedBuckets);
        out.flush();
    }

    static class Cow {
        int start;
        int end;
        int buckets;

        public Cow(int start, int end, int buckets) {
            this.start = start;
            this.end = end;
            this.buckets = buckets;
        }
    }

    static int partition(Cow arr[], int low, int high) {
        int pivot = arr[high].start;
        int i = (low-1); // index of smaller element
        for (int j=low; j<high; j++) {
            // If current element is smaller than or
            // equal to pivot
            if (arr[j].start <= pivot) {
                i++;
    
                // swap arr[i] and arr[j]
                Cow temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    
        // swap arr[i+1] and arr[high] (or pivot)
        Cow temp = arr[i+1];
        arr[i+1] = arr[high];
        arr[high] = temp;
    
        return i+1;
    }
    
    static void sort(Cow arr[], int low, int high) {
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
