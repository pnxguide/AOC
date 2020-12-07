import java.util.*;

public class D7B {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        
        // things about strings & indexes
        Map<String, Map<String, Integer>> colorMap = new HashMap<>();

        while(in.hasNextLine()) {
            String line = in.nextLine();

            String[] allBags = line.split(" bags contain ");

            String bagColor = allBags[0];
            String[] innerBagArray = allBags[1].split(" (bag)s{0,1}(, |.)");

            Map<String, Integer> innerBagMap = new HashMap<>();
            for(String b : innerBagArray) {
                if(b.equals("no other")) break;
                String[] bagColorAndCount = b.split(" ", 2);

                int bagCount = Integer.parseInt(bagColorAndCount[0]);
                String innerBagColor = bagColorAndCount[1];

                innerBagMap.put(innerBagColor, bagCount);
            }

            colorMap.put(bagColor, innerBagMap);
        }
        in.close();

        // depth first search
        int totalBagCount = 0;
        Deque<String> colorStack = new ArrayDeque<>();
        Deque<Integer> currentStack = new ArrayDeque<>();
        Deque<Integer> parentStack = new ArrayDeque<>();

        colorStack.push("shiny gold");
        currentStack.push(1);
        parentStack.push(1);

        while(!colorStack.isEmpty()) {
            String currentColor = colorStack.pop();
            int currentCount = currentStack.pop() * parentStack.pop();
            totalBagCount += currentCount;

            Map<String, Integer> innerBagMap = colorMap.get(currentColor);
            if(colorMap.get(currentColor) == null) continue;
            Set<String> innerBagSet = innerBagMap.keySet();

            for(String bag : innerBagSet) {
                colorStack.push(bag);
                currentStack.push(innerBagMap.get(bag));
                parentStack.push(currentCount);
            }
        }
        
        System.out.println(totalBagCount - 1 /* uncount the shiny gold bag */);
    }
}
