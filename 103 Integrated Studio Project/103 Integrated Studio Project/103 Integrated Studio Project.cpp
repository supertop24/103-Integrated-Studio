#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <ctime>
using namespace std;

struct login
{
    string email;
    string password;
    string typeCode;//a for admin t for teacher p for parent
    string name;
    string loginAccT;//To keep tracking type acc that login first array for type of account, second for name
    string loginAccN;
};
struct teacher
{
    string name;
    string phone;
    string age;
    string subject;
};
struct student
{
    string name;
    int studentID;
    int Class;//1-5
    int age;
    int date, month, year;
    string mother;
    string father;
    string address;
    string phoneNumber;
};
struct grade
{
    string name;
    string code;//m=math e=english h=history s=science e=economic
    int score;
};
void writeLoginData(login login)
{
    ofstream outputFile("Login.txt", ios::app);

    if (outputFile.is_open())
    {
        outputFile << endl << login.email << "," << login.password << "," << login.typeCode << "," << login.name;
        outputFile.close();
    }
}
void teacherProfile(teacher teacher)
{
    ofstream outputFile("Teacher.txt", ios::app);

    if (outputFile.is_open())
    {
        outputFile << endl << teacher.name << "," << teacher.phone << "," << teacher.age << "," << teacher.subject;
        outputFile.close();
    }
}
void studentProfile(student student)
{
    ofstream outputFile("StudentInfo.txt", ios::app);

    if (outputFile.is_open())
    {
        outputFile << endl << student.name << "," << student.studentID << "," << student.Class << "," << student.age << "," << student.date << "," << student.month << "," << student.year << "," << student.mother << "," << student.father << "," << student.address << "," << student.phoneNumber;
        outputFile.close();
    }
}
void studentGrade(grade grade)
{
    ofstream outputFile("StudentGrade.txt", ios::app);

    if (outputFile.is_open())
    {
        outputFile << endl << grade.name << "," << grade.code << "," << grade.score;
        outputFile.close();
    }
}
void displayLogin(HANDLE screen, login& login);
void displaySorting(HANDLE screen, login login);
bool validateEmail(const string& a)
{
    regex b("^[A-Za-z0-9.%_+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

    return regex_match(a, b);
}
bool validatePassword(const string& a)
{
    regex b("^[A-Za-z0-9]{8,}$");

    return regex_match(a, b);
}
bool validateExistedEmail(login input)
{
    vector<string>email;
    vector<string>pass;
    vector<string>type;
    vector<string>name;
    if (input.email == "admin@admin.com")
    {
        return false;
    }
    ifstream inputFile("Login.txt");
    if (inputFile.is_open())
    {
        int line_count = 1;
        string line;
        while (getline(inputFile, line))
        {
            if (line.empty())
            {
            }
            else
            {
                stringstream ss(line);
                string token;
                int parameter_count = 1;
                while (getline(ss, token, ','))
                {
                    if (parameter_count == 1)
                    {
                        email.push_back(token);
                    }
                    if (parameter_count == 2)
                    {
                        pass.push_back(token);
                    }
                    if (parameter_count == 3)
                    {
                        type.push_back(token);
                    }
                    if (parameter_count == 4)
                    {
                        name.push_back(token);
                    }
                    parameter_count++;
                }
                line_count++;
            }
        }
        for (int a = 0; a < line_count - 1; a++)
        {
            if (email[a] == input.email)
            {
                inputFile.close();
                return false;
            }
        }
        inputFile.close();
    }
    return true;
}
bool dateValidation(int date, int month)
{
    if (month == 2)
    {
        if (date > 0 && date < 30)
        {
            return true;
        }
    }
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (date > 0 && date < 32)
        {
            return true;
        }
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (date > 0 && date < 31)
        {
            return true;
        }
    }
    return false;
}
string loginValidation(login& input)
{
    vector<string>email;
    vector<string>pass;
    vector<string>type;
    vector<string>name;
    if (input.email == "admin@admin.com")
    {
        if (input.password == "admin")
        {
            return input.loginAccT = "a";
        }
    }
    ifstream inputFile("Login.txt");
    if (inputFile.is_open())
    {
        int line_count = 1;
        string line;
        while (getline(inputFile, line))
        {
            if (line.empty())
            {

            }
            else
            {
                stringstream ss(line);
                string token;
                int parameter_count = 1;
                while (getline(ss, token, ','))
                {
                    if (parameter_count == 1)
                    {
                        email.push_back(token);
                    }
                    if (parameter_count == 2)
                    {
                        pass.push_back(token);
                    }
                    if (parameter_count == 3)
                    {
                        type.push_back(token);
                    }
                    if (parameter_count == 4)
                    {
                        name.push_back(token);
                    }
                    parameter_count++;
                }
                line_count++;
            }
        }
        for (int a = 0; a < line_count - 1; a++)
        {
            if (email[a] == input.email)
            {
                if (pass[a] == input.password)
                {
                    input.loginAccT = type[a];
                    input.loginAccN = name[a];
                    inputFile.close();
                    return input.loginAccT, input.loginAccN;
                }
            }
        }
        inputFile.close();
    }
    return input.loginAccT = "None";
}
void cursor(HANDLE screen, int row, int col)
{
    COORD position;
    position.Y = row;
    position.X = col;
    SetConsoleCursorPosition(screen, position);
}
struct listTeacher
{
    vector<string>name;
    vector<string>phone;
    vector<string>age;
    vector<string>subject;
};
void TeacherPassInfo(listTeacher& list, int& countS)
{
    ifstream inputFile("Teacher.txt");
    if (inputFile.is_open())
    {
        int line_count = 1;
        string line;
        while (getline(inputFile, line))
        {
            if (line.empty())
            {
            }
            else
            {
                stringstream ss(line);
                string token;
                int parameter_count = 1;
                while (getline(ss, token, ','))
                {
                    if (parameter_count == 1)
                    {
                        list.name.push_back(token);
                    }
                    if (parameter_count == 2)
                    {
                        list.phone.push_back(token);
                    }
                    if (parameter_count == 3)
                    {
                        list.age.push_back(token);
                    }
                    if (parameter_count == 4)
                    {
                        list.subject.push_back(token);
                    }
                    parameter_count++;
                }
                line_count++;
            }
        }
        countS = line_count - 1;
        inputFile.close();
    }
}
void displayTeacherProfile(HANDLE screen, login login, listTeacher list, int option)
{
    string temp;
    system("cls");
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << list.name[option - 1] << " Profile : " << endl;
    cursor(screen, 5, 26);
    cout << "Name : " << list.name[option - 1];
    cursor(screen, 6, 26);
    cout << "Age " << list.age[option - 1];
    cursor(screen, 7, 26);
    cout << "Phone Number : " << list.phone[option - 1];
    cursor(screen, 8, 26);
    cout << "Subject Teaching : " << list.subject[option - 1];
    cursor(screen, 10, 26);
    cout << "Press Enter to continue ";
    cin.ignore(10000, '\n');
    getline(cin, temp, '\n');
    displaySorting(screen, login);
}
void ViewTeacherProfile(HANDLE screen, login login)
{
    int option;
    int TeacherNumbers;
    listTeacher list;
    system("cls");
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "           View Teacher Profile           " << endl;
    cursor(screen, 5, 26);
    cout << "Teacher Name list :";
    TeacherPassInfo(list, TeacherNumbers);
    for (int a = 0; a < TeacherNumbers; a++)
    {
        cursor(screen, a + 6, 26);
        cout << a + 1 << ". " << list.name[a];
    }
    cursor(screen, 6 + TeacherNumbers, 26);
    cout << "Option input : " << endl;
    cursor(screen, 6 + TeacherNumbers, 40);
    cin >> option;
    while (option > TeacherNumbers || option < 1)
    {
        cursor(screen, 6 + TeacherNumbers, 45);
        cout << "Input a valid option!" << endl;
        cursor(screen, 6 + TeacherNumbers, 40);
        cout << "   ";
        cursor(screen, 6 + TeacherNumbers, 40);
        cin >> option;
    };
    displayTeacherProfile(screen, login, list, option);
}
void StudentPassInfo(student& student, login login)
{
    ifstream inputFile("StudentInfo.txt");
    if (inputFile.is_open())
    {
        int line_count = 1;
        string line;
        while (getline(inputFile, line))
        {
            if (line.empty())
            {
            }
            else
            {
                stringstream ss(line);
                string token;
                int parameter_count = 1;
                int filterNumber = 1;
                string filterName;
                while (getline(ss, token, ','))
                {
                    if (filterNumber == 1)
                    {
                        filterName = token;
                        filterNumber++;
                    }
                    if (filterName == login.loginAccN)
                    {
                        if (parameter_count == 1)
                        {
                            student.name = token;
                        }
                        if (parameter_count == 2)
                        {
                            student.studentID = stoi(token);
                        }
                        if (parameter_count == 3)
                        {
                            student.Class = stoi(token);
                        }
                        if (parameter_count == 4)
                        {
                            student.age = stoi(token);
                        }
                        if (parameter_count == 5)
                        {
                            student.date = stoi(token);
                        }
                        if (parameter_count == 6)
                        {
                            student.month = stoi(token);
                        }
                        if (parameter_count == 7)
                        {
                            student.year = stoi(token);
                        }
                        if (parameter_count == 8)
                        {
                            student.mother = token;
                        }
                        if (parameter_count == 9)
                        {
                            student.father = token;
                        }
                        if (parameter_count == 10)
                        {
                            student.address = token;
                        }
                        if (parameter_count == 11)
                        {
                            student.phoneNumber = token;
                        }
                        parameter_count++;
                    }
                }
                line_count++;
            }
            line_count - 1;
        }
    }
}
struct listGrade
{
    vector<int>ec;
    vector<int>hi;
    vector<int>ma;
    vector<int>en;
    vector<int>sc;
};
void GradePassInfo(listGrade& list, login login, int* subject)
{
    ifstream inputFile("StudentGrade.txt");
    if (inputFile.is_open())
    {
        int line_count = 0;
        string line;
        while (getline(inputFile, line))
        {
            if (line.empty())
            {
            }
            else
            {
                stringstream ss(line);
                string token;
                int parameter_count = 1;
                int temp = 1;
                int a;
                string temps, code;
                while (getline(ss, token, ','))
                {
                    if (login.loginAccN == token)
                    {
                        temps = token;
                        temp++;
                    }
                    if (temps == login.loginAccN)
                    {
                        if (parameter_count == 1)
                        {
                        }
                        if (parameter_count == 2)
                        {
                            code = token;
                            if (code == "ec")
                            {
                                subject[0]++;
                            }
                            if (code == "ma")
                            {
                                subject[1]++;
                            }
                            if (code == "hi")
                            {
                                subject[2]++;
                            }
                            if (code == "sc")
                            {
                                subject[3]++;
                            }
                            if (code == "en")
                            {
                                subject[4]++;
                            }
                        }
                        if (parameter_count == 3)
                        {
                            if (code == "ec")
                            {
                                a = stoi(token);
                                list.ec.push_back(a);
                            }
                            if (code == "ma")
                            {
                                a = stoi(token);
                                list.ma.push_back(a);
                            }
                            if (code == "hi")
                            {
                                a = stoi(token);
                                list.hi.push_back(a);
                            }
                            if (code == "sc")
                            {
                                a = stoi(token);
                                list.sc.push_back(a);
                            }
                            if (code == "en")
                            {
                                a = stoi(token);
                                list.en.push_back(a);
                            }
                        }
                        parameter_count++;
                    }
                    else
                    {

                    }
                }
                line_count++;
            }
        }
        inputFile.close();
    }
}
void ChildReportReview(HANDLE screen, login login)
{
    student student;
    string temp;
    listGrade list;
    int subject[5]{ 0,0,0,0,0 };//1 for ec, 2 for ma, 3 for hi, 4 for sc, 5 for en
    int page = 10;
    system("cls");
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "             Student's Report             " << endl;
    StudentPassInfo(student, login);
    cursor(screen, 5, 26);
    cout << "Name : " << student.name << endl;
    cursor(screen, 6, 26);
    cout << "Student ID : " << student.studentID << endl;
    cursor(screen, 7, 26);
    cout << "Class : " << student.Class << endl;
    GradePassInfo(list, login, subject);
    cursor(screen, 9, 26);
    cout << "Economic :";
    if (subject[0] == 0)
    {
        cursor(screen, page, 26);
        cout << "No grades yet!";
    }
    else
    {
        for (int a = 0; a < subject[0]; a++)
        {
            cursor(screen, page + a, 26);
            cout << a + 1 << ". " << list.ec[a];
        }
    }
    page += subject[0];
    cursor(screen, page + 1, 26);
    cout << "Math : ";
    if (subject[1] == 0)
    {
        cursor(screen, page + 2, 26);
        cout << "No grades yet!";
    }
    else
    {
        for (int a = 0; a < subject[1]; a++)
        {
            cursor(screen, page + 2 + a, 26);
            cout << a + 1 << ". " << list.ma[a];
        }
    }
    page += subject[1];
    cursor(screen, page + 3, 26);
    cout << "History :";
    if (subject[2] == 0)
    {
        cursor(screen, page + 4, 26);
        cout << "No grades yet!";
    }
    else
    {
        for (int a = 0; a < subject[2]; a++)
        {
            cursor(screen, page + 4 + a, 26);
            cout << a + 1 << ". " << list.hi[a];
        }
    }
    page += subject[2];
    cursor(screen, page + 5, 26);
    cout << "Science :";
    if (subject[3] == 0)
    {
        cursor(screen, page + 6, 26);
        cout << "No grades yet!";
    }
    else
    {
        for (int a = 0; a < subject[3]; a++)
        {
            cursor(screen, page + 6 + a, 26);
            cout << a + 1 << ". " << list.sc[a];
        }
    }
    page += subject[3];
    cursor(screen, page + 7, 26);
    cout << "English :";
    if (subject[4] == 0)
    {
        cursor(screen, page + 8, 26);
        cout << "No grades yet!";
    }
    else
    {
        for (int a = 0; a < subject[4]; a++)
        {
            cursor(screen, page + 8 + a, 26);
            cout << a + 1 << ". " << list.en[a];
        }
    }
    page += subject[4];
    cursor(screen, page + 10, 26);
    cout << "Press Enter to continue ";
    cin.ignore(10000, '\n');
    getline(cin, temp, '\n');
    displaySorting(screen, login);
}
void CreateTeacherAccount(HANDLE screen, login& login)
{
    teacher teacher;
    system("cls");
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "          Create Teacher Account          " << endl;
    cursor(screen, 5, 26);
    cout << "Enter Email : ";
    cursor(screen, 6, 26);
    cout << "Enter Password : ";
    cursor(screen, 7, 26);
    cout << "Enter Name : ";
    cursor(screen, 8, 26);
    cout << "Enter Age : ";
    cursor(screen, 9, 26);
    cout << "Enter Phone Number : ";
    cursor(screen, 10, 26);
    cout << "Enter Subject : ";
    cursor(screen, 5, 39);
    cin >> login.email;
    while (validateEmail(login.email) == false || validateExistedEmail(login) == false)
    {
        cursor(screen, 12, 26);
        cout << "Invalid email or already exist!" << endl;
        cursor(screen, 5, 39);
        cout << "                                             ";
        cursor(screen, 5, 39);
        cin >> login.email;
    }
    cursor(screen, 12, 26);
    cout << "                                             ";
    cursor(screen, 6, 42);
    cin >> login.password;
    while (validatePassword(login.password) == false)
    {
        cursor(screen, 12, 26);
        cout << "Invalid Password! (Minimal 8 Characters, No Special Characters)" << endl;
        cursor(screen, 6, 42);
        cout << "                                             ";
        cursor(screen, 6, 42);
        cin >> login.password;
    }
    cursor(screen, 12, 26);
    cout << "                                                                  ";
    cin.ignore(10000, '\n');
    cursor(screen, 7, 38);
    getline(cin, login.name);
    teacher.name = login.name;
    cursor(screen, 8, 37);
    cin >> teacher.age;
    cursor(screen, 9, 46);
    cin >> teacher.phone;
    cursor(screen, 10, 41);
    cin >> teacher.subject;
    login.typeCode = "t";
    writeLoginData(login);
    teacherProfile(teacher);
    displaySorting(screen, login);
}
void teacherProfileUpdating(listTeacher list, int TeacherNumbers)
{
    ofstream outputFile("Teacher.txt");

    if (outputFile.is_open())
    {
        for (int a = 0; a < TeacherNumbers; a++)
        {
            outputFile << endl << list.name[a] << "," << list.phone[a] << "," << list.age[a] << "," << list.subject[a];
        }
        outputFile.close();
    }
}
void displayTPforUpdate(HANDLE screen, login login, listTeacher& list, int option, int TeacherNumbers)
{
    string temp;
    int profilenumber;
    system("cls");
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << list.name[option - 1] << " Profile : " << endl;
    cursor(screen, 5, 26);
    cout << "Profile list : ";
    cursor(screen, 6, 26);
    cout << "1. Name : " << list.name[option - 1];
    cursor(screen, 7, 26);
    cout << "2. Age : " << list.age[option - 1];
    cursor(screen, 8, 26);
    cout << "3. Phone Number : " << list.phone[option - 1];
    cursor(screen, 9, 26);
    cout << "4. Subject Teaching : " << list.subject[option - 1];
    cursor(screen, 10, 26);
    cout << "5. Exit";
    cursor(screen, 12, 26);
    cout << "Select number of list to change : ";
    cursor(screen, 12, 58);
    cin >> profilenumber;
    while (profilenumber < 1 || profilenumber>5)
    {
        cursor(screen, 12, 62);
        cout << "Input valid option between 1-5!";
        cursor(screen, 12, 58);
        cout << "   ";
        cursor(screen, 12, 58);
        cin >> profilenumber;
    }
    cin.ignore(10000, '\n');
    switch (profilenumber)
    {
    case 1:
        cursor(screen, 6, 35);
        cout << "                                       ";
        cursor(screen, 6, 35);
        getline(cin, list.name[option - 1]);
        break;
    case 2:
        cursor(screen, 7, 34);
        cout << "                                       ";
        cursor(screen, 7, 34);
        cin >> list.age[option - 1];
        break;
    case 3:
        cursor(screen, 8, 43);
        cout << "                                       ";
        cursor(screen, 8, 43);
        cin >> list.phone[option - 1];
        break;
    case 4:
        cursor(screen, 9, 47);
        cout << "                                       ";
        cursor(screen, 9, 47);
        cin >> list.subject[option - 1];
        break;
    case 5:
        displaySorting(screen, login);
        break;
    }
    teacherProfileUpdating(list, TeacherNumbers);
    displaySorting(screen, login);
}
void ChangeTeacherProfile(HANDLE screen, login login)
{
    system("cls");
    int TeacherNumbers;
    int option;
    listTeacher list;
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "          Changes Teacher Profile         " << endl;
    cursor(screen, 5, 26);
    cout << "Teachers List : " << endl;
    TeacherPassInfo(list, TeacherNumbers);
    for (int a = 0; a < TeacherNumbers; a++)
    {
        cursor(screen, a + 6, 26);
        cout << a + 1 << ". " << list.name[a];
    }
    cursor(screen, 6 + TeacherNumbers, 26);
    cout << "Option input : " << endl;
    cursor(screen, 6 + TeacherNumbers, 40);
    cin >> option;
    while (option > TeacherNumbers || option < 1)
    {
        cursor(screen, 6 + TeacherNumbers, 45);
        cout << "Input a valid option!" << endl;
        cursor(screen, 6 + TeacherNumbers, 40);
        cout << "   ";
        cursor(screen, 6 + TeacherNumbers, 40);
        cin >> option;
    };
    displayTPforUpdate(screen, login, list, option, TeacherNumbers);
}
struct listStudent
{
    vector <string> name;
    vector <string >father;
    vector < string >address;
    vector<string>mom;
    vector <int> studentID;
    vector <int> Class;
    vector <int> age;
    vector <string>phoneNumber;
    vector<int> date;
    vector<int> month;
    vector<int> year;
};
void StudentsPassInfo(listStudent& list, int& counts)
{
    ifstream inputFile("StudentInfo.txt");
    if (inputFile.is_open())
    {
        int line_count = 0;
        string line;
        while (getline(inputFile, line))
        {
            if (line.empty())
            {
            }
            else
            {
                stringstream ss(line);
                string token;
                int parameter_count = 1;
                while (getline(ss, token, ','))
                {
                    int a;
                    if (parameter_count == 1)
                    {
                        list.name.push_back(token);
                    }
                    if (parameter_count == 2)
                    {
                        a = stoi(token);
                        list.studentID.push_back(a);
                    }
                    if (parameter_count == 3)
                    {
                        a = stoi(token);
                        list.Class.push_back(a);
                    }
                    if (parameter_count == 4)
                    {
                        a = stoi(token);
                        list.age.push_back(a);
                    }
                    if (parameter_count == 5)
                    {
                        a = stoi(token);
                        list.date.push_back(a);
                    }
                    if (parameter_count == 6)
                    {
                        a = stoi(token);
                        list.month.push_back(a);
                    }
                    if (parameter_count == 7)
                    {
                        a = stoi(token);
                        list.year.push_back(a);
                    }
                    if (parameter_count == 8)
                    {
                        list.mom.push_back(token);
                    }
                    if (parameter_count == 9)
                    {
                        list.father.push_back(token);
                    }
                    if (parameter_count == 10)
                    {
                        list.address.push_back(token);
                    }
                    if (parameter_count == 11)
                    {
                        list.phoneNumber.push_back(token);
                    }
                    parameter_count++;

                }
                line_count++;
            }
            line_count - 1;
        }
        counts = line_count;
        inputFile.close();
    }
}
bool studentIDValidation(int studentID)
{
    int counts = 0;
    listStudent list;
    StudentsPassInfo(list, counts);
    for (int a = 0; a < counts; a++)
    {
        if (studentID == list.studentID[a])
        {
            return false;
        }
    }
    return true;
}
void StudentNumbersCount(listStudent list, int counts, int option, int& ClassNumber)
{
    int temp = 0;
    for (int a = 0; a < counts; a++)
    {
        if (list.Class[a] == option)
        {
            temp++;
        }
    }
    ClassNumber = temp;
}
void Classdisplay(HANDLE screen, login login, int option)
{
    listStudent list;
    int StudentNumbers;
    int page = 5;
    int number = 0;
    int ClassNumber = 0;
    string temp;
    system("cls");
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "            Class " << option << " Student List" << "             " << endl;
    StudentsPassInfo(list, StudentNumbers);
    StudentNumbersCount(list, StudentNumbers, option, ClassNumber);
    if (ClassNumber == 0)
    {
        cursor(screen, page, 26);
        cout << "Class is empty!";
    }
    else
    {
        for (int a = 0; a < StudentNumbers; a++)
        {
            if (list.Class[a] == option)
            {
                cursor(screen, page + number, 26);
                cout << number + 1 << ". " << list.name[a] << " (" << list.studentID[a] << ")";
                number++;
            }
        }
    }
    page += ClassNumber;
    cursor(screen, page + 1, 26);
    cout << "Press Enter to continue ";
    cin.ignore(10000, '\n');
    getline(cin, temp, '\n');
    displaySorting(screen, login);
}
void ViewClassAndStudentProfile(HANDLE screen, login login)
{
    int option;
    system("cls");
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "      View Class and Student Profile      " << endl;
    cursor(screen, 5, 26);
    cout << "Class lists: " << endl;
    cursor(screen, 6, 26);
    cout << "1. Class 1";
    cursor(screen, 7, 26);
    cout << "2. Class 2";
    cursor(screen, 8, 26);
    cout << "3. Class 3";
    cursor(screen, 9, 26);
    cout << "4. Class 4";
    cursor(screen, 10, 26);
    cout << "5. Class 5";
    cursor(screen, 12, 26);
    cout << "Option input : ";
    cursor(screen, 12, 40);
    cin >> option;
    while (option > 5 || option < 1)
    {
        cursor(screen, 12, 45);
        cout << "Input a valid option!" << endl;
        cursor(screen, 12, 40);
        cout << "   ";
        cursor(screen, 12, 40);
        cin >> option;
    }
    Classdisplay(screen, login, option);
}
struct listLogin
{
    vector<string>email;
    vector<string>pass;
    vector<string>code;
    vector<string>name;
};
void LoginPassInfo(listLogin& list, int& counts)
{
    ifstream inputFile("Login.txt");
    if (inputFile.is_open())
    {
        int line_count = 0;
        string line;
        while (getline(inputFile, line))
        {
            if (line.empty())
            {
            }
            else
            {
                stringstream ss(line);
                string token;
                int parameter_count = 1;
                while (getline(ss, token, ','))
                {
                    if (parameter_count == 1)
                    {
                        list.email.push_back(token);
                    }
                    if (parameter_count == 2)
                    {
                        list.pass.push_back(token);
                    }
                    if (parameter_count == 3)
                    {
                        list.code.push_back(token);
                    }
                    if (parameter_count == 4)
                    {
                        list.name.push_back(token);
                    }
                    parameter_count++;
                }
                line_count++;
            }
            line_count - 1;
        }
        counts = line_count;
        inputFile.close();
    }
}
void loginUpdating(listLogin list, int counts)
{
    ofstream outputFile("Login.txt");

    if (outputFile.is_open())
    {
        for (int a = 0; a < counts; a++)
        {
            outputFile << endl << list.email[a] << "," << list.pass[a] << "," << list.code[a] << "," << list.name[a];
        }
        outputFile.close();
    }
}
void LoginCountLine(listStudent list, int option, int& check, int& countline, listLogin& lists)
{
    LoginPassInfo(lists, countline);
    for (int a = 0; a < countline; a++)
    {
        if (lists.name[a] == list.name[option - 1])
        {
            check = a;
        }
    }
}
void studentProfileUpdating(listStudent list, int counts)
{
    ofstream outputFile("StudentInfo.txt");

    if (outputFile.is_open())
    {
        for (int a = 0; a < counts; a++)
        {
            outputFile << endl << list.name[a] << "," << list.studentID[a] << "," << list.Class[a] << "," << list.age[a] << "," << list.date[a] << "," << list.month[a] << "," << list.year[a] << "," << list.mom[a] << "," << list.father[a] << "," << list.address[a] << "," << list.phoneNumber[a];
        }
        outputFile.close();
    }
}
struct listGradeUpdate
{
    vector<string>name;
    vector<string>code;
    vector<int>score;
    vector<int>check;
};
void GradePassInfo(listGradeUpdate& grade, int& line_counts, string name)
{
    ifstream inputFile("StudentGrade.txt");
    if (inputFile.is_open())
    {
        int line_count = 0;
        string line;
        int check = 0;
        while (getline(inputFile, line))
        {
            if (line.empty())
            {
            }
            else
            {
                stringstream ss(line);
                string token;
                int parameter_count = 1;
                int a;
                while (getline(ss, token, ','))
                {
                    if (parameter_count == 1)
                    {
                        grade.name.push_back(token);
                    }
                    if (parameter_count == 2)
                    {
                        grade.code.push_back(token);
                    }
                    if (parameter_count == 3)
                    {
                        a = stoi(token);
                        grade.score.push_back(a);
                        check++;
                    }
                    if (parameter_count == 1 && token == name)
                    {
                        grade.check.push_back(check);
                        line_counts++;
                    }
                    parameter_count++;
                }
                line_count++;
            }
            line_count - 1;
        }
        inputFile.close();
    }
}
void gradeUpdateing(listGradeUpdate grade, int counts)
{
    ofstream outputFile("StudentGrade.txt");

    if (outputFile.is_open())
    {
        for (int a = 0; a < counts; a++)
        {
            outputFile << endl << grade.name[grade.check[a]] << "," << grade.code[grade.check[a]] << "," << grade.score[grade.check[a]];
        }
        outputFile.close();
    }
}
void displaySPforUpdate(HANDLE screen, login login, listStudent& list, int option, int counts)
{
    int profilenumber;
    int check;
    int countline;
    int gradecounts = 0;
    listGradeUpdate grade;
    listLogin lists;
    system("cls");
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << list.name[option - 1] << "'s Profile :" << endl;
    cursor(screen, 5, 26);
    cout << "1. Student ID :" << list.studentID[option - 1] << endl;
    cursor(screen, 6, 26);
    cout << "2. Student Name : " << list.name[option - 1] << endl;
    cursor(screen, 7, 26);
    cout << "3. Class : " << list.Class[option - 1] << endl;
    cursor(screen, 8, 26);
    cout << "4. Age : " << list.age[option - 1] << endl;
    cursor(screen, 9, 26);
    cout << "5. Date of Birth :" << list.month[option - 1] << "/" << list.date[option - 1] << "/" << list.year[option - 1] << endl;
    cursor(screen, 10, 26);
    cout << "6. Mother Name : " << list.mom[option - 1] << endl;
    cursor(screen, 11, 26);
    cout << "7. Father Name : " << list.father[option - 1] << endl;
    cursor(screen, 12, 26);
    cout << "8. Address : " << list.address[option - 1] << endl;
    cursor(screen, 13, 26);
    cout << "9. Contact : " << list.phoneNumber[option - 1] << endl;
    cursor(screen, 14, 26);
    cout << "10. Exit";
    cursor(screen, 16, 26);
    cout << "Select number of list to change : ";
    cursor(screen, 16, 59);
    cin >> profilenumber;
    cin.ignore(10000, '\n');
    while (profilenumber < 1 || profilenumber>10)
    {
        cursor(screen, 16, 63);
        cout << "Input valid option between 1-10!";
        cursor(screen, 16, 59);
        cout << "   ";
        cursor(screen, 16, 59);
        cin >> profilenumber;
    }
    switch (profilenumber)
    {
    case 1:
        cursor(screen, 5, 41);
        cout << "                                       ";
        cursor(screen, 5, 41);
        cin >> list.studentID[option - 1];
        break;
    case 2:
        cursor(screen, 6, 43);
        cout << "                                       ";
        cursor(screen, 6, 43);
        LoginCountLine(list, option, check, countline, lists);
        GradePassInfo(grade, gradecounts, list.name[option - 1]);
        getline(cin, list.name[option - 1]);
        lists.name[check] = list.name[option - 1];
        for (int a = 0; a < gradecounts; a++)
        {
            grade.name[grade.check[a]] = list.name[option - 1];
        }
        gradeUpdateing(grade, gradecounts);
        loginUpdating(lists, countline);
        break;
    case 3:
        cursor(screen, 7, 36);
        cout << "                                       ";
        cursor(screen, 7, 36);
        cin >> list.Class[option - 1];
        while (list.Class[option - 1] < 1 || list.Class[option - 1]>5)
        {
            cursor(screen, 7, 43);
            cout << "Please enter valid class 1-5!" << endl;
            cursor(screen, 7, 36);
            cout << "    ";
            cursor(screen, 7, 36);
            cin >> list.Class[option - 1];
        }
        break;
    case 4:
        cursor(screen, 8, 34);
        cout << "                                       ";
        cursor(screen, 8, 34);
        cin >> list.age[option - 1];
        break;
    case 5:
        cursor(screen, 9, 44);
        cout << "MM";
        cursor(screen, 9, 46);
        cout << "/";
        cursor(screen, 9, 47);
        cout << "DD";
        cursor(screen, 9, 49);
        cout << "/";
        cursor(screen, 9, 50);
        cout << "YYYY";
        cursor(screen, 9, 44);
        cout << "  ";
        cursor(screen, 9, 44);
        cin >> list.month[option - 1];
        while (list.month[option - 1] < 1 || list.month[option - 1]>12)
        {
            cursor(screen, 9, 55);
            cout << "Input valid month between 1-12!";
            cursor(screen, 9, 44);
            cout << "  ";
            cursor(screen, 9, 44);
            cin >> list.month[option - 1];
        }
        cursor(screen, 9, 55);
        cout << "                                  ";
        cursor(screen, 9, 47);
        cout << "  ";
        cursor(screen, 9, 47);
        cin >> list.date[option - 1];
        while (dateValidation(list.date[option - 1], list.month[option - 1]) == false)
        {
            cursor(screen, 9, 55);
            cout << "Input valid date!";
            cursor(screen, 9, 47);
            cout << "  ";
            cursor(screen, 9, 47);
            cin >> list.date[option - 1];
        }
        cursor(screen, 9, 55);
        cout << "                                  ";
        cursor(screen, 9, 50);
        cout << "    ";
        cursor(screen, 9, 50);
        cin >> list.year[option - 1];
        while (list.year[option - 1] < 1950 || list.year[option - 1]>2020)
        {
            cursor(screen, 9, 55);
            cout << "Input valid year!";
            cursor(screen, 9, 50);
            cout << "    ";
            cursor(screen, 9, 50);
            cin >> list.year[option - 1];
        }
        cursor(screen, 9, 55);
        cout << "                                  ";
        break;
    case 6:
        cursor(screen, 10, 42);
        cout << "                                       ";
        cursor(screen, 10, 42);
        getline(cin, list.mom[option - 1]);
        break;
    case 7:
        cursor(screen, 11, 42);
        cout << "                                       ";
        cursor(screen, 11, 42);
        getline(cin, list.father[option - 1]);
        break;
    case 8:
        cursor(screen, 12, 38);
        cout << "                                       ";
        cursor(screen, 12, 38);
        getline(cin, list.address[option - 1]);
        break;
    case 9:
        cursor(screen, 13, 38);
        cout << "                                       ";
        cursor(screen, 13, 38);
        cin >> list.phoneNumber[option - 1];
        break;
    case 10:
        displaySorting(screen, login);
        break;
    }
    studentProfileUpdating(list, counts);
    displaySorting(screen, login);
}
void ChangeStudentProfile(HANDLE screen, login login)
{
    system("cls");
    listStudent list;
    int option;
    int counts;
    int page = 6;
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "          Change Student Profile          " << endl;
    cursor(screen, 5, 26);
    cout << "Students list :";
    StudentsPassInfo(list, counts);
    if (counts == 0)
    {
        cursor(screen, 6, 26);
        cout << "None of Student!";
    }
    else
    {
        for (int a = 0; a < counts; a++)
        {
            cursor(screen, page + a, 26);
            cout << a + 1 << ". " << list.name[a] << " (" << list.studentID[a] << ")";
        }
        cursor(screen, page + counts + 2, 26);
        cout << "Option input :";
        cursor(screen, page + counts + 2, 40);
        cin >> option;
        while (option > counts || option < 1)
        {
            cursor(screen, page + counts + 2, 45);
            cout << "Input a valid option!" << endl;
            cursor(screen, page + counts + 2, 40);
            cout << "   ";
            cursor(screen, page + counts + 2, 40);
            cin >> option;
        };
        displaySPforUpdate(screen, login, list, option, counts);
    }
}
bool studentIDValidation(int studentID, listStudent list, int counts, int& ary)
{
    for (int a = 0; a < counts; a++)
    {
        if (list.studentID[a] == studentID)
        {
            ary = a;
            return true;
        }
    }
    return false;
}
void InputStudentGrade(HANDLE screen, login login)
{
    system("cls");
    grade grade;
    int studentID, option, counts, ary;
    listStudent list;
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "          Input Student's Grades          " << endl;
    cursor(screen, 5, 26);
    cout << "Student's ID : ";
    cursor(screen, 5, 40);
    cin >> studentID;
    StudentsPassInfo(list, counts);
    while (studentIDValidation(studentID, list, counts, ary) == false)
    {
        cursor(screen, 5, 40);
        cout << "           ";
        cursor(screen, 5, 51);
        cout << "Invalid ID!";
        cursor(screen, 5, 40);
        cin >> studentID;
    }
    cursor(screen, 6, 26);
    cout << list.name[ary] << "'s Score";
    cursor(screen, 7, 26);
    cout << "Subject List :" << endl;
    cursor(screen, 8, 26);
    cout << "1. Economic" << endl;
    cursor(screen, 9, 26);
    cout << "2. Math" << endl;
    cursor(screen, 10, 26);
    cout << "3. History" << endl;
    cursor(screen, 11, 26);
    cout << "4. Science" << endl;
    cursor(screen, 12, 26);
    cout << "5. English" << endl;
    cursor(screen, 13, 26);
    cout << "Option input : " << endl;
    cursor(screen, 14, 26);
    cout << "Grade input : " << endl;
    cursor(screen, 13, 40);
    cin >> option;
    while (option < 1 || option>5)
    {
        cursor(screen, 13, 45);
        cout << "Invalid option!";
        cursor(screen, 13, 40);
        cout << "    ";
        cursor(screen, 13, 40);
        cin >> option;
    }
    switch (option)
    {
    case 1:
        grade.code = "ec";
        break;
    case 2:
        grade.code = "ma";
        break;
    case 3:
        grade.code = "hi";
        break;
    case 4:
        grade.code = "sc";
        break;
    case 5:
        grade.code = "en";
        break;
    }
    cursor(screen, 13, 45);
    cout << "                     ";
    cursor(screen, 14, 39);
    cin >> grade.score;
    while (grade.score > 100 || grade.score < 0)
    {
        cursor(screen, 14, 44);
        cout << "Input valid grade between 0-100";
        cursor(screen, 14, 39);
        cout << "     ";
        cursor(screen, 14, 39);
        cin >> grade.score;
    }
    grade.name = list.name[ary];
    studentGrade(grade);
    displaySorting(screen, login);
}
void AddingStudentProfile(HANDLE screen, login& login)
{
    system("cls");
    string dob[3];
    student student;
    srand((unsigned)time(0));
    student.studentID = 10000 + rand() % 10000;
    while (studentIDValidation(student.studentID) == false)
    {
        student.studentID = 10000 + rand() % 10000;
    }
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "          Adding Student Profile          " << endl;
    cursor(screen, 5, 26);
    cout << "Student ID :" << student.studentID << endl;
    cursor(screen, 6, 26);
    cout << "Student Name : " << endl;
    cursor(screen, 7, 26);
    cout << "Class :       (Class 1-5)" << endl;
    cursor(screen, 8, 26);
    cout << "Age : " << endl;
    cursor(screen, 9, 26);
    cout << "Date of Birth :MM/DD/YYYY" << endl;
    cursor(screen, 10, 26);
    cout << "Mother Name : " << endl;
    cursor(screen, 11, 26);
    cout << "Father Name : " << endl;
    cursor(screen, 12, 26);
    cout << "Address : " << endl;
    cursor(screen, 13, 26);
    cout << "Contact : " << endl;
    cursor(screen, 14, 26);
    cout << "Email : " << endl;
    cursor(screen, 15, 26);
    cout << "Password : " << endl;
    cin.ignore(10000, '\n');
    cursor(screen, 6, 40);
    getline(cin, student.name);
    login.name = student.name;
    cursor(screen, 7, 33);
    cin >> student.Class;
    while (student.Class < 1 || student.Class>5)
    {
        cursor(screen, 7, 40);
        cout << "Please enter valid class 1-5!" << endl;
        cursor(screen, 7, 33);
        cout << "    ";
        cursor(screen, 7, 33);
        cin >> student.Class;
    }
    cursor(screen, 8, 31);
    cin >> student.age;
    cursor(screen, 9, 41);
    cout << "  ";
    cursor(screen, 9, 41);
    cin >> student.month;
    while (student.month < 1 || student.month>12)
    {
        cursor(screen, 9, 52);
        cout << "Input valid month between 1-12!";
        cursor(screen, 9, 41);
        cout << "  ";
        cursor(screen, 9, 41);
        cin >> student.month;
    }
    cursor(screen, 9, 52);
    cout << "                                  ";
    cursor(screen, 9, 44);
    cout << "  ";
    cursor(screen, 9, 44);
    cin >> student.date;
    while (dateValidation(student.date, student.month) == false)
    {
        cursor(screen, 9, 52);
        cout << "Input valid date!";
        cursor(screen, 9, 44);
        cout << "  ";
        cursor(screen, 9, 44);
        cin >> student.date;
    }
    cursor(screen, 9, 52);
    cout << "                                  ";
    cursor(screen, 9, 47);
    cout << "    ";
    cursor(screen, 9, 47);
    cin >> student.year;
    while (student.year < 1950 || student.year>2020)
    {
        cursor(screen, 9, 52);
        cout << "Input valid year!";
        cursor(screen, 9, 47);
        cout << "    ";
        cursor(screen, 9, 47);
        cin >> student.year;
    }
    cursor(screen, 9, 52);
    cout << "                                  ";
    cin.ignore(10000, '\n');
    cursor(screen, 10, 39);
    getline(cin, student.mother);
    cursor(screen, 11, 39);
    getline(cin, student.father);
    cursor(screen, 12, 35);
    getline(cin, student.address);
    cursor(screen, 13, 35);
    cin >> student.phoneNumber;
    cursor(screen, 14, 33);
    cin >> login.email;
    while (validateEmail(login.email) == false || validateExistedEmail(login) == false)
    {
        cursor(screen, 17, 26);
        cout << "Invalid email or already exist!" << endl;
        cursor(screen, 14, 33);
        cout << "                                             ";
        cursor(screen, 14, 33);
        cin >> login.email;
    }
    cursor(screen, 17, 26);
    cout << "                                             ";
    cursor(screen, 15, 36);
    cin >> login.password;
    while (validatePassword(login.password) == false)
    {
        cursor(screen, 17, 26);
        cout << "Invalid Password! (Minimal 8 Characters, No Special Characters)" << endl;
        cursor(screen, 15, 36);
        cout << "                                             ";
        cursor(screen, 15, 36);
        cin >> login.password;
    }
    login.typeCode = "p";
    studentProfile(student);
    writeLoginData(login);
    displaySorting(screen, login);
}
void adminDisplay(HANDLE screen, login login)
{
    system("cls");
    int option;
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "              Admin Options              " << endl;
    cursor(screen, 5, 26);
    cout << "1. Create Teacher Account" << endl;
    cursor(screen, 6, 26);
    cout << "2. View Teacher Profile" << endl;
    cursor(screen, 7, 26);
    cout << "3. Change Teacher Profile" << endl;
    cursor(screen, 8, 26);
    cout << "4. View Class and Student Profile" << endl;
    cursor(screen, 9, 26);
    cout << "5. Child Report Review" << endl;
    cursor(screen, 10, 26);
    cout << "6. Adding Student Profile" << endl;
    cursor(screen, 11, 26);
    cout << "7. Input Student Grade" << endl;
    cursor(screen, 12, 26);
    cout << "8. Change Student Profile" << endl;
    cursor(screen, 13, 26);
    cout << "9. Log out" << endl;
    cursor(screen, 15, 26);
    cout << "Option input : " << endl;
    cursor(screen, 15, 40);
    cin >> option;
    while (option > 9 || option < 1)
    {
        cursor(screen, 15, 45);
        cout << "Input a valid option!" << endl;
        cursor(screen, 15, 40);
        cout << "   ";
        cursor(screen, 15, 40);
        cin >> option;
    };
    switch (option)
    {
    case 1:
        CreateTeacherAccount(screen, login);
        break;
    case 2:
        ViewTeacherProfile(screen, login);
        break;
    case 3:
        ChangeTeacherProfile(screen, login);
        break;
    case 4:
        ViewClassAndStudentProfile(screen, login);
        break;
    case 5:
        ChildReportReview(screen, login);
        break;
    case 6:
        AddingStudentProfile(screen, login);
        break;
    case 7:
        InputStudentGrade(screen, login);
        break;
    case 8:
        ChangeStudentProfile(screen, login);
        break;
    case 9:
        displayLogin(screen, login);
        break;
    }
}
void parentDisplay(HANDLE screen, login login)
{
    system("cls");
    int option;
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "             Parents Options             " << endl;
    cursor(screen, 5, 26);
    cout << "1. Child Report Review" << endl;
    cursor(screen, 6, 26);
    cout << "2. View Teacher Profile" << endl;
    cursor(screen, 7, 26);
    cout << "3. Log out" << endl;
    cursor(screen, 9, 26);
    cout << "Option input : " << endl;
    cursor(screen, 9, 40);
    cin >> option;
    while (option > 3 || option < 1)
    {
        cursor(screen, 9, 45);
        cout << "Input a valid option!" << endl;
        cursor(screen, 9, 40);
        cout << "   ";
        cursor(screen, 9, 40);
        cin >> option;
    };
    switch (option)
    {
    case 1:
        ChildReportReview(screen, login);
        break;
    case 2:
        ViewTeacherProfile(screen, login);
        break;
    case 3:
        displayLogin(screen, login);
        break;
    }
}
void teacherDisplay(HANDLE screen, login login)
{
    system("cls");
    int option;
    cursor(screen, 1, 26);
    cout << "Auckland Primary School's Data Information" << endl;
    cursor(screen, 3, 26);
    cout << "              Teacher Options             " << endl;
    cursor(screen, 5, 26);
    cout << "1. View Class and Student Profile" << endl;
    cursor(screen, 6, 26);
    cout << "2. Adding Student Profile" << endl;
    cursor(screen, 7, 26);
    cout << "3. Input Student Grade" << endl;
    cursor(screen, 8, 26);
    cout << "4. Change Student Profile" << endl;
    cursor(screen, 9, 26);
    cout << "5. Log out" << endl;
    cursor(screen, 11, 26);
    cout << "Option input : " << endl;
    cursor(screen, 11, 40);
    cin >> option;
    while (option > 5 || option < 1)
    {
        cursor(screen, 11, 45);
        cout << "Input a valid option!" << endl;
        cursor(screen, 11, 40);
        cout << "   ";
        cursor(screen, 11, 40);
        cin >> option;
    };
    switch (option)
    {
    case 1:
        ViewClassAndStudentProfile(screen, login);
        break;
    case 2:
        AddingStudentProfile(screen, login);
        break;
    case 3:
        InputStudentGrade(screen, login);
        break;
    case 4:
        ChangeStudentProfile(screen, login);
        break;
    case 5:
        displayLogin(screen, login);
        break;
    }
}
void numberOfAttemps(HANDLE screen, int attempts)
{
    if (attempts == 1)
    {
        cursor(screen, 9, 26);
        cout << "2 Attempts left!" << endl;
    }
    if (attempts == 2)
    {
        cursor(screen, 9, 26);
        cout << "1 Attempts left!" << endl;
    }
    if (attempts == 3)
    {
        cursor(screen, 5, 26);
        cout << "Out of attempts to login!" << endl;
        cursor(screen, 7, 26);
        cout << "Program is Terminated!" << endl;
        exit(0);
    }
}
void displayLogin(HANDLE screen, login& login)
{
    int attempts = 0;
    do
    {
        system("cls");
        cursor(screen, 1, 26);
        cout << "Auckland Primary School's Data Information" << endl;
        cursor(screen, 3, 26);
        cout << "                   LOGIN                  " << endl;
        numberOfAttemps(screen, attempts);
        cursor(screen, 5, 26);
        cout << "Email : " << endl;
        cursor(screen, 7, 26);
        cout << "Password : " << endl;
        cursor(screen, 5, 33);
        cin >> login.email;
        cursor(screen, 7, 36);
        cin >> login.password;
        loginValidation(login);
        displaySorting(screen, login);
        attempts++;
    } while (login.loginAccT == "None");
}
void displaySorting(HANDLE screen, login login)
{
    if (login.loginAccT == "a")
    {
        adminDisplay(screen, login);
    }
    else if (login.loginAccT == "t")
    {
        teacherDisplay(screen, login);
    }
    else if (login.loginAccT == "p")
    {
        parentDisplay(screen, login);
    }
}
int main()
{
    login login;
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    displayLogin(screen, login);
}
