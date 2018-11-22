#ifndef _FORUM
#define _FORUM

#include <string>
#include <list>
#include "Subforum.h"


class Forum
{
	protected:
		
 	
	private:	
		std::list<Subforum*> subForums;
		std::string title;
		std::list<Thread*> threads;
		int ID;
	

	public:
		//Forum();
		Forum(std::string  , int , int , std::string, int , int , std::string);
		Forum(std::string thetitle, int& theID){
			title = thetitle;
			ID = theID;
		}
		~Forum();
		//void print(){
		//std::cout << title << std::endl;
		//}

		void visit(char& , std::string , std::string,std::string,int&);
		void print(){
			std::cout << title << std::endl;
			std::cout << "ID:" << ID << std::endl;
		}
		int returnmyID(){
			return ID;
		}
};

#endif