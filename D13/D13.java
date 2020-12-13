import java.util.*;

public class D13 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int time = in.nextInt();

        String[] line = in.next().split(",");
        in.close();
        
        int minTime = Integer.MAX_VALUE;
        int ans = 0;
        for(int i = 0; i < line.length; i++) {
            if(!line[i].equals("x")) {
                int busTime = Integer.parseInt(line[i]);
                int remainingTime = busTime - time % busTime;
                if(remainingTime < minTime) {
                    minTime = remainingTime;
                    ans = remainingTime * busTime;
                }
            }
        }

        System.out.println(ans);
    }
}
