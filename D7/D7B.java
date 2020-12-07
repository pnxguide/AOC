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
            String[] bagInsideArray = allBags[1].split(" (bag)s{0,1}(, |.)");

            Map<String, Integer> bagInsideMap = new HashMap<>();
            for(String b : bagInsideArray) {
                if(b.equals("no other")) continue;
                String[] bagColorAndCount = b.split(" ", 2);

                int bagCount = Integer.parseInt(bagColorAndCount[0]);
                String bagInsideColor = bagColorAndCount[1];

                bagInsideMap.put(bagInsideColor, bagCount);
            }

            colorMap.put(bagColor, bagInsideMap);
        }

        // depth first search
        int totalBagCount = 0;
        Stack<String> colorStack = new Stack<>();
        Stack<Integer> currentStack = new Stack<>();
        Stack<Integer> parentStack = new Stack<>();

        colorStack.push("shiny gold");
        currentStack.push(1);
        parentStack.push(1);

        while(!colorStack.isEmpty()) {
            String currentColor = colorStack.pop();
            int currentCount = currentStack.pop() * parentStack.pop();
            totalBagCount += currentCount;

            Map<String, Integer> bagInsideMap = colorMap.get(currentColor);
            if(colorMap.get(currentColor) == null) continue;
            Set<String> bagInsideSet = bagInsideMap.keySet();

            for(String bag : bagInsideSet) {
                colorStack.push(bag);
                currentStack.push(bagInsideMap.get(bag));
                parentStack.push(currentCount);
            }
        }
        
        System.out.println(totalBagCount - 1 /* uncount the shiny gold bag */);

        in.close();
    }
}
