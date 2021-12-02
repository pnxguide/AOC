import java.util.*;

public class D2 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int valid = 0;

        while(in.hasNext()) {
            String[] inputs = in.nextLine().split("[- :]+");
            int min = Integer.parseInt(inputs[0]);
            int max = Integer.parseInt(inputs[1]);
            char target = inputs[2].charAt(0);
            char[] pwd = inputs[3].toCharArray();

            /*
            int cnt = 0;
            for(int i = 0; i < pwd.length; i++) {
                if(pwd[i] == target) {
                    cnt++;
                }
            }

            if(cnt >= min && cnt <= max) {
                valid++;
            }
            */

            if(pwd[min - 1] == target ^ pwd[max - 1] == target) {
                valid++;
            }
        }
        in.close();

        System.out.println(valid);
    }
}