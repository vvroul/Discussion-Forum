#include <list>
#include "Forum.h"
#include "Subforum.h"

namespace System
{

	int LastForumID;
	int LastThreadID, MAXTHREADSIZE;
	int LastPostID, MAXPOSTSIZE;
	int MAXUSERNAMESIZE, MAXPASSWORDSIZE;


	//class Forum;
	//class User;

	std::list<int> Forums;

	void ExitSystem();
}