import java.util.*;

public class D11B {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        List<String> lines = new ArrayList<>();
        while(in.hasNextLine()) {
            lines.add(in.nextLine());
        }
        in.close();

        int rowSize = lines.size();
        int colSize = lines.get(0).length();

        char[][] grid = new char[rowSize][colSize];
        for(int i = 0; i < rowSize; i++) {
            grid[i] = lines.get(i).toCharArray();
        }

        while(true) {
            char[][] currentGrid = new char[rowSize][colSize];
            for(int i = 0; i < rowSize; i++) {
                currentGrid[i] = grid[i].clone();
            }

            boolean isChange = false;

            for(int i = 0; i < rowSize; i++) {
                for(int j = 0; j < colSize; j++) {
                    int count = 0;

                    switch(grid[i][j]) {
                        case '#':
                            // upper left
                            for(int x = 1; i-x >= 0 && j-x >= 0; x++) {
                                if(grid[i-x][j-x] == '#') {
                                    count++;
                                    break;
                                } else if(grid[i-x][j-x] == 'L') {
                                    break;
                                }
                            }

                            // upper
                            for(int x = 1; i-x >= 0; x++) {
                                if(grid[i-x][j] == '#') {
                                    count++;
                                    break;
                                } else if(grid[i-x][j] == 'L') {
                                    break;
                                }
                            }

                            // upper right
                            for(int x = 1; i-x >= 0 && j+x < colSize; x++) {
                                if(grid[i-x][j+x] == '#') {
                                    count++;
                                    break;
                                } else if(grid[i-x][j+x] == 'L') {
                                    break;
                                }
                            }

                            // left
                            for(int x = 1; j-x >= 0; x++) {
                                if(grid[i][j-x] == '#') {
                                    count++;
                                    break;
                                } else if(grid[i][j-x] == 'L') {
                                    break;
                                }
                            }

                            // right
                            for(int x = 1; j+x < colSize; x++) {
                                if(grid[i][j+x] == '#') {
                                    count++;
                                    break;
                                } else if(grid[i][j+x] == 'L') {
                                    break;
                                }
                            }

                            // lower left
                            for(int x = 1; i+x < rowSize && j-x >= 0; x++) {
                                if(grid[i+x][j-x] == '#') {
                                    count++;
                                    break;
                                } else if(grid[i+x][j-x] == 'L') {
                                    break;
                                }
                            }

                            // lower
                            for(int x = 1; i+x < rowSize; x++) {
                                if(grid[i+x][j] == '#') {
                                    count++;
                                    break;
                                } else if(grid[i+x][j] == 'L') {
                                    break;
                                }
                            }

                            // lower right
                            for(int x = 1; i+x < rowSize && j+x < colSize; x++) {
                                if(grid[i+x][j+x] == '#') {
                                    count++;
                                    break;
                                } else if(grid[i+x][j+x] == 'L') {
                                    break;
                                }
                            }
                        
                            if(count >= 5) {
                                currentGrid[i][j] = 'L';
                                isChange = true;
                            }

                            break;
                            
                        case 'L':
                            // upper left
                            for(int x = 1; i-x >= 0 && j-x >= 0; x++) {
                                if(grid[i-x][j-x] == '#') {
                                    count--;
                                    break;
                                } else if(grid[i-x][j-x] == 'L') {
                                    break;
                                }
                            }

                            // upper
                            for(int x = 1; i-x >= 0; x++) {
                                if(grid[i-x][j] == '#') {
                                    count--;
                                    break;
                                } else if(grid[i-x][j] == 'L') {
                                    break;
                                }
                            }

                            // upper right
                            for(int x = 1; i-x >= 0 && j+x < colSize; x++) {
                                if(grid[i-x][j+x] == '#') {
                                    count--;
                                    break;
                                } else if(grid[i-x][j+x] == 'L') {
                                    break;
                                }
                            }

                            // left
                            for(int x = 1; j-x >= 0; x++) {
                                if(grid[i][j-x] == '#') {
                                    count--;
                                    break;
                                } else if(grid[i][j-x] == 'L') {
                                    break;
                                }
                            }

                            // right
                            for(int x = 1; j+x < colSize; x++) {
                                if(grid[i][j+x] == '#') {
                                    count--;
                                    break;
                                } else if(grid[i][j+x] == 'L') {
                                    break;
                                }
                            }

                            // lower left
                            for(int x = 1; i+x < rowSize && j-x >= 0; x++) {
                                if(grid[i+x][j-x] == '#') {
                                    count--;
                                    break;
                                } else if(grid[i+x][j-x] == 'L') {
                                    break;
                                }
                            }

                            // lower
                            for(int x = 1; i+x < rowSize; x++) {
                                if(grid[i+x][j] == '#') {
                                    count--;
                                    break;
                                } else if(grid[i+x][j] == 'L') {
                                    break;
                                }
                            }

                            // lower right
                            for(int x = 1; i+x < rowSize && j+x < colSize; x++) {
                                if(grid[i+x][j+x] == '#') {
                                    count--;
                                    break;
                                } else if(grid[i+x][j+x] == 'L') {
                                    break;
                                }
                            }

                            if(count == 0) {
                                currentGrid[i][j] = '#';
                                isChange = true;
                            }

                            break;
                    }
                }
            }

            if(!isChange) {
                break;
            }

            grid = currentGrid;
        }

        int count = 0;
        for(int i = 0; i < rowSize; i++) {
            for(int j = 0; j < colSize; j++) {
                if(grid[i][j] == '#')   count++;
            }
        }
        System.out.println(count);
    }
}
