package savingsaccount;

public class SavingsAccount
{
    static double annualInterestRate = 0.06;
    private double savingsBalance = 0;

    public SavingsAccount(double money)
    {
        savingsBalance += money;
    }

    public double calculateMonthlyInterest()
    {
        double interest = savingsBalance * annualInterestRate / 12;
        savingsBalance += interest;
        return interest;
    }

    static void modifyInterestRate(double rate)
    {
        annualInterestRate = rate;
    }
}
