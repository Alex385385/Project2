#include <iostream>
#include <string>
using namespace std;



class BankAccount
{
protected:
   double balance;
   int numDeposits;
   int numWithdrawls;
   double interestRate;
   double serviceCharge;
public:
   BankAccount()
   {
      balance = 0;
      numDeposits = 0;
      numWithdrawls = 0;
      interestRate = 0.0;
      serviceCharge = 0.0;
   }
   BankAccount(double bal, double rate)
   {
      balance = bal;
      numDeposits = 0;
      numWithdrawls = 0;
      interestRate = rate;
      serviceCharge = 0;
   }
   int getBalance()
   {
      return balance;
   }
   virtual void deposit(double bal)
   {
      balance += bal;
      numDeposits++;
   }
   virtual void withdrawl(double bal)
   {
      balance -= bal;
      numWithdrawls++;
   }
   virtual void calcInt()
   {
      double MIR = interestRate/12;
      double monthlyInterest = balance * MIR;
      balance = balance + monthlyInterest;
   }
   virtual void monthlyProc()
   {
      balance - serviceCharge;
      calcInt();
      numWithdrawls = 0;
      numDeposits = 0;
      serviceCharge = 0;
   }
   void print()
   {
      cout << "balance: " << balance << endl;
      cout << "Number of deposits: " << numDeposits << endl;
      cout << "Number of Withdrawls: " << numWithdrawls << endl;
      cout << "Interest Rate: " << interestRate << endl;
      cout << "Service Charge: " << serviceCharge << endl;
   }
};

class SavingsAccount : public BankAccount
{
private:
   bool status;
public:
   SavingsAccount(double bal, double rate) : BankAccount(bal, rate)
   {
      balance = bal;
      numDeposits = 0;
      numWithdrawls = 0;
      interestRate = rate;
      serviceCharge = 0;
   }
   void withdrawl(double amount)
   {
      if(balance >= 25)
      {
         BankAccount::withdrawl(amount);
      }
      else
      {
         cout << "Your account is below $25, it is inactive." << endl;
      }
   }
   void deposit(double amount)
   {
      double holder = balance + amount;
      if(holder >= 25)
      {
         BankAccount::deposit(amount);
      }
      else
      {
         cout << "Your account is inactive, the amount of deposit is below $25" << endl;
      }
   }
   void monthlyProc()
   {
      if(numDeposits > 4)
      {
         serviceCharge += 1;
      }
   }
};

class CheckingAccount : public BankAccount
{
private:
   double checkWithdrawl;
public:
   CheckingAccount(double bal, double rate) : BankAccount(bal, rate)
   {
      balance = bal;
      numDeposits = 0;
      numWithdrawls = 0;
      interestRate = rate;
      serviceCharge = 0;
   }
   void withdrawl(double amount)
   {
      if(amount > balance)
      {
         serviceCharge += 15;
         BankAccount::withdrawl(amount);
      }
   }
   void monthlyProc()
   {
      double holder = 5 + (0.10 * checkWithdrawl);
      serviceCharge += holder;
   }
};


void menu(CheckingAccount checking, SavingsAccount savings)
{
   int menu_choice;
   double amount;

   cout << "BANK ACCOUNT MENU " << "\n\n";
   cout << "1. Savings Account Deposit\n";
   cout << "2. Checking Account Deposit\n";
   cout << "3. Savings Account Withdrawal\n";
   cout << "4. Checking Account Withdrawal\n";
   cout << "5. Display Account Statistics\n";
   cout << "6. Exit\n";

   do
   {
      cout << "Your choice, please: (1-6) ";
      cout << menu_choice;
      cin >> menu_choice;
      cout << menu_choice;

      if (menu_choice <= 0 || menu_choice >= 7)
      {
         cout << "Invalid option selected!\n";
      }
   } while (menu_choice <= 0 || menu_choice >= 7);

   switch(menu_choice)
   {
      case 1:
         cout << "Enter amount to deposit: $";
         cin >> amount;

         savings.deposit(amount);

         cout << "\n\n";

         menu(checking, savings);
         break;
      case 2:
         cout << "Enter amount to deposit: $";
         cin >> amount;

         checking.deposit(amount);

         cout << "\n\n";

         menu(checking, savings);
         break;
      case 3:
         cout << "Enter amount to withdrawl: $";
         cin >> amount;

         savings.withdrawl(amount);

         cout << "\n\n";

         menu(checking, savings);
         break;
      case 4:
         cout << "Enter amount to withdraw: $";
         cin >> amount;

         checking.withdrawl(amount);

         cout << "\n\n";

         menu(checking, savings);
         break;
      case 5:
         cout << "\n";

         cout << "SAVINGS ACCOUNT MONTHLY STATISTICS:\n";
         savings.monthlyProc();
         savings.print();

         cout << "\n";

         cout << "CHECKING ACCOUNT MONTHLY STATISTICS:\n";
         checking.monthlyProc();
         checking.print();

         cout << "\n\n";

         menu(checking, savings);
         break;
      case 6:
         cout << "\n\n";
         break;
      default:
         break;
    }
}


int main()
{
   double startSaveBalance, startCheckBalance, annualInterestRate;
   double amountWithdrawl, amountDeposit;

   cout << "Enter starting balance for savings: $ ";
   cin >> startSaveBalance;
   cout << "Enter starting balance for checking: $ ";
   cin >> startCheckBalance;

   cout << "Enter annual interest rate: ";
   cin >> annualInterestRate;

   SavingsAccount savings(startSaveBalance, annualInterestRate);
   CheckingAccount checkings(startCheckBalance, annualInterestRate);
   menu(checkings, savings);


   return 0;
}
