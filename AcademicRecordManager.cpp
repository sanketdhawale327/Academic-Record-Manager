#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>

using namespace std;

class Student
{
public:
    int roll;
    string name;
    string division;
    float marks;
};

vector<Student> students;

// Store all student records in CSV file (Comma-Separated Values)
void saveToFile()
{
    ofstream file("students.csv");

    for (const auto &s : students)
    {
        file << s.roll << ","
             << s.name << ","
             << s.division << ","
             << s.marks << endl;
    }

    file.close();
}

// Read student data from CSV file
void loadFromFile()
{
    ifstream file("students.csv");

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        Student s;
        string temp;

        getline(ss, temp, ',');
        s.roll = stoi(temp);

        getline(ss, s.name, ',');

        getline(ss, s.division, ',');

        getline(ss, temp, ',');
        s.marks = stof(temp);

        students.push_back(s);
    }

    file.close();
}

int getValidRoll()
{
    int roll;

    while (!(cin >> roll) || roll <= 0)
    {
        cout << "Invalid Roll Number! Enter Again: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return roll;
}

float getValidMarks()
{
    float marks;

    while (!(cin >> marks) || marks < 0 || marks > 100)
    {
        cout << "Invalid Marks! Enter Between 0 and 100: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return marks;
}

void addStudent()
{
    Student s;

    cout << "\nEnter Roll No: ";
    s.roll = getValidRoll();

    for (const auto &st : students)
    {
        if (st.roll == s.roll)
        {
            cout << "Roll Number Already Exists!\n";
            return;
        }
    }

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Division: ";
    getline(cin, s.division);

    cout << "Enter Marks: ";
    s.marks = getValidMarks();

    students.push_back(s);

    saveToFile();

    cout << "\nStudent Added Successfully!\n";
}

void displayStudents()
{
    if (students.empty())
    {
        cout << "\nNo Records Found!\n";
        return;
    }

    cout << "\n===== STUDENT RECORDS =====\n";

    for (const auto &s : students)
    {
        cout << "\nRoll No : " << s.roll;
        cout << "\nName    : " << s.name;
        cout << "\nDivision: " << s.division;
        cout << "\nMarks   : " << s.marks;
        cout << "\n--------------------------\n";
    }
}

void searchStudent()
{
    cout << "\nEnter Roll No to Search: ";

    int roll = getValidRoll();

    for (const auto &s : students)
    {
        if (s.roll == roll)
        {
            cout << "\nStudent Found!\n";
            cout << "Name    : " << s.name << endl;
            cout << "Division: " << s.division << endl;
            cout << "Marks   : " << s.marks << endl;
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

void updateStudent()
{
    cout << "\nEnter Roll No to Update: ";

    int roll = getValidRoll();

    for (auto &s : students)
    {
        if (s.roll == roll)
        {
            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Division: ";
            getline(cin, s.division);

            cout << "Enter New Marks: ";
            s.marks = getValidMarks();

            saveToFile();

            cout << "\nStudent Updated Successfully!\n";
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

void deleteStudent()
{
    cout << "\nEnter Roll No to Delete: ";

    int roll = getValidRoll();

    for (auto it = students.begin(); it != students.end(); ++it)
    {
        if (it->roll == roll)
        {
            students.erase(it);

            saveToFile();

            cout << "\nStudent Deleted Successfully!\n";
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}

void sortByMarks()
{
    sort(students.begin(), students.end(),
         [](const Student &a, const Student &b)
         {
             return a.marks > b.marks;
         });

    cout << "\nStudents Sorted By Marks (Descending)\n";
}

void statistics()
{
    if (students.empty())
    {
        cout << "\nNo Records Available!\n";
        return;
    }

    float total = 0;
    float highest = students[0].marks;
    float lowest = students[0].marks;

    int pass = 0;
    int fail = 0;

    for (const auto &s : students)
    {
        total += s.marks;

        if (s.marks > highest)
            highest = s.marks;

        if (s.marks < lowest)
            lowest = s.marks;

        if (s.marks >= 40)
            pass++;
        else
            fail++;
    }

    cout << "\n===== STATISTICS =====\n";
    cout << "Average Marks : " << total / students.size() << endl;
    cout << "Highest Marks : " << highest << endl;
    cout << "Lowest Marks  : " << lowest << endl;
    cout << "Pass Students : " << pass << endl;
    cout << "Fail Students : " << fail << endl;
}

int main()
{
    loadFromFile();

    int choice;

    do
    {
        cout << "\n\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort By Marks\n";
        cout << "7. Statistics\n";
        cout << "8. Exit\n";

        cout << "Enter Choice: ";

        while (!(cin >> choice))
        {
            cout << "Invalid Choice! Enter Again: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice)
        {
        case 1:
            addStudent();
            break;

        case 2:
            displayStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            sortByMarks();
            break;

        case 7:
            statistics();
            break;

        case 8:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}