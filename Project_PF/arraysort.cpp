#include <iostream>
#include <ctime>
#pragma warning(disable : 4996)
using namespace std;

int main() 
{
	time_t now;
	struct tm nowLocal;
	now = time(NULL);//Getting time from OS
	nowLocal = *localtime(&now);
	cout << "DATE " << nowLocal.tm_mday << " /" << nowLocal.tm_mon + 1<<" /" << nowLocal.tm_year + 1900<<endl;
	cout << "TIME " << nowLocal.tm_hour << ": " << nowLocal.tm_min << ": " << nowLocal.tm_sec;
	return 0;
	
}