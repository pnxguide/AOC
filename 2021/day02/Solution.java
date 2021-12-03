import java.util.Scanner;
import java.io.File;

public class Solution
{
  public static void solveA(Scanner in)
  {
    int x = 0, y = 0;

    while (in.hasNextLine())
    {
      String cmd  = in.next();
      int val     = in.nextInt();
      in.nextLine();

      switch (cmd)
      {
        case "forward":
          x += val;
          break;
        case "up":
          y -= val;
          break;
        case "down":
          y += val;
          break;
      }
    }

    System.out.println(x * y);
  }

  public static void solveB(Scanner in)
  {
    int x = 0, y = 0;
    int aim = 0;

    while (in.hasNextLine())
    {
      String cmd  = in.next();
      int val     = in.nextInt();
      in.nextLine();

      switch (cmd)
      {
        case "forward":
          x += val;
          y += (val * aim);
          break;
        case "up":
          aim -= val;
          break;
        case "down":
          aim += val;
          break;
      }
    }

    System.out.println(x * y);
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
