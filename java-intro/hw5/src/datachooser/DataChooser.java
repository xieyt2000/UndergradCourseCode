package datachooser;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;

public class DataChooser {
    public DataChooser(String in_path, String out_path) {
        try {
            Scanner input = new Scanner(new File(in_path));
            PrintStream output = new PrintStream(new File(out_path));
            while (input.hasNextLine()) {
                String line = input.nextLine();
                String dep = line.split(",")[3];
                output.println(dep);
            }
        } catch (FileNotFoundException ignored) {
        }
    }
}
