#include<iostream>
#include<fstream>
using namespace std;
int my_strcmp(char arr1[], char arr2[])
{
	int x = 0;
	while (arr1[x] != '\0' || arr2[x] != '\0')
	{
		if (arr1[x] == arr2[x])
			x++;
		else
			return -1;
	}
	return 0;
}
int main()
{
	cout << "yess";
	char ar1[15];
	cin >> ar1;
	char ar2[15];
	cin >> ar2;

	cout << my_strcmp(ar1, ar2);
	system("pause");
	return 0;
}