import java.util.*;

public class D6 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int sum = 0;

        // Set<Character> answers = new HashSet<>();
        int[] answers = new int[26];
        int peopleCount = 0;

        while(in.hasNextLine()) {
            String line = in.nextLine();
            if(line.equals("")) {
                /*
                sum += answers.size();
                answers = new HashSet<>();
                */

                for(int i : answers) {
                    if(i == peopleCount) sum++;
                }

                answers = new int[26];
                peopleCount = 0;
                continue;
            }

            char[] choices = line.toCharArray();
            for(char c : choices) {
                // answers.add(c);
                answers[c - 0x61]++;
            }

            peopleCount++;
        }

        in.close();

        // sum += answers.size();
        
        for(int i : answers) {
            if(i == peopleCount) sum++;
        }

        System.out.println(sum);
    }
}