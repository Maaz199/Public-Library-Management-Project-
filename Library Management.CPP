#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>
class book
{
  char bno[6];
  char bname[50];
  char aname[20];
 public:
  void create_book()
    {
      cout<<endl<<"NEW BOOK ENTRY...\n";
      cout<<endl<<"Enter The book no.";
      cin>>bno;
      cout<<endl<<endl<<"Enter The Name of The Book ";
      gets(bname);
      cout<<endl<<endl<<"Enter The Author's Name ";
      gets(aname);
      cout<<endl<<endl<<endl<<"Book Added in record...";
    }
  void show_book()
    {
      cout<<endl<<"Book no. : "<<bno;
      cout<<endl<<"Book Name : ";
      puts(bname);
      cout<<endl<<"Author Name : ";
      puts(aname);
    }
  void modify_book()
    {
      cout<<endl<<"Book no. : "<<bno;
      cout<<endl<<"Modify Book Name : ";
      gets(bname);
      cout<<endl<<"Modify Author's Name of Book : ";
      gets(aname);
    }
  char* retbno()
    {
      return bno;
    }
  void report()
    {
      cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
    }
};
class student
{
  char admno[6];
  char name[20];
  char stbno[6];
  int token;
 public:
  void create_student()
    {
      clrscr();
      cout<<endl<<"NEW CUSTOMER ENTRY...\n";
      cout<<endl<<"Enter ID no. ";
      cin>>admno;
      cout<<endl<<endl<<"Enter The Name of The Customer ";
      gets(name);
      token=0;
      stbno[0]='/0';
      cout<<endl<<endl<<"Customer Record Created..";
    }
  void show_student()
    {
      cout<<endl<<"ID no. : "<<admno;
      cout<<endl<<"Customer Name : ";
      puts(name);
      cout<<endl<<"No of Book issued : "<<token;
      if(token==1)
      cout<<endl<<"Book No "<<stbno;
    }
  void modify_student()
    {
      cout<<endl<<"ID no. : "<<admno;
      cout<<endl<<"Modify Customer Name : ";
      gets(name);
    }
  char* retadmno()
    {
      return admno;
    }
  char* retstbno()
    {
      return stbno;
    }
  int rettoken()
    {
      return token;
    }
 void addtoken()
    {
      token=1;
    }
 void resettoken()
    {
      token=0;
    }
 void getstbno(char t[])
    {
      strcpy(stbno,t);
    }
 void report()
    {
      cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;
    }
};
fstream fp,fp1;
book bk;
student st;
void write_book()
 {
   char ch;
   fp.open("book.dat",ios::out|ios::app);
   do
    {
      clrscr();
      bk.create_book();
      fp.write((char*)&bk,sizeof(book));
      cout<<endl<<endl<<"Do you want to add more record..(y/n?)";
      cin>>ch;
    }
    while(ch=='y'||ch=='Y');
	fp.close();
 }
void write_student()
 {
   char ch;
   fp.open("student.dat",ios::out|ios::app);
   do
     {
       st.create_student();
       fp.write((char*)&st,sizeof(student));
       cout<<endl<<endl<<"do you want to add more record..(y/n?)";
       cin>>ch;
     }
   while(ch=='y'||ch=='Y');
       fp.close();
 }
void display_spb(char n[])
 {
    cout<<endl<<"BOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
     {
       if(strcmpi(bk.retbno(),n)==0)
	 {
	   bk.show_book();
	   flag=1;
	 }
     }
    fp.close();
    if(flag==0)
    cout<<endl<<endl<<"Book does not exist";
    getch();
 }
void display_sps(char n[])
 {
    cout<<endl<<"Customer DETAILS\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
     {
       if((strcmpi(st.retadmno(),n)==0))
       {
	 st.show_student();
	 flag=1;
       }
     }
    fp.close();
    if(flag==0)
    cout<<endl<<endl<<"Customer does not exist";
    getch();
 }
void modify_book()
 {
    char n[6];
    int found=0;
    clrscr();
    cout<<endl<<"tMODIFY BOOK REOCORD.... ";
    cout<<endl<<endl<<"Enter The book no. of The book";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
     {
       if(strcmpi(bk.retbno(),n)==0)
       {
	 bk.show_book();
	 cout<<endl<<"Enter The New Details of book"<<endl;
	 bk.modify_book();
	 int pos=-1*sizeof(bk);
	 fp.seekp(pos,ios::cur);
	 fp.write((char*)&bk,sizeof(book));
	 cout<<endl<<endl<<"\t Record Updated";
	 found=1;
       }
     }
    fp.close();
    if(found==0)
    cout<<endl<<"Record Not Found ";
    getch();
 }
void modify_student()
 {
    char n[6];
    int found=0;
    clrscr();
    cout<<endl<<"MODIFY CUSTOMER RECORD... ";
    cout<<endl<<"Enter The ID no. of The customer";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
     {
       if(strcmpi(st.retadmno(),n)==0)
       {
	 st.show_student();
	 cout<<endl<<"Enter The New Details of Customer"<<endl;
	 st.modify_student();
	 int pos=-1*sizeof(st);
	 fp.seekp(pos,ios::cur);
	 fp.write((char*)&st,sizeof(student));
	 cout<<endl<<endl<<"\t Record Updated";
	 found=1;
       }
     }
    fp.close();
    if(found==0)
    cout<<endl<<endl<<"Record Not Found ";
    getch();
 }
void delete_student()
 {
    char n[6];
    int flag=0;
    clrscr();
    cout<<endl<<endl<<endl<<"DELETE CUSTOMER...";
    cout<<"\n\nEnter The ID no. of ";
    cout<<"the Customer You Want To Delete : ";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&st,sizeof(student)))
     {
       if(strcmpi(st.retadmno(),n)!=0)
       fp2.write((char*)&st,sizeof(student));
       else
       flag=1;
     }
    fp2.close();
    fp.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    if(flag==1)
    cout<<endl<<endl<<"Record Deleted ..";
    else
    cout<<endl<<endl<<"Record not found";
    getch();
 }
void delete_book()
 {
    char n[6];
    clrscr();
    cout<<endl<<endl<<endl<<"DELETE BOOK ...";
    cout<<endl<<endl<<"Enter The Book no. of the ";
    cout<<"Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
     {
       if(strcmpi(bk.retbno(),n)!=0)
       {
	 fp2.write((char*)&bk,sizeof(book));
       }
     }
    fp2.close();
    fp.close();
    remove("book.dat");
    rename("Temp.dat","book.dat");
    cout<<endl<<endl<<"Record Deleted ..";
    getch();
 }
void display_alls()
 {
    clrscr();
    fp.open("student.dat",ios::in);
    if(!fp)
     {
       cout<<endl<<"ERROR!!! FILE COULD NOT BE OPEN ";
       getch();
       return;
     }
    cout<<"\n\n\t\tCUSTOMER LIST\n\n";
    cout<<"===================================================";
    cout<<"===============\n";
    cout<<endl<<"\tID No."<<setw(15)<<"Name"<<setw(20);
    cout<<"Book Issued\n";
    cout<<"====================================================";
    cout<<"==============\n";
    while(fp.read((char*)&st,sizeof(student)))
     {
       st.report();
     }
    fp.close();
    getch();
 }
void display_allb()
 {
    clrscr();
    fp.open("book.dat",ios::in);
    if(!fp)
      {
	cout<<endl<<"ERROR!!! FILE COULD NOT BE OPEN ";
	getch();
	return;
      }
    cout<<"\n\n\t\tBook LIST\n\n";
    cout<<"=========================================================";
    cout<<"================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
    cout<<"=========================================================";
    cout<<"================\n";
    while(fp.read((char*)&bk,sizeof(book)))
      {
	bk.report();
      }
    fp.close();
    getch();
 }
void book_issue()
 {
    char sn[6],bn[6];
    int found=0,flag=0;
    clrscr();
    cout<<endl<<"BOOK ISSUE ...";
    cout<<endl<<"Enter The student's admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
      {
	if(strcmpi(st.retadmno(),sn)==0)
	  {
	    found=1;
	    if(st.rettoken()==0)
	      {
		cout<<endl<<endl<<"Enter the book no. ";
		cin>>bn;
		while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
		 {
		   if(strcmpi(bk.retbno(),bn)==0)
		     {
		       bk.show_book();
		       flag=1;
		       st.addtoken();
		       st.getstbno(bk.retbno());
		       int pos=-1*sizeof(st);
		       fp.seekp(pos,ios::cur);
		       fp.write((char*)&st,sizeof(student));
		       cout<<"\n\n\t Book issued successfully\n\nPlease";
		       cout<<"Note: Write current date";
		       cout<<"in backside of book and submit within 10 days";
		       cout<<" fine Rs. 5 for each day";
		       cout<<"after 10 days period";
		     }
		 }
		if(flag==0)
		cout<<"Book no does not exist";
	      }
			else
				cout<<"You have not returned the last book ";

	  }
      }
	if(found==0)
	cout<<"Student record not exist...";
	getch();
	fp.close();
	fp1.close();
 }
void book_deposit()
 {
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    clrscr();
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The student's id.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
      {
	if(strcmpi(st.retadmno(),sn)==0)
	  {
	     found=1;
	     if(st.rettoken()==1)
	       {
		 while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
		   {
		     if(strcmpi(bk.retbno(),st.retstbno())==0)
		       {
			  bk.show_book();
			  flag=1;
			  cout<<"\n\nBook deposited in no. of days";
			  cin>>day;
			  if(day>15)
			    {
			      fine=(day-15)*5;
			      cout<<"\n\nFine has to deposited Rs. "<<fine;
			    }
			  st.resettoken();
			  int pos=-1*sizeof(st);
			  fp.seekp(pos,ios::cur);
			  fp.write((char*)&st,sizeof(student));
			  cout<<"\n\n\t Book deposited successfully";
		       }
		   }
		 if(flag==0)
		 cout<<"Book no does not exist";
	       }
	     else
	     cout<<"No book is issued..please check!!";
	  }
      }
    if(found==0)
    cout<<"Customer record not exist...";
    getch();
    fp.close();
    fp1.close();
 }
void intro()
 {
    clrscr();
    gotoxy(35,8);
    cout<<"WELCOME";
    gotoxy(30,11);
    cout<<"NEWTON Public library";
    gotoxy(26,14);
    cout<<"I.P Extension, Patparganj";
    gotoxy(33,17);
    cout<<"Delhi-110092";
    cout<<endl<<endl<<"MADE BY : Maaz Mohammed";
    cout<<endl<<endl<<"CLASS : XII A";
    cout<<endl<<endl<<"Enter any key to continue";
    getch();
 }
void admin_menu()
 {
    clrscr();
    cout<<"Enter passward to continue";
    int ch2;
    long int fun;
    cin>>fun;
    if(fun==129855)
  {
    cout<<"\n\n\n\tADMINISTRATOR MENU";
    cout<<"\n\n\t1.CREATE CUSTOMER RECORD";
    cout<<"\n\n\t2.DISPLAY ALL CUSTOMER RECORD";
    cout<<"\n\n\t3.DISPLAY SPECIFIC CUSTOMER RECORD ";
    cout<<"\n\n\t4.MODIFY CUSTOMER RECORD";
    cout<<"\n\n\t5.DELETE CUSTOMER RECORD";
    cout<<"\n\n\t6.CREATE BOOK ";
    cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
    cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
    cout<<"\n\n\t9.MODIFY BOOK ";
    cout<<"\n\n\t10.DELETE BOOK ";
    cout<<"\n\n\t11.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
    cin>>ch2;
    switch(ch2)
      {
	case 1: clrscr();
		write_student();
		break;
	case 2: display_alls();
		break;
	case 3: {
		  char num[6];
		  clrscr();
		  cout<<"\n\n\tPlease Enter The ID No. ";
		  cin>>num;
		  display_sps(num);
		  break;
		}
	case 4: modify_student();
		break;
	case 5: delete_student();
		break;
	case 6: clrscr();
		write_book();break;
	case 7: display_allb();
		break;
	case 8: {
		  char num[6];
		  clrscr();
		  cout<<"\n\n\tPlease Enter The book No. ";
		  cin>>num;
		  display_spb(num);
		  break;
		}
	case 9: modify_book();break;
	case 10: delete_book();break;
	case 11: return;
	default:cout<<"\a";
      }
    admin_menu();
  }
  else
   {
      cout<<"wrong password";
      getch();
      exit(2);
    }
 }
void main()
 {
    char ch;
    intro();
    do
      {
	clrscr();
	cout<<"\n\n\n\tMAIN MENU";
	cout<<"\n\n\t01. BOOK ISSUE";
	cout<<"\n\n\t02. BOOK DEPOSIT";
	cout<<"\n\n\t03. ADMINISTRATOR MENU";
	cout<<"\n\n\t04. EXIT";
	cout<<"\n\n\tPlease Select Your Option (1-4) ";
	ch=getche();
	switch(ch)
	{
	  case '1':clrscr();
		   book_issue();
		   break;
	  case '2':book_deposit();
		   break;
	  case '3':admin_menu();
		   break;
	  case '4':exit(0);
	  default :cout<<"\a";
	}
      }while(ch!='4');
 }
