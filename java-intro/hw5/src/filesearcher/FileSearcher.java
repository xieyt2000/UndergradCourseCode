package filesearcher;

import java.io.*;

public class FileSearcher {
    File file;

    public FileSearcher(String s) {
        file = new File(s);
    }

    public int search(String input) {
        input = input.toLowerCase();
        int counter = 0;
        try {
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line;
            while ((line = reader.readLine()) != null) {
                String[] words = line.split("[\\W_]+");
                for (String i : words) {
                    if (input.equals(i.toLowerCase())) {
                        counter++;
                    }
                }
            }
        } catch (IOException ignored) {
        }
        return counter;
    }
}
