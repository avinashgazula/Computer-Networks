#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
int main()
{
	int c;
	c=0;
	cout<<"This is statement 1\n";
	c=fork();
	if(c>0)
	{
		cout<<"This is statement 2\n";
		wait();
		cout<<"This is statement 5\n";
	}
	else
	{
		cout<<"This is statement 3\n";
	}
	return 0;
}