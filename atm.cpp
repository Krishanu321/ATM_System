#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class BankAccount
{
private:
    const int customerAccountNumber = 12345;
    const int pinNumber = 54321;
    int accountBalance = 3000;

    queue<string> transactionHistory;

    bool validateCustomerDetails()
    {
        int inputAccountNumber, inputPinNumber;
        int retryCount = 3;

        cout << "Welcome!\n";

        while (true)
        {
            cout << "Please enter your Bank Account Number: ";
            cin >> inputAccountNumber;

            if (inputAccountNumber == customerAccountNumber)
                break;
            else
                cout << "Invalid Account Number! Try again.\n";
        }

        while (retryCount > 0)
        {
            cout << "Enter your PIN: ";
            cin >> inputPinNumber;

            if (inputPinNumber == pinNumber)
                return true;

            retryCount--;
            if (retryCount > 0)
                cout << "Invalid PIN! " << retryCount << " attempts left. Try again.\n";
            else
            {
                cout << "Your account is locked! Too many failed attempts.\n";
                return false;
            }
        }

        return false;
    }

    int displayMenu()
    {
        int option;

        cout << "\nWelcome to Your Account! Please choose an option:\n";
        cout << "1 - View Account Balance\n";
        cout << "2 - Withdraw Cash\n";
        cout << "3 - Deposit Cash\n";
        cout << "4 - View Transaction History\n";
        cout << "5 - Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        return option;
    }

    void displayAccountBalance() const
    {
        cout << "\nYour account balance is: Rs." << accountBalance << endl;
    }

    bool binarySearch(vector<int> &options, int amount)
    {
        return binary_search(options.begin(), options.end(), amount);
    }

    void withdrawCash()
    {
        vector<int> withdrawalOptions = {20, 40, 60, 100, 200};
        sort(withdrawalOptions.begin(), withdrawalOptions.end());
        int option, customAmount;
        bool isTransactionActive = true;

        while (isTransactionActive)
        {
            cout << "\nWithdrawal Options:\n";
            for (int i = 0; i < withdrawalOptions.size(); i++)
                cout << i + 1 << " - Rs." << withdrawalOptions[i] << "/-\n";
            cout << "6 - Cancel Transaction\n";
            cout << "7 - Custom Amount\n";
            cout << "Choose an option: ";
            cin >> option;

            if (option >= 1 && option <= withdrawalOptions.size())
            {
                int amountToWithdraw = withdrawalOptions[option - 1];
                if (amountToWithdraw > accountBalance)
                    cout << "Insufficient balance! Your account balance is Rs." << accountBalance << ".\n";
                else
                {
                    accountBalance -= amountToWithdraw;
                    cout << "Transaction successful! Your new balance is Rs." << accountBalance << ".\n";
                    transactionHistory.push("Withdraw: Rs." + to_string(amountToWithdraw));
                    if (transactionHistory.size() > 10)
                        transactionHistory.pop();
                    isTransactionActive = false;
                }
            }
            else if (option == 6)
            {
                cout << "Transaction cancelled.\n";
                isTransactionActive = false;
            }
            else if (option == 7)
            {
                cout << "Enter the custom amount to withdraw: ";
                cin >> customAmount;
                if (customAmount > accountBalance)
                    cout << "Insufficient balance! Your account balance is Rs." << accountBalance << ".\n";
                else
                {
                    accountBalance -= customAmount;
                    cout << "Transaction successful! Your new balance is Rs." << accountBalance << ".\n";
                    transactionHistory.push("Withdraw: Rs." + to_string(customAmount));
                    if (transactionHistory.size() > 10)
                        transactionHistory.pop();
                    isTransactionActive = false;
                }
            }
            else
            {
                cout << "Invalid option! Try again.\n";
            }
        }
    }

    void depositCash()
    {
        vector<int> depositOptions = {20, 40, 60, 100, 200};
        sort(depositOptions.begin(), depositOptions.end());
        int option, customAmount;
        bool isTransactionActive = true;

        while (isTransactionActive)
        {
            cout << "\nDeposit Options:\n";
            for (int i = 0; i < depositOptions.size(); i++)
                cout << i + 1 << " - Rs." << depositOptions[i] << "/-\n";
            cout << "6 - Cancel Transaction\n";
            cout << "7 - Custom Amount\n";
            cout << "Choose an option: ";
            cin >> option;

            if (option >= 1 && option <= depositOptions.size())
            {
                int amountToDeposit = depositOptions[option - 1];
                accountBalance += amountToDeposit;
                cout << "Transaction successful! Your new balance is Rs." << accountBalance << ".\n";
                transactionHistory.push("Deposit: Rs." + to_string(amountToDeposit));
                if (transactionHistory.size() > 10)
                    transactionHistory.pop();
                isTransactionActive = false;
            }
            else if (option == 6)
            {
                cout << "Transaction cancelled.\n";
                isTransactionActive = false;
            }
            else if (option == 7)
            {
                cout << "Enter the custom amount to deposit: ";
                cin >> customAmount;
                accountBalance += customAmount;
                cout << "Transaction successful! Your new balance is Rs." << accountBalance << ".\n";
                transactionHistory.push("Deposit: Rs." + to_string(customAmount));
                if (transactionHistory.size() > 10)
                    transactionHistory.pop();
                isTransactionActive = false;
            }
            else
            {
                cout << "Invalid option! Try again.\n";
            }
        }
    }

    void viewTransactionHistory()
    {
        if (transactionHistory.empty())
        {
            cout << "No transaction history available.\n";
        }
        else
        {
            cout << "\nLast 10 Transactions:\n";
            queue<string> tempQueue = transactionHistory;
            while (!tempQueue.empty())
            {
                cout << tempQueue.front() << endl;
                tempQueue.pop();
            }
        }
    }

public:
    void run()
    {
        if (validateCustomerDetails())
        {
            bool isSessionActive = true;

            while (isSessionActive)
            {
                switch (displayMenu())
                {
                case 1:
                    displayAccountBalance();
                    break;
                case 2:
                    withdrawCash();
                    break;
                case 3:
                    depositCash();
                    break;
                case 4:
                    viewTransactionHistory();
                    break;
                case 5:
                    cout << "Thank you for using our service! Goodbye.\n";
                    isSessionActive = false;
                    break;
                default:
                    cout << "Invalid option! Try again.\n";
                    break;
                }
            }
        }
    }
};

int main()
{
    BankAccount account;
    account.run();
    return 0;
}
