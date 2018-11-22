#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include "FunctionsPrototypes.h"
#include "System.h"
#include "Post.h"

using namespace std;
using namespace System;



//HANDLERS
void Forum::visit(char& User , string fileone , string filetwo,string filethree,int& totalforums){	//	fileone(threads.t)	filetwo(helper.txt) filethree(number.txt) totalforums(current number of forums)
	cout << "Forum " << ID << ":" << title << endl;
	cout << "Threadfilename : " << fileone << endl;
	cout << "Subforumfilename : " << filetwo << endl;
	switch (User){
		int subforumtovisit, threadtovisit;
		char selection;
	case 'A':{//The Administrator's case
		bool leave = false;
		do
		{
			cout << "If you want to visit a subforum,type F" << endl;
			cout << "If you want to create a new subforum,type N" << endl;
			cout << "If you want to change a subforum's title,type E" << endl;
			cout << "If you want to delete a subforum,type D" << endl;
			cout << "If you want to move a subforum,type M" << endl;
			cout << "If you want to visit a thread,type T" << endl;
			cout << "If you want to create a new thread,type W" << endl;
			cout << "If you want to change a thread's title,type J" << endl;
			cout << "If you want to delete a thread,type R" << endl;
			cout << "If you want to move a thread,type B" << endl;
			cout << "If you want to sticky/unsticky a thread,type Y" << endl;
			cout << "If you want to lock/unlock a thread,type K" << endl;
			cout << "If you want to leave,type L" << endl;
			cin >> selection;
			if (selection == 'F'){//Visit a subforum
				cout << "Here are the subforums:" << endl;
				list<Subforum*>::iterator i;
				int number = 1;
				for (i = subForums.begin(); i != subForums.end(); ++i){
					cout << "This is subforum number " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the subforum you want to visit" << endl;
				cin >> subforumtovisit;
				i = subForums.begin();
				for (number = 0; number < subforumtovisit; ++number){
					++i;
				}//Reached the subforum
				--i;
				ifstream input(filetwo.c_str());
				int numofinterest, indnum;
				string whatever, threads, title;
				input >> indnum;//Scanning the first three numbers,that we don't need
				input >> numofinterest;
				while (numofinterest != subforumtovisit){//Searching for the appropriate files to pass to the visit() function
					input >> title;
					input >> threads;
					input >> numofinterest;
				}
				input >> title;
				input >> threads;
				(*i)->visit(User, threads, filetwo, "number.txt");//And now visiting it
			}
			else if (selection == 'N'){//Create a new subforum
				string thetitle, threadsfile;
				cout << "Insert the title of the new subforum" << endl;
				cin >> thetitle;
				cout << "Insert a filename for the file about this subforum's threads." << endl;
				cin >> threadsfile;
				Subforum* newbie = new Subforum(thetitle, ID);
				subForums.push_back(newbie);
				int howmany = 0;//Number of subforums
				list<Subforum*>::iterator i;
				for (i = subForums.begin(); i != subForums.end(); ++i){
					++howmany;
				}
				ofstream write(filetwo.c_str(), ios::app);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				write << endl << endl << howmany << endl << thetitle << endl << threadsfile;
			}
			else if (selection == 'E'){
				cout << "Here are the subforums:" << endl;
				list<Subforum*>::iterator i;
				int number = 1;
				for (i = subForums.begin(); i != subForums.end(); ++i){
					cout << "This is subforum number " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the subforum whose title you want to change" << endl;
				cin >> subforumtovisit;
				i = subForums.begin();
				for (number = 0; number < subforumtovisit; ++number){
					++i;
				}//Reached the subforum
				--i;
				const char* newfiletwo = filetwo.c_str();//We must convert the name of the file,because of the functions remove() and rename()
				(*i)->ChangemyTitle(newfiletwo);
			}
			else if (selection == 'D'){//Delete a subforum
				cout << "Here are the subforums:" << endl;
				list<Subforum*>::iterator i;
				int number = 1;
				for (i = subForums.begin(); i != subForums.end(); ++i){
					cout << "This is subforum number " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the subforum you want to delete" << endl;
				cin >> subforumtovisit;
				i = subForums.begin();
				for (number = 0; number < subforumtovisit; ++number){
					++i;
				}//Reached the subforum
				--i;
				fix_the_files_subforums(filetwo, subforumtovisit);
				(*i)->deleteMe();//Deleting its contents
				subForums.remove(*i);//Removing it from the list of subforums
			}
			else if (selection == 'M'){
				cout << "Here are the subforums:" << endl;
				list<Subforum*>::iterator i;
				int number = 1;
				for (i = subForums.begin(); i != subForums.end(); ++i){
					cout << "This is subforum number " << number << endl;
					(*i)->print();
					++number;
				}
				int subforumtomove, subsalready, forumserial;
				cout << "Please,type the number of the subforum you want to move" << endl;
				cin >> subforumtomove;
				cout << "Please,insert the ID of the forum in which you want to move the subforum" << endl;
				cin >> forumserial;
				cout << "Please,type the number of the subforums conatined already in the forum of destination" << endl;
				cin >> subsalready;
				MoveSubforum(subforumtomove, subsalready, forumserial, ID);
			}
			if (selection == 'W'){//Creation of the new thread
				string thetile, postingname;
				cout << "PLease,insert the title of the new thread" << endl;
				cin >> thetile;
				cout << "Please,insert a name for the file of this thread's posts" << endl;
				cin >> postingname;
				Thread* newbie = new Thread(thetile, postingname, ID);
				threads.push_back(newbie);
				int howmany = 0;
				list<Thread*>::iterator i;
				for (i = threads.begin(); i != threads.end(); ++i){
					++howmany;
				}
				ofstream write(fileone.c_str(), ios::app);
				write << endl << endl << howmany << endl << thetile << endl << postingname;
			}
			else if (selection == 'F'){//Visit a subforum
				cout << "Here are the subforums:" << endl;
				list<Subforum*>::iterator i;
				int number = 1;
				for (i = subForums.begin(); i != subForums.end(); ++i){
					cout << "This is subforum number " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the subforum you want to visit" << endl;
				cin >> subforumtovisit;
				i = subForums.begin();
				for (number = 0; number < subforumtovisit; ++number){
					++i;
				}//Reached the subforum
				ifstream input("helper.txt");
				int numofinterest, indnum;
				string whatever, threads, title;
				input >> indnum;//Scanning the first three numbers,that we don't need
				input >> numofinterest;
				while (numofinterest != subforumtovisit){//Searching for the appropriate files to pass to the visit() function
					input >> title;
					input >> threads;
					input >> numofinterest;
				}
				input >> title;
				input >> threads;
				(*i)->visit(User, threads, filetwo, "number.txt");//And now visiting it
			}
			else if (selection == 'T'){//Visit a thread
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread you want to visit" << endl;
				cin >> threadtovisit;
				i = threads.begin();
				for (number = 0; number < threadtovisit; ++number){
					++i;
				}//Reached it
				--i;
				(*i)->visit(User);//And now visiting it
			}
			else if (selection == 'R'){//Delete a thread
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread you want to delete" << endl;
				cin >> threadtovisit;
				i = threads.begin();
				for (number = 0; number < threadtovisit; ++number){
					++i;
				}//Reached it
				--i;
				(*i)->deletemyposts();//Delete the posts of the thread
				string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				threadtovisit = TheNumber(thetitle, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				fix_the_files_threads_delete(fileone, threadtovisit);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				threads.remove(*i);//Deleting it
			}
			else if (selection == 'B'){//Move a thread
				char answer;
				cout << "If you want to move a thread in a subforum,in another forum,type D" << endl;
				cout << "If you want to move a thread in another forum,but not in a subforum,type F" << endl;
				cin >> answer;
				if (answer == 'D'){
					cout << "Here are the threads:" << endl;
					list<Thread*>::iterator i;
					int number = 1;
					for (i = threads.begin(); i != threads.end(); ++i){
						cout << "This is thread number: " << number << endl;
						(*i)->print();
						++number;
					}
					int totalthreads, threadser, forA, forB, subB;
					cout << "Please,insert the number of the thread you want to move" << endl;
					cin >> threadser;
					i = threads.begin();
					for (number = 0; number < threadser; ++number){
						++i;
					}//Reached it
					--i;//!!!!!!!!
					string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
					threadser = TheNumber(thetitle, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
					cout << "Please,insert the number of the forum you're in" << endl;
					cin >> forA;
					cout << "Please,insert the number of the forum in which the thread will be moved" << endl;
					cin >> forB;
					cout << "Please,insert the number of the subforum in which the thread will be moved" << endl;
					cin >> subB;
					cout << "Please,insert the total number of the threads in the subforum of destination" << endl;
					cin >> totalthreads;
					MoveThreadFFTS(threadser, totalthreads, forA, forB, subB);
				}
				else if (answer == 'F'){
					cout << "Here are the threads:" << endl;
					list<Thread*>::iterator i;
					int number = 1;
					for (i = threads.begin(); i != threads.end(); ++i){
						cout << "This is thread number: " << number << endl;
						(*i)->print();
						++number;
					}
					int threadser, threadtotal, forB;
					cout << "Please,insert the number of the thread you want to move" << endl;
					cin >> threadser;
					i = threads.begin();
					for (number = 0; number < threadser; ++number){
						++i;
					}//Reached it
					--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadser = TheNumber(thetitle, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					cout << "Please,insert the number of the forum of destination" << endl;
					cin >> forB;
					cout << "Please,insert the total number of threads in the forum of destination" << endl;
					cin >> threadtotal;
					MoveThreadToForum(threadser, threadtotal, ID, forB);
				}
			}
			else if (selection == 'J'){//Change a thread's title
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread whose title you want to change" << endl;
				cin >> threadtovisit;
				i = threads.begin();
				for (number = 0; number < threadtovisit; ++number){
					++i;
				}//Reached it
				--i;
				const char* newfileone = fileone.c_str();
				string newtitle;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				cout << "Please,insert the new title" << endl;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				cin >> newtitle;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				(*i)->ChangemyTitle(newfileone, newtitle);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				(*i)->ChangemyTitle(newtitle);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			}
			else if (selection == 'Y'){//Sticky/Unsticky thread
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread tha you want to stick/unstick" << endl;
				cin >> threadtovisit;
				i = threads.begin();
				for (number = 0; number < threadtovisit; ++number){
					++i;
				}//Reached it
				--i;
				char answer;
				cout << "Type S if you want to stick the thread,otherwise type U" << endl;
				cin >> answer;
				if (answer == 'S'){//The user wants to stick the thread
					if (!((*i)->ISsticky())){//It is not sticky
						(*i)->stick_it();
						string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						threadtovisit = TheNumber(title, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						fix_the_files_threads_sticky(fileone, threadtovisit, 'S');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
						Thread* newthread = new Thread();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						(*newthread) = (*(*i));//Copying the item//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						threads.remove(*i);//Removing the item
						threads.push_front(newthread);//Pushing the copy of the item at the front of the list
						cout << "This thread is now a sticky one" << endl;
					}
					else{//It is sticky
						cout << "This thread is already a sticky one" << endl;
					}
				}
				else if (answer == 'U'){//The user wants to unstick the thread
					if ((*i)->ISsticky()){//It is sticky
						(*i)->unstick_it();
						string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						threadtovisit = TheNumber(title, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						fix_the_files_threads_sticky(fileone, threadtovisit, 'U');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						cout << "This thread is no longer sticky" << endl;
					}
					else{//It is not sticky
						cout << "This thread is not sticky already" << endl;
					}
				}
			}
			else if (selection == 'K'){//Lock/Unlock thread
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread tha you want to lock/lock" << endl;
				cin >> threadtovisit;
				i = threads.begin();
				for (number = 0; number < threadtovisit; ++number){
					++i;
				}//Reached it
				--i;
				char answer;
				cout << "Type L if you want to lock the thread,otherwise type U" << endl;
				cin >> answer;
				if (answer == 'L'){//The user wants to lock the thread
					if (!((*i)->ISlocked())){//It is  unlocked
						(*i)->lock_it();
						string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						threadtovisit = TheNumber(title, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						fix_the_files_threads_locked(fileone, threadtovisit, 'L');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						cout << "Thread locked!" << endl;
					}
					else{//It is locked
						cout << "This thread is already locked" << endl;
					}
				}
				else if (answer == 'U'){//The user wants to unlock the thread
					if ((*i)->ISlocked()){//It is locked
						(*i)->unlock_it();
						string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						threadtovisit = TheNumber(title, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						fix_the_files_threads_locked(fileone, threadtovisit, 'U');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						cout << "Thread unlocked!" << endl;
					}
					else{//It is unlocked
						cout << "This thread is unlocked already" << endl;
					}
				}
			}
			else if (selection == 'L'){
				leave = true;
			}
		} while (!leave);
		break;
	}//End of case 'A'
	case 'M':{//Moderator's case
		bool leave = false;
		do//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{ 
		cout << "If you want to create a new thread,type N" << endl;
		cout << "If you want to delete a thread,type D" << endl;
		cout << "If you want to move a thread,type M" << endl;
		cout << "If you want to change a thread's title,type E" << endl;
		cout << "If you want to sticky/unsticky a thread,type Y" << endl;
		cout << "If you want to lock/unlock a thread,type K" << endl;
		cout << "If you want to visit a subforum,type F" << endl;
		cout << "If you want to visit a thread,type T" << endl;
		cout << "If you want to leave,type L" << endl;
		cin >> selection;
		if (selection == 'N'){//Creation of the new thread
			string thetile, postingname;
			cout << "PLease,insert the title of the new thread" << endl;
			cin >> thetile;
			cout << "Please,insert a name for the file of this thread's posts" << endl;
			cin >> postingname;
			Thread* newbie = new Thread(thetile, postingname, ID);
			threads.push_back(newbie);
			int howmany = 0;
			list<Thread*>::iterator i;
			for (i = threads.begin(); i != threads.end(); ++i){
				++howmany;
			}
			ofstream write(fileone.c_str(), ios::app);
			write << endl << endl << howmany << endl << thetile << endl << postingname;
		}
		else if (selection == 'F'){//Visit a subforum
			cout << "Here are the subforums:" << endl;
			list<Subforum*>::iterator i;
			int number = 1;
			for (i = subForums.begin(); i != subForums.end(); ++i){
				cout << "This is subforum number " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the subforum you want to visit" << endl;
			cin >> subforumtovisit;
			i = subForums.begin();
			for (number = 0; number < subforumtovisit; ++number){
				++i;
			}//Reached the subforum
			--i;
			ifstream input(filetwo.c_str());
			int numofinterest, indnum;
			string whatever, threads, title;
			input >> indnum;//Scanning the first three numbers,that we don't need
			input >> numofinterest;
			while (numofinterest != subforumtovisit){//Searching for the appropriate files to pass to the visit() function
				input >> title;
				input >> threads;
				input >> numofinterest;
			}
			input >> title;
			input >> threads;
			(*i)->visit(User, threads, filetwo, "number.txt");//And now visiting it
		}
		else if (selection == 'T'){//Visit a thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread you want to visit" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;
			(*i)->visit(User);//And now visiting it
		}
		else if (selection == 'D'){//Delete a thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread you want to delete" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;
			(*i)->deletemyposts();
			string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			threadtovisit = TheNumber(thetitle, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
			fix_the_files_threads_delete(fileone, threadtovisit);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			threads.remove(*i);//Deleting it
		}
		else if (selection == 'M'){//Move a thread
			char answer;
			cout << "If you want to move a thread in a subforum,in another forum,type D" << endl;
			cout << "If you want to move a thread in another forum,but not in a subforum,type F" << endl;
			cin >> answer;
			if (answer == 'D'){
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				int totalthreads, threadser, forA, forB, subB;
				cout << "Please,insert the number of the thread you want to move" << endl;
				cin >> threadser;
				i = threads.begin();
				for (number = 0; number < threadser; ++number){
					++i;
				}//Reached it
				--i;//!!!!!!!!
				string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				threadser = TheNumber(thetitle, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				cout << "Please,insert the number of the forum you're in" << endl;
				cin >> forA;
				cout << "Please,insert the number of the forum in which the thread will be moved" << endl;
				cin >> forB;
				cout << "Please,insert the number of the subforum in which the thread will be moved" << endl;
				cin >> subB;
				cout << "Please,insert the total number of the threads in the subforum of destination" << endl;
				cin >> totalthreads;
				MoveThreadFFTS(threadser, totalthreads, forA, forB, subB);
			}
			else if (answer == 'F'){
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				int threadser, threadtotal, forB;
				cout << "Please,insert the number of the thread you want to move" << endl;
				cin >> threadser;
				i = threads.begin();
				for (number = 0; number < threadser; ++number){
					++i;
				}//Reached it
				--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				threadser = TheNumber(thetitle, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				cout << "Please,insert the number of the forum of destination" << endl;
				cin >> forB;
				cout << "Please,insert the total number of threads in the forum of destination" << endl;
				cin >> threadtotal;
				MoveThreadToForum(threadser, threadtotal, ID, forB);
			}
		}
		else if (selection == 'E'){//Change a thread's title
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread whose title you want to change" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;
			const char* newfileone = fileone.c_str();
			(*i)->ChangemyTitle(newfileone);
		}
		else if (selection == 'Y'){//Sticky/Unsticky thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread that you want to stick/unstick" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;
			char answer;
			cout << "Type S if you want to stick the thread,otherwise type U" << endl;
			cin >> answer;
			if (answer == 'S'){//The user wants to stick the thread
				if (!((*i)->ISsticky())){//It is not sticky
					(*i)->stick_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					fix_the_files_threads_sticky(fileone, threadtovisit, 'S');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					Thread* newthread = new Thread;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					(*newthread) = (*(*i));//Copying the item
					threads.remove(*i);//Removing the item
					threads.push_front(newthread);//Pushing the copy of the item at the front of the list
					cout << "This thread is now a sticky one" << endl;
				}
				else{//It is sticky
					cout << "This thread is already a sticky one" << endl;
				}
			}
			else if (answer == 'U'){//The user wants to unstick the thread
				if ((*i)->ISsticky()){//It is sticky
					(*i)->unstick_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					fix_the_files_threads_sticky(fileone, threadtovisit, 'U');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					cout << "This thread is no longer sticky" << endl;
				}
				else{//It is not sticky
					cout << "This thread is not sticky already" << endl;
				}
			}
		}
		else if (selection == 'K'){//Lock/Unlock thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread tha you want to lock/lock" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;
			char answer;
			cout << "Type L if you want to lock the thread,otherwise type U" << endl;
			cin >> answer;
			if (answer == 'L'){//The user wants to lock the thread
				if (!((*i)->ISlocked())){//It is  unlocked
					(*i)->lock_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					fix_the_files_threads_locked(fileone, threadtovisit, 'L');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
					cout << "Thread locked!" << endl;
				}
				else{//It is locked
					cout << "This thread is already locked" << endl;
				}
			}
			else if (answer == 'U'){//The user wants to unlock the thread
				if ((*i)->ISlocked()){//It is locked
					(*i)->unlock_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, fileone);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					fix_the_files_threads_locked(fileone, threadtovisit, 'U');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
					cout << "Thread unlocked!" << endl;
				}
				else{//It is unlocked
					cout << "This thread is unlocked already" << endl;
				}
			}
		}
		else if (selection == 'L'){
			leave = true;
		}
	} while (!leave);
	break;
	}//End of case 'M'
	default:{//Cases 'R','W' 
		bool leave = false;
		do
		{
			cout << "If you want to visit a thread,type T" << endl;
			cout << "If you want to visit a subforum,type F" << endl;
			cout << "If you want to leave,type L" << endl;
			cin >> selection;
			if (selection == 'F'){
				cout << "Here are the subforums:" << endl;
				list<Subforum*>::iterator i;
				int number = 1;
				for (i = subForums.begin(); i != subForums.end(); ++i){
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the subforum you want to visit" << endl;
				cin >> subforumtovisit;
				i = subForums.begin();
				for (number = 0; number < subforumtovisit; ++number){
					++i;
				}//Reached the subforum
				--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				ifstream input(filetwo.c_str());
				int numofinterest, indnum;
				string whatever, threads, title;
				input >> indnum;//Scanning the first three numbers,that we don't need
				input >> numofinterest;
				while (numofinterest != subforumtovisit){//Searching for the appropriate files to pass to the visit() function
					input >> title;
					input >> threads;
					input >> numofinterest;
				}
				input >> title;
				input >> threads;
				(*i)->visit(User, threads, filetwo, "number.txt");//And now visiting it
			}
			else if (selection == 'T'){//Visit a thread
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread you want to visit" << endl;
				cin >> threadtovisit;
				i = threads.begin();
				for (number = 0; number < threadtovisit; ++number){
					++i;
				}//Reached it
				--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				(*i)->visit(User);//And now visiting it
			}
			else if (selection == 'L'){
				leave = true;
			}
		} while (!leave);
		break;
	}//End of default case
	}//End of case-switch
}



void Subforum::visit(char& User , string threadfile , string subforumfile , string forumfile){
	cout << "Subforum" << ID << ":" << title << endl;
	switch (User){
		int threadtovisit;
		char selection;
	case 'A':{//Administrator's case
		bool leave = false;
		do
		{//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
		cout << "If you want to create a new thread,type N" << endl;
		cout << "If you want to delete a thread,type D" << endl;
		cout << "If you want to move a thread,type M" << endl;
		cout << "If you want to change a thread's title,type E" << endl;
		cout << "If you want to sticky/unsticky a thread,type Y" << endl;
		cout << "If you want to lock/unlock a thread,type K" << endl;
		cout << "If you want to visit a thread,type T" << endl;
		cin >> selection;
		if (selection == 'N'){//Creation of the new thread
			string thetile, postingname;
			cout << "PLease,insert the title of the new thread" << endl;
			cin >> thetile;
			cout << "Please,insert a name for the file of this thread's posts" << endl;
			cin >> postingname;
			Thread* newbie = new Thread(thetile, postingname, ID);
			threads.push_back(newbie);
			int howmany = 0;
			list<Thread*>::iterator i;
			for (i = threads.begin(); i != threads.end(); ++i){
				++howmany;
			}
			ofstream write(threadfile.c_str(), ios::app);
			write << endl << endl << howmany << endl << thetile << endl << postingname;
		}
		else if (selection == 'T'){//Visit a thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread you want to visit" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			(*i)->visit(User);//And now visiting it
		}
		else if (selection == 'D'){//Delete a thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread you want to delete" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			(*i)->deletemyposts();
			string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
			threadtovisit = TheNumber(thetitle, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
			fix_the_files_threads_delete(threadfile, threadtovisit);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
			threads.remove(*i);//Deleting it
		}
		else if (selection == 'M'){//Move a thread
			char answer;
			cout << "If you want to move a thread in another subforum,in this forum,type S" << endl;
			cout << "If you want to move a thread in another subforum,in a different forum,type D" << endl;
			cout << "If you want to move a thread in another forum,but not in a subforum,type F" << endl;
			cin >> answer;
			if (answer == 'S'){
				int threadser, threadtotal, subA, subB;
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread you want to move" << endl;
				cin >> threadser;
				i = threads.begin();
				for (number = 0; number < threadser; ++number){
					++i;
				}//Reached it
				--i;//!!!!!!!!
				string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				threadser = TheNumber(thetitle, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				cout << "Please,type the number of the subforum you're in" << endl;
				cin >> subA;
				cout << "Please,type the number of the subforum in which you want to move this thread" << endl;
				cin >> subB;
				cout << "Please,insert the number of threads that are already contained in the subforum of destination" << endl;
				cin >> threadtotal;
				MoveThreadToSubforum(subforumfile, threadser, threadtotal, subA, subB);
			}
			else if (answer == 'D'){
				int threadser, threadtotal, subA, subB, forA, forB;
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread you want to move" << endl;
				cin >> threadser;
				i = threads.begin();
				for (number = 0; number < threadser; ++number){
					++i;
				}//Reached it
				--i;//!!!!!!!!
				string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				threadser = TheNumber(thetitle, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				cout << "Please,insert the number of threads that are already contained in the subforum of destination" << endl;
				cin >> threadtotal;
				cout << "Please,type the number of the subforum you're in" << endl;
				cin >> subA;
				cout << "Please,type the number of the subforum in which you want to move this thread" << endl;
				cin >> subB;
				cout << "Please,type the ID of the forum you're in" << endl;
				cin >> forA;
				cout << "Please,type the ID of the forum of destination" << endl;
				cin >> forB;
				MoveThreadFSTS(threadser, threadtotal, forA, forB, subA, subB);
			}
			else if (answer == 'F'){
				int threadser, threadtotal, subA, forA, forB;
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread you want to move" << endl;
				cin >> threadser;
				i = threads.begin();
				for (number = 0; number < threadser; ++number){
					++i;
				}//Reached it
				--i;//!!!!!!!!
				string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				threadser = TheNumber(thetitle, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				cout << "Please,type the number of the subforum you're in" << endl;
				cin >> subA;
				cout << "Please,type the ID of the forum you're in" << endl;
				cin >> forA;
				cout << "Please,type the ID of the forum of destination" << endl;
				cin >> forB;
				cout << "Please,insert the number of threads that are already contained in the forum of destination" << endl;
				cin >> threadtotal;
				MoveThreadFSTF(threadser, threadtotal, forA, forB, subA);
			}
		}
		else if (selection == 'E'){//Change a thread's title
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread whose title you want to change" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
			const char* newthreadfile = threadfile.c_str();
			(*i)->ChangemyTitle(newthreadfile);
		}
		else if (selection == 'Y'){//Sticky/Unsticky thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread that you want to stick/unstick" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			char answer;
			cout << "Type S if you want to stick the thread,otherwise type U" << endl;
			cin >> answer;
			if (answer == 'S'){//The user wants to stick the thread
				if (!((*i)->ISsticky())){//It is not sticky
					(*i)->stick_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
					fix_the_files_threads_sticky(threadfile, threadtovisit, 'S');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					Thread* newthread = new Thread();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					(*newthread) = (*(*i));//Copying the item
					threads.remove(*i);//Removing the item
					threads.push_front(newthread);//Pushing the copy of the item at the front of the list
					cout << "This thread is now a sticky one" << endl;
				}
				else{//It is sticky
					cout << "This thread is already a sticky one" << endl;
				}
			}
			else if (answer == 'U'){//The user wants to unstick the thread
				if ((*i)->ISsticky()){//It is sticky
					(*i)->unstick_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
					threadtovisit = TheNumber(title, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					fix_the_files_threads_sticky(threadfile, threadtovisit, 'U');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					cout << "This thread is no longer sticky" << endl;
				}
				else{//It is not sticky
					cout << "This thread is not sticky already" << endl;
				}
			}
		}
		else if (selection == 'K'){//Lock/Unlock thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread tha you want to lock/lock" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
			char answer;
			cout << "Type L if you want to lock the thread,otherwise type U" << endl;
			cin >> answer;
			if (answer == 'L'){//The user wants to lock the thread
				if (!((*i)->ISlocked())){//It is  unlocked
					(*i)->lock_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
					fix_the_files_threads_locked(threadfile, threadtovisit, 'L');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
					cout << "Thread locked!" << endl;
				}
				else{//It is locked
					cout << "This thread is already locked" << endl;
				}
			}
			else if (answer == 'U'){//The user wants to unlock the thread
				if ((*i)->ISlocked()){//It is locked
					(*i)->unlock_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
					fix_the_files_threads_locked(threadfile, threadtovisit, 'U');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
					cout << "Thread unlocked!" << endl;
				}
				else{//It is unlocked
					cout << "This thread is unlocked already" << endl;
				}
			}
		}
		else if (selection == 'L'){
			leave = true;
		}
	} while (!leave);
	break;
	}//End of case 'A'
	case 'M':{//Moderator's case
		bool leave = false;
		do
		{//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
		cout << "If you want to create a new thread,type N" << endl;
		cout << "If you want to delete a thread,type D" << endl;
		cout << "If you want to move a thread,type M" << endl;
		cout << "If you want to change a thread's title,type E" << endl;
		cout << "If you want to sticky/unsticky a thread,type Y" << endl;
		cout << "If you want to lock/unlock a thread,type K" << endl;
		cout << "If you want to visit a thread,type T" << endl;
		cin >> selection;
		if (selection == 'N'){//Creation of the new thread
			string thetile, postingname;
			cout << "PLease,insert the title of the new thread" << endl;
			cin >> thetile;
			cout << "Please,insert a name for the file of this thread's posts" << endl;
			cin >> postingname;
			Thread* newbie = new Thread(thetile, postingname, ID);
			threads.push_back(newbie);
			int howmany = 0;
			list<Thread*>::iterator i;
			for (i = threads.begin(); i != threads.end(); ++i){
				++howmany;
			}
			ofstream write(threadfile.c_str(), ios::app);
			write << endl << endl << howmany << endl << thetile << endl << postingname;

		}
		else if (selection == 'T'){//Visit a thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread you want to visit" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			(*i)->visit(User);//And now visiting it
		}
		else if (selection == 'D'){//Delete a thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread you want to delete" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			(*i)->deletemyposts();
			string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			threadtovisit = TheNumber(thetitle, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
			fix_the_files_threads_delete(threadfile, threadtovisit);
			threads.remove(*i);//Deleting it
		}
		else if (selection == 'M'){//Move a thread
			char answer;
			cout << "If you want to move a thread in another subforum,in this forum,type S" << endl;
			cout << "If you want to move a thread in another subforum,in a different forum,type D" << endl;
			cout << "If you want to move a thread in another forum,but not in a subforum,type F" << endl;
			cin >> answer;
			if (answer == 'S'){
				int threadser, threadtotal, subA, subB;
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread you want to move" << endl;
				cin >> threadser;
				i = threads.begin();
				for (number = 0; number < threadser; ++number){
					++i;
				}//Reached it
				--i;//!!!!!!!!
				string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				threadser = TheNumber(thetitle, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				cout << "Please,type the number of the subforum you're in" << endl;
				cin >> subA;
				cout << "Please,type the number of the subforum in which you want to move this thread" << endl;
				cin >> subB;
				cout << "Please,insert the number of threads that are already contained in the subforum of destination" << endl;
				cin >> threadtotal;
				MoveThreadToSubforum(subforumfile, threadser, threadtotal, subA, subB);
			}
			else if (answer == 'D'){
				int threadser, threadtotal, subA, subB, forA, forB;
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread you want to move" << endl;
				cin >> threadser;
				i = threads.begin();
				for (number = 0; number < threadser; ++number){
					++i;
				}//Reached it
				--i;//!!!!!!!!
				string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				threadser = TheNumber(thetitle, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				cout << "Please,insert the number of threads that are already contained in the subforum of destination" << endl;
				cin >> threadtotal;
				cout << "Please,type the number of the subforum you're in" << endl;
				cin >> subA;
				cout << "Please,type the number of the subforum in which you want to move this thread" << endl;
				cin >> subB;
				cout << "Please,type the ID of the forum you're in" << endl;
				cin >> forA;
				cout << "Please,type the ID of the forum of destination" << endl;
				cin >> forB;
				MoveThreadFSTS(threadser, threadtotal, forA, forB, subA, subB);
			}
			else if (answer == 'F'){
				int threadser, threadtotal, subA, forA, forB;
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread you want to move" << endl;
				cin >> threadser;
				i = threads.begin();
				for (number = 0; number < threadser; ++number){
					++i;
				}//Reached it
				--i;//!!!!!!!!
				string thetitle = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				threadser = TheNumber(thetitle, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
				cout << "Please,type the number of the subforum you're in" << endl;
				cin >> subA;
				cout << "Please,type the ID of the forum you're in" << endl;
				cin >> forA;
				cout << "Please,type the ID of the forum of destination" << endl;
				cin >> forB;
				cout << "Please,insert the number of threads that are already contained in the forum of destination" << endl;
				cin >> threadtotal;
				MoveThreadFSTF(threadser, threadtotal, forA, forB, subA);
			}
		}
		else if (selection == 'E'){//Change a thread's title
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread whose title you want to change" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			const char* newthreadfile = threadfile.c_str();
			(*i)->ChangemyTitle(newthreadfile);
		}
		else if (selection == 'Y'){//Sticky/Unsticky thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread tha you want to stick/unstick" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			char answer;
			cout << "Type S if you want to stick the thread,otherwise type U" << endl;
			cin >> answer;
			if (answer == 'S'){//The user wants to stick the thread
				if (!((*i)->ISsticky())){//It is not sticky
					(*i)->stick_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					fix_the_files_threads_sticky(threadfile, threadtovisit, 'S');
					Thread* newthread = new Thread();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					(*newthread) = (*(*i));//Copying the item
					threads.remove(*i);//Removing the item
					threads.push_front(newthread);//Pushing the copy of the item at the front of the list
					cout << "This thread is now a sticky one" << endl;
				}
				else{//It is sticky
					cout << "This thread is already a sticky one" << endl;
				}
			}
			else if (answer == 'U'){//The user wants to unstick the thread
				if ((*i)->ISsticky()){//It is sticky
					(*i)->unstick_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					fix_the_files_threads_sticky(threadfile, threadtovisit, 'U');
					cout << "This thread is no longer sticky" << endl;
				}
				else{//It is not sticky
					cout << "This thread is not sticky already" << endl;
				}
			}
		}
		else if (selection == 'K'){//Lock/Unlock thread
			cout << "Here are the threads:" << endl;
			list<Thread*>::iterator i;
			int number = 1;
			for (i = threads.begin(); i != threads.end(); ++i){
				cout << "This is thread number: " << number << endl;
				(*i)->print();
				++number;
			}
			cout << "Please,type the number of the thread tha you want to lock/lock" << endl;
			cin >> threadtovisit;
			i = threads.begin();
			for (number = 0; number < threadtovisit; ++number){
				++i;
			}//Reached it
			--i;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			char answer;
			cout << "Type L if you want to lock the thread,otherwise type U" << endl;
			cin >> answer;
			if (answer == 'L'){//The user wants to lock the thread
				if (!((*i)->ISlocked())){//It is  unlocked
					(*i)->lock_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					fix_the_files_threads_locked(threadfile, threadtovisit, 'L');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					cout << "Thread locked!" << endl;
				}
				else{//It is locked
					cout << "This thread is already locked" << endl;
				}
			}
			else if (answer == 'U'){//The user wants to unlock the thread
				if ((*i)->ISlocked()){//It is locked
					(*i)->unlock_it();
					string title = (*i)->returnmyTitle();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					threadtovisit = TheNumber(title, threadfile);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					fix_the_files_threads_locked(threadfile, threadtovisit, 'U');//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
					cout << "Thread unlocked!" << endl;
				}
				else{//It is unlocked
					cout << "This thread is unlocked already" << endl;
				}
			}
		}
		else if (selection == 'L'){
			leave = true;
		}
	} while (!leave);
	break;
	}//End of case 'M'
	default:{//Cases 'R','W'
		bool leave = false;
		do
		{
			char selection;
			cout << "If you want to visit a thread,type T" << endl;
			cout << "If you want to leave,type L" << endl;
			cin >> selection;
			if (selection == 'T'){
				cout << "Here are the threads:" << endl;
				list<Thread*>::iterator i;
				int number = 1;
				for (i = threads.begin(); i != threads.end(); ++i){
					cout << "This is thread number: " << number << endl;
					(*i)->print();
					++number;
				}
				cout << "Please,type the number of the thread you want to visit" << endl;
				cin >> threadtovisit;
				i = threads.begin();
				for (number = 0; number < threadtovisit; ++number){
					++i;
				}//Reached it
				--i;
				(*i)->visit(User);//And now visiting it
			}
			else if (selection == 'L'){
				leave = true;
			}
		} while (!leave);
		break;
	}
	}
}



void Thread::visit(char& User){
	cout << "Thread" << ID << ":" << title << endl;
	switch (User){
		char selection;
	case 'R':{//Regular User's case
		bool leave = false;
		do{
			cout << "If you want to view the posts,type V" << endl;
			cout << "If you want to reply,type R" << endl;
			cout << "if you want to leave the thread,type B" << endl;
			cin >> selection;
			if (selection == 'B'){//Change 
				leave = true;
			}
			else if (selection == 'V'){//Printing the content of the file of posting
				post.print();
			}
			else if (selection == 'R'){//Reply to a post
				if (locked){//If the thread is locked,the user cannot post
					cout << "Sorry,this thread is locked" << endl;
				}
				else{
					post.posting();//
				}
			}
		} while (!leave);
		break;
	}//End of case 'R'
	case 'W':{//Case 'W'
		bool leave = false;
		do{
			cout << "If you want to view the posts,type V" << endl;
			cout << "if you want to leave the thread,type B" << endl;
			cin >> selection;
			if (selection == 'B'){//Change 
				leave = true;
			}
			else if (selection == 'V'){//Printing the content of the file of posting
				post.print();
			}
		} while (!leave);
		break;
	}
	default:{//Cases 'A' and 'M'
		bool leave = false;
		do{
			cout << "If you want to view the posts,type V" << endl;
			cout << "If you want to reply,type R" << endl;
			cout << "If you want to erase a post,type A" << endl;
			cout << "If you want to move a post,type S" << endl;
			cout << "if you want to leave the thread,type B" << endl;
			cin >> selection;
			if (selection == 'B'){//Change 
				leave = true;
			}
			else if (selection == 'V'){//Printing the content of the file of posting
				post.print();
			}
			else if (selection == 'R'){//Reply to a post
				if (locked){//If the thread is locked,the user cannot post
					cout << "Sorry,this thread is locked" << endl;
				}
				else{
					post.posting();
				}
			}
			else if (selection == 'A'){//Erase a post
				cout << "In the erase selection!" << endl;
				post.print();
				string posttoerase;
				cout << "Type the post you want to erase" << endl;
				cin >> posttoerase;
				bool found = false;
				string replacing = "Deleted_Line";
				string  helpingval;
				cout << "This is the file:" << post.myFileName() << endl;
				ifstream fa(post.myFileName().c_str());					//reading file
				ofstream temp("posttemporary.txt");				//temporary file
				if (fa.good() == false)
				{
					cout << "Error reading from file " << endl;
				}
				size_t len = posttoerase.length();

				while (getline(fa, helpingval))
				{
					while (true)
					{
						cout << "helpingval=" << helpingval << endl;
						size_t pos = helpingval.find(posttoerase);
						if (pos != string::npos)
						{
							cout << "Found,and now gonna replace it" << endl;
							found = true;//!!!!!!!!!!!!!!!!!!THERE WAS NOT THIS LINE
							helpingval.replace(pos, len, replacing);
						}
						else
						{
							break;
						}
						if (found){//THERE WAS NOT THIS IF
							break;
						}
					}
					temp << helpingval << '\n';
					cout << "Printed:" << helpingval << endl;
				}

				cout << "Post deleted!" << endl;
				fa.close();
				temp.close();
				string oldname = post.myFileName();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				const char* newname = oldname.c_str();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				remove(newname);
				rename("posttemporary.txt", newname);
			}
			else if (selection == 'S'){//Move a post-WORK WITH FILES
				cout << "In the move selection!" << endl;
				post.print();
				string posttobeMoved, username, thepost, usernametobemoved;
				cout << "Type the post you want to be moved " << endl;
				cin >> posttobeMoved;
				string filename = post.myFileName();
				ifstream read(filename.c_str());
				ofstream write("temporary.txt");
				while (true){
					read >> username;
					read >> thepost;
					if (posttobeMoved == thepost){
						write << "" << endl;
						usernametobemoved = username;
						break;
					}
					write << username << endl;
					write << thepost << endl;
				}
				while (true){//Copy all the rest
					read >> username;
					if (read.eof()){
						break;
					}
					write << username << endl;
				}
				read.close();
				write.close();
				const char* erase = filename.c_str();
				remove(erase);
				rename("temporary.txt", erase);
				int forA,subA;
				string threadtitle;
				cout << "Please,insert the ID of the forum you're in" << endl;
				cin >> forA;
				cout << "Please,insert the number of the subforum you're in" << endl;
				cin >> subA;
				cout << "Please insert the the title of the thread where you want to move the post" << endl;
				cin >> threadtitle;
				MovePostToSubforum(thepost,username, forA, subA,  threadtitle);
			}
		} while (!leave);
		break;
		}//End of default case 
	}
}
void Subforum::ChangemyTitle(const char* filetowrite, string newtitle)//filetowrite:the file about the subforums must be updated
{
	/*
	title = newtitle;
	ifstream input(filetowrite);
	int numofinterest, indnum;
	string whatever, threads, oldtitle;
	input >> indnum;//Scanning the first numbers,that we don't need
	input >> numofinterest;
	while (numofinterest != serialnumber){//Searching for the appropriate files to pass to the visit() function
	input >> oldtitle;
	input >> threads;
	input >> numofinterest;
	}
	input >> oldtitle;
	input >> threads;

	*/
	bool found = false;
	string helpingval;
	ifstream fa(filetowrite);					//reading file
	ofstream temp("temporarytitle.txt");				//temporary file

	if (fa.good() == false)
	{
		cout << "Error reading from file " << endl;
	}

	size_t len = title.length();

	while (getline(fa, helpingval))
	{
		while (true)
		{
			size_t pos = helpingval.find(title);
			if (pos != string::npos)
			{
				found = true;
				helpingval.replace(pos, len, newtitle);
			}
			else
			{
				break;
			}
			if (found)
			{
				break;
			}
		}

		temp << helpingval << "\n";
	}

	cout << "Title changed! " << endl;

	fa.close();
	temp.close();
	remove(filetowrite);
	rename("temporarytitle.txt", filetowrite);////I CHANGED NAMES HERE!!!!!!!!!!!!1

	cin.get();



	/*ifstream read(filetowrite);
	ofstream write("temporaryfix.txt");
	int numofinterest;
	string title, file;*/




}



void Subforum::deleteMe(){//Deletes the contents of a subforum
	list<Thread*>::iterator i;
	for (i = threads.begin(); i != threads.end(); ++i){
		(*i)->deletemyposts();
		delete *i;
	}
}


void Thread::deletemyposts(){//Deletes the posts of a thread
	const char* postname = (post.myFileName()).c_str();  //Converting the name of a post-file to const char*
	remove(postname);//Deleting the file
}

void Thread::ChangemyTitle(const char* filetowrite, string newtitle)//filetowrite:the file about the threads must be updated
{
	bool found = false;
	string helpingval;
	ifstream fa(filetowrite);						//reading file
	ofstream temp("temporarytitle.txt");				//temporary file

	if (fa.good() == false)
	{
		cout << "Error reading from file " << endl;
	}

	size_t len = title.length();

	while (getline(fa, helpingval))
	{
		while (true)
		{
			size_t pos = helpingval.find(title);
			if (pos != string::npos)
			{
				found = true;
				helpingval.replace(pos, len, newtitle);
			}
			else
			{
				break;
			}
			if (found)
			{
				break;
			}
		}

		temp << helpingval << '\n';
	}

	cout << "Tile changed! " << endl;

	fa.close();
	temp.close();
	remove(filetowrite);
	rename("temporarytitle.txt", filetowrite);

	cin.get();


}



//USER
void UserCatalog()
{
	string name , pass;
	ifstream usa("testing.txt");

	while (usa >> name)
	{
		usa >> pass;
		cout << "Username : " << name << endl;
		cout << "Password : " << pass << endl;
		cout << endl;
	}
}




void ChangeUserCategory()
{
	bool found = false;
	string replacing;
	string usertobeChanged, helpingval , category;
	ifstream fa("testing.txt");						//reading file
	ofstream temp("temporarycat.txt");				//temporary file

	if (fa.good() == false)
	{
		cout << "Error reading from file " << endl;
	}
	cout << "Please give username to change his category " << endl;
	cin >> usertobeChanged;

	cout << "Please give his category " << endl;
	cin >> category;
	cout << "Please enter the category you want to change with " << endl;
	cin >> replacing;

	size_t len = category.length();

	while (getline(fa , helpingval))
	{
		while (true)
		{
			size_t pos = helpingval.find(usertobeChanged);
			if (pos != string::npos)
			{
				found = true;
				helpingval.replace(pos, len, replacing);
			}
			else
			{
				break;
			}
			if (found)
			{
				break;
			}
		}

		temp << helpingval << '\n';
	}

	cout << "User's category changed! " << endl;

	fa.close();
	temp.close();
	remove("testing.txt");
	rename("temporarycat.txt", "testing.txt");

	cin.get();
}



void DeleteUser()
{
	bool found = false;
	string replacing = "Deleted_User ";
	string usertobeDeleted, helpingval;
	ifstream fa("testing.txt");					//reading file
	ofstream temp("temporary.txt");				//temporary file

	if (fa.good() == false)
	{
		cout << "Error reading from file " << endl;
	}
	cout << "Give username you want to delete " << endl;
	cin >> usertobeDeleted;
	
	size_t len = usertobeDeleted.length();
	
	while (getline(fa, helpingval))
	{
		while (true)
		{
			size_t pos = helpingval.find(usertobeDeleted);
			if (pos != string::npos)
			{
				helpingval.replace(pos, len, replacing);
			}
			else
			{
				break;
			}
		}

		temp << helpingval << '\n';
	}

	cout << "User deleted! " << endl;
	
	fa.close();
	temp.close();
	remove("testing.txt");
	rename("temporary.txt", "testing.txt");

	
	cin.get();
}



void ChangeUsername()
{
	bool found = false;
	string replacing;
	string nametobeChanged, helpingval;
	ifstream fa("testing.txt");						//reading file
	ofstream temp("temporaryname.txt");				//temporary file

	if (fa.good() == false)
	{
		cout << "Error reading from file " << endl;
	}
	cout << "Please give username to change" << endl;
	cin >> nametobeChanged;

	cout << "Please enter the name you want to change with " << endl;
	cin >> replacing;

	size_t len = nametobeChanged.length();

	while (getline(fa, helpingval))
	{
		while (true)
		{
			size_t pos = helpingval.find(nametobeChanged);
			if (pos != string::npos)
			{
				helpingval.replace(pos, len, replacing);
			}
			else
			{
				break;
			}
		}

		temp << helpingval << '\n';
	}

	cout << "User's name changed! " << endl;

	fa.close();
	temp.close();
	remove("testing.txt");
	rename("temporaryname.txt", "testing.txt");

	cin.get();
}



void ChangePassword()
{
	bool found = false;
	string replacing , usernam;
	string passtobeChanged, helpingval;
	ifstream fa("testing.txt");						//reading file
	ofstream temp("temporarypass.txt");				//temporary file

	if (fa.good() == false)
	{
		cout << "Error reading from file " << endl;
	}
	cout << "Please give a password you want to change" << endl;
	cin >> passtobeChanged;

	cout << "Please enter the password you want to change with " << endl;
	cin >> replacing;
	
	size_t len = passtobeChanged.length();

	while (fa >> usernam)
	{
		fa >> helpingval;
		while (true)
		{
			size_t pos = helpingval.find(passtobeChanged);
			if (pos != string::npos)
			{
				helpingval.replace(pos, len, replacing);
			}
			else
			{
				break;
			}	
		}

		temp << "\n";
		temp << usernam << "\n";
		temp << helpingval << "\n";
	}

	cout << "User's password changed! " << endl;

	fa.close();
	temp.close();
	remove("testing.txt");
	rename("temporarypass.txt", "testing.txt");
	cin.get();
}



bool decipher_the_answer(char *answer){
	char ans1[5] = "Yes";
	char ans2[5] = "No";
	char ans3[5] = "yes";
	char ans4[5] = "no";
	char ans5[5] = "YES";
	char ans6[5] = "NO";
	if ((strcmp(answer, ans1) == 0) || (strcmp(answer, ans3) == 0) || (strcmp(answer, ans5) == 0)){
		return true;
	}
	if ((strcmp(answer, ans2) == 0) || (strcmp(answer, ans4) == 0) || (strcmp(answer, ans6) == 0)){
		return false;
	}
}



void Registration(string name , string pass,char& user)
{
	string fileUserName, filePassWord , isthereaLine;
	bool registered = false, breakpoint = false;
	fstream reg("testing.txt", ios::in);

	while (!registered)
	{
		while (getline(reg , isthereaLine))
		{
			reg >> fileUserName >> filePassWord;
			if ((name.compare(fileUserName) == 0) && (pass.compare(filePassWord) == 0))
			{
				breakpoint = true;		//user should change credentials
				break;
			}
		}

		if (breakpoint)
		{
			cout << "Your registration failed." << endl;
			cout << "Please insert a new username." << endl;
			cin >> name;
			cout << "Please insert a new password." << endl;
			cin >> pass;
			breakpoint = false;
		}
		else
		{
			fstream reg("testing.txt", ios::app);           //registration success
			reg << endl << endl << name << endl << pass;
			registered = true;
			cout << "Registration successful " << endl;
		}
	}
	string strU = "RU";  //Regular User
	string strM = "MD";  //Moderator
	string strA = "AD";  //Administrator
	size_t found;
	found = name.find(strA);
	if (found != string::npos){   //We're looking at an Administrator
		cout << "You are an Administrator" << endl;
		user = 'A';
	}
	found = name.find(strM);
	if (found != string::npos){   //We're looking at a Moderator
		cout << "You are a Moderator" << endl;
		user = 'M';
	}
	found = name.find(strU);
	if (found != string::npos){  //We're looking at a Regular User
		cout << "You are a Regular User" << endl;
		user = 'R';
	}
}



void fix_the_files_subforums(string filetobefixed, int& serialnumber){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ifstream read(filetobefixed.c_str());
	ofstream write("temporaryfix.txt");
	int numofinterest;
	string title, filetoerase;
	read >> numofinterest;
	write << --numofinterest << endl;//W	e're down one subforum!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	read >> numofinterest;
	while (numofinterest != serialnumber){//Copying filetobefixed to the temporaryfix.txt
		write << numofinterest << endl;
		read >> title;
		write << title << endl;
		read >> filetoerase;
		write << filetoerase << endl;
		read >> numofinterest;
	}//We found the block of information we wanted
	write << "\n";//Instead of numofinterest
	read >> title;
	write << "\n";//Instead of the title
	read >> filetoerase;
	const char* erase = filetoerase.c_str();
	remove(erase);//Deleted the file about the subforum's threads
	write << "\n";//Instead of the title of the threads file
	while (true){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		read >> numofinterest;
		if (read.eof()){
			break;
		}
		--numofinterest;
		write << numofinterest << endl;//Now that we've deleted an item,the serial numbers need to change
		read >> title;
		write << title << endl;
		read >> filetoerase;
		write << filetoerase << endl;
	}
	read.close();
	write.close();
	erase = filetobefixed.c_str();
	remove(erase);//Erasing the old file
	rename("temporaryfix.txt", erase);//Renaming the temporary file
}

void fix_the_files_threads_delete(string filetobefixed, int& serialnumber){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ifstream read(filetobefixed.c_str());
	ofstream write("temporaryfix.txt");
	int numofinterest;
	char letter;
	string title, filetoerase;
	read >> numofinterest;//This is the total number of threads
	write << --numofinterest << endl;//And now we've deleted a thread//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	read >> numofinterest;
	while (numofinterest != serialnumber){//Copying filetobefixed to the temporaryfix.txt
		write << numofinterest << endl;
		read >> title;
		write << title << endl;
		read >> filetoerase;
		write << filetoerase << endl;
		read >> letter;
		write << letter << endl;
		read >> letter;
		write << letter << endl;
		read >> numofinterest;
	}//We found the block of information we wanted
	write << "\n";//Instead of numofinterest
	read >> title;
	write << "\n";//Instead of the title
	read >> filetoerase;
	const char* erase = filetoerase.c_str();
	remove(erase);//Deleted the file about the subforum's threads
	write << "\n";//Instead of the title of the threads file
	read >> letter;
	write << "\n";
	read >> letter;
	write << "\n";
	while (true){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		read >> numofinterest;
		if (read.eof()){
			break;
		}
		--numofinterest;
		write << numofinterest << endl;//Now that we've deleted an item,the serial numbers need to change
		read >> title;
		write << title << endl;
		read >> filetoerase;
		write << filetoerase << endl;
		read >> letter;
		write << letter << endl;
		read >> letter;
		write << letter << endl;

	}
	read.close();
	write.close();
	erase = filetobefixed.c_str();
	remove(erase);//Erasing the old file
	rename("temporaryfix.txt", erase);//Renaming the temporary file	
}

void fix_the_files_threads_sticky(string filetobefixed, int& serialnumber, char chartoreplace){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ifstream read(filetobefixed.c_str());
	ofstream write("temporaryfix.txt");
	int numofinterest;
	char letter;
	string title, filetoerase;
	read >> numofinterest;
	write << numofinterest << endl;
	read >> numofinterest;
	while (numofinterest != serialnumber){//Copying filetobefixed to the temporaryfix.txt
		write << numofinterest;
		read >> title;
		write << title << endl;
		read >> filetoerase;
		write << filetoerase << endl;
		read >> letter;
		write << letter << endl;
		read >> letter;
		write << letter << endl;
		read >> numofinterest;
	}//We found the block of information we wanted
	write << numofinterest << endl;
	read >> title;
	write << title << endl;
	read >> filetoerase;
	write << filetoerase << endl;
	read >> letter;
	write << letter << endl;
	read >> letter;
	write << chartoreplace << endl;
	while (true){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
		read >> numofinterest;
		if (read.eof()){
			break;
		}
		write << numofinterest << endl;
		read >> title;
		write << title << endl;
		read >> filetoerase;
		write << filetoerase << endl;
		read >> letter;
		write << letter << endl;
		read >> letter;
		write << letter << endl;
	}
	read.close();
	write.close();
	const char* erase = filetobefixed.c_str();
	remove(erase);//Erasing the old file
	rename("temporaryfix.txt", erase);//Renaming the temporary file	
}

void fix_the_files_threads_locked(string filetobefixed, int& serialnumber, char chartoreplace){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	cout << "This is the file:" << filetobefixed << endl;
	ifstream read(filetobefixed.c_str());
	ofstream write("temporaryfix.txt");
	int numofinterest;
	char letter;
	string title, filetoerase;
	read >> numofinterest;
	write << numofinterest << endl;
	read >> numofinterest;
	while (numofinterest != serialnumber){//Copying filetobefixed to the temporaryfix.txt
		write << numofinterest << endl;
		read >> title;
		write << title << endl;
		read >> filetoerase;
		write << filetoerase << endl;
		read >> letter;
		write << letter << endl;
		read >> letter;
		write << letter << endl;
		read >> numofinterest;
	}//We found the block of information we wanted
	write << numofinterest << endl;
	read >> title;
	write << title << endl;
	read >> filetoerase;
	write << filetoerase << endl;
	read >> letter;
	write << chartoreplace << endl;
	read >> letter;
	write << letter << endl;
	while (true){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		read >> numofinterest;
		if (read.eof()){
			break;
		}
		write << numofinterest << endl;
		read >> title;
		write << title << endl;
		read >> filetoerase;
		write << filetoerase << endl;
		read >> letter;
		write << letter << endl;
		read >> letter;
		write << letter << endl;
	}
	read.close();
	write.close();
	const char* erase = filetobefixed.c_str();
	remove(erase);//Erasing the old file
	rename("temporaryfix.txt", erase);//Renaming the temporary file	


}



void UniverseConstruction(list<Forum*>& forums)
{
	int lastThread;					//number of thread's in forum
	ifstream file("number.txt");
	file >> LastForumID;
	file >> LastThreadID;
	file >> lastThread;
	int serialnumber;
	//Forum A("Skillet & Jen", LastForumID, LastThreadID,"helper.txt");


	//FROM NOW ON,THIS IS TOTALLY NEW CODE
	string forumtitles, inputfiles , threadfiles;
	cout << "Going to create the forums" << endl;
	for (int i = 0; i < LastForumID; ++i){
		cout << "Starting..." << endl;
		file >> serialnumber;//Forum's serial number in the input file
		file >> threadfiles;
		file >> forumtitles;
		file >> LastThreadID;
		file >> inputfiles;
		Forum* mypForum = new Forum(forumtitles, LastForumID, LastThreadID, inputfiles,i+1 , lastThread , threadfiles);
		forums.push_back(mypForum);
		cout << "A new forum's in the list." << endl;
	}
}

	//DESTRUCTIOOONNNN!!! 
	

void UniverseDestruction(list<Forum*>& forums)
{
	cout << "exiting..." << endl;
	cout << "Going to destroy everything" << endl;
	list<Forum*>::iterator i;
	for (i = forums.begin(); i != forums.end(); ++i){
		cout << "I'm in the main-for" << endl;
		delete *i;
	}
	cout << "Everything went smoothly" << endl;
	cin.get();
}



//POST
void Post::posting(){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ofstream file(nameFile.c_str(), ios::app);
	if (file.is_open()){
		string youranswer, yourusername;
		cout << "Insert your username" << endl;
		cin >> yourusername;
		cout << "Write your answer" << endl;
		cout << "(Keep in mind that you should write posts of 1 line.If you want to indicate spaces, use underscores)" << endl;
		cin >> youranswer;//Getting the user's post
		file << "\n";
		file << yourusername << "\n";
		file << youranswer << "\n";//Printing it to the posting file
		file << "\n" << endl;
	}
	else{
		cout << "Sorry,cannot open the file needed.Please,try again later." << endl;
	}
}



void Post::print(){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ifstream file(nameFile.c_str());
	if (file.is_open()){
		while (true){//As long as there are text lines
			if (file.eof()){
				break;
			}
			string stringtoprint;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			file >> stringtoprint;
			cout << stringtoprint << endl;//Print the post
		}
	}
	else{//Couldn't open the file
		cout << "Sorry,cannot display the post." << endl;
	}
}





void Thread::operator=(Thread& other){
	cout << "In the = function" << endl;
	title = other.title;
	sticky = other.sticky;
	locked = other.locked;
	//postfile = other.postfile;
	post = other.post;
	cout << "Copied everything,returning" << endl;
}





void Post::operator=(Post& other){//Copy-constructor
	nameFile = other.nameFile;
}


void MoveSubforum(int& A, int& B, int& FB, int& FA){
	//A the original serial number of the subforum that's about to be moved
	//FA the Forum in which the subforum was originally
	//FB the Forum where we will send the subforum
	//B number of already existant subforums in the forum of destination
	cout << "Okay,in the moving function" << endl;
	string fileofOrigin, fileofDestination, whatever;
	int useless, numofinterest;
	ifstream read("number.txt");
	read >> useless;
	read >> useless;
	read >> useless;
	read >> numofinterest;
	while (numofinterest != FA){//Searching for the appropriate file of origin
		cout << "Searching..." << endl;
		read >> whatever;
		read >> whatever;
		read >> useless;
		read >> fileofOrigin;
		read >> numofinterest;
	}
	cout << "Found!" << endl;
	read >> whatever;
	read >> whatever;
	read >> useless;
	read >> fileofOrigin;//We got the file we need
	cout << "Just got the file we were looking for,that is" << fileofOrigin << endl;
	read.close();//Closing the stream for now
	//Now we will extract the information about the subforum,so we need to update the file of origin
	cout << "Now going to update the file of origin" << endl;
	ifstream take(fileofOrigin.c_str());//Getting into the file of origin
	ofstream write("temporary.txt");
	string title, threadsfile, THEtitle, THEthreadsfile;
	take >> useless;//Scanning the very first number
	write << --useless << endl;//Copying the file of origin to the temporary-we're down a subforum in total
	take >> numofinterest;
	while (numofinterest != A){
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> threadsfile;
		write << threadsfile << endl;
		take >> numofinterest;
	}//Reached the block of the subforum we want to extract
	cout << "Found the block we'll extract" << endl;
	write << "\n";//The subforum will be extracted,so we won't copy its information
	take >> title;
	write << "\n";
	THEtitle = title;//We need to keep this one
	take >> threadsfile;
	write << "\n";
	THEthreadsfile = threadsfile;//We need to keep this one 
	cout << "Okay,going to copy the rest" << endl;
	while (true){//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		take >> numofinterest;
		if (take.eof()){
			break;
		}
		--numofinterest;//Now we're down a subforum
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> threadsfile;
		write << threadsfile << endl;
	}
	take.close();
	write.close();//Closing the files
	const char* erase = fileofOrigin.c_str();
	remove(erase);//Deleting the old file of origin
	rename("temporary.txt", erase);
	cout << "Okay,fixed the whole erase/rename thing" << endl;
	//Extracted the information about the subforum we'll move,and copied all the rest
	cout << "And now going to search for the file of destination" << endl;
	ifstream reread("number.txt");
	reread >> useless;//Read the first three numbers of the file the we don't need
	reread >> useless;
	reread >> useless;
	reread >> numofinterest;
	while (numofinterest != FB){//Searching for the appropriate file of origin
		reread >> whatever;
		reread >> whatever;
		reread >> useless;
		reread >> fileofDestination;
		reread >> numofinterest;
	}
	reread >> whatever;
	reread >> whatever;
	reread >> useless;
	reread >> fileofDestination;//We got the file we need
	cout << "Just found the file of destination,that is:" << fileofDestination << endl;
	reread.close();//Closing the stream for now
	cout << "Now going to update it" << endl;
	ifstream readagain(fileofDestination.c_str());
	ofstream writeagain("ttemporary.txt");
	readagain >> useless;
	cout << "This is the old number of subforums" << endl;
	writeagain << ++useless << endl;//Now there's one more subforum
	while (true){
		readagain >> numofinterest;
		if (readagain.eof()){
			break;
		}
		writeagain << numofinterest << endl;
		readagain >> title;
		writeagain << title << endl;
		readagain >> threadsfile;
		writeagain << threadsfile << endl;
	}
	readagain.close();
	writeagain.close();
	ofstream rewrite("ttemporary.txt", ios::app);//Opening the destination file again
	rewrite << endl << endl;//Writing at the end of it the information about the new subforum
	++B;//Now we are plus one subforum
	rewrite << B << endl;
	rewrite << THEtitle << endl << THEthreadsfile << endl;
	rewrite.close();
	erase = fileofDestination.c_str();
	remove(erase);
	rename("ttemporary.txt", erase);
	cout << "Okay,wrote" << endl;
}


void MoveThreadToSubforum(string subforumsinput, int& A, int& B, int& FA, int& FB){//WORKING!!!!!!!!!!
	//MOVING A THREAD FROM A SUBFORUM IN ANOTHER,IN THE SAME FORUM
	//subforumsinput-the file of a forum that contains the information about its subforums-list
	//A the original serial number of the thread that's about to be moved
	//B the total number of threads in the subforum of destination
	//FA subforum of origin
	//FB subforum of destination
	cout << "In the moving function" << endl;
	int numofinterest;
	string title, threadsfile;
	ifstream read(subforumsinput.c_str());
	read >> numofinterest;//Scanning the first number,that we don't need
	read >> numofinterest;
	while (numofinterest != FA){
		cout << "Searching..." << endl;
		read >> title;
		read >> threadsfile;
		read >> numofinterest;
	}
	read >> title;
	read >> threadsfile;//We need this particular file
	read.close();
	cout << "The file of origin is" << threadsfile << endl;
	//Now must update this threadsfile,for we will move one thread from it
	ofstream write("temporary.txt");
	ifstream take(threadsfile.c_str());
	char letter, THEl, THEs;
	int useless;
	string postingfile, THEpostingfile, THEtitle;
	take >> useless;//Scanned the first number
	write << --useless << endl;//We're down a thread
	take >> numofinterest;
	while (numofinterest != A){
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> postingfile;
		write << postingfile << endl;
		take >> letter;
		write << letter << endl;
		take >> letter;
		write << letter << endl;
		take >> numofinterest;
	}//We reached the thread that will be moved,so we won't copy its elements
	write << "\n";
	take >> THEtitle;//We need to keep the THEvariables
	write << "\n";
	take >> THEpostingfile;
	take >> THEl;
	take >> THEs;
	//Finished with the block of interest
	while (true){//We will copy the rest of the file
		take >> numofinterest;
		if (take.eof()){
			break;
		}
		--numofinterest;//We are a thread down from  now on
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> postingfile;
		write << postingfile << endl;
		take >> letter;
		write << letter << endl;
		take >> letter;
		write << letter << endl;
	}
	take.close();
	write.close();
	const char* erase = threadsfile.c_str();
	remove(erase);
	rename("temporary.txt", erase);//Swapped names
	//Now we need to find the threadsinput file of the subforum of destination,to copy this information
	ifstream reread(subforumsinput.c_str());
	reread >> numofinterest;//Scanning the first number,that we don't need
	reread >> numofinterest;
	while (numofinterest != FB){
		reread >> title;
		reread >> threadsfile;
		reread >> numofinterest;
	}
	reread >> title;
	reread >> threadsfile;//We need this particular file
	reread.close();
	cout << "The file of destination is:" << threadsfile << endl;
	ifstream readagain(threadsfile.c_str());
	ofstream writeagain("ttemporary.txt");
	readagain >> useless;
	writeagain << ++useless << endl;//There's one more thread now
	while (true){
		readagain >> numofinterest;
		if (readagain.eof()){
			break;
		}
		numofinterest;
		writeagain << numofinterest << endl;
		readagain >> title;
		writeagain << title << endl;
		readagain >> postingfile;
		writeagain << postingfile << endl;
		readagain >> letter;
		writeagain << letter << endl;
		readagain >> letter;
		writeagain << letter << endl;
	}//Copied the file
	readagain.close();
	writeagain.close();
	ofstream enrich("ttemporary.txt", ios::app);
	++B;//Now we're plus 1 thread
	enrich << endl << endl << B << endl;
	enrich << THEtitle << endl;
	enrich << THEpostingfile << endl;
	enrich << THEl << endl;
	enrich << THEs << endl;
	enrich.close();
	erase = threadsfile.c_str();
	remove(erase);
	rename("ttemporary.txt", erase);
	cout << "DONE!" << endl;
}

void MoveThreadToForum(int& A, int& B, int& FA, int& FB){//WORKING
	//MOVES A THREAD FROM A FORUM(NOT IN SUBFORUM) IN ANOTHER FORUM(NOT IN SUBFORUM)
	//A the original serial number of the thread that's about to be moved
	//FA the Forum in which the thream was originally
	//FB the Forum where we will send the thread
	//B number of already existant threads in the forum of destination
	cout << "In the moving" << endl;
	string fileofOrigin, fileofDestination, whatever;
	int useless, numofinterest;
	ifstream read("number.txt");
	read >> useless;
	read >> useless;
	read >> useless;
	read >> numofinterest;
	while (numofinterest != FA){//Searching for the appropriate file of origin
		read >> fileofOrigin;
		read >> whatever;
		read >> useless;
		read >> whatever;
		read >> numofinterest;
	}
	read >> fileofOrigin;//We will need this file
	cout << "We'll update the file" << fileofOrigin << endl;
	read.close();//Closing the stream for now
	ofstream write("temporary.txt");
	ifstream take(fileofOrigin.c_str());
	char letter, THEl, THEs;
	//int useless;  COMMENTED BECAUSE OF ERROR
	string postingfile, THEpostingfile, THEtitle, title;
	take >> useless;//Scanned the first number
	write << --useless << endl;
	take >> numofinterest;
	while (numofinterest != A){
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> postingfile;
		write << postingfile << endl;
		take >> letter;
		write << letter << endl;
		take >> letter;
		write << letter << endl;
		take >> numofinterest;
	}//We reached the thread that will be moved,so we won't copy its elements
	write << "\n";
	take >> THEtitle;//We need to keep the THEvariables
	take >> THEpostingfile;
	write << "\n";
	take >> THEl;
	take >> THEs;
	//Finished with the block of interest
	while (true){//We will copy the rest of the file
		take >> numofinterest;
		if (take.eof()){
			break;
		}
		--numofinterest;//We are a thread down from  now on
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> postingfile;
		write << postingfile << endl;
		take >> letter;
		write << letter << endl;
		take >> letter;
		write << letter << endl;
	}
	take.close();
	write.close();
	const char* erase = fileofOrigin.c_str();
	remove(erase);
	rename("temporary.txt", erase);//Swapped names
	ifstream reread("number.txt");//Reopening the file to search for the file of destination
	reread >> useless;
	reread >> useless;
	reread >> useless;
	reread >> numofinterest;
	while (numofinterest != FB){//Searching for the appropriate file of destination
		reread >> fileofDestination;
		reread >> whatever;
		reread >> useless;
		reread >> whatever;
		reread >> numofinterest;
	}
	reread >> fileofDestination;//We will need this file
	reread.close();//Closing the stream for now
	cout << "And now we'll update the file" << fileofDestination << endl;
	ifstream readagain(fileofDestination.c_str());
	ofstream writeagain("ttemporary.txt");
	readagain >> useless;
	writeagain << ++useless << endl;
	while (true){
		readagain >> numofinterest;
		if (readagain.eof()){
			break;
		}
		++numofinterest;//We are a thread down from  now on
		writeagain << numofinterest << endl;
		readagain >> title;
		writeagain << title << endl;
		readagain >> postingfile;
		writeagain << postingfile << endl;
		readagain >> letter;
		writeagain << letter << endl;
		readagain >> letter;
		writeagain << letter << endl;
	}
	readagain.close();
	writeagain.close();
	ofstream enrich("ttemporary.txt", ios::app);
	enrich << endl << endl;
	++B;//We are plus one thread
	enrich << B << endl;
	enrich << THEtitle << endl;
	enrich << THEpostingfile << endl;
	enrich << THEl << endl;
	enrich << THEs << endl;
	enrich.close();
	erase = fileofDestination.c_str();
	remove(erase);
	rename("ttemporary.txt", erase);
	cout << "DONE!" << endl;
}


void MoveThreadFSTS(int& A, int&B, int& FA, int& FB, int& SA, int& SB){//WORKING
	//MOVES A THREAD FROM A SUBFORUM INTO A SUBFORUM,IN ANOTHER FORUM
	//A the serial number of the thread,in the original subforum
	//B the total number of threads in the subforum of destination
	//FA the serial number of the original forum
	//FB the serial number of the forum of destination
	//SA the serial number of the original subforum
	//SB the serial number of the subforum of destination
	int numofinterest, useless;
	string wanted, whatever;
	ifstream read("number.txt");
	read >> useless;
	read >> useless;
	read >> useless;
	read >> numofinterest;
	while (numofinterest != FA){//Searching for the appropriate file of origin
		read >> whatever;
		read >> whatever;
		read >> useless;
		read >> wanted;
		read >> numofinterest;
	}
	read >> whatever;
	read >> whatever;
	read >> useless;
	read >> wanted;//We got the file we need
	read.close();//Closing the stream for now
	string title, threadsfile;
	ifstream readagain(wanted.c_str());//Open this file,to find the file with the information for the thread
	readagain >> numofinterest;//We don't need this first number
	readagain >> numofinterest;
	while (numofinterest != SA){
		readagain >> title;
		readagain >> threadsfile;
		readagain >> numofinterest;
	}
	readagain >> title;
	readagain >> threadsfile;//We need this particular file
	readagain.close();
	//We will update the threads file
	cout << "We'll take our information from the file" << threadsfile << endl;
	ofstream write("temporary.txt");
	ifstream take(threadsfile.c_str());
	char letter, THEl, THEs;
	//int useless;  COMMENTED BECAUSE OF ERROR
	string postingfile, THEpostingfile, THEtitle;
	take >> useless;//Scanned the first number
	write << --useless << endl;//We're down a thread
	take >> numofinterest;
	while (numofinterest != A){
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> postingfile;
		write << postingfile << endl;
		take >> letter;
		write << letter << endl;
		take >> letter;
		write << letter << endl;
		take >> numofinterest;
	}//We reached the thread that will be moved,so we won't copy its elements
	write << "\n";
	take >> THEtitle;//We need to keep the THEvariables
	write << "\n";
	take >> THEpostingfile;
	take >> THEl;
	take >> THEs;
	//Finished with the block of interest
	while (true){//We will copy the rest of the file
		take >> numofinterest;
		if (take.eof()){
			break;
		}
		--numofinterest;//We are a thread down from  now on
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> postingfile;
		write << postingfile << endl;
		take >> letter;
		write << letter << endl;
		take >> letter;
		write << letter << endl;
	}
	take.close();
	write.close();
	const char* erase = threadsfile.c_str();
	remove(erase);
	rename("temporary.txt", erase);//Swapped names
	ifstream reread("number.txt");
	reread >> useless;
	reread >> useless;
	reread >> useless;
	reread >> numofinterest;
	while (numofinterest != FB){//Searching for the appropriate file of destination
		reread >> whatever;
		reread >> whatever;
		reread >> useless;
		reread >> wanted;
		reread >> numofinterest;
	}
	reread >> whatever;
	reread >> whatever;
	reread >> useless;
	reread >> wanted;//We got the file we need
	reread.close();//Closing the stream for now
	ifstream andread(wanted.c_str());//Open this file,to find the file with the information for the thread
	andread >> numofinterest;//We don't need this first number
	andread >> numofinterest;
	while (numofinterest != SB){
		andread >> title;
		andread >> threadsfile;
		andread >> numofinterest;
	}
	andread >> title;
	andread >> threadsfile;//We need this particular file
	andread.close();
	//We will update the threads file
	cout << "We'll update the file" << threadsfile << endl;
	ifstream rereadagain(threadsfile.c_str());
	ofstream writeagain("ttemporary.txt");
	rereadagain >> useless;
	writeagain << ++useless << endl;//There's one more thread now
	while (true){
		rereadagain >> numofinterest;
		if (rereadagain.eof()){
			break;
		}
		writeagain << numofinterest << endl;
		rereadagain >> title;
		writeagain << title << endl;
		rereadagain >> postingfile;
		writeagain << postingfile << endl;
		rereadagain >> letter;
		writeagain << letter << endl;
		rereadagain >> letter;
		writeagain << letter << endl;
	}
	rereadagain.close();
	writeagain.close();
	ofstream enrich("ttemporary.txt", ios::app);
	++B;//Now we're plus 1 thread
	enrich << endl << endl << B << endl;
	enrich << THEtitle << endl;
	enrich << THEpostingfile << endl;
	enrich << THEl << endl;
	enrich << THEs << endl;
	enrich.close();
	erase = threadsfile.c_str();
	remove(erase);
	rename("ttemporary.txt", erase);
	cout << "DONE!" << endl;
}


void MoveThreadFFTS(int&A, int&B, int&FA, int&FB, int&SB){//WORKING!!!!!!!!!!!!!!!!
	//MOVES A THREAD FROM A FORUM(NOT IN SUBFORUM) INTO A SUBFORUM IN ANOTHER FORUM
	//A serial number of the thread in the original forum
	//B serial number of the thread in the subforum of destination
	//FA serial number of the original forum
	//FB serial number of the forum of destination
	//SB serial number of the subforum of destination
	cout << "Okay,in moving function" << endl;
	string fileofOrigin, whatever;
	int useless, numofinterest;
	ifstream read("number.txt");
	read >> useless;
	read >> useless;
	read >> useless;
	read >> numofinterest;
	while (numofinterest != FA){//Searching for the appropriate file of origin
		read >> fileofOrigin;
		read >> whatever;
		read >> useless;
		read >> whatever;
		read >> numofinterest;
	}
	read >> fileofOrigin;//We will need this file
	read.close();//Closing the stream for now
	cout << "We will update the file" << fileofOrigin << endl;
	ofstream write("temporary.txt");
	ifstream take(fileofOrigin.c_str());
	char letter, THEl, THEs;
	//int useless;COMMENTED BECAUSE OF ERROR
	string postingfile, THEpostingfile, THEtitle, title;
	take >> useless;//Scanned the first number
	write << --useless << endl;//We're down a thread here
	take >> numofinterest;
	while (numofinterest != A){
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> postingfile;
		write << postingfile << endl;
		take >> letter;
		write << letter << endl;
		take >> letter;
		write << letter << endl;
		take >> numofinterest;
	}//We reached the thread that will be moved,so we won't copy its elements
	write << "\n";
	take >> THEtitle;//We need to keep the THEvariables
	write << "\n";
	take >> THEpostingfile;
	write << "\n";
	take >> THEl;
	write << "\n";
	take >> THEs;
	write << "\n";
	//Finished with the block of interest
	while (true){//We will copy the rest of the file
		take >> numofinterest;
		if (take.eof()){
			break;
		}
		--numofinterest;//We are a thread down from  now on
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> postingfile;
		write << postingfile << endl;
		take >> letter;
		write << letter << endl;
		take >> letter;
		write << letter << endl;
	}
	take.close();
	write.close();
	const char* erase = fileofOrigin.c_str();
	remove(erase);
	rename("temporary.txt", erase);//Swapped names
	string wanted;//The file of the subforum
	ifstream reread("number.txt");
	reread >> useless;
	reread >> useless;
	reread >> useless;
	reread >> numofinterest;
	while (numofinterest != FB){//Searching for the appropriate file of destination
		reread >> whatever;
		reread >> whatever;
		reread >> useless;
		reread >> wanted;
		reread >> numofinterest;
	}
	reread >> whatever;
	reread >> whatever;
	reread >> useless;
	reread >> wanted;//We got the file we need
	reread.close();//Closing the stream for now
	string threadsfile;
	ifstream andread(wanted.c_str());//Open this file,to find the file with the information for the thread
	andread >> numofinterest;//We don't need this first number
	andread >> numofinterest;
	while (numofinterest != SB){
		andread >> title;
		andread >> threadsfile;
		andread >> numofinterest;
	}
	andread >> title;
	andread >> threadsfile;//We need this particular file
	andread.close();
	//We will update the threads file
	cout << "We'll update the file " << threadsfile << endl;
	ifstream readagain(threadsfile.c_str());
	ofstream writeagain("ttemporary.txt");
	readagain >> useless;
	writeagain << ++useless << endl;//There's one more thread now
	while (true){
		readagain >> numofinterest;
		if (readagain.eof()){
			break;
		}
		writeagain << numofinterest << endl;
		readagain >> title;
		writeagain << title << endl;
		readagain >> postingfile;
		writeagain << postingfile << endl;
		readagain >> letter;
		writeagain << letter << endl;
		readagain >> letter;
		writeagain << letter << endl;
	}
	readagain.close();
	writeagain.close();
	ofstream enrich("ttemporary.txt", ios::app);
	++B;//Now we're plus 1 thread
	enrich << endl << endl << B << endl;
	enrich << THEtitle << endl;
	enrich << THEpostingfile << endl;
	enrich << THEl << endl;
	enrich << THEs << endl;
	enrich.close();
	erase = threadsfile.c_str();
	remove(erase);
	rename("ttemporary.txt", erase);
	cout << "DONE!" << endl;
}

void MoveThreadFSTF(int&A, int&B, int&FA, int&FB, int&SA){//WORKING!!!!!!!!!!!!!!!
	//A the serial number of the thread in the original subforum
	//B the total number of forums in the forum of destination
	//FB the serial number of the forum of destination
	//FA the serial number of the forum of origin
	//SA the serial number of the forum of origin
	cout << "Okay,in the moving" << endl;
	int numofinterest, useless;
	string wanted, whatever;
	ifstream read("number.txt");
	read >> useless;
	read >> useless;
	read >> useless;
	read >> numofinterest;
	while (numofinterest != FA){//Searching for the appropriate file of origin
		read >> whatever;
		read >> whatever;
		read >> useless;
		read >> wanted;
		read >> numofinterest;
	}
	read >> whatever;
	read >> whatever;
	read >> useless;
	read >> wanted;//We got the file we need
	read.close();//Closing the stream for now
	string title, threadsfile;
	ifstream readagain(wanted.c_str());//Open this file,to find the file with the information for the thread
	readagain >> numofinterest;//We don't need this first number
	readagain >> numofinterest;
	while (numofinterest != SA){
		readagain >> title;
		readagain >> threadsfile;
		readagain >> numofinterest;
	}
	readagain >> title;
	readagain >> threadsfile;//We need this particular file
	readagain.close();
	//We will update the threads file
	cout << "We'll update the file" << threadsfile << endl;
	ofstream write("temporary.txt");
	ifstream take(threadsfile.c_str());
	char letter, THEl, THEs;
	//int useless; COMMENTED BECAUSE OF ERROR
	string postingfile, THEpostingfile, THEtitle;
	take >> useless;//Scanned the first number
	write << --useless << endl;
	take >> numofinterest;
	while (numofinterest != A){
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> postingfile;
		write << postingfile << endl;
		take >> letter;
		write << letter << endl;
		take >> letter;
		write << letter << endl;
		take >> numofinterest;
	}//We reached the thread that will be moved,so we won't copy its elements
	write << "\n";
	take >> THEtitle;//We need to keep the THEvariables
	write << "\n";
	take >> THEpostingfile;
	take >> THEl;
	take >> THEs;
	//Finished with the block of interest
	while (true){//We will copy the rest of the file
		take >> numofinterest;
		if (take.eof()){
			break;
		}
		--numofinterest;//We are a thread down from  now on
		write << numofinterest << endl;
		take >> title;
		write << title << endl;
		take >> postingfile;
		write << postingfile << endl;
		take >> letter;
		write << letter << endl;
		take >> letter;
		write << letter << endl;
	}
	take.close();
	write.close();
	const char* erase = threadsfile.c_str();
	remove(erase);
	rename("temporary.txt", erase);//Swapped names
	string fileofDestination;
	ifstream reread("number.txt");//Reopening the file to search for the file of destination
	reread >> useless;
	reread >> useless;
	reread >> useless;
	reread >> numofinterest;
	while (numofinterest != FB){//Searching for the appropriate file of destination
		reread >> fileofDestination;
		reread >> whatever;
		reread >> useless;
		reread >> whatever;
		reread >> numofinterest;
	}
	reread >> fileofDestination;//We will need this file
	reread.close();//Closing the stream for now
	//We will update the threads file
	cout << "Now we'll update the file" << fileofDestination << endl;
	ifstream rereadagain(fileofDestination.c_str());
	ofstream writeagain("ttemporary.txt");
	rereadagain >> useless;
	writeagain << ++useless << endl;
	while (true){
		rereadagain >> numofinterest;
		if (rereadagain.eof()){
			break;
		}
		writeagain << numofinterest << endl;
		rereadagain >> title;
		writeagain << title << endl;
		rereadagain >> postingfile;
		writeagain << postingfile << endl;
		rereadagain >> letter;
		writeagain << letter << endl;
		rereadagain >> letter;
		writeagain << letter << endl;
	}
	rereadagain.close();
	writeagain.close();
	ofstream enrich("ttemporary.txt", ios::app);
	++B;//Now we're plus 1 thread
	enrich << endl << endl << B << endl;
	enrich << THEtitle << endl;
	enrich << THEpostingfile << endl;
	enrich << THEl << endl;
	enrich << THEs << endl;
	enrich.close();
	erase = fileofDestination.c_str();
	remove(erase);
	rename("ttemporary.txt", erase);
	cout << "DONE!" << endl;
}



int TheNumber(string title, string thefile){//The title of the thread,and the file to read our information from
	ifstream read(thefile.c_str());
	int number;
	string thistitle;
	char letter;
	read >> number;//Scanning the first number,that's useless
	while (true){
		read >> number;//The serial number,according to the file
		if (read.eof()){
			break;
		}
		read >> thistitle;//Scanning the title
		if (thistitle == title){//Found the title of the thread we're interested in
			return number;
		}
		read >> thistitle;//Now scanning the title of the file about the posts
		read >> letter >> letter;//Scanning the two letters;
	}
	return 0;
}



void MovePostToSubforum(string postline, string username,int& FD,int& SD,string thetitle){
	//MOVES A POST IN A SUBFORUM
	//postline-the line to be moved,username-its username
	//FD-the forum of destination
	//SD the subforum of destination
	cout << "Okay,in the moving function" << endl;
	string fileofOrigin, fileofDestination, whatever;
	int useless, numofinterest;
	ifstream read("number.txt");
	read >> useless;
	read >> useless;
	read >> useless;
	read >> numofinterest;
	while (numofinterest != FD){//Searching for the appropriate file of origin
		cout << "Searching..." << endl;
		read >> whatever;
		read >> whatever;
		read >> useless;
		read >> fileofOrigin;
		read >> numofinterest;
	}
	read >> whatever;
	read >> whatever;
	read >> useless;
	read >> fileofOrigin;//Got the file we need
	read.close();
	string threadsfile,title;
	ifstream reread(fileofOrigin.c_str());
	reread >> numofinterest;//We don't need this first number
	reread >> numofinterest;
	while (numofinterest != SD){
		reread >> title;
		reread >> threadsfile;
		reread >> numofinterest;
	}
	reread >> title;
	reread >> threadsfile;//We need this particular file
	reread.close();
	string postsfile;
	char letter;
	ifstream readagain(threadsfile.c_str());
	readagain >> useless;
	while (true){
		readagain >> useless;
		readagain >> title;
		if (title == thetitle){
			break;
		}
		readagain >> postsfile;
		readagain >> letter;
		readagain >> letter;
	}
	readagain >> postsfile;
	readagain.close();
	ofstream write(postsfile.c_str(), ios::app);
	write << username << endl;
	write << postline << endl;
	write.close();
	cout << "DONE!" << endl;
}

/*
void MovePostToThreadS(string postline, string username, int& FA, int& SB, string thetitle){
	//MOVES A POST FROM ONE THREAD TO ANOTHER,IN DIFFERENT SUBFORUMS
	//postline-the post to move,username
	//FA the forum we're in
	//SB the subforum of destination
	//thetitle-the thread's title
	int numofinterest, useless;
	string wanted, whatever;
	ifstream read("number.txt");
	read >> useless;
	read >> useless;
	read >> useless;
	read >> numofinterest;
	while (numofinterest != FA){//Searching for the appropriate file of origin
		read >> whatever;
		read >> whatever;
		read >> useless;
		read >> wanted;
		read >> numofinterest;
	}
	read >> whatever;
	read >> whatever;
	read >> useless;
	read >> wanted;//We got the file we need
	read.close();//Closing the stream for now
	string title, threadsfile;
	ifstream reread(wanted.c_str());
	reread >> numofinterest;//We don't need this first number
	reread >> numofinterest;
	while (numofinterest != SB){
		reread >> title;
		reread >> threadsfile;
		reread >> numofinterest;
	}
	reread >> title;
	reread >> threadsfile;//We need this particular file
	reread.close();
	string postsfile;
	char letter;
	ifstream readagain(threadsfile.c_str());
	readagain >> useless;
	while (true){
		readagain >> useless;
		readagain >> title;
		if (title == thetitle){
			break;
		}
		readagain >> postsfile;
		readagain >> letter;
		readagain >> letter;
	}
	readagain >> postsfile;
	readagain.close();
	ofstream write(postsfile.c_str(), ios::app);
	write << username << endl;
	write << postline << endl;
	write.close();
	cout << "DONE!" << endl;
}
*/

void MovePostToThreadT(string postline, string username, int& FD, string thetitle){
	//MOVES A POST IN A FORUM'THREAD
	//postline,username
	//FD,the forum's number
	//thetitle,the thread's title
	cout << "In the moving" << endl;
	string fileofOrigin, fileofDestination, whatever;
	int useless, numofinterest;
	ifstream read("number.txt");
	read >> useless;
	read >> useless;
	read >> useless;
	read >> numofinterest;
	while (numofinterest != FD){//Searching for the appropriate file of destination
		read >> fileofOrigin;
		read >> whatever;
		read >> useless;
		read >> whatever;
		read >> numofinterest;
	}
	read >> fileofOrigin;//We will need this file
	cout << "We'll update the file" << fileofOrigin << endl;
	read.close();//Closing the stream for now
	ifstream reread(fileofOrigin.c_str());
	char letter;
	string postingfile, title;
	reread >> useless;//Scanned the first number
	while (true){
		reread >> numofinterest;
		reread >> title;
		if (title == thetitle){
			break;
		}
		reread>> postingfile;
	    reread >> letter;
		reread >> letter;
	}
	reread >>postingfile;
	reread.close();
	ofstream write(postingfile.c_str(), ios::app);
	write << username << endl;
	write << postline << endl;
	write.close();
	cout << "DONE!" << endl;
}

/*void MovePostToThreadSUB(string postline, string username, int& FA, int& SB, string thetitle){
	//MOVEA A POST FROM A THREAD,IN A THREAD IN A SUBFORUM
	//postline,username
	//FA the forum we're in
	//SB subforum of destination
	//thetitle-the thread's title
	int numofinterest, useless;
	string wanted, whatever;
	ifstream read("number.txt");
	read >> useless;
	read >> useless;
	read >> useless;
	read >> numofinterest;
	while (numofinterest != FA){//Searching for the appropriate file of origin
		read >> whatever;
		read >> whatever;
		read >> useless;
		read >> wanted;
		read >> numofinterest;
	}
	read >> whatever;
	read >> whatever;
	read >> useless;
	read >> wanted;//We got the file we need
	read.close();//Closing the stream for now
	string title, threadsfile;
	ifstream readagain(wanted.c_str());//Open this file,to find the file with the information for the thread
	readagain >> numofinterest;//We don't need this first number
	readagain >> numofinterest;
	while (numofinterest != SB){
		readagain >> title;
		readagain >> threadsfile;
		readagain >> numofinterest;
	}
	readagain >> title;
	readagain >> threadsfile;//We need this particular file
	readagain.close();
	ifstream reread(threadsfile.c_str());
	char letter;
	string postingfile, title;
	reread >> useless;//Scanned the first number
	while (true){
		reread >> numofinterest;
		reread >> title;
		if (title == thetitle){
			break;
		}
		reread >> postingfile;
		reread >> letter;
		reread >> letter;
	}
	reread >> postingfile;
	reread.close();
	ofstream write(postingfile.c_str(), ios::app);
	write << username << endl;
	write << postline << endl;
	write.close();
	cout << "DONE!" << endl;
}
*/
