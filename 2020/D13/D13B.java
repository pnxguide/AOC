import java.util.*;

public class D13B {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        in.nextInt();
        String[] line = in.next().split(",");
        in.close();

        int maxIndex = 0;
        int max = 0;

        int[] buses = new int[line.length];
        for(int i = 0; i < line.length; i++) {
            if(line[i].equals("x")) continue;
            buses[i] = Integer.parseInt(line[i]);
            if(buses[i] > max) {
                maxIndex = i;
                max = buses[i];
            }
        }

        long[] starts = new long[line.length];
        long[] lcm = new long[line.length];

        long maxIncrement = 0;
        int maxIncrementIndex = 0;

        for(int i = 0; i < buses.length; i++) {
            if(i == maxIndex) continue;
            int diff = i - maxIndex;
            lcm[i] = max * buses[i];

            if(lcm[i] > maxIncrement) {
                maxIncrementIndex = i;
                maxIncrement = lcm[i];
            }

            for(int j = 1; j < max; j++) {
                long x = j * buses[i];
                long y = 0;
                if(i < maxIndex) {
                    y = x - ((long)Math.ceil((double)x / (double)max) * max);
                } else if(i > maxIndex) {
                    y = x - (x / max * max);
                }
                if(y == diff) {
                    starts[i] = x - i;
                }
            }
        }

        for(long i = starts[maxIncrementIndex]; ; i += maxIncrement) {
            boolean isSame = true;
            for(int j = 0; j < buses.length; j++) {
                if(starts[j] == 0 || maxIncrementIndex == j) continue;
                if((i % lcm[j] - starts[j]) % lcm[j] != 0) {
                    isSame = false;
                    break;
                }
            }

            if(isSame) {
                System.out.println(i);
                break;
            }
        }
    }
}
