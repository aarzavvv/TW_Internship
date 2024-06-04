// Including necessary Libraries
#include<iostream>
#include<mysql.h>
#include<mysqld_error.h>
#include<string>

using namespace std;

// Global Variables
MYSQL *CONNECTION;
MYSQL_ROW row;
MYSQL_RES* res;

// Functions Declaration
void start_connection();
void end_connection();
char get_option();
void open_new_account();
int get_new_account_id();
void deposit_amount();
void close_account();
void withdraw_amount();
void balance_enquiry();
void modify_account();
void list_account_holders();
void main_menu();


// Functions Defining
// Connecting MYSQL with the Code
void start_connection()
{
	CONNECTION = mysql_init(NULL);
	if(!CONNECTION)
	{
		cout<<"Error in initializing MYSQL connection: "<<mysql_error(CONNECTION)<<endl;
		exit(1);
	}
	if(!mysql_real_connect(CONNECTION, "localhost", "root", "0000", "bank", 0, NULL, 0))
	{
		cout<<"Error in connecting to MySQL database: "<<mysql_error(CONNECTION)<<endl;
        exit(1);
	}
	cout<<"Connection Established Successfully!!!"<<endl;
}

// Connection Ending
void end_connection()
{
    mysql_close(CONNECTION);
    cout<<"Connection successfully Closed !!!"<<endl;
}

// Options in the main_menu
char get_option()
{
	char ch;
	cout<<"1. Open new Account"<<endl;
    cout<<"2. Deposit Amount"<<endl;
    cout<<"3. Withdraw Amount"<<endl;
    cout<<"4. Balance Enquiry"<<endl;
    cout<<"5. List Account Holders"<<endl;
    cout<<"6. Close an Account"<<endl;
    cout<<"7. Modify an Account"<<endl;
    cout<<"8. Exit"<<endl;
    cout<<"ENTER OPTION NO. [1-8]: ";
    cin>>ch;
    return ch;
}

// Opening new Account
void open_new_account()
{
	string name, dob, addr;
	int ctc, opbal;
	cout<<"ENTER NAME: ";
	cin.ignore();
	getline(cin, name);

	cout<<"ENTER D.O.B [YYY-MM-DD]: ";
	cin>>dob;

	cout<<"ENTER CONTACT: ";
    cin>>ctc;

    cout<<"ENTER ADDRESS: ";
    cin.ignore();
    getline(cin, addr);

    cout<<"ENTER OPENING BALANCE: ";
    cin>>opbal;

    int idno = get_new_account_id();
    cout<<"Your new Account ID is "<<idno<<endl;

    string sql = "INSERT INTO account (ID, NAME, DOB, ADDRESS, CONTACT, OPEN_BALANCE) VALUES ('" + to_string(idno) + "', '" + name + "', '" + dob + "', '" + addr + "', '" + to_string(ctc) + "', '" + to_string(opbal) + "')";
    if(mysql_query(CONNECTION, sql.c_str()))
    {
    	cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
    	exit(1);
	}
	string sql2 = "INSERT INTO amount (ID, NAME, BALANCE) VALUES ('" + to_string(idno) + "', '" + name + "', '" + to_string(opbal) + "')";
    if(mysql_query(CONNECTION, sql2.c_str()))
	{
        cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
        exit(1);
    }
    cout<<"DATA ENTERED SUCCESSFULLY"<<endl;
}

// Generating new ID no.
int get_new_account_id()
{
	if(mysql_query(CONNECTION, "SELECT MAX(ID) AS max_id FROM account"))
	{
        cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
        exit(1);
    }
    res = mysql_store_result(CONNECTION);
    if(!res)
	{
        cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
        exit(1);
    }
    row = mysql_fetch_row(res);
    int new_account_id = atoi(row[0]);
    mysql_free_result(res);
    return new_account_id + 1;
}

// Depositing Amount
void deposit_amount()
{
    int idno, amount;
    cout<<"ENTER ACCOUNT NO.: ";
    cin>>idno;
    cout<<"ENTER AMOUNT: ";
    cin>>amount;
    string sql = "UPDATE amount SET BALANCE = BALANCE + " + to_string(amount) + " WHERE ID = " + to_string(idno);
    if(mysql_query(CONNECTION, sql.c_str()))
	{
        cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
        exit(1);
    }
    cout<<"AMOUNT DEPOSITED SUCCESSFULLY"<<endl;
}

// Closing an Account
void close_account()
{
	int idno;
	cout<<"ENTER ACCOUNT NO.: ";
	cin>>idno;
	string sql = "DELETE FROM amount WHERE ID = " + to_string(idno);
	if(mysql_query(CONNECTION, sql.c_str()))
	{
		cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
		exit(1);
	}
	string sql2 = "DELETE FROM account WHERE ID = " + to_string(idno);
	if(mysql_query(CONNECTION, sql2.c_str()))
	{
		cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
		exit(1);
	}
	cout<<"ACCOUNT CLOSED SUCCESSFULLY"<<endl;
}

// Withdrawing Amount
void withdraw_amount()
{
    int idno, dr;
    cout<<"ENTER ACCOUNT NO.: ";
	cin>>idno;
	cout<<"ENTER AMOUNT: ";
	cin>>dr;
	string sql = "UPDATE amount SET BALANCE = BALANCE - " + to_string(dr) + " WHERE ID = " + to_string(idno);
	if(mysql_query(CONNECTION, sql.c_str()))
	{
		cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
		exit(1);
	}
	cout<<"ACCOUNT CLOSED SUCCESSFULLY"<<endl;
}

// Balance Enquiry
void balance_enquiry()
{
	int idno;
	cout<<"ENTER ACCOUNT NO.: ";
	cin>>idno;
	string sql = "SELECT BALANCE FROM amount WHERE ID = " + to_string(idno);
	if(mysql_query(CONNECTION, sql.c_str()))
	{
		cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
		exit(1);
	}
	res = mysql_store_result(CONNECTION);
	if(!res)
	{
		cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
		exit(1);
	}
	row = mysql_fetch_row(res);
	cout<<"THE BALANCE IS "<<row[0]<<endl;
	mysql_free_result(res);
}

// Customer Details
void get_customer_details()
{
	int idno;
	cout<<"ENTER ACCOUNT NO.: ";
	cin>>idno;
	string sql = "SELECT * FROM account WHERE ID = " + to_string(idno);
	if(mysql_query(CONNECTION, sql.c_str()))
	{
		cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
		exit(1);
	}
		res = mysql_store_result(CONNECTION);
	if(!res)
	{
		cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
		exit(1);
	}
	row = mysql_fetch_row(res);
	cout<<"THE CUSTOMER DETAILS ARE AS "<<row[0]<<", "<<row[1]<<", "<<row[2]<<", "
	<<row[3]<<", "<<row[4]<<", "<<row[5]<<endl;
	mysql_free_result(res);
}

// Listing Account Holders
void list_account_holders()
{
	string sql = "SELECT * FROM account";
	if(mysql_query(CONNECTION, sql.c_str()))
	{
		cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
		exit(1);
	}
	res = mysql_store_result(CONNECTION);
	if(!res)
	{
		cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
		exit(1);
	}
	cout<<"LIST OF ACCOUNT HOLDERS: "<<endl;
	while((row = mysql_fetch_row(res)))
	{
		cout<<"ID: "<<row[0]<<", Name: "<<row[1]<<", DOB: "<<row[2]<<", Address: "<<
		row[3]<<", Contact: "<<row[4]<<", Opening Balance: "<<row[5]<<endl;
	}
	mysql_free_result(res);
}

// Modifying an Account
void modify_account()
{
    int idno;
	cout<<"ENTER ACCOUNT NO.: ";
	cin>>idno;

	string name, dob, addr;
	int ctc;
	double open_bal;

	// Name
	cout<<"ENTER THE NEW NAME: ";
	cin.ignore();
	getline(cin, name);
	// DOB
	cout<<"ENTER THE NEW PREFERRED D.O.B [YYYY-MM-DD]: ";
	cin>>dob;
	// Address
	cout<<"ENTER THE NEW PREFFERED ADDRESS: ";
	cin.ignore();
	getline(cin, addr);
	// Contact
	cout<<"ENTER THE NEW CONTACT: ";
    cin>>ctc;
    // Balance Update
    cout<<"ENTER THE NEW BALANCE UPDATE: ";
    cin>>open_bal;
    string sql = "UPDATE account SET NAME = '" + name + "', DOB = '" + dob + "', ADDRESS = '" + addr + "', CONTACT = '" + to_string(ctc) + "', OPEN_BALANCE = '" + to_string(open_bal) + "' WHERE ID = " + to_string(idno);
    if(mysql_query(CONNECTION, sql.c_str()))
    {
        cout<<"Error: "<<mysql_error(CONNECTION)<<endl;
        exit(1);
    }
    cout<<"ACCOUNT MODIFIED SUCCESSFULLY."<<endl;
}

// Main Menu
void main_menu()
{
	cout<<"----- WELCOME TO OUR SILLY BANK -----"<<endl;

	while (true)
	{
		char ch = get_option();
		if(ch == '8')
		{
			cout<<"EXITING THE SYSTEM!!!"<<endl;
			break;
		}

		if(ch >= '1' && ch <= '7')
		{
			start_connection();
			switch(ch)
			{
				case '1':
					open_new_account();
					break;
				case '2':
					deposit_amount();
					break;
				case '3':
					withdraw_amount();
					break;
				case '4':
					balance_enquiry();
					break;
				case '5':
					list_account_holders();
					break;
				case '6':
					close_account();
					break;
				case '7':
					modify_account();
					break;
				default:
					break;
			}
			end_connection();
		}
		else
		{
			cout<<"Wrong option!!!"<<endl;
		}
	}
	cout<<"----- Thank You, Visit Again! -----"<<endl;
}

// Main Function
int main()
{
	// Establishing Connection
	start_connection();

	// Calling Main Menu
	main_menu();

	// Ending Connection
	end_connection();

	return 0;
}



