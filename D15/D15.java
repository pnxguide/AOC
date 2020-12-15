import java.util.*;

public class D15 {
    public static void main(String[] args) {
        int[] starts = {0,1,4,13,15,12,16};
        Map<Integer, Integer> prev = new HashMap<>();

        for(int i = 0; i < starts.length; i++) {
            prev.put(starts[i], i + 1);
        }

        int cur = 0;
        int diff = 0;
        for(int i = starts.length + 1; i < 30000000; i++) {
            diff = prev.get(cur) == null ? 0 : i - prev.get(cur);
            prev.put(cur, i);
            cur = diff;
        }

        System.out.println(cur);
    }
}