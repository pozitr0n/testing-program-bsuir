#include "common.h"
#include "test.h"

using namespace std;

int main()
{	
	setlocale(LC_ALL, "russian_russia");	
	string name;
	cout<<"Ââåäèòå âàøå èìÿ: ";
	cin>>name;
	CTest test(name);
	if(test.Open("test1.txt", "answer1.txt"))
		test.RunTest();
	else
		_getch();
	return 0;
}
