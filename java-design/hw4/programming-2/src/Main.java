import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;

public class Main {
    public static void main(String[] args) {
        TreeMap<Integer, Integer> shellNum = new TreeMap<>();
        Scanner sin = new Scanner(System.in);
        final int N = sin.nextInt();
        try {
            for (int i = 0; i < N; i++) {
                int command = sin.nextInt(), value = sin.nextInt();
                switch (command) {
                    case 1: {
                        shellNum.put(value, shellNum.getOrDefault(value, 0) + 1);
                        break;
                    }
                    case 2: {
                        Map.Entry<Integer, Integer> tradeShell = shellNum.floorEntry(value);
                        shellNum.put(tradeShell.getKey(), tradeShell.getValue() - 1);
                        if (tradeShell.getValue() == 0) shellNum.remove(tradeShell.getKey());
                        break;
                    }
                    case 3: {
                        Map.Entry<Integer, Integer> tradeShell = shellNum.ceilingEntry(value);
                        shellNum.put(tradeShell.getKey(), tradeShell.getValue() - 1);
                        if (tradeShell.getValue() == 1) shellNum.remove(tradeShell.getKey());
                        break;
                    }
                }
            }
            int total = 0;
            for (Map.Entry<Integer, Integer> entry : shellNum.entrySet()) {
                total += entry.getValue() * entry.getKey();
            }
            System.out.println(total);
        } catch (NullPointerException e) {
            System.out.println(-1);
        }
    }
}
