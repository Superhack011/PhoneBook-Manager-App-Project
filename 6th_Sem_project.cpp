#include<iostream>
#include<string>
#include<stdio.h>
#include<conio.h>
#include<fstream>

using namespace std;

void home();
void number_Add();
void show();
void find();
void record_delete();
void update();

class diary{
    int Sr_no;
    string name;
    string mobilenum;
    string email;
    string groupby;

    public:
    int getSRnumber(){
        return Sr_no;
    }
    void data_stored(){
        cout<<"\n..........Create New Phone Record..........\n";
        cout<<"Enter Serial Number : "; cin>>Sr_no;
        cout<<"Enter the Name : "; getline(cin,name);
        cout<<"Enter Mobile Number : "; getline(cin,mobilenum);
        cout<<"Enter E-Mail ID : "; getline(cin, email);
        cout<<"Enter Record Group : "; getline(cin, groupby);
        cout<<endl<<endl;
    }

    void data_show(){
        cout<<"\n..........Phone Book Record..........\n";
        cout<<"Sr_No : "<<Sr_no<<endl;
        cout<<"Name : "<<name<<endl;
        cout<<"Mobile NO. : "<<mobilenum<<endl;
        cout<<"E-Mail ID : "<<email<<endl;
        cout<<"Record Group : "<<groupby<<endl;
        cout<<endl;
    }


}dp;

void number_Add(){
    ofstream fout;
    fout.open("phoneBook.dat",ios::out|ios::binary|ios::app);
    dp.data_stored();
    fout.write((char*)&dp,sizeof(dp));
    fout.close();
    cout<<endl<<"Record Saved to the file.........."<<endl;

}

void show(){
    ifstream fin;
    fin.open("PhoneBook.dat",ios::out|ios::binary|ios::app);
    while(fin.read((char*) &dp,sizeof(dp))){
        dp.data_show();
    }
    fin.close();
    cout<<endl<<"Reading of Data inb File is Completed........."<<endl;
}

void find(){
    ifstream fin;
    int n,flag = 0;
    fin.open("PhoneBook.dat",ios::out|ios::binary|ios::app);
    cout<<"Enter the serial number of Record to display : ";
    cin>>n;

    while(fin.read((char*)&dp, sizeof(dp))){
        if (n == dp.getSRnumber()){
            dp.data_show();
            flag++;
            cout<<"\n\n.....Record Found and Displayed.......\n";
        }
    }
    fin.close();
    if (flag == 0){
        cout<<"\nThe record of Serial Number " <<n<<" is not found in the file .....\n";

    }
    cout<<"\n.....Reading the data file completed.....\n";
}

void record_delete(){
    ifstream fin;
    ofstream fout;

    int n, flag = 0;
    fin.open("PhoneBook.dat",ios::out|ios::binary|ios::app);
    fout.open("temp.dat",ios::out | ios::binary);
    cout<<"Enter the Serial Number of Record to delete : ";
    cin>>n;

    while(fin.read((char*)&dp,sizeof(dp))){
        if (n == dp.getSRnumber()){
            cout<<"\nThe Following record is deleted...\n";
            dp.data_show();
            flag++;
        }
        else {
            fout.write((char*)&dp,sizeof(dp));
        }

    }
    fin.close();
    fout.close();

    if (flag == 0){
        cout<<"\nThe Record of Serial number "<<n<<" is not in the file.\n";

    }
    cout<<"\nReading of data file is completed..."<<endl;

    remove("PhoneBook.dat");
    rename("temp.dat","PhoneBook.dat");

}

void update(){
    fstream fio;
    int n, flag = 0, pos;
    fio.open("PhoneBook.dat",ios::out | ios::binary | ios::in);

    cout<<"Enter the Serial number of Record to Modify : ";
    cin>>n;

    while(fio.read((char*)&dp,sizeof(dp))){
        pos = fio.tellg();
        if (n == dp.getSRnumber()){
            cout<<"\nThe Following record will be modified..."<<endl;
            dp.data_show();
            flag++;
            cout<<"\nEnter the New Details : \n";
            dp.data_stored();
            fio.seekg(pos-sizeof(dp));
            fio.write((char*)&dp,sizeof(dp));
            cout<<"\nData Modified Successfully.....\n";
        }
    }
    fio.close();
    if (flag == 0){
        cout<<"\nThe Record of Serial Number "<<n<<" is not in the file...\n";

    }
    cout<<"\nReading of Data File is Completed...."<<endl;
}

void home(){
    int ch;
    do {
        cout<<"........PhoneBook Records........."<<endl;
        cout<<"----------------------------------"<<endl;
        cout<<"::::::::::::Menu::::::::::::::::::"<<endl;
        cout<<"1. To Add a new Contact...\n";
        cout<<"2. To Display all Contacts...\n";
        cout<<"3. To Search a Specific Contacts...\n";
        cout<<"4. To Delete a Contacts...\n";
        cout<<"5. To Update a Specific Contacts...\n";
        cout<<"6. Exit"<<endl;

        cout<<"Enter your Choice : "; cin>>ch;

        switch(ch){
            case 1: number_Add();
            case 2: show();
            case 3: find();
            case 4: record_delete();
            case 5: update();
        }
        getch();
    }while(ch);

}


int main (){
    cout<<"Hello World!"<<endl;

    home();

    return 0;
}
