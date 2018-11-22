#ifndef _POST
#define _POST

#include <string>


class Post {
private:
	std::string nameFile;
public:
	//std::string content;
	Post(std::string);
	Post(){
		;
	}
	void operator=(Post&);
	void posting();
	void print();
	std::string myFileName(){
		return nameFile;
	}
};



#endif