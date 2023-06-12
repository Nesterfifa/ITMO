import java.math.BigInteger;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int b = scanner.nextInt();
        int k = scanner.nextInt();
        BigInteger n = new BigInteger(scanner.next(), 16);
        BigInteger sqrt = n.sqrt();
        Set<BigInteger> divisors = new TreeSet<>();

        while (divisors.size() < k) {
            sqrt = sqrt.add(BigInteger.ONE);
            BigInteger diff = sqrt.multiply(sqrt).subtract(n);
            BigInteger diffSqrt = diff.sqrt();
            if (diffSqrt.multiply(diffSqrt).compareTo(diff) == 0) {
                divisors.add(sqrt.subtract(diffSqrt));
                divisors.add(sqrt.add(diffSqrt));
            }
        }

        Set<BigInteger> ans = new TreeSet<>();
        for (BigInteger d1 : divisors) {
            for (BigInteger d2 : divisors) {
                BigInteger gcd = d1.gcd(d2);
                if (gcd.isProbablePrime(40)) {
                    ans.add(gcd);
                }
            }
        }
        for (BigInteger d : ans) {
            System.out.println(d.toString(16));
        }
    }
}
