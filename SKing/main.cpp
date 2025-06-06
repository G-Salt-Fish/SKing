#include "SKing.h"

int main()
{
	using namespace sk;
	Int a, b;
	cout.setf(ios_base::boolalpha);
	while (cin >> a >> b)
	{
		cout << bool(a >= b) << endl;
	}
	
	pause;
	return 0;
}
