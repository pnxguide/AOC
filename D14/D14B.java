import java.util.*;

public class D14B {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        Map<Long, Long> mem = new HashMap<>();
        String mask = "";
        while(in.hasNextLine()) {
            String line = in.nextLine();
            String[] tokens = line.split(" = ");
            
            if(tokens[0].equals("mask")) {
                mask = tokens[1];
            } else {
                String addrStr = tokens[0].replace("mem[", "")
                    .replace("]", "");
                long addr = Long.parseLong(addrStr);
                long val = Long.parseLong(tokens[1]);

                for(Long addrLong : mask(mask, addr)) {
                    mem.put(addrLong, val);
                }
            }
        }
        in.close();

        long sum = 0;
        for(Long key : mem.keySet()) {
            sum += mem.get(key);
        }
        System.out.println(sum);
    }

    static List<Long> mask(String mask, long val) {
        char[] maskBits = mask.toCharArray();
        int[] valBits = new int[36];

        int ptr = maskBits.length - 1;
        long tmp = val;
        while(tmp > 0) {
            if(maskBits[ptr] == '1') {
                valBits[ptr--] = 1;
            } else {
                valBits[ptr--] = (int)(tmp % 2);
            }
            tmp /= 2;
        }

        while(ptr >= 0) {
            if(maskBits[ptr] == '1') {
                valBits[ptr] = 1;
            }
            ptr--;
        }

        List<Integer> xIdx = new ArrayList<>();
        for(int i = 0; i < maskBits.length; i++) {
            if(maskBits[i] == 'X') {
                xIdx.add(i);
            }
        }
        int xCnt = xIdx.size();

        List<Long> addrs = new ArrayList<>();
        long permutation = (long)Math.pow(2, xCnt);
        for(int i = 0; i < permutation; i++) {
            int[] iBits = new int[xCnt];
            ptr = 0;
            tmp = i;
            while(tmp > 0) {
                iBits[ptr++] = (int)(tmp % 2);
                tmp /= 2;
            }

            for(int j = 0; j < xCnt; j++) {
                valBits[xIdx.get(j)] = iBits[j];
            }

            long sum = 0;
            long multiple = (long)Math.pow(2, maskBits.length - 1);
            for(int j = 0; j < maskBits.length; j++) {
                sum += multiple * valBits[j];
                multiple /= 2;
            }
            addrs.add(sum);
        }

        return addrs;
    }
}