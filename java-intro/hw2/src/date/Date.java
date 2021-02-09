package date;

public class Date
{
    int year = 0;
    int month = 0;
    int day = 0;
    String[] MONTH_LIST = {
            "", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"
    };

    private int getMonth(String s)
    {
        for (int i = 1; i < 13; i++)
        {
            if (s.equals(MONTH_LIST[i]))
            {
                return i;
            }
        }
        return -1;
    }

    public Date(String str)
    {
        String[] dateParts = str.split("[.,]");
        month = getMonth(dateParts[0].strip());
        day = Integer.parseInt(dateParts[1].strip());
        year = Integer.parseInt(dateParts[2].strip());
    }

    public Date(String m, int d, int y)
    {
        day = d;
        year = y;
        month = getMonth(m.split("\\.")[0].strip());
    }

    public Date(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
    }

    String print()
    {
        return year + "/" + month + "/" + day;
    }
}
