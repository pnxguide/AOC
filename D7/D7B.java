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
            String[] bagInsideArray = allBags[1].split(" (bag)s{0,1}(,|.)( ){0,1}");

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
        Stack<DFSParameters> dfs = new Stack<>();
        dfs.push(new DFSParameters("shiny gold", 1, 1));

        while(!dfs.isEmpty()) {
            DFSParameters params = dfs.pop();

            System.out.println(params);

            String currentColor = params.color;
            int currentCount = params.bagCount * params.parentBagCount;
            totalBagCount += currentCount;

            Map<String, Integer> bagInsideMap = colorMap.get(currentColor);
            if(colorMap.get(currentColor) == null) continue;
            Set<String> bagInsideSet = bagInsideMap.keySet();

            for(String bag : bagInsideSet) {
                dfs.push(new DFSParameters(bag, bagInsideMap.get(bag), currentCount));
            }
        }
        
        System.out.println(totalBagCount - 1 /* uncount the shiny gold bag */);

        in.close();
    }
}

class DFSParameters {
    String color;
    int bagCount;
    int parentBagCount;

    DFSParameters(String color, 
        int bagCount, 
        int parentBagCount) {

        this.color = color;
        this.bagCount = bagCount;
        this.parentBagCount = parentBagCount;
    }

    @Override
    public String toString() {
        return color + " " + bagCount + " " + parentBagCount;
    }
}