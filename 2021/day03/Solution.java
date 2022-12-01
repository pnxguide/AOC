import java.util.Scanner;
import java.io.File;

public class Solution
{
  public static void solveA(Scanner in)
  {
    char[] line = in.nextLine().toCharArray();
    int length = line.length, lineCount = 1;

    int[] cnt = new int[length];
    for (int i = 0; i < length; i++)
    {
      if (line[i] == '1')
      {
        cnt[i]++;
      }
    }

    while (in.hasNextLine())
    {
      lineCount++;
      line = in.nextLine().toCharArray();

      for (int i = 0; i < length; i++)
      {
        if (line[i] == '1')
        {
          cnt[i]++;
        }
      }
    }

    long gamma = 0, epsilon = 0;
    long pow = 1;
    for (int i = 0; i < length; i++)
    {
      long cur = cnt[length-1-i];
      if (cur > (lineCount / 2))
      {
        gamma += pow;
      }

      else
      {
        epsilon += pow;
      }

      pow *= 2;
    }

    System.out.println(gamma * epsilon);
  }

  public static void solveB(Scanner in)
  {
    
  }

  public static void main(String[] args)
    throws java.io.FileNotFoundException
  {
    Scanner in = new Scanner(new File("input.txt"));

    // solveA(in);
    solveB(in);

    in.close();
  }
}