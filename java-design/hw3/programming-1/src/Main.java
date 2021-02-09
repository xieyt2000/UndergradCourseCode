import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws IOException {
        Scanner systemIn = new Scanner(System.in);
        HashMap<Character, Integer> charCount = new HashMap<>();
        while (systemIn.hasNext()) {
            String fileName = systemIn.next();
            String encoding = systemIn.next();
            File file = new File(fileName);
            Scanner fileIn = new Scanner(file, encoding);
            while (fileIn.hasNextLine()) {
                String content = fileIn.nextLine();
                for (int i = 0; i < content.length(); i++) {
                    Character character = content.charAt(i);
                    charCount.put(character, charCount.getOrDefault(character, 0) + 1);
                }
            }
            fileIn.close();
        }
        ArrayList<Map.Entry<Character, Integer>> charCountList = new ArrayList<>(charCount.entrySet());
        charCountList.sort(new EntryCmp());
        int total = 0;
        for (Map.Entry<Character, Integer> entry : charCountList) {
            total += entry.getValue();
        }
        PrintStream ps = new PrintStream(new FileOutputStream(new File("statistics.txt"), true));
        ps.println(total);
        for (Map.Entry<Character, Integer> entry : charCountList) {
            ps.println(entry.getKey() + " " + entry.getValue());
        }
    }
}

class EntryCmp implements Comparator<Map.Entry<Character, Integer>> {
    @Override
    public int compare(Map.Entry<Character, Integer> o1, Map.Entry<Character, Integer> o2) {
        if (o1.getValue().equals(o2.getValue())) {
            return o1.getKey().compareTo(o2.getKey());
        }
        return o2.getValue().compareTo(o1.getValue());
    }
}
