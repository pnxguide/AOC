import java.util.*;

public class D11 {
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
                            if(i-1 >= 0 && j-1 >= 0 && grid[i-1][j-1] == '#')               count++;
                            if(i-1 >= 0 && grid[i-1][j] == '#')                             count++;
                            if(i-1 >= 0 && j+1 < colSize && grid[i-1][j+1] == '#')          count++;
                            if(j-1 >= 0 && grid[i][j-1] == '#')                             count++;
                            if(j+1 < colSize && grid[i][j+1] == '#')                        count++;
                            if(i+1 < rowSize && j-1 >= 0 && grid[i+1][j-1] == '#')          count++;
                            if(i+1 < rowSize && grid[i+1][j] == '#')                        count++;
                            if(i+1 < rowSize && j+1 < colSize && grid[i+1][j+1] == '#')     count++;
                        
                            if(count >= 4) {
                                currentGrid[i][j] = 'L';
                                isChange = true;
                            }

                            break;
                        case 'L':
                            if(i-1 >= 0 && j-1 >= 0 && grid[i-1][j-1] == '#')               count--;
                            if(i-1 >= 0 && grid[i-1][j] == '#')                             count--;
                            if(i-1 >= 0 && j+1 < colSize && grid[i-1][j+1] == '#')          count--;
                            if(j-1 >= 0 && grid[i][j-1] == '#')                             count--;
                            if(j+1 < colSize && grid[i][j+1] == '#')                        count--;
                            if(i+1 < rowSize && j-1 >= 0 && grid[i+1][j-1] == '#')          count--;
                            if(i+1 < rowSize && grid[i+1][j] == '#')                        count--;
                            if(i+1 < rowSize && j+1 < colSize && grid[i+1][j+1] == '#')     count--;
        
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
