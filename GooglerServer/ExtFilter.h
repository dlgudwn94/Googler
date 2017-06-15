#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define EXTFILTER_FILE "filter.dat" 

class node{
public:
	string ary[50];
	node *next;
};
class extFilter{
public:
	extFilter();
	~extFilter();
	int checkName(string name);
	int addFilter(string ext);
	void showFilter();
private:
	int init();
	fstream file;
	node* list;
	int flg;
	int last;
};