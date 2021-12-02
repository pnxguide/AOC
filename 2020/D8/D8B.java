import java.util.*;

public class D8B {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        List<String> opCodeList = new ArrayList<>();
        List<Integer> opValueList = new ArrayList<>();

        int idx = 0;
        List<Integer> candidateList = new ArrayList<>();

        while(in.hasNextLine()) {
            String[] tokens = in.nextLine().split(" ");
            String op = tokens[0];
            int val = Integer.parseInt(tokens[1]);

            opCodeList.add(op);
            opValueList.add(val);

            if(op.equals("jmp") && val <= 0) {
                candidateList.add(idx);
            }

            idx++;
        }
        in.close();

        String[] ops = opCodeList.toArray(String[]::new);
        Integer[] vals = opValueList.toArray(Integer[]::new);

        boolean[] isVisited;

        int accumulator;
        int ptr = 0;

        for(Integer i : candidateList) {
            isVisited = new boolean[ops.length];
            accumulator = 0;
            ptr = 0;
            ops[i] = "nop";

            while(!isVisited[ptr]) {
                isVisited[ptr] = true;

                switch(ops[ptr]) {
                    case "jmp":
                        ptr += vals[ptr];
                        break;
                    case "acc":
                        accumulator += vals[ptr];
                    case "nop":
                        ptr++;
                        break;
                }

                if(ptr >= ops.length) {
                    System.out.println(idx);
                    System.out.println(accumulator);
                    return;
                }
            }

            ops[i] = "jmp";
        }
    }
}
