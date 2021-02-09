import java.io.File;
import java.io.FileFilter;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String pattern = new Scanner(System.in).next().toLowerCase();
        File dir = new File("input/test/case");
        File[] files = dir.listFiles(new FileFilter() {
            @Override
            public boolean accept(File pathname) {
                if (pathname.isDirectory())
                    return false;
                String name = pathname.getName();
                return name.toLowerCase().contains(pattern);
            }
        });
        ArrayList<String> fileNames = new ArrayList<>();
        for (File file : files) {
            fileNames.add(file.getName());
        }
        fileNames.sort(String::compareTo);
        for (String name : fileNames) {
            System.out.println(name);
        }
    }
}
