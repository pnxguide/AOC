import java.util.*;

public class D7 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        
        // things about strings & inverted index
        Map<String, Set<String>> colorMap = new HashMap<>();

        while(in.hasNextLine()) {
            String line = in.nextLine();

            String[] allBags = line.split(" bags contain ");

            String bagColor = allBags[0];
            String[] bagInsideArray = allBags[1].split(" (bag)s{0,1}(, |.)");

            for(String b : bagInsideArray) {
                if(b.equals("no other")) continue;
                String bagInsideColor = b.replaceAll("[0-9]+ ", "");

                if(colorMap.get(bagInsideColor) == null) {
                    colorMap.put(bagInsideColor, new HashSet<>());
                }

                Set<String> bagInsideSet = colorMap.get(bagInsideColor);
                bagInsideSet.add(bagColor);

                colorMap.put(bagInsideColor, bagInsideSet);
            }
        }

        // depth first search
        Set<String> answers = new HashSet<>();
        Stack<String> dfs = new Stack<>();
        dfs.push("shiny gold");

        while(!dfs.isEmpty()) {
            String currentColor = dfs.pop();

            if(colorMap.get(currentColor) == null) continue;

            for(String bagColor : colorMap.get(currentColor)) {
                if(answers.contains(bagColor)) continue;

                answers.add(bagColor);
                dfs.push(bagColor);
            }
        }
        
        System.out.println(answers.size());
        in.close();
    }
}
