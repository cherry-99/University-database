#include<iostream>
#include<fstream>
#include<stdio.h>
 
using namespace std;
 

class Student{
    private:
        int SRN;
        char name[20];
        int math;
        int chem;
    public:
        void read();
        void display();
        int getSRN()            { return SRN;}
        int getMath()             { return math;}
        int getChem()             { return chem;}
        void updateMath(int m)  { math=m;}
        void updateChem(int c)  {chem = c;}
};
 
void Student::read(){
    cout<<"Enter student SRN : ";
    cin>>SRN;
    cout<<"Enter name : ";
    cin.ignore(1);
    cin.getline(name,20);
    cout<<"Enter mathematics marks :  ";
    cin>>math;
    cout << "Enter chemistry marks : ";
    cin >> chem;
}
 
void Student::display()
{
    cout << "SRN" << "\t" << "Name" << "\t" << "Math" << "\t" << "Chem" << endl;
    cout<<SRN<<"\t"<<name<<"\t"<<math<<"\t"<<chem<<endl;
}
 
fstream file;
 
//Will delete file when program is being executed
//because we are create file in append mode
void deleteExistingFile(){
    remove("STUDENT.DAT");
}
 
void appendToFille(){
    Student    x;
     
    x.read();
     
    file.open("STUDENT.DAT",ios::binary|ios::app);
    if(!file){
        cout<<"ERROR IN CREATING FILE\n";
        return;
    }
    //write into file
    file.write((char*)&x,sizeof(x));
    file.close();
    cout<<"Record added sucessfully.\n";
}
 
void displayAll(){
    Student    x;
     
    file.open("STUDENT.DAT",ios::binary|ios::in);
    if(!file){
        cout<<"ERROR IN OPENING FILE \n";
        return;
    }
    while(file){
    if(file.read((char*)&x,sizeof(x)))
        x.display();
    }
  file.close();
}
 
void searchForRecord(){
    Student    x;
    int c;
    int isFound=0;
 
    cout<<"Enter SRN : ";
    cin>>c;
 
 
    file.open("STUDENT.DAT",ios::binary|ios::in);
    if(!file){
        cout<<"DATABASE DOESN'T EXIST! \n";
        return;
    }
    while(file){
        if(file.read((char*)&x,sizeof(x))){
            if(x.getSRN()==c){
                cout<<"RECORD FOUND\n";
                x.display();
                isFound=1;
                break;
            }
        }
    }
    if(isFound==0){
        cout<<"Record not found!!!\n";
    }
    file.close();
}
 
//Function to increase salary
void modify(){
    Student x;
    int c;
    int isFound=0;
    int math;
    int chem;
    char sub[10];
    std::string str1 ("math");
    std::string str2 ("chem");
 
    cout<<"Enter SRN \n";
    cin>>c;
    cout << "Do you want to update math or chem : ";
    cin >> sub;
    if(str1.compare(sub) == 0)
    {
        file.open("STUDENT.DAT",ios::binary|ios::in);
        if(!file){
            cout<<"ERROR IN OPENING FILE \n";
            return;
        }
        while(file){
            if(file.read((char*)&x,sizeof(x))){
                if(x.getSRN()==c){
                    cout<<"New marks : ";
                    cin >> math;
                    x.updateMath(math);
                    isFound=1;
                    break;
                }   
            }
        }
        if(isFound==0){
            cout<<"Record not found!!!\n";
        }
        file.close();
        cout<<"Marks updated successfully."<<endl;
    }
    else if(str2.compare(sub) == 0)
    {
        file.open("STUDENT.DAT",ios::binary|ios::in);
        if(!file){
            cout<<"ERROR IN OPENING FILE \n";
            return;
        }
        while(file){
            if(file.read((char*)&x,sizeof(x))){
                if(x.getSRN()==c){
                    cout<<"New marks : ";
                    cin >> chem;
                    x.updateChem(chem);
                    isFound=1;
                    break;
                }   
            }
        }
        if(isFound==0){
            cout<<"Record not found!!!\n";
        }
        file.close();
        cout<<"Marks updated successfully."<<endl;
    }
}

 
int main()
{
     char ch;
 
    //if required then only remove the file
     deleteExistingFile();
    
    while(1)
    {
        int choice;
        cout << "Enter choice\n"<<"1. Student login\n" << "2. Teacher login\n" << "3. Admin login\n" << "4. Exit\n";
        cin >> choice;
        switch(choice)
        {
            case 1 : cout << "Warning : Students can only view data\n";
                    searchForRecord();
                    break;
            case 2 :
                {
                    string flag("y");
                    std::string str3 ("teacher");
                    char confirm[20];
                    cout << "Enter your password : ";
                    cin >> confirm;
                    if(str3.compare(confirm) == 0)
                    {
                        while(flag == "y" || flag == "Y")
                        {
                            int num;
                            cout << "1. View all records\n";
                            cout << "2. Display particular record\n";
                            cout << "3. Modify marks\n";
                            cout << "Enter your choice : ";
                            cin >> num;
                            switch(num)
                            {
                                case 1 : displayAll();
                                        break;
                                case 2 : searchForRecord();
                                        break;
                                case 3 : modify();
                                        break;
                            }
                            cout<<"Do you want to continue?(y/n) : ";
                            cin>>flag;
                        }
                    }
                    else
                    {
                        cout << "You have entered the wrong password :( \n";
                    }
                    break;
                }
            case 3 : 
                {
                    string flag2("y");
                    std::string str4 ("admin");
                    char confirm2[20];
                    cout << "Enter your password : ";
                    cin >> confirm2;
                    if(str4.compare(confirm2) == 0)
                    {
                        while(flag2 == "y" || flag2 == "Y")
                        {
                            int num2;
                            cout << "1. Append new record\n";
                            cout << "2. Display particular record\n";
                            cout << "3. Display all records\n";
                            cout << "4. Modify record values\n";
                            cout << "Enter your choice : ";
                            cin >> num2;
                            switch(num2)
                            {
                                case 1 : appendToFille();
                                        break;
                                case 2 : searchForRecord();
                                        break;
                                case 3 : displayAll();
                                        break;
                                case 4 : modify();
                                        break;
                            }
                            cout<<"Do you want to continue in admin mode?(y/n) : ";
                            cin>>flag2;
                        }
                    }
                    else
                    {
                        cout << "You have entered the wrong password! :(\n";
                    }
                    break;
                }
            case 4 : exit(1);

        }
    }
    //  do{
    //  int n;
 
    //  cout<<"ENTER CHOICE\n"<<"1.ADD AN STUDENT\n"<<"2.DISPLAY\n"<<"3.SEARCH\n"<<"4.CHANGE/UPDATE MARKS\n";
    //  cout<<"Make a choice: ";
    //  cin>>n;
 
    //  switch(n){
    //       case 1:
    //         appendToFille();
    //         break;
    //       case 2 :
    //         displayAll();
    //         break;
    //       case 3:
    //         searchForRecord();
    //         break;
    //     case 4:
    //         modify();
    //         break;
    //     default :
    //         cout<<"Invalid Choice\n";
    //  }
 
    //  cout<<"Do you want to continue ? : ";
    //  cin>>ch;
 
    //  }while(ch=='Y'||ch=='y');
     
    // return 0;
}