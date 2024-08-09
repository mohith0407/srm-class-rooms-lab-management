#include <bits/stdc++.h>
using namespace std;
int validate_email(string email) // ! status : checked
{
    if (email.length() > 13) // ! @srmap.edu.in - length is 13
    {
        int n = email.find('@');
        if (n != 0)
        {
            int uscore = 0;
            for (int i = 0; i < n; i++)
            {
                if (email[i] < 'a' || email[i] > 'z')
                {
                    if (email[i] == '_' && uscore != 1)
                        uscore += 1; // ! only one '_' is allowed
                    else
                        return 0;
                }
            }
            if (email.substr(n + 1) == "srmap.edu.in")
                return 1;
            return 0;
        }
        else
            return 0;
    }
    else
        return 0;
}
string is_there(string log, string user_name) // ! status : checked3
{
    ifstream file(log);
    string x; // ! checking if user already exist or not
    while (file)
    {
        getline(file, x);
        if (x.substr(0, x.find(' ')) == user_name)
        {
            file.close();
            return x;
        }
    }
    file.close();
    return "0";
}
string user_login(int x = 1) // ! status = checked
{
    string user_name, password;
    string log;
    if (x == 1)
        log = "admin_password_log.txt";
    else
        log = "password_log.txt";
    do
    {
        int n;
        if (x == 1)
        {
            cout << "\t\t\t\t========================================================================" << endl;
            cout << "\t\t\t\t|                                                                      |" << endl;
            cout << "\t\t\t\t|   1.Register                                                         |" << endl;
            cout << "\t\t\t\t|   2.Login                                                            |" << endl;
            cout << "\t\t\t\t|   3.Reset your password                                              |" << endl;
            cout << "\t\t\t\t|   4.Exit                                                             |" << endl;
            cout << "\t\t\t\t|                                                                      |" << endl;
            cout << "\t\t\t\t========================================================================" << endl;
            cout << "\t\t\t\tEnter choise : ";
            cin >> n;
        }
        else
        {
            cout << "\t\t\t\t========================================================================" << endl;
            cout << "\t\t\t\t|                                                                      |" << endl;
            cout << "\t\t\t\t|   1.Login                                                            |" << endl;
            cout << "\t\t\t\t|   2.Reset your password                                              |" << endl;
            cout << "\t\t\t\t|   3.Exit                                                             |" << endl;
            cout << "\t\t\t\t|                                                                      |" << endl;
            cout << "\t\t\t\t========================================================================" << endl;
            cout << "\t\t\t\tEnter choise : ";
            cin >> n;
            n++;
        }
        switch (n)
        {
        case 1:
        {
            fflush(stdin);
            cout << "\t\t\t\tEnter email id : ";
            getline(cin, user_name);
            if (validate_email(user_name))
            {
                if (is_there(log, user_name) == "0")
                {
                    string x;
                    do
                    {
                        cout << "\t\t\t\tEnter password ( min 8 characters ): ";
                        getline(cin, password);
                        if (password.length() >= 8)
                        {
                            cout << "\t\t\t\tConform your password : "; // ! reverifying password
                            getline(cin, x);
                            if (x != password)
                                cout << "\t\t\t\t\t\t- password not matched re enter again -\n";
                            else
                                break;
                        }
                        else
                            cout << "\t\t\t\t\t\t!!!!! ~ password length must be minimum 8" << endl;

                    } while (1);
                    cout << "\n\t\t\t\t\t\t --- you are successfully registered ---\n\n";
                    ofstream file(log, ios::app);
                    file << user_name + " " + password << endl; // ! adding new user into log
                    file.close();
                }
                else
                    cout << "\t\t\t\t\t\tUser already exist......!/#$%^*()" << endl;
            }
            else
                cout << "\t\t\t\t\t\tInvalid username......!/#$%^*()\n";

            break;
        }
        case 2:
        {
            ifstream file(log);
            fflush(stdin);
            cout << "\t\t\t\tEnter email id : ";
            getline(cin, user_name);
            cout << "\t\t\t\tEnter password : ";
            getline(cin, password);
            if (validate_email(user_name))
            {
                string x = is_there(log, user_name);
                if (x != "0")
                {
                    x = x.substr(x.find(' ') + 1);
                    if (x == password)
                        return user_name;
                    else
                        cout << "\t\t\t\t\t\tIncorrect password......!/#$%^*()" << endl;
                }
                else
                    cout << "\t\t\t\tuser does not exist......!/#$%^*()" << endl;
            }
            else
                cout << "\t\t\t\tInvalid username and password......!/#$%^*()\n";
            break;
        }
        case 3:
        {
            ifstream file(log);
            ofstream t("temp.txt", ios::app);
            fflush(stdin);
            cout << "\t\t\t\tEnter user_name : ";
            getline(cin, user_name);
            if (validate_email(user_name))
            {
                int p = 0;
                while (file)
                {
                    string pass, user;
                    getline(file, user);
                    pass = user.substr(user.find(" ") + 1);
                    if (user == user_name)
                    {
                        p = 1;
                        do
                        {
                            cout << "\t\t\t\tEnter password : ";
                            getline(cin, password);
                            cout << "\t\t\t\tConform your password : ";
                            getline(cin, pass);
                            if (pass != password)
                                cout << "\t\t\t\t- password not matched re enter again -\n";
                            else
                            {
                                p = 2;
                                cout << "\t\t\t\tpassword updated\n";
                                break;
                            }
                        } while (1);
                    }
                    t << (user + " " + pass) << endl;
                }
                file.close();
                t.close();
                if (p == 0)
                {
                    cout << "\t\t\t\tInvalid username\n"
                         << "\t\t\t\tUser is un registered\n";
                    remove("temp.txt");
                }
                else
                {
                    if (x == 2)
                    {
                        remove("password_log.txt");
                        rename("temp.txt", "password_log.txt");
                    }
                    else
                    {
                        remove("admin_password_log.txt");
                        rename("temp.txt", "admin_password_log.txt");
                    }
                }
            }
            else
                cout << "\t\t\t\tInvalid Email";
            break;
        }
        case 4:
            return "-";
        }
    } while (1);
}
class time_slot // ! status = checked
{
    string name, sub, sec;

public:
    int vacant;
    time_slot()
    {
        vacant = 1;
    }
    void book_slot(string x, int s, int e, string str)
    {
        name = x;
        cout << "\t\t\t\tEnter subject name : ";
        fflush(stdin);
        getline(cin, sub);
        fflush(stdin);
        cout << "\t\t\t\tEnter section : ";
        getline(cin, sec);
        ifstream check(sec + ".txt");
        if (check)
        {
            while (!check.eof())
            {
                string temp;
                getline(check, temp);
                temp = temp.substr(0, temp.find(' '));
                if (temp == to_string(s) + "-" + to_string(e))
                {
                    cout << "\t\t\t\t\tThis section is already having a class in same slot" << endl;
                    cout<< "\t\t\t\t\tYou can see the available rooms from the menu\n"<<endl;
                    check.close();
                    return;
                }
            }
        }
        check.close();
        name += ".txt";
        ofstream file(name, ios::app);
        ofstream m(sec + ".txt", ios::app);
        file << to_string(s) + "-" + to_string(e) + " " + sub + " " + sec + " " + str << endl;
        m << to_string(s) + "-" + to_string(e) << " " << str << " " << name.substr(0, name.find('.')) << " " << sub << endl;
        file.close();
        m.close();
        vacant = 0;
        cout << "\t\t\t\t\t\t-------------Slot booked------------" << endl;
    }
};
class class_room
{
    int available;

public:
    time_slot t[8];
    class_room()
    {
        available = 1;
    }
    int found(string name, string s)
    {
        ifstream file(name + ".txt");
        string a;
        while (file)
        {
            getline(file, a);
            if (a.substr(0, a.find(' ')) == s)
                return 1;
        }
        file.close();
        return 0;
    }
    void book(string str)
    {
        if (available)
        {
            string name, sub, sec;
            int s, e;
            cout << "\t\t\t\tEnter start time : ";
            cin >> s;
            cout << "\t\t\t\tEnd time : ";
            cin >> e;
            if (s >= 1 && s <= 5)
                s += 12;
            if (e >= 1 && e <= 5)
                e += 12;
            if ((s >= 9 && s <= 17) && (e >= 9 && e <= 17) && (e - s) == 1)
            {
                int i = s % 9;
                if (s > 12 && s <= 17)
                    s -= 12;
                if (e > 12 && e <= 17)
                    e -= 12;

                if (t[i].vacant)
                {
                up:
                    fflush(stdin);
                    cout << "\t\t\t\tEnter lecturers name : ";
                    getline(cin, name);
                    if (is_there("password_log.txt", name + "@srmap.edu.in") != "0")
                    {
                        if (found(name, to_string(s) + "-" + to_string(e)))
                        {
                            cout << "\t\t\t\t oops!! '" + name + "' " + " has another lecture in the same slot\n";
                            goto up;
                        }
                        else

                            t[i].book_slot(name, s, e, str);
                    }
                    else
                    {
                        cout << "\t\t\t\tLecturer not found\n";
                        cout << "\t\t\t\tDo you want to add this lecturer\n\t\t\t\tEnter '1' ~ else '0' : ";
                        int n;
                        cin >> n;
                        if (n)
                        {
                            ofstream file("password_log.txt", ios::app);
                            file << name + "@srmap.edu.in"
                                 << " " << name << endl;
                            file.close();
                            t[i].book_slot(name, s, e, str);
                        }
                        else
                        {
                            cout << "\n\t\t\t\tEnter again\n"
                                 << endl;
                            goto up;
                        }
                    }
                }
                else
                    cout << "\t\t\t\t\t\tTime slot is already booked" << endl;
            }
            else
                cout << "\t\t\t\t\t\t Inavlid time slot" << endl; // !Only 1hr duration class can be added
        }
        else
            cout << "\t\t\t\t\t\tRoom un available";
    }
    int check_availability(int s)
    {
        if (t[s % 9].vacant)
            return 1;
        return 0;
    }
};
class_room room[50];
int slot_display(string x, int p)
{
    string y;
    int count = 0;
    ifstream file(x + ".txt");
    if (file)
    {
        while (!file.eof())
        {
            getline(file, y);
            if (y.length() != 0)
            {
                count++;
                if (p==0 || p==1){
                    cout << count << endl;
                cout << "\t\t\t\tTime slot : " << y.substr(0, y.find(' ')) << endl;
                y = y.substr(y.find(' ') + 1);
                cout << "\t\t\t\tSubject : " << y.substr(0, y.find(' ')) << endl;
                y = y.substr(y.find(' ') + 1);
                cout << "\t\t\t\tSection : " << y.substr(0, y.find(' ')) << endl;
                y = y.substr(y.find(' ') + 1);
                cout << "\t\t\t\tRoom no : " << y.substr(0, y.find(' ')) << endl;
                }
                if (p == 2)
                {
                    y = y.substr(y.find(' ') + 1);
                    cout << "\t\t\t\tRemarks : " << y << endl;
                }
                cout << "\t\t\t\t---------------------------------------------------------" << endl;
            }
        }
        return count;
    }
    else
        cout << "\t\t\t\tNo classes found" << endl;
    return 0;
}
void Admin_login()
{
    string x = user_login();
    if (x != "-")
    {
        int n;
        do
        {
            cout << "\t\t\t\t ========================================================================" << endl;
            cout << "\t\t\t\t|                                                                        |" << endl;
            cout << "\t\t\t\t|   1 . Assign a class                                                   |" << endl;
            cout << "\t\t\t\t|   2 . Add a lecturer                                                   |" << endl;
            cout << "\t\t\t\t|   3 . Check remarks                                                    |" << endl;
            cout << "\t\t\t\t|   4 . Check available room                                             |" << endl;
            cout << "\t\t\t\t|   5 . Get section wise time table                                      |" << endl;
            cout << "\t\t\t\t|   6 . Logout                                                           |" << endl;
            cout << "\t\t\t\t|                                                                        |" << endl;
            cout << "\t\t\t\t ========================================================================" << endl;
            cout << "\n\t\t\t\tEnter choise : ";
            cin >> n;
            switch (n)
            {
            case 1:
            {
                int x, y, z;
                do
                {
                    cout << "\t\t\t\tEnter room number : ";
                    cin >> n;
                    if ((n > 100 && n <= 110) || (n > 200 && n <= 210) || (n > 300 && n <= 310) || (n > 400 && n <= 410) || (n > 500 && n <= 510))
                    {
                        x = n % 10;
                        y = n / 100;
                        z = (n / 10) % 10;
                        if (z == 1)
                            x = 10;
                        y = (y - 1) * 10 + (x - 1);
                        break;
                    }
                    else
                        cout << "\t\t\t\t\t\t\t\t---Invalid room number---" << endl;
                } while (1);
                room[y].book(to_string(n));
                break;
            }
            case 2:
            {
                string name;
                cout << "\t\t\t\tEnter lecuter name : ";
                fflush(stdin);
                getline(cin, name);
                if (is_there("password_log.txt", name + "@srmap.edu.in") == "0")
                {
                    ofstream file("password_log.txt", ios::app);
                    file << name + "@srmap.edu.in" + " " + name << endl;
                    file.close();
                }
                else
                    cout << "\t\t\t\t\t\t\t\t-----Lecturer already exists----" << endl;
                break;
            }
            case 3:
            {
                slot_display("note_log", 2);
                break;
            }
            case 4:
            {
                int s, e;
                cout << "\t\t\t\tEnter start time : ";
                cin >> s;
                cout << "\t\t\t\tEnter end time : ";
                cin >> e;
                for (int i = 0; i < 50; i++)
                {
                    if (room[i].check_availability(s))
                    {
                        int x = i / 10, y = i % 10;
                        if (y == 9)
                            cout << "\t\t\t\t" << (x + 1) * 100 + 10 << endl;
                        else
                            cout << "\t\t\t\t" << (x + 1) * 100 + (y + 1) << endl;
                    }
                }
                break;
            }
            case 5:
            {
                string x;
                cout << "\t\t\t\tEnter section name : ";
                fflush(stdin);
                getline(cin, x);
                ifstream op(x + ".txt");
                if (op)
                {
                    while (!op.eof())
                    {
                        getline(op, x);
                        if (x.length() != 0)
                        {
                            cout << "\t\t\t\tTime : " << x.substr(0, x.find(" ")) << endl;
                            x = x.substr(x.find(" ") + 1);
                            cout << "\t\t\t\tRoom no : " << x.substr(0, x.find(" ")) << endl;
                            x = x.substr(x.find(" ") + 1);
                            cout << "\t\t\t\tLecturer name : " << x.substr(0, x.find(" ")) << endl;
                            x = x.substr(x.find(" ") + 1);
                            cout << "\t\t\t\tSubject : " << x << endl;
                            cout << "\t\t\t\t--------------------------------------------------------------------" << endl;
                        }
                    }
                    op.close();
                }
                else
                    cout << "\t\t\t\tSection not found" << endl;
                break;
            }
            case 6:
                return;
            default:
                break;
            }
        } while (1);
    }
}
void Lecturer_login()
{
    string x = user_login(2);
    x = x.substr(0, x.find('@'));
    if (x != "-")
    {
        int n;
        do
        {
            cout << "\t\t\t\t ========================================================================" << endl;
            cout << "\t\t\t\t|                                                                        |" << endl;
            cout << "\t\t\t\t|   1 . Check Shedule                                                    |" << endl;
            cout << "\t\t\t\t|   2 . Write a comment on a class                                       |" << endl;
            cout << "\t\t\t\t|   3 . Logout                                                           |" << endl;
            cout << "\t\t\t\t|                                                                        |" << endl;
            cout << "\t\t\t\t ========================================================================" << endl;
            cout << "\n\t\t\t\tEnter choise : ";
            cin >> n;
            switch (n)
            {
            case 1:
            {
                int c = slot_display(x, 0);
                cout << "\t\t\t\tToday lectures : " << c << endl;
                break;
            }
            case 2:
            {
                string str;
                int c = slot_display(x, 1), i = 0;
                if (c)
                {
                    cout << "Select a class : ";
                    cin >> n;
                    ifstream file(x + ".txt");
                    while (i < n)
                    {
                        getline(file, str);
                        i++;
                    }
                    file.close();
                    ofstream log("note_log.txt", ios::app);
                    log << str << " ";
                    fflush(stdin);
                    cout << "Enter comment : ";
                    getline(cin, str);
                    log << str << endl;
                    log.close();
                    cout << " Note added" << endl;
                }
            }
            break;
            case 3:
                cout << "\t\t\t\t\t\t\t\tSuccesfully logged out" << endl;
                return;
            default:
                break;
            }
        } while (1);
    }
}
int main()
{
    int n;
    do
    {
        cout << "\t\t\t\t========================================================================" << endl;
        cout << "\t\t\t\t|          - WELCOME TO SRM CLASSROOM MANAGEMENT SYSTEM -              |" << endl;
        cout << "\t\t\t\t|                                                                      |" << endl;
        cout << "\t\t\t\t|   1 . Admin login                                                    |" << endl;
        cout << "\t\t\t\t|   2 . Lecturer login                                                 |" << endl;
        cout << "\t\t\t\t|   3 . Exit                                                           |" << endl;
        cout << "\t\t\t\t|                                                                      |" << endl;
        cout << "\t\t\t\t========================================================================" << endl;
        cout << "\n\t\t\t\tEnter choise : ";
        cin >> n;
        switch (n)
        {
        case 1:
            Admin_login();
            break;
        case 2:
            Lecturer_login();
            break;
        case 3:
            cout << "\t\t\t\tThank_you";
            return 0;
        default:
            cout << "\t\t\t\tEnter dispalyed choices only\n";
        }
    } while (1);
    return 0;
}
