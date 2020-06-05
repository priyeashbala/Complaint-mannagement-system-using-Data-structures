#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<sstream>
#include<fstream>

using  namespace std;
int index=1000,index_hard[100],index_soft[100],index_conn[100],j=0;
class comp
{
	public: 
	int cid;
	char ctype[30],stat[50],nf[30];  //complaint attributes
}c;
string st1 = "regd";  //filename definition
string st11="proc";
string st111 = "finish";
string st2=".dat"; //filename extension
fstream f1;
fstream f2;
fstream f3;
fstream f4;
fstream f5;
fstream f6;
int welcome()
{
	int i;
	cout<<"1 - Customer login \n2 - Executive login\n3 - Exit\n";
	cout<<"Enter the option\n";
	cin>>i;
return i;
}
	
	
void new_complaint()
{
comp a;    //complaint class object
int o; char p;
string s;
cout<<"Choose the type of complaint\n";
cout<<"1 - Hardware issues\n2 - Software issues\n3 - Connectivity issues\n";    //choose the complaint type
cin>>o;
a.cid = index++;
if(o==1)
{
	strcpy(a.ctype,"Hardware issues");
	f2.open("ID_hard.txt",ios::app);
	f2<<a.cid;
	f2<<" ";
	f2.close();
}
	
if(o==2)
{
	strcpy(a.ctype,"Software issues");
	f2.open("ID_soft.txt",ios::app);
	f2<<a.cid;
	f2<<" ";
	f2.close();
}
if(o==3)	
{
	strcpy(a.ctype,"Connectivity issues");
	f2.open("ID_conn.txt",ios::app);
	f2<<a.cid;
	f2<<" ";
	f2.close();
}
strcpy(a.stat,"Registered");  //status of complaint as registered
cout<<"Complaint has been successfully registered\n";
cout<<"Your complaint ID is: "<<a.cid;  //display complaint ID to the customer

stringstream ss;
ss<<a.cid;
string src = st1+ss.str()+st2;  //using stringstream, appropriate filename is created for the complaint ID


f1.open(src.c_str(),ios::binary|ios::out);  //create a new file for given complaint

if(!f1)
{
	cout<<"cannot open file!\n";
}
else
{
	f1.write((char *)&a, sizeof(a));   //complaint details are written in the binry file
	
	
}
f1.close();		//close the file stream


stringstream ss1;
ss1<<(a.cid)-1;   

	string prev_src = st1+ss1.str()+st2;         //to add the next filename to the previous one from the second file

	f1.open(prev_src.c_str(),ios::binary|ios::in);  
	if(f1.good())
	{
	
	if(f1)
	{
		
		f1.read((char *) &a, sizeof(comp));
		strcpy(a.nf,src.c_str());
	}
	f1.close();
	f1.open(prev_src.c_str(),ios::binary|ios::out);
	if(f1)
	{
		f1.write((char *)&a, sizeof(comp));	
	}
	f1.close();
	prev_src="";
	src="";
	} 

}

void status(int id)
{
	comp b;
	stringstream ss1;
	ss1<<id;
	string src= st1+ss1.str()+st2;
	f1.open(src.c_str(),ios::binary|ios::in);
	if(!f1)
		cout<<"Cannot open the file\n";
	else
	{
	f1.read((char *) &b, sizeof(b));
	cout<<"\nThe complaint details are as follows :-\n";
	cout<<"Complaint ID : "<<b.cid<<endl;
	cout<<"Complaint type : "<<b.ctype<<endl;
	cout<<"Complaint status : "<<b.stat<<endl<<endl;
	//cout<<"Next file : "<<b.nf<<endl;
	
	}
f1.close();
}

void executive()
{
	comp b;
	int exec_index=1000,u;
	char z='y';
	cout<<"Press 1- to go through the complaints and solve them\nPress 2- to view the status of a complaint using its ID\nPress 3- to view category wise complaints\n";
	cin>>u;
	if(u==1)
	{
	while(z=='y'||z=='Y')
	{
	f4.open("ID_no_exec.txt",ios::in);
	if(f4)
	{
		f4>>exec_index;
	}
	stringstream ss2;
	ss2<<exec_index;
	f4.close();

	string src=  st1+ss2.str()+st2;   //for building file's name
	f5.open(src.c_str(),ios::binary|ios::in);
	if(f5)
	{
		f5.read((char *)&b, sizeof(b));
		cout<<"The complaint details are as follows :-\n";
		cout<<"Complaint ID : "<<b.cid<<endl;
		cout<<"Complaint type : "<<b.ctype<<endl;
		cout<<"Complaint status : "<<b.stat<<endl;
		f5.close();
		
		f4.open("ID_no_exec.txt",ios::out);
		f4<<(b.cid+1);
		f4.close();
		
		cout<<"Do you want to add this to processing (1) or completed list (2) ?\n";
		int o;
		cin>>o;
		if(o==1)
		{
			strcpy(b.stat,"Processing");
		}
		if(o==2)
		{
			strcpy(b.stat,"Completed");
		}		
	
			f3.open(src.c_str(),ios::binary|ios::out);
			f3.write((char *)&b,sizeof(b));
			f3.close();
	}
	cout<<"Do you want to check further complaints (Y/N) ? \n";
	cin>>z;
}
}

else if(u==2)
{
	int id;
	cout<<"Enter the complaint ID to check the status : ";
	cin>>id; cout<<"\n";
	status(id);
}

else
{
	cout<<"Enter 1- to view hardware complaints\nEnter 2- to view software complaints\nEnter 3-to view connectivity complaints\n";
	int r;
	cin>>r;
	if(r==1)
	{
	
	int p=0;
	f6.open("ID_hard.txt",ios::in);
	while(f6)
	{
		f6>>index_hard[p++];
	}
	index_hard[p]=0;	
	f6.close();
	p=0;
	while(index_hard[p]!=0)
	{
		status(index_hard[p++]);	
	}
	
	}
	else if(r==2)
	{
	int p=0;
	f6.open("ID_soft.txt",ios::in);
	while(f6)
	{
		f6>>index_soft[p++];
	}
	index_soft[p]=0;	
	f6.close();
	p=0;
	while(index_soft[p]!=0)
	{
		status(index_soft[p++]);	
	}
	}
	else if(r==3)
	{
	int p=0;
	f6.open("ID_conn.txt",ios::in);
	while(f6)
	{
		f6>>index_conn[p++];
	}
	index_conn[p]=0;	
	f6.close();
	p=0;
	while(index_conn[p]!=0)
	{
		status(index_conn[p++]);	
	}
	}
	
}

}

int main()
{
	f2.open("ID_no.txt",ios::in);
	if(f2)
	{
		f2>>index;
	}
	f2.close();
	int i;
	i=welcome();
	while(i!=3)
	{
	switch(i)
	{
		case 1: int c;
				
				
				cout<<"\t\t\t Welcome to the Customer login\n";
				cout<<"1 - Register a new complaint\n2 - Check the status of a complaint\n";
				cout<<"Enter the option\n";
				cin>>c;
				switch(c)
				{
					case 1: new_complaint();
							//cout<<"Complaint_portal\n";
							f2.open("ID_no.txt",ios::out);
							f2<<index;
							f2.close();																														
							break;
							
					case 2: int id;
							cout<<"Enter the complaint ID to check the status : ";
							cin>>id; cout<<"\n";

							status(id);
							//cout<<"Status portal";
							break;
					default: cout<<"Please enter a valid option\n";
				}
				break;
		case 2: cout<<"\t\t\t Executive login \n";
				executive();
				break;
				
		case 3: exit(0);
				break;
		default: cout<<"Please enter a valid option\n";
	}
	
	cout<<"\n\n";
	i=welcome();
	}
	return 0;
}

