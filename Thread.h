#ifndef _THREAD
#define _THREAD

#include <string>
#include "Post.h"


class Thread
{
private:
	std::string title;
	bool sticky;
	bool locked;
	int ID; //subforum's ID
	//std::string postfile;
	Post post;


public:
	Thread(std::string, std::string, int&);
	Thread(std::string, int, int, std::string, char&, char&);
	Thread() :post()
	{
		;
	}
	~Thread();
	////NEW STUFF
	void operator=(Thread&);
	void visit(char&);
	void deletemyposts();
	void print(){
		std::cout << title << std::endl;
	}
	int returnmyID(){
		return ID;
	}
	void ChangemyTitle(const char*, std::string);
	void ChangemyTitle(std::string newtitle){
		title = newtitle;
	}
	bool ISsticky(){
		return sticky;
	}
	bool ISlocked(){
		return locked;
	}
	void stick_it(){
		sticky = true;
	}
	void lock_it(){
		locked = true;
	}
	void unstick_it(){
		sticky = false;
	}
	void unlock_it(){
		locked = false;
	}
	std::string returnmyTitle(){
		return title;
	}
	//void Post();
};
#endif