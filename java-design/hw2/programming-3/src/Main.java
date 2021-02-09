import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int m = input.nextInt();
        input.nextLine();
        HashMap<BaseStaff, NaiveStaff> hashMap = new HashMap<>();
        for (int i = 0; i < n; i++) {
            String info=input.nextLine();
            String[] infoWords=info.split(" ");
            Staff staff = new Staff(infoWords[0], Integer.parseInt(infoWords[1]),info);
            hashMap.put(staff, staff);
        }
        for (int i = 0; i < m; i++) {
            String type = input.next();
            type = ((type.equals("S")) ? "Student" : "Teacher");
            int number = input.nextInt();
            Staff staff = new Staff(type, number, "");
            hashMap.get(staff).punch();
        }
        int maxPunch = 0;
        Staff maxStaff = null;
        for (Map.Entry<BaseStaff, NaiveStaff> entry : hashMap.entrySet()) {
            if (entry.getValue().punchCounter() > maxPunch) {
                maxStaff = (Staff) entry.getKey();
                maxPunch = entry.getValue().punchCounter();
            }
        }
        assert maxStaff != null;
        System.out.println(maxStaff.getInfo());
    }
}

class Staff extends NaiveStaff {
    final private String info;

    public Staff(String type, int number, String info) {
        super(type, number);
        this.info=info;
    }

    public String getInfo() {
        return info;
    }
}