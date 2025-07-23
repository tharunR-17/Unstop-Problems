import java.util.*;

public class Main {
    static final int MOD = 1000000007;

    public static int ways(int sum) {
        // Write your logic here.
        if(sum == 0)return 1;
        if(sum < 0) return 0;
        int way = 0;

        for(int i=1;i<=6;i++){
            way = way+ways(sum-i)%MOD;
        }
        return way%MOD; // Placeholder
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int result = ways(n);
        System.out.println(result);
    }
}
