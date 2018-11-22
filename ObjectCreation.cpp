#include <iostream>
#include <fstream>
#include <string>
#include "Forum.h"
#include "Post.h"

using namespace std;


Forum::Forum(string t, int i, int j, string inputfiles, int id, int v, string threadfiles)   // i (forums) , j(subforum threads) , v(forum threads)
{
	int k, m;											// k (subforums) , m(threads in the forum)
	ifstream con(inputfiles.c_str());					//file with subforums titles and thread stuff  ADDITION BY ME!!!!!!!!!!!!!!!!!!!!!
	ifstream com(threadfiles.c_str());					//file with threads titles that belong to forum
	string myString, fileName, theString, tfileName;	// myString (subforum's name)  , fileName (input file information about posts) , theString(thread's name) , tfileName(input file information about posts of forum's threads)
	cout << i << endl;
	cout << j << endl;
	title = t;
	con >> k;											//give k the first number in inputfiles (how many subforums in the forum) 
	com >> m;											//give m the first number in forumthreads (how many threads in the forum)
	cout << k << endl;
	cout << "A forum with title : " << " $$ " << t << " $$ " << " created " << endl;
	cout << "Number of forums : " << i << endl;
	ID = id;

	//FORUM THREADS
	for (int a = 0; a < m; ++a)
	{
		char Locked, Sticky;
		int serialnumber;	//Thread's serial number for input file
		cout << "Forum's threads , before subforum's threads........ " << endl;
		com >> serialnumber;
		com >> theString;
		com >> tfileName;
		com >> Locked;
		com >> Sticky;
		Thread* mytList = new Thread(theString, id, a + 1, tfileName, Locked, Sticky);
		threads.push_back(mytList);
		cout << "Thread inside list " << endl;
	}

	cout << "Going to place the sticky threads to the appropriate position " << endl;
	list<Thread*>::iterator b, g; //If a thread is sticky , it must be placed at the top of the list
	bool in = false;
	b = threads.begin();
	while (b != threads.end())
	{
		g = b; //Save iterator's value
		cout << "In da loop " << endl;
		if ((*b)->ISsticky())
		{
			in = true;
			++g; //moving to next item
			cout << "In da if " << endl;
			Thread* newthread = (*b);
			cout << "Sticky thread found " << endl;
			(*newthread) = (*(*b));//Copying the item
			threads.remove(*b);//Removing the item
			cout << "Out of pointers " << endl;
			threads.push_front(newthread);//Pushing the copy of the item at the front of the list
			cout << "Sticky thread placed at the top of the list " << endl;
			b = g;
		}

		if (!in)	//We didn't find a sticky thread
		{
			++b;
		}
		else        //We found a sticky thread
		{
			in = false;
		}
	}



	//SUBFORUMS
	for (int a = 0; a < k; ++a)
	{
		int serialnumber; //Subforum's serial number in input file
		con >> serialnumber;
		con >> myString;
		con >> fileName;
		Subforum* mypList = new Subforum(myString, id, a + 1, fileName, ID);
		subForums.push_back(mypList);
		cout << "Object inside list" << endl;
	}
}



Forum::~Forum()
{
	cout << "In the forum destructor" << endl;
	list<Subforum*>::iterator i;
	for (i = subForums.begin(); i != subForums.end(); ++i){
		cout << "I'm the for that destroys the list of subforums" << endl;
		delete *i;
	}
	cout << "Forum destroyed" << endl;
}



Subforum::Subforum(string t, int j, int b, string name, int id)   //t (title)  , j(forum number) , b(subforum number) , name(input post..)
{
	ifstream thra(name.c_str());
	char Locked, Sticky;
	int p, serialnumber;					// p (number of threads) , serialnumber(Subforum's threads serial number for input file)
	string myString, postingName;			// myString (thread's name) , postingName (file for posting)
	thra >> p;
	title = t;
	cout << "A Subforum with title : " << " $$ " << t << " $$ " << " created " << endl;

	cout << "Number of threads " << p << endl;
	ID = j;


	for (int a = 0; a < p; ++a)
	{
		thra >> serialnumber;
		thra >> myString >> postingName;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		thra >> Locked;
		thra >> Sticky;
		Thread * mypThread = new Thread(myString, ID, a + 1, postingName, Locked, Sticky);			//a+1 (number of threads)
		threads.push_back(mypThread);
		cout << "A thread inside subforum " << endl;
	}

	cout << "Going to place the sticky threads to the appropriate position " << endl;
	list<Thread*>::iterator i, g; //If a thread is sticky , it must be placed at the top of the list
	bool in = false;
	i = threads.begin();
	while (i != threads.end())
	{
		g = i; //Save iterator's value
		cout << "In da loop " << endl;
		if ((*i)->ISsticky())
		{
			in = true;
			++g; //moving to next item
			cout << "In da if " << endl;
			Thread* newthread = (*i);
			cout << "Sticky thread found " << endl;
			(*newthread) = (*(*i));//Copying the item
			threads.remove(*i);//Removing the item
			cout << "Out of pointers " << endl;
			threads.push_front(newthread);//Pushing the copy of the item at the front of the list
			cout << "Sticky thread placed at the top of the list " << endl;
			i = g;
		}

		if (!in)	//We didn't find a sticky thread
		{
			++i;
		}
		else        //We found a sticky thread
		{
			in = false;
		}
	}

}


Subforum::Subforum(std::string thetitle, int& ForumID){
	title = thetitle;
	ID = ForumID;
	cout << "A new,empty subforum has been created" << endl;
}



Subforum::~Subforum()
{
	cout << "In the subforum destructor" << endl;
	list<Thread*>::iterator i;
	for (i = threads.begin(); i != threads.end(); ++i){
		(*i)->deletemyposts();//ADDITION TO THE DESTRUCTOR
		cout << "In the for that destroys the list of threads" << endl;
		delete *i;
	}
	cout << "Subforum destroyed" << endl;
}


Thread::Thread(string t, int l, int n, string postingName, char& Locked, char& Sticky) : post(postingName)  // t(title) , l (ID) , n (number of thread)
{
	cout << "In the thread constructor" << endl;
	title = t;
	ID = l;
	cout << Locked << endl;
	if (Locked == 'L')
	{
		locked = true;
		cout << "The thread is locked " << endl;
	}
	else
	{
		locked = false;
		cout << "Thread not locked " << endl;
	}
	if (Sticky == 'S')
	{
		sticky = true;
		cout << "The thread is sticky " << endl;
	}
	else
	{
		sticky = false;
		cout << "Thread not sticky " << endl;
	}
	cout << "A Thread with title : " << " $$ " << t << " $$ " << " created " << endl;
}


Thread::Thread(string thetitle, string postingfile, int& theID) :post(postingfile){
	title = thetitle;
	ID = theID;
	sticky = false;
	locked = false;
}


Thread::~Thread()
{
	cout << "Thread destroyed " << endl;
}


Post::Post(string postingName)
{
	//Constructor
	nameFile = postingName;
	cout << "Post created and the file is : " << postingName << endl;
}




/*
Debugging session#3
-Φτιάχτηκαν οι constructors ώστε να μοιράζονται τα σωστά IDs σε subforums και threads.








*/