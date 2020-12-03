import java.util.*;

public class D1 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        List<Integer> inputs = new ArrayList<>();
        while(in.hasNext()) {
            inputs.add(in.nextInt());
        }

        in.close();

        Integer[] arr = inputs.toArray(new Integer[inputs.size()]);

        /*
        for(int i = 0; i < arr.length; i++) {
            for(int j = i + 1; j < arr.length; j++) {
                int sum = arr[i] + arr[j];
                if(sum == 2020) {
                    System.out.println(arr[i] * arr[j]);
                }
            }
        }
        */

        for(int i = 0; i < arr.length; i++) {
            for(int j = i + 1; j < arr.length; j++) {
                for(int k = j + 1; k < arr.length; k++) {
                    int sum = arr[i] + arr[j] + arr[k];
                    if(sum == 2020) {
                        System.out.println(arr[i] * arr[j] * arr[k]);
                    }
                }
            }
        }
    }
}