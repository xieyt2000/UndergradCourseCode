
import java.util.ArrayDeque;
import java.util.LinkedList;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        City city = new City();
        city.read();
        if (city.checkConnected())
            System.out.println("YES");
        else
            System.out.println("NO");
    }
}

class City {
    private int n;
    LinkedList<Integer>[] roads;

    void read() {
        Scanner sin = new Scanner(System.in);
        n = sin.nextInt();
        roads = new LinkedList[n + 1];
        for (int i = 0; i < n + 1; i++) {
            roads[i] = new LinkedList<>();
        }
        for (int i = 0; i < n - 1; i++) {
            int a = sin.nextInt(), b = sin.nextInt();
            roads[a].add(b);
            roads[b].add(a);
        }
    }

    boolean checkConnected() {
        ArrayDeque<Integer> visitedQueue = new ArrayDeque<>();
        boolean[] visited = new boolean[n + 1];
        visitedQueue.add(1);
        while (!visitedQueue.isEmpty()) {
            int curMarket = visitedQueue.poll();
            visited[curMarket] = true;
            for (int i : roads[curMarket]){
                if(!visited[i])
                    visitedQueue.add(i);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (!visited[i])
                return false;
        }
        return true;
    }
}