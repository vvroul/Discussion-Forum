/* #ifndef _USER
#define _USER

#include <string>
//

class User
{
	std::string userType;


	public : 
		User();
		~User();
	

		void Registration(std::string const& userName, std::string const& password);
		 void ForumVisit();
		void CreateThread();
		void Reply();

		void DeleteThread();
		void DeletePost();
		void LockThread();
		void PinPost();
	
	private : 
		int userID;
		std::string password, userName;

};

#endif

*/