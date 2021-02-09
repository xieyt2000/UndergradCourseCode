import java.util.LinkedHashSet;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sin = new Scanner(System.in);
        LinkedHashSet<String> textSet = new LinkedHashSet<>();
        while (sin.hasNextLine()) {
            textSet.add(sin.nextLine());
        }
        System.out.println(textSet.size());
        for (String text : textSet) {
            System.out.println(text);
        }
    }
}
