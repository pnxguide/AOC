import java.util.*;

public class D24 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        Map<String, Integer> flippedTiles = new HashMap<>();
        int minX = Integer.MAX_VALUE;
        int minY = Integer.MAX_VALUE;
        int maxX = Integer.MIN_VALUE;
        int maxY = Integer.MIN_VALUE;

        while(in.hasNext()) {
            char[] line = in.next().toCharArray();
            int x = 0;
            int y = 0;

            for(int i = 0; i < line.length; i++) {
                switch(line[i]) {
                    case 'n':
                        if(line[++i] == 'w') {
                            --y;
                        } else {
                            ++x;
                            --y;
                        }
                        break;
                    case 's':
                        if(line[++i] == 'w') {
                            --x;
                            ++y;
                        } else {
                            ++y;
                        }
                        break;
                    case 'w':
                        --x;
                        break;
                    case 'e':
                        ++x;
                        break;
                }
            }

            if(x > maxX) maxX = x;
            if(x < minX) minX = x;
            if(y > maxY) maxY = y;
            if(y < minY) minY = y;

            String coor = x + ":" + y;
            Integer counter = flippedTiles.get(coor);
            if(counter == null) {
                flippedTiles.put(coor, 1);
            } else {
                flippedTiles.put(coor, ++counter);
            }
        }
        in.close();

        int rangeX = maxX - minX + 202;
        int rangeY = maxY - minY + 202;
        boolean[][] floors = new boolean[rangeY][rangeX];

        // int blackTileCount = 0;
        for(String coor : flippedTiles.keySet()) {
            if(flippedTiles.get(coor) % 2 != 0) {
                // blackTileCount++;
                String[] coorTokens = coor.split(":");
                floors[Integer.parseInt(coorTokens[1]) + minY + 101][Integer.parseInt(coorTokens[0]) + minX + 101] = true;
            }
        }
        // System.out.println(blackTileCount);

        for(int day = 0; day < 100; day++) {
            boolean[][] floorCopies = new boolean[rangeY][rangeX];
            for(int i = 0; i < rangeY; i++) {
                floorCopies[i] = floors[i].clone();
            }
            
            for(int i = 1; i < rangeY - 1; i++) {
                for(int j = 1; j < rangeX - 1; j++) {
                    int count = 0;
                    if(floors[i-1][j]) count++;
                    if(floors[i-1][j+1]) count++;
                    if(floors[i][j-1]) count++;
                    if(floors[i][j+1]) count++;
                    if(floors[i+1][j-1]) count++;
                    if(floors[i+1][j]) count++;

                    if(floors[i][j] && (count == 0 || count > 2)) {
                        floorCopies[i][j] = false;
                    } else if(!floors[i][j] && count == 2) {
                        floorCopies[i][j] = true;
                    }
                }
            }

            for(int i = 0; i < rangeY; i++) {
                floors[i] = floorCopies[i].clone();
            }
        }


        int tileCount = 0;
        for(int i = 0; i < rangeY; i++) {
            for(int j = 0; j < rangeX; j++) {
                if(floors[i][j]) tileCount++;
            }
        }
        System.out.println(tileCount);
    }
}