#include<iostream>
#include<ctype.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<process.h>
#include<fstream>
using namespace std;
class mobile
{
 protected:
     char mobbrand[25];
     char mobname[25];
     long int mobmodno;
     float price;
public:
     virtual void get()=0;
     virtual void put()=0;
};
class bill: public mobile
{
    float dis;
public:
        void get()
        {
            cout<<"\n Enter the mobile details:";
            cout<<"\n Enter the brand name:";
            cin>>mobbrand;
            cout<<"\n Mobile model name: ";
            cin>>mobname;
            cout<<"\n Mobile model number: ";
            cin>>mobmodno;
            cout<<"\n Mobile price: ";
            cin>>price;
            cout<<"\n Enter the discount in percentage(%)";
            cin>>dis;
        }
    void put()
    {
        cout<<"\n The mobile details are:";
        cout<<"\n Mobile brand name: ";
        cout<<mobbrand;
        cout<<"\n Mobile model name: ";
        cout<<mobname;
        cout<<"\n Mobile model number: ";
        cout<<mobmodno;
        cout<<"\n Mobile price: ";
        cout<<price;
        cout<<"\n Discount : ";
        cout<<dis<<"%";
    }
}b;
class admin: public bill
{
public:
    void add()
    {
    char ch='y';
	fstream fout("mobile.dat",ios::out|ios::binary|ios::app);
	while(ch=='y' || ch =='Y')
	{
		get();
		fout.write((char*)&b, sizeof(b));
		cout<<"\n Do you want to continue writing records ? If yes type y";
		cin>>ch;
	}
        fout.close();
    }
    void modify()
    {
    long int modno;
	cout<<"\n Enter model number of record to be modified.";
	cin>>modno;
	fstream f("mobile.dat",ios::in|ios::out|ios::binary);
	if(!f)
	{
		cout<<"\n File not Found";
	}
	else
	{
	    int pos=0;
	    int flag1=0;
		while(f.read((char*)&b, sizeof(b)))
		{
		   // if(!f.read((char*)&b, sizeof(b)))
            //break;
           pos=f.tellg();
			if(mobmodno==modno)
			{
				cout<<"\n Enter the details of the modified record"<<endl;
				get();
				f.seekg(pos-1*sizeof(b));
				f.write((char*)&b, sizeof(b));
				flag1=1;
				break;
			}
			if(flag1==0)
			{
				 cout<<"\n Record not found";
			}
			f.close();
		}
	}
    }
    void del()
    {
    long int modno;
	cout<<"\n Enter model number of record to be deleted";
	cin>>modno;
	fstream temp("temp.dat",ios::out|ios::binary);
	fstream f("binary.dat",ios::in| ios::binary);
	if(!f)
	{
		cout<<"File not Found";
	}
	else
	{
		/*if(!f.read((char*)&b, sizeof(b)))
		break;*/
		while(f.read((char*)&b, sizeof(b)))
		{
			if(modno==mobmodno)
			{
				temp.write((char*)&b, sizeof(b));
			}
			else
			{
				 cout<<"\n Record not found";
			}
			f.read((char*)&b, sizeof(b));
		}
	}
	temp.close();
	f.close();
	remove("mobile.dat");
	rename("temp.dat", "mobile.dat");
    }


    void display()
    {
        fstream f("mobile.dat",ios::in| ios::binary);
	if(!f)
	{
		cout<<"\n Error. File not Found";
	}
	else
	{

		while(f.read((char*)&b, sizeof(b)))
		{  // if(!f.read((char*)&b,sizeof(b))))
		   // break;
			put();
		}
	}
	f.close();
    }
};
class user: public bill
{
public:
    void display()
    {
        int ch,x,y;
        char brname[25];
        cout<<"\n How do you want to display the mobile details?\n 1. Brand Name \n 2. Price range";
        cin>>ch;
        if(ch==1)
        {
            fstream f("mobile.dat",ios::in | ios::out | ios::binary);
            if(!f)
            cout<<"Error. File cannot be opened.";
            else
            {
                while(f.read((char*)&b, sizeof(b))
                {
                   // if(!f.read((char*)&b, sizeof(b)))
                   //     break;
                    cin>>brname;
                    if(strcmp(brname,mobbrand)==0)
                        {
                            put();
                        }
                }
            }
            f.close();
        }
        else if(ch==2)
        {
            fstream f("mobile.dat",ios::in | ios::out | ios::binary);
            if(!f)
            cout<<"Error. File cannot be opened.";
            else
            {
                while(f.read((char*)&b, sizeof(b)))
                {
                  //  if(!f.read((char*)&b, sizeof(b)))
                  //      break;
            cout<<"\n Enter the price range: ";
            cout<<"\n from.. ";
            cin>>x;
            cout<<"\t to.. ";
            cin>>y;
            if(x<price && price<y)
                put();
                }
            }
        f.close();
        }
        else cout<<"\n Sorry, wrong choice!";
    }
    void billgen(long int modno)
    {
        fstream f("mobile.dat",ios::in | ios::out | ios::binary);
            if(!f)
            cout<<"Error. File cannot be opened.";
            else
            {
                while(!f.eof())
                {
                    if(!f.read((char*)&b, sizeof(b)))
                        break;
                        if(modno==mobmodno)
                        {
                            float total;
                            total= price-(price*dis*0.01);
                            put();
                            cout<<"\n Final Price: Rs. "<<total;
                        }
                }
            }
            f.close();
    }

};
int main()
{
    user u;
int c;
char z='y';
mmenu:
cout<<"\n 1.Admin  2. User";
cin>>c;
if(c==1)
{
    int pass;
    menu:
        cout<<"\n Enter password";
    cin>>pass;
    if(!(pass==1234))
    {
        cout<<"Invalid password.";
        goto menu;
    }
    else
    {
        admin a;
        char rep='y';
        cout<<"\n 1.Add 2.Modify 3.Delete 4.Display";
        int ch;
        cin>>ch;
        do
        {
            switch(ch)
            {
                case 1:a.add();
                break;
                case 2:a.modify();
                break;
                case 3:a.del();
                break;
                case 4:a.admin::display();
                break;
                default: cout<<"\n Wrong choice.";
            }
            cout<<"\n Do you want to continue?";
            cin>>rep;
        }while(rep=='y' || rep=='Y');
    }
}
else if(c==2)
{

    long int l;
    int k;
    char rep='y';
    do
        {
        cout<<"\n 1.Search for mobile 2.Generate bill : ";
        cin>>k;
        switch(k)
            {
                case 1: u.user::display();
                break;
                case 2:
                cout<<"\n enter the model no:";
                cin>>l;

              u.billgen(l);
                break;
                default: cout<<"\n Wrong choice! ";
            }
        cout<<"\n Do you want to continue? ";
        cin>>rep;
        }while(rep=='y' || rep=='Y');
}
else
{cout<<"\n Wrong choice. Do you want to go to the main menu? :";
cin>>z;

if(z=='y' || z=='Y')
    goto mmenu;

}
return 0;
}
