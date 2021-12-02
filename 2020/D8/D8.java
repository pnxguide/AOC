import java.util.*;

public class D8 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        List<String> opCodeList = new ArrayList<>();
        List<Integer> opValueList = new ArrayList<>();

        while(in.hasNextLine()) {
            String[] tokens = in.nextLine().split(" ");
            opCodeList.add(tokens[0]);
            opValueList.add(Integer.parseInt(tokens[1]));
        }
        in.close();

        String[] ops = opCodeList.toArray(String[]::new);
        Integer[] vals = opValueList.toArray(Integer[]::new);

        int accumulator = 0;
        int ptr = 0;
        boolean[] isVisited = new boolean[ops.length];

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
        }

        System.out.println(accumulator);
    }
}
