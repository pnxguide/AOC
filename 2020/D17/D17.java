import java.util.Scanner;

public class D17 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        final int SPACE_INIT_ROW = 8;
        final int SPACE_INIT_COL = 8;
        final int SPACE_INIT_Z = 1;
        final int SPACE_INIT_W = 1;
        final int ROUND = 6;

        int totalW = SPACE_INIT_W+((ROUND+1)*2);
        int totalZ = SPACE_INIT_Z+((ROUND+1)*2);
        int totalRow = SPACE_INIT_ROW+((ROUND+1)*2);
        int totalCol = SPACE_INIT_COL+((ROUND+1)*2);
        boolean[][][][] spaces = new boolean[totalRow][totalCol][totalZ][totalW];

        int row = 0;
        while(in.hasNextLine()) {
            char[] lineArr = in.nextLine().toCharArray();
            for(int i = 0; i < lineArr.length; i++) {
                spaces[ROUND+1+row][ROUND+1+i][ROUND+1][ROUND+1] = lineArr[i] == '#';
            }
            row++;
        }
        in.close();

        for(int cycle = 1; cycle <= ROUND; cycle++) {
            boolean[][][][] currentSpaces = new boolean[totalRow][totalCol][totalZ][totalW];
            for(int z = (ROUND+1)-cycle; z < (ROUND+2)+cycle; z++) {
                for(int w = (ROUND+1)-cycle; w < (ROUND+2)+cycle; w++) {
                    for(int y = ROUND+1-cycle; y < ROUND+SPACE_INIT_ROW+1+cycle; y++) {
                        for(int x = ROUND+1-cycle; x < ROUND+SPACE_INIT_COL+1+cycle; x++) {
                            int count = 0;
                            for(int xn = -1; xn <= 1; xn++) {
                                for(int yn = -1; yn <= 1; yn++) {
                                    for(int zn = -1; zn <= 1; zn++) {
                                        for(int wn = -1; wn <= 1; wn++) {
                                            if(xn == 0 && yn == 0 && zn == 0 && wn == 0) continue;
                                            if(spaces[x+xn][y+yn][z+zn][w+wn]) count++;
                                        }
                                    }
                                }
                            }
    
                            if(spaces[x][y][z][w]) {
                                if(count == 2 || count == 3) {
                                    currentSpaces[x][y][z][w] = true;
                                }
                            } else {
                                if(count == 3) {
                                    currentSpaces[x][y][z][w] = true;
                                }
                            }
                        }
                    }
                }
            }
            
            for(int w = 0; w < totalW; w++) {
                for(int i = 0; i < totalZ; i++) {
                    for(int j = 0; j < totalCol; j++) {
                        for(int k = 0; k < totalRow; k++) {
                            spaces[k][j][i][w] = currentSpaces[k][j][i][w];
                        }
                    }
                }
            }
        }

        int count = 0;
        for(int w = 0; w < totalW; w++) {
            for(int i = 0; i < totalZ; i++) {
                for(int j = 0; j < totalCol; j++) {
                    for(int k = 0; k < totalRow; k++) {
                        if(spaces[k][j][i][w]) {
                            count++;
                        }
                    }
                }
            }
        }
        System.out.println(count);
    }
}