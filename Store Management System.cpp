#include<iostream>
#include<conio.h>
#include<fstream>
#include<string.h>
long id=11811974;//to generete id
using namespace std;
class Customer//date type for customer
{ 
    public:
	char name[10];
	char pwd[20];
	long c_id;
};
class item //data type item
{
	public:
	char name[20];
	int price;
	int qt;
};
void NewCustomer()
{
    ifstream fd("help.txt",ios::in);//to read the file
    fd>>id;
    fd.close();
	ofstream file("Customer.txt",ios::binary|ios::app);
	cout<<"\n Enter your Name "<<endl;
	char name[10];
	cin>>name;
	fflush(stdin);//file flush , clear the next input and considure the the privious input
	cout<<"Enter Your password\n";
	fflush(stdin);
	char pwd[20];
	cin>>pwd;
	cout<<"Hi, "<<name<<" your Customer id1 is "<<id;
	Customer c;
	strcpy(c.name,name);
	strcpy(c.pwd,pwd);
	c.c_id=id;
	file.write((char *)&c,sizeof(c));//to write in binary mode / (char*)& type casting &obj 
	file.close();
	id++;
	ofstream fd1("help.txt",ios::out);
    fd1<<id;
    fd1.close();
}
void shop()
{
	    system("cls");//clear the screen
		ifstream f1("item.txt",ios::binary);
		item i;
		int n=0;
		f1.seekg(0,ios::beg);//begning of the current cursre
		while(f1.read((char *)&i,sizeof(i)))//file pointer increse,return Null
		{
			n++;
			cout<<n<<". "<<i.name<<"     "<<i.price<<" "<<i.qt<<endl;
		}
		f1.close();
		int sum=0;//for total amount
		while(1)//always true
		{
		cout<<"Enter item you want to purchase."<<endl;
		int it;
		cin>>it;
		if(it>n||it<1)
		{
			cout<<"Invalid choice .\nTry Again"<<endl;
		}
		else
		{
			ifstream f1("item.txt",ios::binary);
			f1.seekg((it-1)*sizeof(i),ios::beg);//read pointer,begning of current cursre
			f1.read((char*)&i,sizeof(i));// type casting &obj
			f1.close();
			cout<<"Enter the Quantity of "<<i.name<<" You want to purchase."<<endl;
			int Qn;
			cin>>Qn;
			if(Qn>i.qt)
			{
				cout<<"Insufficient Qunatity,Try Something Else."<<endl;
			}
			else
			{
			sum+=Qn*i.price;//sum=sum+
			i.qt-=Qn;
		    }
		    ofstream f2("item.txt",ios::binary|ios::app);
			f2.seekp((it-1)*sizeof(i),ios::beg);//write pointer //curent curser
			f2.write((char*)&i,sizeof(i));
			f2.close();
		}
		cout<<"Enetr 1 if want to purcahase more items.Else enter other value."<<endl;
		int ent;
		cin>>ent;
		if(ent!=1)
		{
		cout<<"Total Amount of bill is "<<sum<<endl;
		f1.close();
				return;
	    }
	}
	f1.close();
}
void login()
{
	 int count=0;
	cout<<"Enetr your customer id\n";
	long id1;
	cin>>id1;
	cout<<"Enter your password\n";
	char pwd[20];
	cin>>pwd;
	Customer c;
	int n=0;
	ifstream file("Customer.txt",ios::binary);
	while(file)//return true if not at end
	{
		n++;
		file.read((char *)&c,sizeof(c));
		if(strcmp(c.pwd,pwd)==0 && c.c_id==id1)
		{
			count=1;
			cout<<"Hi, "<<c.name<<" You are Sucessfully logged in.\n"<<endl;
			shop();
			break;
		}
	}
	if(n==0)
	cout<<"No Users Found"<<endl;
	if(count==0)
	cout<<"No record found.\n";//ahead
	file.close();
}
Customer adm={"Sultan","T",11811974};
void add()
{
	while(1)
	{
	item i;
	cout<<"Enter name of item"<<endl;
	fflush(stdin);
	cin>>i.name;
	fflush(stdin);
	cout<<"Enter price for each item"<<endl;
	cin>>i.price;
	cout<<"Enter Quantity"<<endl;
	cin>>i.qt;
	ofstream fi("item.txt",ios::binary|ios::app);
	fi.write((char*)&i,sizeof(i));
	fi.close();
	int it;
	cout<<"Enetr 1 to Add more items.Else Something Else."<<endl;
	cin>>it;
	if(it!=1)
	break;
}
}
void update()
{
	while(1)
	    {
		ifstream f1("item.txt",ios::binary);//input write
		item i;
		int n=0;
		while(f1.read((char*)&i,sizeof(i)))
		{
			n++;
			cout<<n<<". "<<i.name<<"     "<<i.price<<" "<<i.qt<<endl;
		}
		f1.close();
		if(n==0)
		{
			cout<<"No Items Found."<<endl;
			break;          
		}
		int i1;
		cout<<"Enetr the item you want to update"<<endl;
		cin>>i1;
		if(i1>n||i1<1)
		{
			cout<<"Invalid input"<<endl;
			break;
		}
		fstream f("item.txt",ios::binary|ios::app);
		cout<<"Enter name of item"<<endl;
     	fflush(stdin);//to clean entred file
    	cin>>i.name;
      	fflush(stdin);
      	cout<<"Enter price for each item"<<endl;
    	cin>>i.price;
 	    cout<<"Enter Quantity"<<endl;
    	cin>>i.qt;
        f.seekp((i1-1)*sizeof(i),ios::beg);
        f.seekg((i1-1)*sizeof(i),ios::beg);
    	f.write((char*)&i,sizeof(i));
    	cout<<"Item Updated"<<endl;
    	f.close();
    	cout<<"Enter 1 to update more items.Else Somethin Else."<<endl;
    	cin>>n;
    	if(n!=1)
    	return;
    }
}
void delet()
{
	while(1){
		ifstream fi("item.txt",ios::binary|ios::in);
		item i;
		int n=0;
		while(fi.read((char*)&i,sizeof(i)))
		{
			n++;
			cout<<n<<". "<<i.name<<"     "<<i.price<<" "<<i.qt<<endl;
		}
		if(n==0)
		{
			cout<<"No Items Found."<<endl;
			break;          
		}
		int t=1,t2=n;
		cout<<"Enetr the item you want to delete"<<endl;
		cin>>n;
		if(t2<n||n<0)
		{
			cout<<"Invalid Input"<<endl;
			getch();
			break;
		}
		fi.close();
		ifstream f("item.txt",ios::binary);
		ofstream f1("temp.txt",ios::binary);
		while(f.read((char*)&i,sizeof(i)))
		{
			if(t==n);
			else
			f1.write((char*)&i,sizeof(i));
			t++;
	      }
	      f.close();
	      f1.close();
	      remove("item.txt");
	      rename("temp.txt","item.txt");
	      cout<<"Enter 1 to update more items.Else Somethin Else."<<endl;
    	cin>>n;
    	if(n!=1)
    	return;
	}
}
void Admin()
{
    	system("cls");
	ifstream f("admin.txt",ios::in);
	Customer admin1;
	f.read((char *)&admin1,sizeof(admin1));
	f.close();
	cout<<"Enetr Admin Name"<<endl;
	char name[20];
	fflush(stdin);
	gets(name);
	fflush(stdin);
	cout<<"Enetr id"<<endl;
	int aid;
	fflush(stdin);
	cin>>aid;
	fflush(stdin);
	cout<<"Enetr password"<<endl;
	char pass[20];
	fflush(stdin);
	gets(pass);
	if(strcmp(name,admin1.name)==0&&aid==admin1.c_id&&strcmp(pass,admin1.pwd)==0)
	{
		while(1)
		{
		system("cls");
		cout<<"1.Add item."<<endl;
		cout<<"2.Update item"<<endl;
		cout<<"3.Delete Item"<<endl;
		cout<<"4.Main Menu."<<endl;
		int ch;
		cout<<"Enetr your choice"<<endl;
		cin>>ch;
		switch(ch)
         	{
		case 1:
			add();
			break;
		case 2:
			update();
			break;
		case 3:
		    delet();
			break;
		case 4:
			return;
			break;
		default:
			cout<<"Invalid Choice";
         	}
         	getch();
             }
	   }
	else
	{
		cout<<"No Record Found.Sorry,\nYou may Try next Time"<<endl;
	
	}
		getch();
}
int main()
{
	ofstream f("admin.txt",ios::binary);
 	f.write((char *)&adm,sizeof(adm));
 	f.close();
 while(1)
 {
 	system("cls");
	cout<<"1.New Customer\n";
	cout<<"2.Administrator\n";
	cout<<"3.Login\n";
	cout<<"4.Exit\n";
	int choice;
	cout<<"Enter your choice."<<endl;
	cin>>choice;
	system("cls");
	switch(choice)
	{
		case 1:
			NewCustomer();
			break;
		case 2:
			Admin();
			break;
		case 3:
		  login();
			break;
		case 4:
			exit(0);
			break;
		default:
			cout<<"Invalid Choice";
	}
	getch();
  }
  return 0;
}
