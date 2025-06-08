/*
ID: ishaangoyal12
LANG: JAVA
TASK: censor
*/

import java.io.*;
import java.util.*;

public class censor {

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("censor.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("censor.out")));

        String message = in.readLine();
        String substring = in.readLine();

        StringBuilder censored = new StringBuilder();
        
        for (int i = 0; i < message.length(); i++) {
            censored.append(message.charAt(i));
            if (censored.length() > substring.length()) {
                String check = censored.substring(censored.length() - substring.length());
                if (check.equals(substring)) {
                    censored.delete(censored.length() - substring.length(), censored.length());
                }
            }
        }

        out.println(censored.toString());
        out.flush();
    }
}