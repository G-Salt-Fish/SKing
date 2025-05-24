#include "SKing.h"

#include <limits>

using namespace std;
int main()
{
	
	sk::Int i{ 11ULL };
	string s;
	s = i;
	cout << i + s << endl << s + i;
	pause;
	cin.ignore(string::npos,'\n');

	return 0;
}
