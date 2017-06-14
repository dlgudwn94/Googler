#include "ExtFilter.h"

extFilter::extFilter(){
	init();
}

extFilter::~extFilter(){
	if(list==NULL)return;
	node *np;
	do{
	np=list;
	list=list->next;
	delete np;
	}while(list!=NULL);
}

int extFilter::init(){
	flg=0;
	list=NULL;
	file.open(EXTFILTER_FILE,ios::in);
	if(!file.is_open())return 1;
	char buf[16] = { 0, };
	last=0;
	node *np;
	flg=1;
	list= new node;
	np=list;
	np->next=NULL;
	while(!file.eof()){
		file.getline(buf,16);
		if (strcmp(buf, "\0") != 0) {
			if (last == 50) {
				last = 0;
				np->next = new node;
				np = np->next;
				np->next = NULL;
			}
			np->ary[last].append(buf);
			last++;
		}
	}
	file.close();
	return 0;
}
int extFilter::checkName(string name){
	if(flg==0)return 0; //초기화 되지 않음
	int pointer=name.find_last_of('.');
	if (pointer>=0) name=name.substr(pointer+1,name.length());
	node *np;
	int i;
	np=list;
	do{
		if (np->next != NULL) {
			for (i = 0; i < 50; i++) {
				if (name.compare(np->ary[i]) == 0)return 1;
			}
		}
		else {
			for (i = 0; i < last; i++) {
				if (name.compare(np->ary[i]) == 0)return 1;
			}

		}
		np=np->next;
	}while(np!=NULL);
	return 0;
}
int extFilter::addFilter(string ext){
	file.open(EXTFILTER_FILE,ios::out|ios::app);
	if(!file.is_open())return 1;
	file.write(ext.c_str(),ext.length());
	file.put('\n');
	file.close();
	node *np;
	if(list==NULL){
		list=new node;
		list->next=NULL;
		last=0;
		np=list;
	}else{
		np=list;
		while(np->next!=NULL)np=np->next;
	}
	if(last==50){
		np->next=new node;
		np=np->next;
		np->next=NULL;
		np->ary[0].append(ext);
		last=1;
	}else{
		np->ary[last].append(ext);
		last++;
	}
	return 0;
}
void extFilter::showFilter(){
	node *np;
	int i;
	np=list;
	cout<<"[Filter-List-Start]"<<endl;
	do{
		if(np->next!=NULL){
			for(i=0;i<50;i++){
				cout<<np->ary[i]<<endl;
			}
		}else{
			for(i=0;i<last;i++){
				cout<<np->ary[i]<<endl;
			}
		}
		np=np->next;
	}while(np!=NULL);
	cout<<"[Filter-List-End]"<<endl;
}