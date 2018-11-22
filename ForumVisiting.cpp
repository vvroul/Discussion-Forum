#include <iostream>
#include <fstream>
//#include "System.h"
#include "FunctionsPrototypes.h"

using namespace std;
//using namespace System;

int main()
{
	ifstream file("number.txt");
	char answer, User = 'W';
	cout << "Welcome to D.I.T Lists!" << endl;
	cout << "Type R to Register\nType L to Login\nType W to Wander." << endl;
	cin >> answer;
	switch (answer)
	{
	case 'L':
	{
		// LOGIN 
		//if (decipher_the_answer(answer)){ //The user typed "yes"
		bool Jen = true;
		string username, password, istherealine, userusername, userpassword;
		cout << "Please,insert your username." << endl;
		cin >> userusername;   //The user inserts their username
		cout << "Please,insert your password." << endl;
		cin >> userpassword;   //The user inserts their password
		string strU = "RU";  //Regular User
		string strM = "MD";  //Moderator
		string strA = "AD";  //Administrator
		size_t found, foundu, foundp;
		ifstream myfile("testing.txt");
		if (myfile.is_open()){
			cout << "File specified opened successfully." << endl;
			while (getline(myfile, istherealine)){
				myfile >> username;
				myfile >> password;
				foundu = username.find(userusername);
				foundp = password.find(userpassword);
				if (foundu != string::npos&&foundp != string::npos){
					cout << "Welcome " << username << endl;
					//USER IDENTIFY
					found = username.find(strA);
					if (found != string::npos){   //We're looking at an Administrator
						cout << "You are an Administrator" << endl;
						User = 'A';
					}
					found = username.find(strM);
					if (found != string::npos){   //We're looking at a Moderator
						cout << "You are a Moderator" << endl;
						User = 'M';
					}
					found = username.find(strU);
					if (found != string::npos){  //We're looking at a Regular User
						cout << "You are a Regular User" << endl;
						User = 'R';
					}
					Jen = false;
					break;
				}
			}
			myfile.close();
			cout << "Everything went smoothly." << endl;

			cin.get();
			if (Jen){  //The user is not registered in the forum
				cout << "Sorry,you are not registered in the forum.You may proceed as a visitor though." << endl;
			}
		}
		else{
			cout << "Unable to open the file specified.Sorry for any inconvenience." << endl;
		}
		break;
	}
	case 'R':
	{
		string username, password;
		cout << "Please insert a Username " << endl;
		cin >> username;
		cout << "Please insert a Password " << endl;
		cin >> password;
		Registration(username, password, User);
		//cin.get();
		break;
	}
	default:
	{
		//END OF LOGIN
		//else{  //The user typed "no"
		cout << "You may proceed to the forum as a visitor." << endl;
		break;
	}
	}
	list<Forum*> forums;
	cout << "Going to create the forum... " << endl;
	UniverseConstruction(forums);
	//THE USER'S DESKTOP
	switch (User)
	{
		int forumtovisit;//The forum that the user chooses to visit
	default://Cases 'W','M' and 'R'
	{
		bool leave = false;
		do
		{
			char selection;
			cout << "If you want to visit a forum,type V" << endl;
			cout << "If you want to exit the system,type X" << endl;
			cin >> selection;
			if (selection == 'V'){
				int k = 1;
				cout << "These are the forums available" << endl;
				list<Forum*>::iterator i;
				int howmany = 0;//Current number of forums
				for (i = forums.begin(); i != forums.end(); ++i){
					(*i)->print();            //PRINTING THE TITLES OF THE FORUMS
					++howmany;
				}
				cout << "Please,type the number of the forum you want to visit" << endl;
				cin >> forumtovisit;
				i = forums.begin();
				for (k = 0; k < forumtovisit; ++k){
					++i;
				}
				--i;//Reached the forum
				ifstream input("number.txt");
				int numofinterest, indnum;
				string whatever, threads, subforums;
				input >> indnum;//Scanning the first three numbers,that we don't need
				input >> indnum;
				input >> indnum;
				input >> numofinterest;
				while (numofinterest != forumtovisit){//Searching for the appropriate files to pass to the visit() function
					input >> threads;
					input >> whatever;
					input >> indnum;
					input >> subforums;
					input >> numofinterest;
				}
				input >> threads;
				input >> whatever;
				input >> indnum;
				input >> subforums;
				(*i)->visit(User, threads, subforums, "number.txt", howmany);//And now visiting it
			}
			else if (selection == 'X'){
				leave = true;
			}
		} while (!leave);
		break;
	}
	case 'A'://Administrator
	{
		bool leave = false;
		do
		{
			char selection;
			cout << "If you want to create a new forum , type L " << endl;
			cout << "If you want to visit a forum , type V " << endl;
			cout << "If you want to see the catalog of the users , type C " << endl;
			cout << "If you want to change a user's category , type H " << endl;
			cout << "If you want to change a user's name , type U " << endl;
			cout << "If you want to change a user's password , type P " << endl;
			cout << "If you want to delete a user , type D " << endl;
			cout << "If you want to exit the system , type X " << endl;
			cin >> selection;
			if (selection == 'L')		//Create a new forum
			{
				string thetitle, threadsfile, subforumsfile;
				cout << "Insert a title for the new forum" << endl;
				cin >> thetitle;
				cout << "Insert a name for the file about this forum's threads" << endl;
				cin >> threadsfile;
				cout << "Insert a name for the file about this forum's subforums" << endl;
				cin >> subforumsfile;
				int howmany = 0;
				list<Forum*>::iterator i;
				for (i = forums.begin(); i != forums.end(); ++i){
					++howmany;
				}
				++howmany;
				Forum* newbie = new  Forum(thetitle, howmany);
				ofstream write("number.txt", ios::app);
				write << "\n";
				write << howmany << endl;
				write << threadsfile << endl;
				write << thetitle << endl;
				write << 0 << endl;//There are no subforums yet
				write << subforumsfile << endl;
			}
			else if (selection == 'V')	//Visit a forum
			{
				cout << "These are the forums available" << endl;
				list<Forum*>::iterator i;
				int current = 0;
				for (i = forums.begin(); i != forums.end(); ++i){
					(*i)->print();            //PRINTING THE TITLES OF THE FORUMS
					++current;
				}
				int forumtovisit;
				int k = 0;
				cout << "Please,type the number of the forum you want to visit" << endl;
				cin >> forumtovisit;
				i = forums.begin();
				for (k = 0; k < forumtovisit; ++k){
					++i;
				}//Reached the forum
				--i;
				ifstream input("number.txt");
				int numofinterest, indnum;
				string whatever, threads, subforums;
				input >> indnum;//Scanning the first three numbers,that we don't need
				input >> indnum;
				input >> indnum;
				input >> numofinterest;
				while (numofinterest != forumtovisit){//Searching for the appropriate files to pass to the visit() function
					input >> threads;
					input >> whatever;
					input >> indnum;
					input >> subforums;
					input >> numofinterest;
				}
				input >> threads;
				input >> whatever;
				input >> indnum;
				input >> subforums;
				(*i)->visit(User, threads, subforums, "number.txt", current);//And now visiting it
				//END OF NEW CODE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if (selection == 'C')	//See users catalog
			{
				UserCatalog();
			}
			else if (selection == 'H')	//Change user's category
			{
				ChangeUserCategory();
			}
			else if (selection == 'U')	//Change username
			{
				ChangeUsername();
			}
			else if (selection == 'P')	//Change password
			{
				ChangePassword();
			}
			else if (selection == 'D')	//Delete user
			{
				DeleteUser();
			}
			else if (selection == 'X')	//Exit
			{
				leave = true;
			}
			else
			{
				cout << "Wrong selection , exiting the system " << endl;
			}
		} while (!leave);
		break;
	}
	}
	cin.get();
	cin.get();
	//return 0;
	cout << "Going to DESTROY our little and poor forum.... " << endl;
	UniverseDestruction(forums);
	cout << "Well..." << endl;
	cin.get();
	cin.get();
	return 0;
}