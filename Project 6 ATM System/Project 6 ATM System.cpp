#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

const string ClientsFileName = "ClientsData.txt";

enum enATMMainMenueOptions { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eLogout = 5 };
enum enQuickWithdrawMenueOptions { Twenty = 1, Fifty = 2, OneHundred = 3, TwoHundred = 4, FourHundred = 5, SixHundred = 6, EightHundred = 7, OneThousand = 8, Exit = 9 };

struct stClientData
{
	string AccountNumber = "";
	string PINCode = "";
	string Name = "";
	string Phone = "";
	bool MarkForDelete = false;
	double AccountBalance = 0;
};

//Global Variabel

stClientData CurrentClient;

//Declarations.

void ShowATMMainMenueOptions();
void GoBackToATMMainMenueOptions();
void ShowQuickWithdrawScreen();
void Login();

//Show Quick Withdraw Screen.

vector <string> SplitString(string str, string Sperator = "#//#")
{
	vector <string> vString;
	short Position = 0;
	string sWord = "";

	while ((Position = str.find(Sperator)) != std::string::npos)
	{
		sWord = str.substr(0, Position);

		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		str.erase(0, Position + Sperator.length());
	}

	if (str != "")
	{
		vString.push_back(str);
	}
	return vString;
}

stClientData ConvertRecordClientInOneLineFromFileTostClientData(string strClientData)
{
	stClientData ClientData;
	vector <string> vClientData;

	vClientData = SplitString(strClientData);

	ClientData.AccountNumber = vClientData[0];
	ClientData.PINCode = vClientData[1];
	ClientData.Name = vClientData[2];
	ClientData.Phone = vClientData[3];
	ClientData.AccountBalance = stod(vClientData[4]);

	return ClientData;
}

vector <stClientData> LoadRecordClientInOneLineFromFileTovClientData(string FileName)
{
	vector <stClientData> vClientData;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line = "";
		stClientData ClientData;

		while (getline(MyFile, Line))
		{
			ClientData = ConvertRecordClientInOneLineFromFileTostClientData(Line);
			vClientData.push_back(ClientData);
		}
		MyFile.close();
	}
	return vClientData;
}

string ConvertRecordClientToOneLine(stClientData ClientData, string Sperator = "#//#")
{
	string strClientData = "";

	strClientData += ClientData.AccountNumber + Sperator;
	strClientData += ClientData.PINCode + Sperator;
	strClientData += ClientData.Name + Sperator;
	strClientData += ClientData.Phone + Sperator;
	strClientData += to_string(ClientData.AccountBalance);

	return strClientData;
}

vector <stClientData> SaveRecordClientInOneLineToFileAfterDeleteOrUpDate(string FileName, vector <stClientData> vClientData)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string strClientData = "";

	if (MyFile.is_open())
	{
		for (stClientData& ClData : vClientData)
		{
			if (ClData.MarkForDelete == false)
			{
				strClientData = ConvertRecordClientToOneLine(ClData);
				MyFile << strClientData << endl;
			}
		}
		MyFile.close();
	}
	return vClientData;
}

short ReadQucikWithdrawOptions()
{
	short ClientChoose = 0;

	do
	{
		cout << "Choose What to Withdraw From [1 to 9]? ";
		cin >> ClientChoose;

	} while (ClientChoose < 1 || ClientChoose > 9);

	return ClientChoose;
}

short GetQuickWithdrawAmount(enQuickWithdrawMenueOptions QuickWithdrawMenueOptions)
{
	switch(QuickWithdrawMenueOptions)
	{
	case enQuickWithdrawMenueOptions::Twenty:
		return 20;
	case enQuickWithdrawMenueOptions::Fifty:
		return 50;
	case enQuickWithdrawMenueOptions::OneHundred:
		return 100;
	case enQuickWithdrawMenueOptions::TwoHundred:
		return 200;
	case enQuickWithdrawMenueOptions::FourHundred:
		return 400;
	case enQuickWithdrawMenueOptions::SixHundred:
		return 600;
	case enQuickWithdrawMenueOptions::EightHundred:
		return 800;
	case enQuickWithdrawMenueOptions::OneThousand:
		return 1000;
	default:
		return 0;
	}
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClientData>& vClientData)
{
	char ClientAnswer = 'n';

	cout << "\n\nAre Your Sure You Want to Perfrom This Transaction? [Y/N]? ";
	cin >> ClientAnswer;

	if (toupper(ClientAnswer) == 'Y')
	{
		for (stClientData& ClData : vClientData)
		{
			if (ClData.AccountNumber == AccountNumber)
			{
				ClData.AccountBalance += Amount;
				cout << "\n\nDone Successfully. New Balance is : " << ClData.AccountBalance << " $ " << endl;
				break;
			}
		}
		SaveRecordClientInOneLineToFileAfterDeleteOrUpDate(ClientsFileName, vClientData);
		return true;
	}
	else
	{
		GoBackToATMMainMenueOptions();
		return false;
	}
}

void PerformQuickWithdrawMenueOptions(enQuickWithdrawMenueOptions QuickWithdrawMenueOptions)
{
	if (QuickWithdrawMenueOptions == enQuickWithdrawMenueOptions::Exit)
		return;

	short WithdrawAmount = GetQuickWithdrawAmount(QuickWithdrawMenueOptions);

	if (WithdrawAmount > CurrentClient.AccountBalance)
	{
		cout << "\n\nThe Amount Exceeds Your Balance, Make Another Choice.\n";
		cout << "Press Any Key to Contnue....";
		system("pause>0");
		ShowQuickWithdrawScreen();
		return;
	}

	vector <stClientData> vClientData = LoadRecordClientInOneLineFromFileTovClientData(ClientsFileName);
	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount * -1, vClientData);
	CurrentClient.AccountBalance -= WithdrawAmount;
}

void ShowQuickWithdrawScreen()
{
		system("Cls");
		cout << "==================================================\n";
		cout << "\t\tQuick Withdraw Screen\n";
		cout << "==================================================\n";
		cout << "\t[1] 20 $ \t [2] 50 $ \n";
		cout << "\t[3] 100 $ \t [4] 200 $ \n";
		cout << "\t[5] 400 $ \t [6] 600 $ \n";
		cout << "\t[7] 800 $ \t [8] 1000 $ \n";
		cout << "\t[9] Exit. \n";
		cout << "==================================================\n";

		cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;

		PerformQuickWithdrawMenueOptions((enQuickWithdrawMenueOptions)ReadQucikWithdrawOptions());
}

//Show Normal Withdraw Screen.

int ReadWithdrawAmount()
{
	int WithdrawAmount = 0;

	do
	{
		cout << "Enter an Amount Multiple Of 5's? ";
		cin >> WithdrawAmount;

	} while (WithdrawAmount % 5 != 0);
	return WithdrawAmount;
}

void ShowNormalWithdrawScreen()
{
	system("Cls");
	cout << "==================================================\n";
	cout << "\t\tNormal Withdraw Screen\n";
	cout << "==================================================\n";

	int WithdrawAmount = ReadWithdrawAmount();

	if (WithdrawAmount > CurrentClient.AccountBalance)
	{
		cout << "\n\nThe Amount Exceeds Your Balance, Make Another Choice.\n";
		cout << "Press Any Key to Contnue....";
		system("pause>0");
		ShowNormalWithdrawScreen();
		return;
	}

	vector <stClientData> vClientData = LoadRecordClientInOneLineFromFileTovClientData(ClientsFileName);
	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawAmount * -1, vClientData);
	CurrentClient.AccountBalance -= WithdrawAmount;
}

//Show Deposit Screen.

double ReadDepositAmount()
{
	double DepositAmount = 0;

	do
	{
		cout << "Please Enter a Positive Amount? ";
		cin >> DepositAmount;

	} while (DepositAmount <= 0);
	return DepositAmount;
}

void PerfromDepositOptions()
{
	double DepositAmount = ReadDepositAmount();
	vector <stClientData> vClientData = LoadRecordClientInOneLineFromFileTovClientData(ClientsFileName);

	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClientData);
	CurrentClient.AccountBalance += DepositAmount;
}

void ShowDepositScreen()
{
	system("Cls");
	cout << "==================================================\n";
	cout << "\t\tDeposit Screen\n";
	cout << "==================================================\n";

	PerfromDepositOptions();
}

//Show Check Balance Screen.

void ShowCheckBalanceScreen()
{
	system("Cls");
	cout << "==================================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "==================================================\n";

	cout << "Your Balance is : " << CurrentClient.AccountBalance << " $ ";
}

//Show ATM Main Menue Screen.

void GoBackToATMMainMenueOptions()
{
	cout << "\n\nPress any key to go back to ATM Main Menue....";
	system("pause>0");
	ShowATMMainMenueOptions();
}

short ReadATMMainMenueOptions()
{
	short ClientChoose = 0;

	do
	{
		cout << "Choose What Do You Want to Do? [1 to 5]? ";
		cin >> ClientChoose;

	} while (ClientChoose < 1 || ClientChoose > 5);

	return ClientChoose;
}

void PerformATMMainMenueOptions(enATMMainMenueOptions ATMMainMenueOptions)
{
	switch (ATMMainMenueOptions)
	{
	case enATMMainMenueOptions::eQuickWithdraw:
	{
		system("Cls");
		ShowQuickWithdrawScreen();
		GoBackToATMMainMenueOptions();
		break;
	}
	case enATMMainMenueOptions::eNormalWithdraw:
	{
		system("Cls");
		ShowNormalWithdrawScreen();
		GoBackToATMMainMenueOptions();
		break;
	}
	case enATMMainMenueOptions::eDeposit:
	{
		system("Cls");
		ShowDepositScreen();
		GoBackToATMMainMenueOptions();
		break;
	}
	case enATMMainMenueOptions::eCheckBalance:
	{
		system("Cls");
		ShowCheckBalanceScreen();
		GoBackToATMMainMenueOptions();
		break;
	}
	case enATMMainMenueOptions::eLogout:
	{
		system("Cls");
		Login();
		break;
	}
	}
}

void ShowATMMainMenueOptions()
{
	system("Cls");
	cout << "==================================================\n";
	cout << "\t\tATM Main Menue Screen\n";
	cout << "==================================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "==================================================\n";

	PerformATMMainMenueOptions((enATMMainMenueOptions)ReadATMMainMenueOptions());
}

//Login.

bool FindClientByAccountNumberAndPINCode(string AccountNumber, string PINCode, stClientData& ClientData)
{
	vector <stClientData> vClientData = LoadRecordClientInOneLineFromFileTovClientData(ClientsFileName);

	for (stClientData& ClData : vClientData)
	{
		if (ClData.AccountNumber == AccountNumber && ClData.PINCode == PINCode)
		{
			ClientData = ClData;
			return true;
		}
	}
	return false;
}

bool LoadClientInfo(string AccountNumber, string PINCode)
{
	if (FindClientByAccountNumberAndPINCode(AccountNumber, PINCode, CurrentClient))
		return true;
	else
		return false;
}

void Login()
{
	bool LoginFalid = false;
	string AccountNumber = "", PINCode = "";

	do
	{
		system("Cls");
		cout << "----------------------------------------------\n";
		cout << "\t\tLogin Screen\n";
		cout << "----------------------------------------------\n";

		if (LoginFalid)
		{
			cout << "Invalid Account Number/PINCode! \n\n";
		}

		cout << "Please Enter Account Number? ";
		cin >> AccountNumber;

		cout << "Please Enter PIN Code? ";
		cin >> PINCode;

		LoginFalid = !LoadClientInfo(AccountNumber, PINCode);

	} while (LoginFalid);

	ShowATMMainMenueOptions();
}

int main()
{
	Login();
	system("pause>0");
	return 0;
}