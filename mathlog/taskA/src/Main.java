import parser.LogicalParser;
import parser.StringSource;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println(new LogicalParser('\0', new StringSource(scanner.nextLine())).parse().toPrefixString());
    }
}
