class admin
{
public:
    void add()
    {
    char ch='y';
	fstream fout("mobile.dat",ios::out|ios::binary|ios::app);
	while(ch=='y' || ch =='Y')
	{
		b.get();
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
	f.open("mobile.dat",ios::in|ios::out|ios::binary);
	if(!f)
	{
		cout<<"\n File not Found";
	}
	else
	{
		f.read((char*)&b, sizeof(b));
		while(!f.eof())
		{
			if(b.mobmodno==modno)
			{
				f.seekg(0,ios::cur);
				cout<<"\n Enter the details of the modified record"<<endl;
				b.get();
				f.seekp(f.tellg() - sizeof(b));
				f.write((char*)&b, sizeof(b));
			}
			else
			{
				 cout<<"\n Record not found";
			}
			f.close();
		}
	}
    }
    void delete()
    {
    long int modno;
	cout<<"\n Enter model number of record to be deleted";
	cin>>modno;
	ofstream temp;
	temp.open("temp.dat",ios::out|ios::binary);
	f.open("binary.dat",ios::in| ios::binary);
	if(!f)
	{
		cout<<"File not Found";
		exit(0);
	}
	else
	{
		f.read((char*)&b, sizeof(b));
		while(!f.eof())
		{
			if(modno==b.mobmodno)
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
        f.open("mobile.dat",ios::in| ios::binary);
	if(!f)
	{
		cout<<"\n Error. File not Found";
	}
	else
	{
		f.read((char*)&b, sizeof(b));
		while(!f.eof())
		{   if(!f.read((char*)&b,sizeof(b))))
		    break;
			b.put();
		}
	}
	f.close();

    }
};
