import java.util.*;

public class D16 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        boolean[] isValid = new boolean[1000];
        int sum = 0;

        int blankLineCount = 0;
        while(in.hasNextLine()) {
            String line = in.nextLine();
            if(line.equals("your ticket:") || line.equals("nearby tickets:")) {
                continue;
            } else if(line.equals("")) {
                blankLineCount++;
                continue;
            }
            
            switch(blankLineCount) {
                case 0:
                    String[] tokens = line.split(":");
                    String[] ranges = tokens[1].replace(" ", "")
                        .split("or");
                    for(String range : ranges) {
                        String[] bounds = range.split("-");
                        int min = Integer.parseInt(bounds[0]);
                        int max = Integer.parseInt(bounds[1]);
                        for(int i = min; i <= max; i++) {
                            isValid[i] = true;
                        }
                    }
                    break;
                case 1:
                    break;
                case 2:
                    String[] seats = line.split(",");
                    for(String seat : seats) {
                        int seatNo = Integer.parseInt(seat);
                        sum += isValid[seatNo] ? 0 : seatNo;
                    }
                    break;
            }
        }
        in.close();

        System.out.println(sum);
    }
}