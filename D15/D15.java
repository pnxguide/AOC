import java.util.*;

public class D15 {
    public static void main(String[] args) {
        int[] starts = {0,1,4,13,15,12,16};
        Map<Integer, Integer> last = new HashMap<>();
        Map<Integer, Integer> prev = new HashMap<>();

        for(int i = 0; i < starts.length; i++) {
            last.put(starts[i], i + 1);
        }

        int cur = starts[starts.length - 1];
        for(int i = starts.length + 1; i <= 30000000; i++) {
            if(prev.get(cur) == null) {
                cur = 0;
                prev.put(cur, last.get(cur));
            } else {
                cur = last.get(cur) - prev.get(cur);
                if(last.get(cur) != null) {
                    prev.put(cur, last.get(cur));
                }
            }
            last.put(cur, i);
        }

        System.out.println(cur);
    }
}