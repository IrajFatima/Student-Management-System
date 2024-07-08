#include <iostream>
#include <vector>
#include <cmath>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <fstream>
using namespace std;
#define MAX_STUDENT 20

enum Gender{
    male,
    female
};

typedef struct Student{
    int id;
    string name;
    int age;
    Gender gender;
    int marks;
}stud;

void load_students(stud* s[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open the file!" << endl;
        return;
    }

    int i = 0;
    while (i < MAX_STUDENT) {
        s[i] = new stud;
        file >> s[i]->id;
        if (file.fail()) {
            delete s[i];
            s[i] = nullptr;
            break;
        }
        file.ignore();
        getline(file, s[i]->name);
        file >> s[i]->age;
        int gender;
        file >> gender;
        s[i]->gender = static_cast<Gender>(gender);
        file >> s[i]->marks;
        file.ignore();
        i++;
    }
    file.close();
}

void save_students(stud* s[], const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open the file!" << endl;
        return;
    }

    for (int i = 0; i < MAX_STUDENT; i++) {
         if (s[i] != nullptr && s[i]->id != -1){
            file << s[i]->id << endl;
            file << s[i]->name << endl;
            file << s[i]->age << endl;
            file << static_cast<int>(s[i]->gender) << endl;
            file << s[i]->marks << endl;
        }
    }
    file.close();
}

bool add_student(stud*s[], const string& filename){
    for(int i=0;i<MAX_STUDENT;i++){
        if(s[i]==nullptr){
            s[i]=new stud;  
            cout<<"Enter the id of the student: ";
            cin>>s[i]->id;
            cout<<"Enter the name of student: ";
            cin.ignore();
            getline(cin,s[i]->name);
            cout<<"Enter the age of the student: ";
            cin>>s[i]->age;
            cout<<"Enter the gender of the student(For male enter 1, for female enter 2): ";
            int temp;
            cin>>temp;
            if(temp==1)
                s[i]->gender=male;
            else if(temp==2)
                s[i]->gender=female;
            else
                cout<<"invalid input"<<endl;
            cout<<"Enter the marks of the student: ";
            cin>>s[i]->marks;
            cout<<"<----------Student added successfully----------->"<<endl;
            save_students(s,filename);
            return true;
        }
    }
    cout<<"<----------space pre occupied----------->"<<endl;
    return false;
}

void display_students(stud*s[]){
    for(int i=0;i<MAX_STUDENT;i++)
        if(s[i]!=nullptr){
            cout<<"<----------------------------------------->"<<endl;
            cout<<"Student id: "<<s[i]->id<<endl;
            cout<<"Student name: "<<s[i]->name<<endl;
            cout<<"Student age: "<<s[i]->age<<endl;
            if(s[i]->gender==male)
                cout<<"Student gender: male"<<endl;
            else if(s[i]->gender==female)
                cout<<"Student gender: female"<<endl;
            cout<<"Student marks: "<<s[i]->marks<<endl;
            cout<<"<----------------------------------------->"<<endl;
        }
}
bool search_student(int id,stud*s[]){
    for (int i = 0; i < MAX_STUDENT; i++){
        if(s[i]!=nullptr&& s[i]->id==id){
            cout<<"<------------Student found---------------->"<<endl;
            cout<<"Student id: "<<s[i]->id<<endl;
            cout<<"Student name: "<<s[i]->name<<endl;
            cout<<"Student age: "<<s[i]->age<<endl;
            if(s[i]->gender==male)
                cout<<"Student gender: male"<<endl;
            else if(s[i]->gender==female)
                cout<<"Student gender: female"<<endl;
            cout<<"Student marks: "<<s[i]->marks<<endl;
            cout<<"<----------------------------------------->"<<endl;
            return true;
        }
    }
    cout<<"<------------Student not found-------------->"<<endl;
    return false;   
}

bool update_student(int id,stud*s[], const string& filename){
    for (int i = 0; i < MAX_STUDENT; i++)
        if(s[i]!=nullptr&& s[i]->id==id){
            cout<<"Enter the new name of the student: ";
            cin.ignore();
            getline(cin,s[i]->name);
            cout<<"Enter the new age of the student: ";
            cin>>s[i]->age;
            cout<<"Enter the new gender of the student(For male enter 1, for female enter 2): ";
            int temp;
            cin>>temp;
            if(temp==1)
                s[i]->gender=male;
            else if(temp==2)
                s[i]->gender=female;
            else
                cout<<"invalid input"<<endl;
            cout<<"Enter the new marks of the student: ";
            cin>>s[i]->marks;
            cout<<"<----------Student updated successfully----------->"<<endl;
            save_students(s,filename);
            return true;
        }
    cout<<"<------------Student not found-------------->"<<endl;
    return false;
}

bool delete_student(int id,stud *s[], const string& filename){
    for (int i = 0; i < MAX_STUDENT; i++)
        if(s[i]!=nullptr&& s[i]->id==id){
            s[i]->id=-1;
            delete s[i];
            s[i]=nullptr;
            cout<<"<----------Student deleted successfully----------->"<<endl;
            save_students(s,filename);
            return true;
        }
    cout<<"<------------Student not found-------------->"<<endl;
    return false;
}
int main(){
    stud* s[MAX_STUDENT];
    for(int i=0;i<MAX_STUDENT;i++)
        s[i]=nullptr;
    const string filename="students.txt";
    load_students(s,filename);
    cout<<"<------------------------------------- Menu --------------------------------------------->"<<endl<<endl;
    cout<<"To add student:      1"<<endl;
    cout<<"To delete student:   2"<<endl;
    cout<<"To update student:   3"<<endl;
    cout<<"To search student:   4"<<endl;
    cout<<"To display students: 5"<<endl;
    cout<<"<---------------------------------------------------------------------------------------->"<<endl<<endl;
    cout<<"Enter the total number of operations you want to perform :";
    int op;
    cin>>op;
    while(op--){
        cout<<"Enter your choice: ";
        int choice;
        cin>>choice;
        switch(choice){
            case 1:
                add_student(s,filename);
                break;
            case 2:
                cout<<"Enter student ID you want to delete : ";
                int id;
                cin>>id;
                delete_student(id,s,filename);
                break;
            case 3:
                cout<<"Enter student ID you want to update : ";
                cin>>id;
                update_student(id,s,filename);
                break;
            case 4:
                cout<<"Enter student ID you want to search : ";
                cin>>id;
                search_student(id,s);
                break;
            case 5:
                display_students(s);
                break;
            default:
                cout<<"Invalid choice"<<endl;


        }
    }
    for(int i=0;i<MAX_STUDENT;i++)
        if(s[i]!=nullptr)
            delete s[i];
    return 0;
}