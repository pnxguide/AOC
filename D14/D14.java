import java.util.*;

public class D14 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        Map<Integer, Long> mem = new HashMap<>();
        String mask = "";

        while(in.hasNextLine()) {
            String line = in.nextLine();
            String[] tokens = line.split(" = ");
            
            if(tokens[0].equals("mask")) {
                mask = tokens[1];
            } else {
                String addrStr = tokens[0].replace("mem[", "")
                    .replace("]", "");
                int addr = Integer.parseInt(addrStr);
                long val = Integer.parseInt(tokens[1]);
                mem.put(addr, mask(mask, val));
            }
        }
        in.close();

        long sum = 0;
        for(Integer key : mem.keySet()) {
            sum += mem.get(key);
        }
        System.out.println(sum);
    }

    static long mask(String mask, long val) {
        char[] maskBits = mask.toCharArray();
        int[] valBits = new int[36];
        
        int ptr = maskBits.length - 1;
        long tmp = val;
        while(tmp > 0) {
            if(tmp % 2 == 0) {
                valBits[ptr--] = 0;
            } else {
                valBits[ptr--] = 1;
            }
            tmp /= 2;
        }

        long sum = 0;
        long multiple = (long)Math.pow(2, maskBits.length - 1);
        for(int i = 0; i < maskBits.length; i++) {
            switch(maskBits[i]) {
                case 'X':
                    sum += multiple * valBits[i];
                    break;
                case '1':
                    sum += multiple;
                    break;
            }
            multiple /= 2;
        }

        return sum;
    }
}