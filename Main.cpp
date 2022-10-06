#include<iostream>
#include<fstream>
#include<string>

using namespace std;

ofstream myfile;
ofstream myfileUpdate;
ifstream counterfileIf;
ofstream counterfileOf;
ofstream registeration;

class accounts {
	string username, password;
public :
	void Register(string, string);
	bool CheckUserName(string);
	bool CheckPassWord(string);
	string userNameREQ();
	void ChangePass(string);
	void ChangeUser(string);
	int nOfEmails = 0;
	void Email(int, string);
	void updateDataFile();
	~accounts(){
		myfile << "\t*system deleted all users down*" << endl;

		myfile.close();
	}
};
// accounts class functions 

void accounts::Register(string n, string p) {
	username = n;
	password = p;


	//myfile <<n<<'\t'<<p << endl;



	//cout << "Registerd succsessfully !" << endl;
}
bool accounts::CheckUserName(string n) {
	if (n == username) return true;
	else return false;
}

void accounts::Email(int i = 0,string mes="old") {
	string AllMails[99];
	AllMails[0] = "Test";
	if ( i == 0) {
		AllMails[nOfEmails] = mes;
		nOfEmails++;
		cout << "Recvied" << endl;
		
	}
	else {
		for (int t = 0; t < nOfEmails; t++) {
			cout << "[" << t << "] " << AllMails[t] << endl;
		}
	}

}

bool accounts::CheckPassWord(string p) {
	if (p == password) return true;
	else return false;

}
string accounts::userNameREQ() {
	return username;
}
void accounts::ChangePass(string p) {
//	myfile << "Log ** user : " << username << " Has changed password from " << password << " To " << p << endl;
	password = p;
}
void accounts::ChangeUser(string n) {
//	myfile << "Log ** user : " << username << " Has changed username to : " << n  << endl;

	username = n;
	

}
void accounts::updateDataFile() {
	myfileUpdate << username << '\t' << password << endl;
}


// account array with maximum size of 99 users
accounts acc[99];
// counter for how many accounts are created
int counter = 0;

// function to check if the username is already in the data base when regiestring new account
bool checkIfUserIsRegisterdAlReady(string n) {
	if (counter == 0)return false;
	else {
		for (int i = 0; i <= counter; i++) {
			if (acc[i].CheckUserName(n)) return true;
			else continue;
		}return false;
	}
}


string checkIfUserIsRegisterdAlReadyFromFile(string n) {
	ifstream checkUserFile;
	checkUserFile.open(n + ".txt");
	string h;
	while (checkUserFile >> h);
	if (h.length() > 0) {
		return h;
	}
	else return "false";

}

// search for user ID by using username
int seeUserId(string n) {
	int Id=0;
	for (int i = 0; i <= counter; i++) {
		if (acc[i].CheckUserName(n)) {
			Id = i;
			break;
		}
		else continue;
	}
	return Id;
}

// session system 
int session = -1;

//login function 
void login() {
	string user, pass;
	int numm = -1;
	while (numm == -1) {
		cout << "Enter user name : ";
		cin >> user;
		if (checkIfUserIsRegisterdAlReady(user) == false) {
			cout << "No such a name in our data base !" << endl;
		}
		// we make the numm = userId , so we can save the userId for later uses , we also use numm as a mini session
		else { numm = seeUserId(user); }
	}
	int numm2 = 1;
	//summ2 is a mini session 
	while (numm2 == 1) {
		cout << "\n Enter Password : ";
		cin >> pass;
		if (acc[numm].CheckPassWord(pass)) {
			cout << "\t Welcome back " << acc[numm].userNameREQ() << " ! " << endl;
			session = numm;
			// we assign any number for numm2 to exit the session
			numm2 = 0;
			
		}
		else cout << "Wrong pass !" << endl;
	}
	
}



//void login() {
//	string user, pass,checkpass;
//	int numm = -1;
//	cout << "type name";
//	cin >> user;
//	checkpass = checkIfUserIsRegisterdAlReadyFromFile(user);
//	if (checkpass == "false")cout << "No such a name";
//	else {
//		cout << "Type password";
//		cin >> pass;
//		if (checkpass == pass)cout << "Welcome back " << user << endl;
//		else cout << "Wrong pass" << endl;
//	}
//
//}

//register function
void Reg(){
	
	string user, pass;
	int numm = 1;
	while (numm == 1) {
		cout << "Enter user name : ";
		cin >> user;
		if (checkIfUserIsRegisterdAlReady(user)) {
			cout << "user already registered" << endl;
		}
		else numm = 0;
	}
	cout << "\n Enter Password : ";
	cin >> pass;
	acc[counter].Register(user, pass);


	/* ofstream{user + ".txt"};
	registeration.open(user + ".txt");
	registeration <<pass << endl;
	registeration.close();
	*/
	counter++;
	counterfileOf.open("count.txt");
	counterfileOf << counter;
	counterfileOf.close();

	myfile << user << '\t' << pass << endl;
	cout << "Registerd succsessfully !" << endl;
}

void AutoReg(string user,string pass) {

	acc[counter].Register(user, pass);
	counter++;

}

void updateDataFiles() {
	myfileUpdate.open("data.txt");

	for (int i = 0; i < counter; i++) {
		acc[i].updateDataFile();
	}
	myfileUpdate.close();
}

int main() {
	//std::ofstream out("data.txt", std::ios_base::app);

	myfile.open("data.txt", std::ios_base::app);
	counterfileIf.open("count.txt");
	myfile << endl;
	//while (counterfileIf >> counter);
	ifstream readData;
	readData.open("data.txt");
	string readUsers, readPass;
	while (readData >> readUsers>>readPass) {
		AutoReg(readUsers, readPass);
//		cout << test1 << endl;
	}
	 
	

	// main loop , non stop
	while (true) {

		// session (-1) login or register 
		while (session == -1) {
			cout << "To login press 1 , to register press 2 " << endl;
			int command;
			cin >> command;
			if (command == 1) {
				login();
			}
			else if (command == 2) {
				Reg();
			}
			else {
				cout << "Wrong input" << endl;
				
			}
		}

		// user session 
		while (session > -1) {
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			cout << "\t *******************************************************\n\n" << endl;
			cout << "\t User ID " << session << endl;
			cout << "\n\n \t *******************************************************\n\n" << endl;
			cout << " \t username : " << acc[session].userNameREQ() << endl;
			cout << "\n\n \t *******************************************************\n\n" << endl;
			cout << "Press 1 for Email : " << endl;
			cout << "\n\n \t *******************************************************\n\n" << endl;
			cout << "Press 2 to change account info : " << endl;
			cout << "\n\n \t *******************************************************\n\n" << endl;
			cout << "Press 0 to logout : " << endl;
			
			int loop1 = 1;
			// loop for command input to know which user chose 
			while (loop1 ==1 ) {

				int command;
				cin >> command;
				// if 0 mean logout
				if (command == 0) {
					session = -1;
					loop1 = 0;
				}
				// if 1 mean send message
				else if (command == 1) {


					int loopp = 1;
					while (loopp == 1) {
						int com;
						cout << "press 1 to show all people you can send message to" << endl;
						cout << "Press 2 to send a Word ! " << endl;
						cout << "Press 3 to show emails" << endl;
						cout << "Press 0 to go back" << endl;
						cin >> com;
						// for loop for all available accounts
						if (com == 1) {
							cout << "[id] Name" << endl;
							for (int i = 0; i < counter; i++) {
								cout << '[' << i << ']'<<" " << acc[i].userNameREQ() << endl;
							}
						}
						else if (com == 0) {
							loopp = 0;
						}
				/*      else if (com == 2) {
					      int sendToId = -1;
							cout << "\n enter user id" << endl;
							cin >> sendToId;
							if (sendToId > counter) {
								cout << "Invild id" << endl;
								sendToId = -1;
							}
							else {
								cout << "Write your Word!" << endl;
								string messageTo;
								cin >> messageTo;
								acc[sendToId].Email(0,messageTo );


							}
						}
						else if (com == 3) {
							acc[session].Email(1);
						}*/
						else cout << "Comming soon !" << endl;


					}


				}
				// if 2 mean change info
				else if (command == 2) {
					int loopp = 1;
					// loop to know which user chose when he chose command 2 before to change his user info
					while (loopp == 1) {
						int com;
						cout << "press 1 to change password" << endl;
						cout << "Press 2 to change user name " << endl;
						cin >> com;
						if (com == 1) {
							string p;
							cout << "Enter new password" << endl;
							cin >> p;
							acc[session].ChangePass(p);
							updateDataFiles();
							loopp = 0;
						}
						else if (com == 2) {
							cout << "Enter new username" << endl;
							string n;
							cin >> n;
							//we need to check if the new user name is taken or not 
							if (checkIfUserIsRegisterdAlReady(n)) {
								cout << "** Username is already taken !" << endl;
							}
							else {
								acc[session].ChangeUser(n);
								updateDataFiles();
								loopp = 0;
							}
						}
						else {
							cout << "wrong command" << endl;
						}
					} loop1 = 0;
				}
				else cout << "Wrong command" << endl;
			}
		}

	}
	return 0;
}
