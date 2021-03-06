#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

class student
{
    int rollno;
    char name[50];
    int p_marks, c_marks, m_marks, e_marks, cs_marks;
    double per;
    char grade;
    void calculate(); //function to calculate grade
public:
    void getdata(); //function to accept data from user
    void showdata() const; //function to show data on screen
    void show_tabular() const;
    int retrollno() const;
    void fileWrite();
}; //class ends here

void student::fileWrite(){
    ofstream outFile;
    outFile.open("final.txt",ios::app);
    outFile<<"\nRoll number of the student : "<<rollno;
    outFile<<"\nName of student : "<<name;
    outFile<<"\nMarks in Physics : "<<p_marks;
    outFile<<"\nMarks in Chemistry : "<<c_marks;
    outFile<<"\nMarks in Maths : "<<m_marks;
    outFile<<"\nMarks in English : "<<e_marks;
    outFile<<"\nMarks in Computer Science :"<<cs_marks;
    outFile<<"\nPercentage of student is  :"<<per;
    outFile<<"\nGrade of student is :"<<grade;
    outFile<<"\n********************************************\n";
    
}
void student::calculate()
{
    per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
    if(per>=60)
        grade='A';
    else if(per>=50)
        grade='B';
    else if(per>=33)
        grade='C';
    else
        grade='F';
}

void student::getdata()
{
    cout<<"\nEnter roll number of the student: ";
    cin>>rollno;
    cout<<"\n\nEnter name of the student: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\nEnter marks in physics out of 100 : ";
    cin>>p_marks;
    cout<<"\nEnter marks in chemistry out of 100 : ";
    cin>>c_marks;
    cout<<"\nEnter marks in maths out of 100 : ";
    cin>>m_marks;
    cout<<"\nEnter marks in english out of 100 : ";
    cin>>e_marks;
    cout<<"\nEnter marks in computer science out of 100 : ";
    cin>>cs_marks;
    calculate();
}

void student::showdata() const
{
    cout<<"\nRoll number of the student : "<<rollno;
    cout<<"\nName of student : "<<name;
    cout<<"\nMarks in Physics : "<<p_marks;
    cout<<"\nMarks in Chemistry : "<<c_marks;
    cout<<"\nMarks in Maths : "<<m_marks;
    cout<<"\nMarks in English : "<<e_marks;
    cout<<"\nMarks in Computer Science :"<<cs_marks;
    cout<<"\nPercentage of student is  :"<<per;
    cout<<"\nGrade of student is :"<<grade;
}

void student::show_tabular() const
{
    cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<p_marks<<setw(4)<<c_marks<<setw(4)<<m_marks<<setw(4)
    <<e_marks<<setw(4)<<cs_marks<<setw(8)<<per<<setw(6)<<grade<<endl;
}

int  student::retrollno() const
{
    return rollno;
}

void write_student(); //write the record in binary file
void display_all(); //read all records from binary file
void display_sp(int); //accept rollno and read record from binary file
void modify_student(int); //accept rollno and update record of binary file
void delete_student(int); //accept rollno and delete selected records from binary file
void class_result(); //display all records in tabular format from binary file
void result(); //display result menu
void intro(); //display welcome screen
void entry_menu();//display entry menu on screen
void finalData();

int main()
{
    char ch;
    cout.setf(ios::fixed|ios::showpoint);
    cout<<setprecision(2); // program outputs decimal number to two decimal places
    intro();
    do
    {
        system("cls");
        cout<<"\n\n\n\tMAIN MENU";
        cout<<"\n\n\t1. RESULT MENU";
        cout<<"\n\n\t2. ENTRY/EDIT MENU";
        cout<<"\n\n\t3. EXIT";
        cout<<"\n\n\tPlease Select Your Option (1-3): ";
        cin>>ch;
        switch(ch)
        {
            case '1': result();
                break;
            case '2': entry_menu();
                break;
            case '3':
                finalData();
                break;
            default :cout<<"\a";
        }
    }while(ch!='3');
    return 0;
}

void write_student()
{
    student st;
    ofstream outFile;
    outFile.open("student.dat",ios::binary|ios::app);
    st.getdata();
    outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
    outFile.close();
    cout<<"\n\nStudent record Has Been Created\n<Press Enter>\n";
    cin.ignore();
    cin.get();
}

void display_all()
{
    student st;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File open failed!\n<Press Enter>\n";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\n\t\tDISPLAY ALL RECORDS !!!\n\n";
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
    {
        st.showdata();
        cout<<"\n\n====================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

void display_sp(int n)
{
    student st;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File open failed!\n<Press Enter>\n";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag=false;
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
    {
        if(st.retrollno()==n)
        {
            st.showdata();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
        cout<<"\n\nRecord does not exist\n<Press Enter>\n";
    cin.ignore();
    cin.get();
}

void modify_student(int n)
{
    bool found=false;
    student st;
    fstream File;
    File.open("student.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"File open failed!\n<Press Enter>\n";
        cin.ignore();
        cin.get();
        return;
    }
    while(!File.eof() && found==false)
    {
        
        File.read(reinterpret_cast<char *> (&st), sizeof(student));
        if(st.retrollno()==n)
        {
            st.showdata();
            cout<<"\n\nEnter new details of student"<<endl;
            st.getdata();
            int pos=(-1)*static_cast<int>(sizeof(st));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char *> (&st), sizeof(student));
            cout<<"\n\n\t Records Updated\n<Press Enter>\n";
            found=true;
        }
    }
    File.close();
    if(found==false)
        cout<<"\n\n Record Not Found\n<Press Enter>\n ";
    cin.ignore();
    cin.get();
}

void delete_student(int n)
{
    student st;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File open failed!\n<Press Enter>\n";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outFile;
    outFile.open("Temp.dat",ios::out);
    inFile.seekg(0,ios::beg);
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
    {
        if(st.retrollno()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
        }
    }
    outFile.close();
    inFile.close();
    remove("student.dat");
    rename("Temp.dat","student.dat");
    cout<<"\n\n\tRecord Deleted .. \n<Press Enter>\n";
    cin.ignore();
    cin.get();
}

void class_result()
{
    student st;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File open failed!\n<Press Enter>\n";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
    cout<<"==========================================================\n";
    cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
    cout<<"==========================================================\n";
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
    {
        st.show_tabular();
    }
    cout<<"\n<Press Enter>\n";
    cin.ignore();
    cin.get();
    inFile.close();
}

void result()
{
    char ch;
    int rno;
    system("cls");
    cout<<"\n\n\n\tRESULT MENU";
    cout<<"\n\n\n\t1. Class Result";
    cout<<"\n\n\t2. Student Report Card";
    cout<<"\n\n\t3. Back to Main Menu";
    cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
    cin>>ch;
    system("cls");
    switch(ch)
    {
        case '1' : class_result(); break;
        case '2' : cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
            display_sp(rno); break;
        case '3' : break;
        default: cout<<"Invalid Choice";
    }
}

void intro()
{
    cout<<"\n\n\n\t\t\t\tREPORT CARD GENERATOR";
    cout<<"\n\n\n\tMade By:";
    cout<<endl<<"\t18121A1205"<<endl<<"\t18121A1260"<<endl<<"\t18121A1254"<<endl<<"\t18121A1245";
    cout<<"\n\n\tDepartment of Information Technology\n\tSree Vidyanikethan Engineering College";
    cout<<"\n\n\n\t<Press Enter>\n\n";
    cin.get();
}

void finalData(){
    student obj;
    ofstream outFile;
    outFile.open("final.txt",ios::out);
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout<<"input file not found! Fatal error";
        exit(0);
    }
    while(inFile.read(reinterpret_cast<char *> (&obj), sizeof(student)))
    {
        obj.fileWrite();
    }
}

void entry_menu()
{
    char ch;
    int num;
    system("cls");
    cout<<"\n\n\n\tENTRY MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
    cin>>ch;
    system("cls");
    switch(ch)
    {
        case '1': write_student(); break;
        case '2': display_all(); break;
        case '3': cout<<"\n\n\tEnter the roll number "; cin>>num;
            display_sp(num); break;
        case '4': cout<<"\n\n\tEnter the roll number "; cin>>num;
            modify_student(num);break;
        case '5': cout<<"\n\n\tEnter the roll number "; cin>>num;
            delete_student(num);break;
        case '6': break;
        default: cout<<"\a"; entry_menu();
    }
}

