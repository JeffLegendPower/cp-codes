import java.io.*;
import java.util.*;

public class cometogether {
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int t = scanner.nextInt();
        for (int i = 0; i < t; i++) {
          int ax = scanner.nextInt();
          int ay = scanner.nextInt();
          int bx = scanner.nextInt();
          int by = scanner.nextInt();
          int cx = scanner.nextInt();
          int cy = scanner.nextInt();
    
          int ans = 1;
          if ((bx >= ax && cx >= ax) || (bx <= ax && cx <= ax)) {
            ans += Math.min(Math.abs(bx - ax), Math.abs(cx - ax));
          }
          if ((by >= ay && cy >= ay) || (by <= ay && cy <= ay)) {
            ans += Math.min(Math.abs(by - ay), Math.abs(cy - ay));
          }
          System.out.println(ans);
        }
    }
}
