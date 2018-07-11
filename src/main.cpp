#include <iostream>

#include "includes/types.h"

using namespace std;

int main()
{
	Position pos = { 1,2,3 };
	cout << float(pos.x) << endl;
	return 0;
}