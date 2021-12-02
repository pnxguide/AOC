import java.util.Scanner;
import java.io.File;

public class Solution
{
  public static void solveA(Scanner in)
  {
    int prev, cur;
    prev = in.nextInt(); 
    in.nextLine();

    int cnt = 0;
    while (in.hasNextLine())
    {
      cur = in.nextInt();
      in.nextLine();
      if (cur > prev)
      {
        cnt++;
      }
      prev = cur;
    }

    System.out.println(cnt);
  }

  public static void solveB(Scanner in)
  {
    int a, b, c, d;
    a = in.nextInt();
    b = in.nextInt();
    c = in.nextInt();
    in.nextLine();

    int cnt = 0;
    while (in.hasNextLine())
    {
      d = in.nextInt();
      in.nextLine();
      if ((b + c + d) > (a + b + c))
      {
        cnt++;
      }
      a = b;
      b = c;
      c = d;
    }

    System.out.println(cnt);
  }

  public static void main(String[] args)
    throws java.io.FileNotFoundException
  {
    Scanner in = new Scanner(new File("day1.txt"));

    // solveA(in);
    solveB(in);

    in.close();
  }
}