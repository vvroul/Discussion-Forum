#include <string>
#include <list>
#include "User.h"
#include "Forum.h"


//HANDLERS
void ForumVisit(char, std::string);
void SubforumVisit(char);
void ThreadVisit(char);


//FORUM
void VisitTheForum(char&);

//SUBFORUM
void CreateSubforum();
std::string ChangeSubforumTitle(std::string t, std::string filename, int linumber);
void DeleteSubforum();
void MoveSubforum();


//POST
void DeletePost();
void MovePostToSubforum(std::string , std::string, int&,int&, std::string);
//void MovePostToThreadS(std::string, std::string, int&, int&, std::string);
void MovePostToThreadT(std::string, std::string, int&, std::string);
//void MovePostToThreadSUB(std::string , std::string , int&, int&, std::string);

//THREAD
void DeleteThread();
std::string ChangeThreadTitle(std::string);
void MoveThread();


//USER
void UserCatalog();
void ChangeUserCategory();
void DeleteUser();
void ChangeUsername();
void ChangePassword();
void SavenExit();


//GENERAL
void ExitSystem();
bool decipher_the_answer(char *answer);
void Registration(std::string name, std::string pass, char&);
void fix_the_files_subforums(std::string, int&);
void fix_the_files_threads_delete(std::string, int&);
void fix_the_files_threads_sticky(std::string, int&, char);
void fix_the_files_threads_locked(std::string, int&, char);
void UniverseConstruction(std::list<Forum*>&);
void UniverseDestruction(std::list<Forum*>&);
void MoveSubforum(int&, int&, int&, int&);
void MoveThreadToSubforum(std::string, int&, int&, int&, int&);
void MoveThreadToForum(int&, int&, int&, int&);
void MoveThreadFSTS(int&, int&, int&, int&, int&, int&);
void MoveThreadFFTS(int&, int&, int&, int&, int&);
void MoveThreadFSTF(int&, int&, int&, int&, int&);
int TheNumber(std::string, std::string);