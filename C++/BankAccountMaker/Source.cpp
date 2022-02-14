/*
Name: Alex Hatoum
Course Number and Section: C++ CS 1119-01
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

class TransactionProcessing {
private:
	string accountName;
	double accountBalance;

public:
	TransactionProcessing();

	void SetName(string name) { accountName = name; }
	void SetBalance(double balance) { accountBalance = balance; }

	string GetName() { return accountName; }
	double GetBalance() { return accountBalance; }

	void Deposit(double amount);
	void Withdraw(double amount);

	void PrintBalance();
	void PrintMenu();
};

TransactionProcessing::TransactionProcessing() {
	accountName = "None";
	accountBalance = 0.00;
}

void TransactionProcessing::Deposit(double amount) {
	accountBalance += amount;
	cout << fixed << setprecision(2) << accountName << "'s Balance is: $" << accountBalance << endl;
	cout << endl;
}

void TransactionProcessing::Withdraw(double amount) {
	if ((accountBalance - amount) < 0) {
		cout << fixed << setprecision(2) << "No sufficient funds for " << accountName << ", Balance is: $" << accountBalance << ". Transaction canceled." << endl;
		cout << endl;
	}
	else {
		accountBalance -= amount;
		cout << fixed << setprecision(2) << accountName << "'s Balance is: $" << accountBalance << endl;
		cout << endl;
	}
}

void TransactionProcessing::PrintBalance() {
	cout << fixed << setprecision(2) << accountName << "'s Balance is: $" << accountBalance << endl;
	cout << endl;
}

void TransactionProcessing::PrintMenu() {
	cout << "Please choose the letter for your transaction or enter E to exit.\n";
	cout << "Enter C to create a new user account\n";
	cout << "Enter D to deposit funds into a user account\n";
	cout << "Enter W to withdraw funds from a user account\n";
	cout << "Enter P to print a user account balance\n";
	cout << "Enter E to exit the program\n";
	cout << "Your choice: ";
}

int main() {
	vector<TransactionProcessing> accountAccessor(1);
	string accountInfo, name, dummyString;
	double initialAmount;
	istringstream inSS;
	char menuChoice;
	int numSpaces = 0;

	cout << "Welcome to Banking Transaction Program\n";
	cout << endl;

	accountAccessor.at(0).PrintMenu();
	accountAccessor.resize(0);
	cin >> menuChoice;
	cin.ignore();
	cout << endl;

	while (menuChoice != 'E') {
		switch (menuChoice) {
		case 'E':
			break;

		case 'C':
			accountAccessor.resize(accountInfo.size() + 1);

			cout << "Please enter the customer name and initial deposit amount: ";
			getline(cin, accountInfo);
			inSS.clear();
			inSS.str(accountInfo);

			numSpaces = 0;
			name.clear();
			for (int i = 0; i < accountInfo.size(); ++i) {
				if (isalpha(accountInfo.at(i)) || isspace(accountInfo.at(i))) {
					name.push_back(accountInfo.at(i));
				}

				if (accountInfo.at(i) == ' ') {
					numSpaces += 1;
				}
			}
			name.erase(name.end() - 1);

			for (int i = 0; i < numSpaces; ++i) {
				inSS >> dummyString;
			}
			inSS >> initialAmount;

			accountAccessor.at(accountAccessor.size() - 1).SetName(name);
			accountAccessor.at(accountAccessor.size() - 1).SetBalance(initialAmount);

			cout << name << "'s Balance is: $" << initialAmount << endl << endl;
			break;

		case 'D':
			cout << "Please enter the account name and the deposit amount: ";
			getline(cin, accountInfo);
			inSS.clear();
			inSS.str(accountInfo);

			numSpaces = 0;
			name.clear();
			for (int i = 0; i < accountInfo.size(); ++i) {
				if (isalpha(accountInfo.at(i)) || isspace(accountInfo.at(i))) {
					name.push_back(accountInfo.at(i));
				}

				if (accountInfo.at(i) == ' ') {
					numSpaces += 1;
				}
			}
			name.erase(name.end() - 1);

			for (int i = 0; i < numSpaces; ++i) {
				inSS >> dummyString;
			}
			inSS >> initialAmount;


			for (int i = 0; i < accountAccessor.size(); ++i) {
				if (accountAccessor.at(i).GetName() == name) {

					accountAccessor.at(i).Deposit(initialAmount);
					break;
				}
			}

			break;
		case 'W':
			cout << "Please enter the account name and the withdraw amount: ";
			getline(cin, accountInfo);
			inSS.clear();
			inSS.str(accountInfo);

			numSpaces = 0;
			name.clear();
			for (int i = 0; i < accountInfo.size(); ++i) {
				if (isalpha(accountInfo.at(i)) || isspace(accountInfo.at(i))) {
					name.push_back(accountInfo.at(i));
				}

				if (accountInfo.at(i) == ' ') {
					numSpaces += 1;
				}
			}
			name.erase(name.end() - 1);

			for (int i = 0; i < numSpaces; ++i) {
				inSS >> dummyString;
			}
			inSS >> initialAmount;


			for (int i = 0; i < accountAccessor.size(); ++i) {
				if (accountAccessor.at(i).GetName() == name) {

					accountAccessor.at(i).Withdraw(initialAmount);
					break;
				}
			}

			break;
		case 'P':
			cout << "Please enter the account name: ";
			getline(cin, accountInfo);

			for (int i = 0; i < accountAccessor.size(); ++i) {
				if (accountAccessor.at(i).GetName() == accountInfo) {
					accountAccessor.at(i).PrintBalance();
					break;
				}
			}
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}

		if (menuChoice == 'E') {
			break;
		}

		accountAccessor.at(0).PrintMenu();
		cin >> menuChoice;
		cin.ignore();
		cout << endl;
	}

	cout << "Thank you for using the Banking transaction program." << endl;

	return 0;
}