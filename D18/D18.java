import java.util.*;

public class D18 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        long result = 0;
        while(in.hasNextLine()) {
            String[] line = (in.nextLine() + ")")
                .replace("(", "( ")
                .replace(")", " )")
                .split(" ");
            Deque<String> stack = new ArrayDeque<>();
            stack.push("(");
            for(String token : line) {
                if(token.equals(")")) {
                    String cur = stack.pop();
                    Deque<Long> nums = new ArrayDeque<>();
                    Deque<Character> ops = new ArrayDeque<>();
                    while(!cur.equals("(")) {
                        switch(cur) {
                            case "+":
                            case "*":
                                ops.push(cur.charAt(0));
                                break;
                            default:
                                nums.push(Long.parseLong(cur));
                        }
                        cur = stack.pop();
                    }
                    long sum = nums.removeFirst();
                    while(!ops.isEmpty()) {
                        char op = ops.removeFirst();
                        if(op == '*' && ops.contains('+')) {
                            nums.addLast(sum);
                            ops.addLast('*');
                            sum = nums.removeFirst();
                            continue;
                        }
                        long b = nums.removeFirst();
                        switch(op) {
                            case '+':
                                sum += b;
                                break;
                            case '*':
                                sum *= b;
                                break;
                        }
                    }
                    stack.push(""+sum);
                } else {
                    stack.push(token);
                }
            }
            result += Long.parseLong(stack.pop());
        }
        System.out.println(result);
        in.close();
    }
}