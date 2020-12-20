import java.util.*;

public class D20 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        Map<Integer, String[]> tileSide = new HashMap<>();
        Map<Integer, char[][][][]> patterns = new HashMap<>();

        while(in.hasNextLine()) {
            String[] tokens = in.nextLine().replace(":", "")
                .split(" ");
            int tileId = Integer.parseInt(tokens[1]);

            char[][][][] pattern = new char[4][4][10][10];
            
            for(int i = 0; ; i++) {
                String line = in.nextLine();
                if(line.equals("")) {
                    break;
                }
                pattern[0][0][i] = line.toCharArray();
            }

            char[] left = new char[10];
            char[] right = new char[10];
            for(int i = 0; i < 10; i++) {
                left[i] = pattern[0][0][9-i][0];
                right[i] = pattern[0][0][i][9];
            }

            String[] tmp = new String[8];
            tmp[0] = new String(pattern[0][0][0]);
            tmp[1] = new String(left);
            tmp[2] = new StringBuilder(new String(pattern[0][0][9])).reverse()
                .toString();
            tmp[3] = new String(right);
            
            for(int i = 4; i < 8; i++) {
                tmp[i] = new StringBuilder(tmp[i-4]).reverse()
                    .toString();
            }

            String[] sides = tmp;

            // type 2
            for(int i = 0; i < 10; i++) {
                pattern[0][1][i] = new StringBuilder(new String(pattern[0][0][i])).reverse()
                    .toString()
                    .toCharArray();
            }

            // type 3
            for(int i = 0; i < 10; i++) {
                pattern[0][2][i] = new StringBuilder(new String(pattern[0][0][9-i])).reverse()
                    .toString()
                    .toCharArray();
            }

            // type 4
            for(int i = 0; i < 10; i++) {
                pattern[0][3][i] = new String(pattern[0][0][9-i]).toCharArray();
            }

            // rotate 1
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 10; k++) {
                    for(int l = 0; l < 10; l++) {
                        pattern[1][j][k][l] = pattern[0][j][9-l][k];
                    }
                }
            }

            // rotate 2
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 10; k++) {
                    for(int l = 0; l < 10; l++) {
                        pattern[2][j][k][l] = pattern[0][j][9-k][9-l];
                    }
                }
            }

            // rotate 3
            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 10; k++) {
                    for(int l = 0; l < 10; l++) {
                        pattern[3][j][k][l] = pattern[0][j][l][9-k];
                    }
                }
            }
            
            tileSide.put(tileId, sides);
            patterns.put(tileId, pattern);
        }
        in.close();

        Integer[] tileIndex = tileSide.keySet().toArray(Integer[]::new);
        int length = tileIndex.length;

        Map<Integer, List<Integer>> bi = new HashMap<>();
        Map<Integer, List<Integer>> all = new HashMap<>();

        Map<Integer, List<Integer>> main = new HashMap<>();
        Map<Integer, List<Integer>> connect = new HashMap<>();

        for(int i = 0; i < length; i++) {
            String[] iSides = tileSide.get(tileIndex[i]);
            List<Integer> candidates = new ArrayList<>();
            List<Integer> mains = new ArrayList<>();
            List<Integer> connects = new ArrayList<>();
            int count = 0;
            for(int j = 0; j < 8; j++) {
                for(int k = 0; k < length; k++) {
                    if(i == k) continue;
                    String[] kSides = tileSide.get(tileIndex[k]);
                    for(int l = 0; l < 4; l++) {
                        if(iSides[j].equals(kSides[l+4])) {
                            candidates.add(tileIndex[k]);
                            mains.add(j);
                            connects.add(l);
                            count++;
                        }
                    }
                }
            }

            if(count == 2) {
                bi.put(tileIndex[i], candidates);
                all.put(tileIndex[i], candidates);
                main.put(tileIndex[i], mains);
                connect.put(tileIndex[i], connects);
            } else if(count == 3) {
                all.put(tileIndex[i], candidates);
                main.put(tileIndex[i], mains);
                connect.put(tileIndex[i], connects);
            } else if(count == 4) {
                all.put(tileIndex[i], candidates);
                main.put(tileIndex[i], mains);
                connect.put(tileIndex[i], connects);
            }
        }

        // part 1
        // long multiple = 1;
        // for(Long key : bi.keySet()) {
        //     multiple *= key;
        // }
        // System.out.println(multiple);

        int[][] board = new int[12][12];
        int[][] boardPattern = new int[12][12];
        int[][] boardRotation = new int[12][12];
        board[0][0] = 1657;
        boardPattern[0][0] = 0;
        boardRotation[0][0] = 0;

        final int[][] leftFlip = {
            {3, 1, 5, 7},
            {0, 2, 6, 4},
            {1, 3, 7, 5},
            {2, 0, 4, 6}
        };
        final int[][] downFlip = {
            {2, 6, 4, 0},
            {3, 7, 5, 1},
            {0, 4, 6, 2},
            {1, 5, 7, 3}
        };
        final int[] leftFilpInc = {1, 0, 3, 2};
        final int[] downFilpInc = {3, 2, 1, 0};

        boolean[] isVisited = new boolean[10000];

        try {
            for(int i = 0; i < 12; i++) {
                for(int j = 0; j < 12; j++) {
                    isVisited[board[i][j]] = true;
                    // if(j > 0 && i % 2 != 0) continue;

                    Integer[] sideIds = all.get(board[i][j])
                        .toArray(Integer[]::new);
                    Integer[] curSides = main.get(board[i][j])
                        .toArray(Integer[]::new);
                    Integer[] targetSides = connect.get(board[i][j])
                        .toArray(Integer[]::new);
    
                    System.out.println(i + " " + j + " " + board[i][j] + " " + boardRotation[i][j] + " " + boardPattern[i][j]);
                    System.out.println(Arrays.toString(sideIds));
                    System.out.println(Arrays.toString(curSides));
                    System.out.println(Arrays.toString(targetSides));
                    
                    int down = downFlip[boardRotation[i][j]][boardPattern[i][j]];
                    int left = leftFlip[boardRotation[i][j]][boardPattern[i][j]];

                    // System.out.println(down + " " + left);

                    System.out.println();
    
                    for(int k = 0; k < sideIds.length; k++) {
                        if(isVisited[sideIds[k]]) continue;
                        // if(j < 12 && curSides[k] == left) {
                        //     board[i][j+1] = sideIds[k];
                        //     boardRotation[i][j+1] = (targetSides[k] + 3) % 4;
                        //     boardPattern[i][j+1] = boardPattern[i][j];
                        // } else if(i < 12 && curSides[k] == down) {
                        //     board[i+1][j] = sideIds[k];
                        //     boardRotation[i+1][j] = targetSides[k];
                        //     boardPattern[i+1][j] = boardPattern[i][j];
                        // } else if(j < 12 && curSides[k] % 4 == left % 4) {
                        //     board[i][j+1] = sideIds[k];
                        //     boardRotation[i][j+1] = (targetSides[k] + 3) % 4;
                        //     boardPattern[i][j+1] = downFilpInc[boardPattern[i][j]];
                        // } else if(i < 12 && curSides[k] % 4 == down % 4) {
                        //     board[i+1][j] = sideIds[k];
                        //     boardRotation[i+1][j] = targetSides[k];
                        //     boardPattern[i+1][j] = leftFilpInc[boardPattern[i][j]];
                        // }
                        if(j < 12 && curSides[k] % 4 == left % 4) {
                            board[i][j+1] = sideIds[k];
                            boardRotation[i][j+1] = (targetSides[k] + 3) % 4;
                            if(curSides[k] >= 4) {
                                // boardRotation[i][j+1] = (targetSides[k] + 1) % 4;
                                boardPattern[i][j+1] = downFilpInc[boardPattern[i][j]];
                            } else {
                                boardPattern[i][j+1] = boardPattern[i][j];
                            }
                        } else if(i < 12 && curSides[k] % 4 == down % 4) {
                            board[i+1][j] = sideIds[k];
                            boardRotation[i+1][j] = targetSides[k];
                            if(curSides[k] >= 4) {
                                boardPattern[i+1][j] = leftFilpInc[boardPattern[i][j]];
                            } else {
                                boardPattern[i+1][j] = boardPattern[i][j];
                            }
                        }
                    }
                }
            }
        } catch(NullPointerException npe) {

        }

        char[][] charBoard = new char[132][132];
        for(int i = 0; i < 12; i++) {
            for(int j = 0; j < 12; j++) {
                if(board[i][j] == 0) continue;
                char[][] sub = patterns.get(board[i][j])[boardRotation[i][j]][boardPattern[i][j]];
                for(int y = 0; y < 10; y++) {
                    for(int x = 0; x < 10; x++) {
                        charBoard[y+(i*11)][x+(j*11)] = sub[y][x];
                    }
                }
            }
        }

        for(int i = 0; i < 132; i++) {
            System.out.println(new String(charBoard[i]));
        }

        // for(Long key : bi.keySet()) {
        //     Integer[] mainSides = main.get(key).toArray(Integer[]::new);
        //     System.out.println(key + " " + Arrays.toString(mainSides));
        // }

    }
}
