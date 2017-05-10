#include <iostream.h>


void Hannoi(int n,char x,char y,char z)  //
{
	if (n==1)
	{
		cout<<x<<"----"<<y<<endl;
	}

	else
	{
		Hannoi(n-1,x,z,y);

		cout<<x<<"----"<<y<<endl;

		Hannoi(n-1,z,y,x);
	}

}


void main()
{
	int n = 3;

	cout<<"´ÓAµ½B"<<endl;
	Hannoi(n,'A','B','C');
}






