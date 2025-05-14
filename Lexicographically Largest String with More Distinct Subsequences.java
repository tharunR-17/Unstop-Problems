import java.util.*;

public class Main {

    // Function to count the number of distinct subsequences of a string
    public static int countDistinctSubsequences(String s) {
        int n = s.length();
        int mod = 1000000007;

        // dp[i] will store the number of distinct subsequences of the substring s[0..i-1]
        long[] dp = new long[n + 1];
        dp[0] = 1;  // Base case: the empty string has exactly 1 subsequence, the empty subsequence.

        // To track the last occurrence of each character
        Map<Character, Integer> lastOccurrence = new HashMap<>();

        for (int i = 1; i <= n; i++) {
            char currentChar = s.charAt(i - 1);

            // The number of subsequences considering the first i characters is twice the subsequences considering the first i-1 characters
            dp[i] = (2 * dp[i - 1]) % mod;

            // If this character has appeared before, subtract the subsequences that would have been counted multiple times
            if (lastOccurrence.containsKey(currentChar)) {
                int lastIndex = lastOccurrence.get(currentChar);
                dp[i] = (dp[i] - dp[lastIndex - 1] + mod) % mod;
            }

            // Update the last occurrence of the current character
            lastOccurrence.put(currentChar, i);
        }

        // Return the number of distinct subsequences, excluding the empty subsequence.
        return (int) (dp[n] - 1);
    }

    // Main function to determine which string has more distinct subsequences or is lexicographically larger
    public static String betterString(String s1, String s2) {
        int subsequencesCountS1 = countDistinctSubsequences(s1);
        int subsequencesCountS2 = countDistinctSubsequences(s2);

        if (subsequencesCountS1 > subsequencesCountS2) {
            return s1;
        } else if (subsequencesCountS2 > subsequencesCountS1) {
            return s2;
        } else {
            // If both strings have the same number of distinct subsequences, return the lexicographically larger string
            return s1.compareTo(s2) > 0 ? s1 : s2;
        }
    }

    public static void main(String[] args) {
        // Example inputs
        Scanner scanner = new Scanner(System.in);
        
        String s1 = scanner.nextLine();
        String s2 = scanner.nextLine();

        // Output the string with more distinct subsequences or the lexicographically larger string if they are the same
        System.out.println(betterString(s1, s2));

        scanner.close();
    }
}
