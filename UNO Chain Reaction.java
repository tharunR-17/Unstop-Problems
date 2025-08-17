import java.util.*;

public class Main {
    public static List<String> userLogic(List<String> cards) {
        boolean changed;

        do {
            changed = false;
            List<String> newList = new ArrayList<>();
            int i = 0;

            while (i < cards.size()) {
                int j = i;
                while (j < cards.size() && isSameGroup(cards.get(i), cards.get(j))) {
                    j++;
                }
                if (j - i >= 3) {
                    changed = true;
                } else {
                    for (int k = i; k < j; k++) {
                        newList.add(cards.get(k));
                    }
                }
                i = j;
            }

            cards = newList;

        } while (changed);

        return cards;
    }

    private static boolean isSameGroup(String a, String b) {
        return a.charAt(0) == b.charAt(0) || a.charAt(1) == b.charAt(1);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.nextLine(); 

        List<String> cards = new ArrayList<>();
        for (int i = 0; i < n; ++i) {
            cards.add(scanner.nextLine().trim().toUpperCase());
        }
        List<String> result = userLogic(cards);
        if (result.isEmpty()) {
            System.out.println("All cards removed!");
        } else {
            System.out.println(String.join(" ", result));
        }
    }
}
