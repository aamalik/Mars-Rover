#include <iostream>
#include <string>
#include "Connection.hh"

using namespace std;

// XP2: To whoever will use this code in XP3: we are deeply sorry that we had no right to replace most of the horrible things that previous group left before us. 
//      Even though it is complete crap, we ensured it works, so please, don't play with it, even though you'd really love to.

int main() {

	Connection conn("localhost",17676,"extra/brainfiles/test1.asm");
	conn.acceptMessage();
	
	return 0;
}
