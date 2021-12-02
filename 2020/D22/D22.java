import java.util.*;

public class D22 {

    static int count = 1;

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int player = 0;
        ArrayDeque<Integer> player1 = new ArrayDeque<>();
        ArrayDeque<Integer> player2 = new ArrayDeque<>();

        while(in.hasNextLine()) {
            String line = in.nextLine();

            if(line.equals("")) {
                continue;
            }

            if(line.contains("Player")) {
                player++;
                continue;
            }

            int card = Integer.parseInt(line);
            switch(player) {
                case 1:
                    player1.addLast(card);
                    break;
                case 2:
                    player2.addLast(card);
                    break;
            }
        }
        in.close();

        // int sum = 0;
        // if(player1.size() > 0) {
        //     int length = player1.size();
        //     for(int i = 1; i <= length; i++) {
        //         sum += player1.removeLast() * i;
        //     }
        // } else if(player2.size() > 0) {
        //     int length = player2.size();
        //     for(int i = 1; i <= length; i++) {
        //         sum += player2.removeLast() * i;
        //     }
        // }
        // System.out.println(sum);

        playRound(player1, player2, count);
    }

    static int playRound(ArrayDeque<Integer> p1, ArrayDeque<Integer> p2, int gameCount) {
        ArrayDeque<Integer> player1 = p1.clone();
        ArrayDeque<Integer> player2 = p2.clone();

        Map<String, Boolean> conf = new HashMap<>();

        while(player1.size() > 0 && player2.size() > 0) {
            int playerWon = 1;
            int card1 = 0;
            int card2 = 0;

            if(conf.get(player1.toString() + player2.toString()) != null) {
                playerWon = 1;
                card1 = player1.removeFirst();
                card2 = player2.removeFirst();
            } else {
                conf.put(player1.toString() + player2.toString(), true);
    
                card1 = player1.removeFirst();
                card2 = player2.removeFirst();
    
                if(card1 <= player1.size() && card2 <= player2.size()) {
                    ArrayDeque<Integer> p1copies = new ArrayDeque<>();
                    ArrayDeque<Integer> p2copies = new ArrayDeque<>();
                    Integer[] p1arr = player1.toArray(Integer[]::new);
                    Integer[] p2arr = player2.toArray(Integer[]::new);
    
                    for(int i = 0; i < card1; i++) {
                        p1copies.add(p1arr[i]);
                    }
    
                    for(int i = 0; i < card2; i++) {
                        p2copies.add(p2arr[i]);
                    }
                    
                    playerWon = playRound(p1copies, p2copies, ++count);
                } else if(card1 > card2) {
                    playerWon = 1;
                } else if(card1 < card2) {
                    playerWon = 2;
                }
            }

            if(playerWon == 1) {
                player1.addLast(card1);
                player1.addLast(card2);
            } else {
                player2.addLast(card2);
                player2.addLast(card1);
            }
        }

        int sum = 0;
        if(player1.size() > 0) {
            if(gameCount == 1) {
                int length = player1.size();
                for(int i = 1; i <= length; i++) {
                    sum += player1.removeLast() * i;
                }
                System.out.println(sum);
            }
            return 1;
        } else if(player2.size() > 0) {
            if(gameCount == 1) {
                int length = player2.size();
                for(int i = 1; i <= length; i++) {
                    sum += player2.removeLast() * i;
                }
                System.out.println(sum);
            }
            return 2;
        }

        return 0;
    }
}