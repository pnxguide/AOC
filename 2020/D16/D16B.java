import java.util.*;

public class D16B {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        List<String> validTitle = new ArrayList<>();
        List<List<Integer>> validList = new ArrayList<>();

        boolean[] isValid = new boolean[1000];
        boolean[][] isValidField = new boolean[1000][1];
        Set<Integer>[] nearbyTickets = new HashSet[1];
        int[] yourTickets = new int[1];

        int fieldCount = 0;
        int blankLineCount = 0;
        while(in.hasNextLine()) {
            String line = in.nextLine();
            if(line.equals("your ticket:")) {
                fieldCount = validTitle.size();
                isValidField = new boolean[1000][fieldCount];
                nearbyTickets = new Set[fieldCount];
                for(int i = 0; i < fieldCount; i++) {
                    for(int v : validList.get(i)) {
                        isValidField[v][i] = true;
                    }
                    nearbyTickets[i] = new HashSet<>();
                }
                yourTickets = new int[fieldCount];
                continue;
            } else if(line.equals("nearby tickets:")) {
                continue;
            } else if(line.equals("")) {
                blankLineCount++;
                continue;
            }
            
            switch(blankLineCount) {
                case 0:
                    String[] tokens = line.split(":");
                    String[] ranges = tokens[1].replace(" ", "")
                        .split("or");
                    List<Integer> validNo = new ArrayList<>();
                    for(String range : ranges) {
                        String[] bounds = range.split("-");
                        int min = Integer.parseInt(bounds[0]);
                        int max = Integer.parseInt(bounds[1]);
                        for(int i = min; i <= max; i++) {
                            isValid[i] = true;
                            validNo.add(i);
                        }
                    }
                    validTitle.add(tokens[0]);
                    validList.add(validNo);
                    break;
                case 1:
                    String[] mySeats = line.split(",");
                    for(int i = 0; i < fieldCount; i++) {
                        yourTickets[i] = Integer.parseInt(mySeats[i]);
                        nearbyTickets[i].add(yourTickets[i]);
                    }
                    break;
                case 2:
                    String[] seats = line.split(",");
                    boolean isSeatValid = true;
                    for(int i = 0; i < fieldCount; i++) {
                        int seatNo = Integer.parseInt(seats[i]);
                        if(!isValid[seatNo]) {
                            isSeatValid = false;
                            break;
                        }
                    }

                    if(isSeatValid) {
                        for(int i = 0; i < fieldCount; i++) {
                            int seatNo = Integer.parseInt(seats[i]);
                            nearbyTickets[i].add(seatNo);
                        }
                    }
                    break;
            }
        }
        in.close();

        List<Integer>[] possibleMap = new List[fieldCount];
        for(int i = 0; i < fieldCount; i++) {
            possibleMap[i] = new ArrayList<>();
        }

        // loop isValidField
        for(int i = 0; i < fieldCount; i++) {
            // loop nearbyTicket
            for(int j = 0; j < fieldCount; j++) {
                boolean isCorrect = true;
                for(Integer seatNo : nearbyTickets[j]) {
                    if(!isValidField[seatNo][i]) {
                        isCorrect = false;
                        break;
                    }
                }
                if(isCorrect) {
                    possibleMap[i].add(j);
                }
            }
        }

        int[] map = new int[fieldCount];
        for(int i = 0; i < fieldCount; i++) {
            map[i] = -1;
        }

        for(int i = 1; i <= fieldCount; i++) {
            for(int j = 0; j < fieldCount; j++) {
                if(possibleMap[j].size() == i) {
                    for(Integer x : possibleMap[j]) {
                        if(map[x] == -1) {
                            map[x] = j;
                            break;
                        }
                    }
                }
            }
        }

        long ans = 1;
        for(int i = 0; i < fieldCount; i++) {
            if(validTitle.get(i).split(" ")[0].equals("departure")) {
                for(int j = 0; j < map.length; j++) {
                    if(map[j] == i) {
                        ans *= yourTickets[j];
                    }
                }
            }
        }

        System.out.println(ans);
    }
}