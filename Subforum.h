#ifndef _SUBFORUM
#define _SUBFORUM

#include <string>
#include <list>
#include "Thread.h"

class Subforum
{
private:
	std::string title;
	int ID; //forum's iD
	std::list<Thread*> threads;


public:
	//Subforum();
	Subforum(std::string, int, int, std::string, int);
	Subforum(std::string, int&);
	~Subforum();

	void visit(char&, std::string, std::string, std::string);
	void print(){
		std::cout << title << std::endl;
		std::cout << "ID:" << ID << std::endl;
	}
	int returnmyID(){
		return ID;
	}

	void ChangemyTitle(const char*, std::string);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	void ChangemyTitle(std::string newtitle){
		title = newtitle;
	}
	void deleteMe();
};

#endif