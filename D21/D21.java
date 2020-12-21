import java.util.*;

public class D21 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        Map<String, Map<String, Integer>> foodMap = new HashMap<>();
        Map<String, Integer> textMap = new HashMap<>();

        while(in.hasNextLine()) {
            String line = in.nextLine();
            String[] tokens = line.split(" [(]contains ");
            String[] texts = tokens[0].split(" ");
            String[] foods = tokens[1].replace(")", "")
                .split(", ");
            
            for(String text : texts) {
                if(textMap.get(text) == null) {
                    textMap.put(text, 1);
                } else {
                    textMap.put(text, textMap.get(text) + 1);
                }
            }
                
            for(String food : foods) {
                if(foodMap.get(food) == null) {
                    foodMap.put(food, new HashMap<>());
                }

                Map<String, Integer> textCount = foodMap.get(food);
                for(String text : texts) {
                    if(textCount.get(text) == null) {
                        textCount.put(text, 1);
                    } else {
                        textCount.put(text, textCount.get(text) + 1);
                    }
                }
            }
        }
        in.close();

        // Part 1
        // Set<String> allergens = new HashSet<>();
        // for(String food : foodMap.keySet()) {
        //     Map<String, Integer> textCount = foodMap.get(food);

        //     int max = 0;
        //     for(String text : textCount.keySet()) {
        //         Integer count = textCount.get(text);
        //         if(count > max) {
        //             max = count;
        //         }
        //     }

        //     for(String text : textCount.keySet()) {
        //         Integer count = textCount.get(text);
        //         if(count == max) {
        //             allergens.add(text);
        //         }
        //     }
        // }
        
        // int ans = 0;
        // for(String text : textMap.keySet()) {
        //     if(!allergens.contains(text)) {
        //         ans += textMap.get(text);
        //     }
        // }

        // System.out.println(ans);

        Map<String, List<String>> inverted = new HashMap<>();
        for(String food : foodMap.keySet()) {
            Map<String, Integer> textCount = foodMap.get(food);

            int max = 0;
            for(String text : textCount.keySet()) {
                Integer count = textCount.get(text);
                if(count > max) {
                    max = count;
                }
            }

            inverted.put(food, new ArrayList<>());

            for(String text : textCount.keySet()) {
                Integer count = textCount.get(text);
                if(count == max) {
                    inverted.get(food).add(text);
                }
            }
        }

        Map<String, String> dictionary = new HashMap<>();
        int foodLength = inverted.keySet().size();
        for(int i = 0; i < foodLength; i++) {
            String textString = "";

            for(String food : inverted.keySet()) {
                List<String> texts = inverted.get(food);
                if(texts.size() == 1) {
                    textString = texts.get(0);
                    dictionary.put(food, textString);
                    break;
                }
            }

            for(String food : inverted.keySet()) {
                List<String> texts = inverted.get(food);
                texts.remove(textString);
            }
        }

        StringBuilder ans = new StringBuilder();
        dictionary.keySet()
            .stream()
            .sorted(Comparator.naturalOrder())
            .forEach(element -> {
                ans.append(dictionary.get(element))
                    .append(",");
            });
        
        System.out.println(ans.substring(0, ans.length() - 1));
    }
}