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

            for(int k = 0; k < 10; k++) {
                for(int l = 0; l < 10; l++) {
                    pattern[0][1][k][l] = pattern[0][0][9-l][k];
                }
            }

            for(int k = 0; k < 10; k++) {
                for(int l = 0; l < 10; l++) {
                    pattern[0][2][k][l] = pattern[0][0][9-k][9-l];
                }
            }

            for(int k = 0; k < 10; k++) {
                for(int l = 0; l < 10; l++) {
                    pattern[0][3][k][l] = pattern[0][0][l][9-k];
                }
            }

            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 10; k++) {
                    pattern[1][j][k] = new StringBuilder(new String(pattern[0][j][k])).reverse()
                        .toString()
                        .toCharArray();
                }
            }

            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 10; k++) {
                    pattern[2][j][k] = new StringBuilder(new String(pattern[0][j][9-k])).reverse()
                        .toString()
                        .toCharArray();
                }
            }

            for(int j = 0; j < 4; j++) {
                for(int k = 0; k < 10; k++) {
                    pattern[3][j][k] = new String(pattern[0][j][9-k]).toCharArray();
                }
            }

            char[][][][] tmpRotate = new char[4][4][10][10];
            tmpRotate[0][0] = pattern[0][0];
            tmpRotate[0][1] = pattern[0][1];
            tmpRotate[0][2] = pattern[0][2];
            tmpRotate[0][3] = pattern[0][3];
            tmpRotate[1][0] = pattern[1][0];
            tmpRotate[1][1] = pattern[1][1];
            tmpRotate[1][2] = pattern[1][0];
            tmpRotate[1][3] = pattern[1][3];
            tmpRotate[2][0] = pattern[2][2];
            tmpRotate[2][1] = pattern[2][3];
            tmpRotate[2][2] = pattern[2][0];
            tmpRotate[2][3] = pattern[2][1];
            tmpRotate[3][0] = pattern[3][0]; 
            tmpRotate[3][1] = pattern[3][1];
            tmpRotate[3][2] = pattern[3][2];
            tmpRotate[3][3] = pattern[3][3];

            pattern = tmpRotate;
            
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

        for(int i = 0; i < 12; i++) {
            for(int j = 0; j < 12; j++) {
                isVisited[board[i][j]] = true;
                Integer[] sideIds = all.get(board[i][j])
                    .toArray(Integer[]::new);
                Integer[] curSides = main.get(board[i][j])
                    .toArray(Integer[]::new);
                Integer[] targetSides = connect.get(board[i][j])
                    .toArray(Integer[]::new);

                // System.out.println(i + " " + j + " | " + boardPattern[i][j] + " " + boardRotation[i][j]);
                
                int down = downFlip[boardRotation[i][j]][boardPattern[i][j]];
                int left = leftFlip[boardRotation[i][j]][boardPattern[i][j]];

                for(int k = 0; k < sideIds.length; k++) {
                    if(isVisited[sideIds[k]]) continue;
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

        boardRotation[4][2] = 1;
        boardPattern[4][2] = 1;
        boardRotation[4][9] = 3;
        boardPattern[4][9] = 1;
        boardRotation[6][1] = 1;
        boardPattern[6][1] = 1;
        boardRotation[8][1] = 1;
        boardPattern[8][1] = 1;
        boardRotation[10][8] = 1;
        boardPattern[10][8] = 1;
        boardRotation[10][11] = 3;
        boardPattern[10][11] = 1;

        // char[][] charBoard = new char[120][120];
        // for(int i = 0; i < 12; i++) {
        //     for(int j = 0; j < 12; j++) {
        //         if(board[i][j] == 0) continue;
        //         char[][] sub = patterns.get(board[i][j])[boardPattern[i][j]][boardRotation[i][j]];
        //         for(int y = 0; y < 10; y++) {
        //             for(int x = 0; x < 10; x++) {
        //                 charBoard[y+(i*10)][x+(j*10)] = sub[y][x];
        //             }
        //         }
        //     }
        // }

        // for(int i = 0; i < 120; i++) {
        //     System.out.println(new String(charBoard[i]));
        // }

        // int[] boardCnt = new int[10000];
        char[][] charBoard = new char[96][96];
        for(int i = 0; i < 12; i++) {
            for(int j = 0; j < 12; j++) {
                if(board[i][j] == 0) continue;
                // boardCnt[board[i][j]]++;
                char[][] sub = patterns.get(board[i][j])[boardPattern[i][j]][boardRotation[i][j]];
                for(int y = 0; y < 8; y++) {
                    for(int x = 0; x < 8; x++) {
                        charBoard[y+(i*8)][x+(j*8)] = sub[1+y][1+x];
                    }
                }
            }
        }

        for(int i = 0; i < 96; i++) {
            System.out.println(new String(charBoard[i]));
        }

        boolean isMonsterFound = false;
        int ans = 0;

        boolean[][][] targetPattern = new boolean[4][3][20];
        targetPattern[0][0][18] =
        targetPattern[0][1][0] = 
        targetPattern[0][1][5] =
        targetPattern[0][1][6] =
        targetPattern[0][1][11] =
        targetPattern[0][1][12] =
        targetPattern[0][1][17] =
        targetPattern[0][1][18] =
        targetPattern[0][1][19] =
        targetPattern[0][2][1] = 
        targetPattern[0][2][4] =
        targetPattern[0][2][7] =
        targetPattern[0][2][10] =
        targetPattern[0][2][13] =
        targetPattern[0][2][16] = true;

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 20; j++) {
                if(targetPattern[0][i][j]) {
                    targetPattern[1][i][19-j] = true;
                    targetPattern[2][2-i][j] = true;
                    targetPattern[3][2-i][19-j] = true;
                }
            }
        }

        for(int p = 0; p < 4; p++) {
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 20; j++) {
                    System.out.print(targetPattern[p][i][j] ? '#' : ' ');
                }
                System.out.println();
            }
            System.out.println();
        }

        for(int p = 0; p < 4; p++) {
            char[][] tmpBoard = new char[96][96];
            for(int i = 0; i < 96; i++) {
                tmpBoard[i] = charBoard[i].clone();
            }

            for(int i = 0; i < 96 - 3; i++) {
                for(int j = 0; j < 96 - 20; j++) {
                    boolean isMonster = true;
                    int[][] monsterPos = new int[2][15];
                    int cnt = 0;
                    for(int k = 0; k < 3; k++) {
                        for(int l = 0; l < 20; l++) {
                            if(targetPattern[p][k][l]) {
                                if(tmpBoard[i+k][j+l] == '#') {
                                    monsterPos[0][cnt] = j+l;
                                    monsterPos[1][cnt] = i+k;
                                    cnt++;
                                } else {
                                    isMonster = false;
                                    break;
                                }
                            }
                        }
                        if(!isMonster) {
                            break;
                        }
                    }
                    if(isMonster) {
                        isMonsterFound = true;
                        for(int x = 0; x < 15; x++) {
                            tmpBoard[monsterPos[1][x]][monsterPos[0][x]] = 'O';
                        }
                    }
                }
            }

            if(isMonsterFound) {
                for(int y = 0; y < 96; y++) {
                    for(int x = 0; x < 96; x++) {
                        if(tmpBoard[y][x] == '#') {
                            ans++;
                        }
                    }
                }
                System.out.println(ans);
                return;
            }
        }

        boolean[][][] targetPattern2 = new boolean[4][20][3];
        for(int p = 0; p < 4; p++) {
            for(int i = 0; i < 20; i++) {
                for(int j = 0; j < 3; j++) {
                    targetPattern2[p][i][j] = targetPattern[p][j][i];
                    System.out.print(targetPattern2[p][i][j] ? '#' : ' ');
                }
                System.out.println();
            }
            System.out.println();
        }

        for(int p = 0; p < 4; p++) {
            char[][] tmpBoard = new char[96][96];
            for(int i = 0; i < 96; i++) {
                tmpBoard[i] = charBoard[i].clone();
            }

            for(int i = 0; i < 96 - 20; i++) {
                for(int j = 0; j < 96 - 3; j++) {
                    boolean isMonster = true;
                    int[][] monsterPos = new int[2][15];
                    int cnt = 0;
                    for(int k = 0; k < 20; k++) {
                        for(int l = 0; l < 3; l++) {
                            if(targetPattern2[p][k][l]) {
                                if(tmpBoard[i+k][j+l] == '#') {
                                    monsterPos[0][cnt] = j+l;
                                    monsterPos[1][cnt] = i+k;
                                    cnt++;
                                } else {
                                    isMonster = false;
                                    break;
                                }
                            }
                        }
                        if(!isMonster) {
                            break;
                        }
                    }
                    if(isMonster) {
                        isMonsterFound = true;
                        for(int x = 0; x < 15; x++) {
                            tmpBoard[monsterPos[1][x]][monsterPos[0][x]] = 'O';
                        }
                    }
                }
            }

            if(isMonsterFound) {
                for(int y = 0; y < 96; y++) {
                    for(int x = 0; x < 96; x++) {
                        if(tmpBoard[y][x] == '#') {
                            ans++;
                        }
                    }
                }
                System.out.println(ans);
                return;
            }
        }
    }
}
