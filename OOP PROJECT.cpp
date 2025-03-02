#include<iostream> 
#include<string>
#include<vector>
#include<limits>
#include<cctype>
#include<fstream>
#include<sstream>
using namespace std;
class Student 
{
private:
    string name;
	string enroll;
    int age;
    double grade;
public:
    // Constructor
    Student(string n,string e,int a,double g)
	{
		name=n;
		enroll=e;
		age=a;
		grade=g;
	} 
    // Getters
    string getName() const
	{
	 return name;
	}
	string getEnroll() const
	{
	 return enroll;
    }
	int getAge() const
	{
	 return age; 
	}
    double getGrade() const 
	{
	 return grade; 
	}
    // Setters
    void setName(string n) 
	{
	   name=n; 
	}
	void setEnroll(string e)
	{
	   enroll=e;	
	}
    void setAge(int a) 
	{
	   age=a; 
	}
    void setGrade(double g) 
	{
	   grade=g;
	}
    // Print student information
    void printInfo() const 
	{
        cout<<"Name: "<<name<<"\nEnrollment no: "<<enroll<<"\nAge: "<<age<<"\nGrade: "<<grade<<endl<<endl;
    }
};
class StudentsManagementSystem 
{
private:
    vector<Student>students;
public:
    // Add a student to the system
    void addStudent(const Student& student)
	{
        students.push_back(student);
        cout<<"Student added."<<endl;
    }
    // Search for a student by enrollment no.
    void searchStudent(const string& enroll) const 
	{
        bool found = false;
       for (int i=0;i<students.size();i++) 
	    {
           if (students[i].getEnroll() == enroll) 
		    {
                students[i].printInfo();
                found = true;
                break;
            }
        }
        if (!found) 
		{
            cout << "Student not found." << endl;
        }
    }
    // Update student information
    void updateStudent(string newname,const string& enroll,int newAge,double newGrade) 
	{
        for (int i=0;i<students.size();i++) 
		{
            if (students[i].getEnroll() == enroll) 
			{
				students[i].setName(newname);
                students[i].setAge(newAge);
                students[i].setGrade(newGrade);
                cout << "Student information updated." << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }
    // Delete a student
    void deleteStudent(const string& enroll) 
	{
        for (int i=0;i<students.size();i++)
		{
            if (students[i].getEnroll() == enroll) 
			{
                students.erase(students.begin()+i);
                cout << "Student deleted." << endl;
                return;
            }
        }
        cout << "Student not found." << endl;
    }
    // Calculate average grade of all students
    void calculateAverage() const 
	{
        if (students.empty()) 
		{
            cout<<"No students in the system."<<endl;
            return;
        }
        double total = 0;
        for (int i=0;i<students.size();i++) 
		{
            total += students[i].getGrade();
        }
        double avg = total / students.size();
        cout<<"Average grade of all students: "<<avg<<endl;
    }
    // Display all students
    void displayAllStudents() const 
	{
        if (students.empty()) 
		{
            cout<<"No students in the system."<<endl;
            return;
        }
        cout<<"List of students:"<<endl;
        for (int i=0;i<students.size();i++) 
		{
            students[i].printInfo();
        }
    }
    // Save student information to a file
    void saveToFile(const string& filename) const 
	{
        ofstream file(filename);
        if (file.is_open()) 
		{
            for (const auto& student : students) 
			{
                file<<student.getName()<<","<<student.getEnroll()<<","<<student.getAge()<<","<<student.getGrade()<<endl;
            }
            file.close();
            cout<<"Student information saved to file."<<endl;
        } 
		else 
		{
            cout << "Unable to open file." << endl;
        }
    }
    // Read student information from a file
    void loadFromFile(const string& filename) 
	{
        ifstream file(filename);
        if (file.is_open()) 
		{
            students.clear();     // Clear existing student data
            string line;
            while(getline(file,line)) 
			{
                stringstream ss(line);
                string name,enroll;
                int age;
                double grade;
                getline(ss,name,',');
                getline(ss,enroll, ',');
                ss>>age;
                ss.ignore();
                ss>>grade;
                students.emplace_back(name,enroll,age,grade);
            }
            file.close();
            cout << "Student information loaded from file." << endl;
        } 
		else 
		{
            cout << "Unable to open file." << endl;
        }
    }  
};
// Function prototypes
string validname();
string validenroll();
int validage();
double validgrade();
int main() 
{
    StudentsManagementSystem system;
    cout << "Welcome to Students Management System" << endl;
    string filename = "student_data.txt";                
    system.loadFromFile(filename);   // Load student data from file
    int choice;
    string name;
    string enroll;
    int age;
    double grade;

    do 
	{
        cout << "------------------------------------------------------------------" << endl;
        cout << "Enter the number of option you want to choose" << endl;
        cout << "1. Add a student" << endl;
        cout << "2. Search for a student" << endl;
        cout << "3. Update student information" << endl;
        cout << "4. Delete a student" << endl;
        cout << "5. Calculate average grade" << endl;
        cout << "6. Display all students" << endl;
        cout << "7. Save student information to file" << endl;
        cout << "8. Exit" << endl;
        cout << "------------------------------------------------------------------" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice)
		{
            case 1:
            {	
                cout << "Enter the name of the student you want to add: ";
                name=validname();
                cout << "Enter the enrollment no. of the student: ";
                enroll=validenroll();
                cout << "Enter the age of the student: ";
                age=validage();
                cout << "Enter the grade of the student: ";
                grade=validgrade();
                system.addStudent(Student(name,enroll,age,grade));
                break;
            }
            case 2:
            {	
                cout << "Enter the enrollment no. of the student you want to search: ";
                enroll=validenroll();
                system.searchStudent(enroll);
                break;
            }
            case 3:
            {	
                cout << "Enter the enrollment no. of the student to update: ";
                enroll=validenroll();
                cout << "Enter name for student: ";
                name=validname();
                cout << "Enter new age for " << name << ": ";
                age=validage();
                cout << "Enter new grade for " << name << ": ";
                grade=validgrade();
                system.updateStudent(name,enroll,age,grade);
                break;
            }
            case 4:
            {	
                cout << "Enter the enrollment no. of the student to delete: ";
                enroll=validenroll();
                system.deleteStudent(enroll);
                break;
            }
            case 5:
            {	
                system.calculateAverage();
                break;
            }
            case 6:
            {            	
                system.displayAllStudents();
                break;
            }
            case 7:
            {
               system.saveToFile(filename);	
               break;    	
			}	
            case 8:
            {	
                cout << "You chose to exit the system." << endl;
                break;
            }
            default:
            {	
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    } while (choice != 7);
    return 0;
}
string validname() 
{
	
    string name;
    bool isValid;
    do 
	{
	   isValid=true;
       getline(cin,name);
       if(name.empty()) 
	   {
			isValid=false;
            cout<<"Invalid input. Please enter name: ";
       }
       else
       {	
        	for (char c : name) 
            {
               if(!isalpha(c) && c!=' ' && c!='-')
               {
                    isValid=false;
                    cout<<"Invalid input. Please enter name: ";
	           }
		    }
	    }
    }
	while(!isValid);
    return name;
}
string validenroll() 
{
    string enroll;
    bool isValid;
    do 
	{
		isValid = true;
        getline(cin,enroll);
        if (enroll.empty()) 
		{
            isValid=false;
			cout<<"Invalid input. Please enter the enrollment number: ";
        } 
    }
	while(!isValid);
    return enroll;
}
int validage() 
{
    int age;
    bool isValid;
    do 
	{
		isValid = true;
		cin>>age;
        if(cin.fail() || age<0)
		{
			isValid=false;
            cout<<"Invalid input. Please enter age: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
    }
	while(!isValid);
    return age;
}
double validgrade() 
{
	double grade;
	bool isValid;
    do 
	{
	   isValid = true;
	   cin>>grade;
       if(cin.fail() || grade<0 || grade>100) 
	   {
            isValid=false;
		    cout<<"Invalid input. Please enter grade: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
    }
	while(!isValid);
    return grade;
}