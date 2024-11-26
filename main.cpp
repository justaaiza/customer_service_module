#include <iostream>
#include <cstdlib>  
#include <ctime>  
using namespace std;

#include "user.h"
#include "userList.h"
#include "complaints.h"

int main()
{
    bool flag = true;

    cout << "Enter the respective code for the service you want to access:" << endl;
    cout << "a:\tregister a user" << endl;
    cout << "b:\tsearch users" << endl;
    cout << "c:\tdelete users" << endl;
    cout << "d:\tprint users data" << endl;
    cout << "e:\tregister a complaint" << endl;
    cout << "f:\tservice a complaint" << endl;
    cout << "g:\tincrease a complaint's priority" << endl;
    cout << "h:\tprint complaints" << endl;
    cout << "i:\texit the menu" << endl;

    userList List;

    while (flag)
    {
        char c;
        cout << "-----------------------------------------------------" << endl;
        cout << "Enter here: ";
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover characters
        cout << "-----------------------------------------------------" << endl;

        if (c == 'a')
        {
            string name, email, country, type;

            cout << "Enter user name: ";
            getline(cin, name);
            cout << "Enter user email: ";
            getline(cin, email);
            cout << "Enter user country: ";
            getline(cin, country);
            cout << "Enter user type: ";
            getline(cin, type);

            user* User = new user(name, email, country, type);
            List.addUser(User);
        }

        else if (c == 'b') 
        {
            int x;
            cout << "1:\tsearch using an ID" << endl;
            cout << "2:\tsearch using a name" << endl;
            cout << "3:\tsearch using an email" << endl;
            cout << "4:\tsearch using a country" << endl;
            cout << "5:\tsearch using a type" << endl;
            cout << "Enter choice: ";
            cin >> x;

            if (cin.fail()) // Check if the input is invalid
            {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining input
                cout << "Invalid input! Please enter a number." << endl;
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
            if (x == 1)
            {
                int y;
                cout << "Enter the ID: ";
                cin >> y;

                if (cin.fail()) // Check ID input
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Please enter a valid integer ID." << endl;
                    continue;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                List.search(y);
            }
            else if (x == 2)
            {
                string str;
                cout << "Enter the name: ";
                getline(cin, str);
                List.searchUsingName(str);
            }
            else if (x == 3)
            {
                string str;
                cout << "Enter the email: ";
                getline(cin, str);
                List.searchUsingEmail(str);
            }
            else if (x == 4)
            {
                string str;
                cout << "Enter the country: ";
                getline(cin, str);
                List.printCountryList(str);
            }
            else if (x == 5)
            {
                string str;
                cout << "Enter the type: ";
                getline(cin, str);
                List.printTypeList(str);
            }
            else
            {
                cout << "Invalid Input!" << endl;
            }
        }


        else if (c == 'c')
        {
            int x;
            cout << "1:\tdelete using an ID" << endl;
            cout << "2:\tdelete using a name" << endl;
            cout << "3:\tdelete using an email" << endl;
            cout << "4:\tdelete using a country" << endl;
            cout << "5:\tdelete using a type" << endl;
            cout << "Enter choice: ";
            cin >> x;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (x == 1)
            {
                int y;
                cout << "Enter the ID: ";
                cin >> y;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                List.deleteUser(y);
            }
            else if (x == 2)
            {
                string str;
                cout << "Enter the name: ";
                getline(cin, str);
                List.deleteUsingName(str);
            }
            else if (x == 3)
            {
                string str;
                cout << "Enter the email: ";
                getline(cin, str);
                List.deleteUsingEmail(str);
            }
            else if (x == 4)
            {
                string str;
                cout << "Enter the country: ";
                getline(cin, str);
                List.deleteUsingCountry(str);
            }
            else if (x == 5)
            {
                string str;
                cout << "Enter the type: ";
                getline(cin, str);
                List.deleteUsingType(str);
            }
            else
                cout << "Invalid Input!" << endl;
        }

        else if (c == 'd')
        {
            int x;
            cout << "1:\tprint list using IDs" << endl;
            cout << "2:\tprint name indices" << endl;
            cout << "3:\tprint email indices" << endl;
            cout << "4:\tprint users by country" << endl;
            cout << "5:\tprint users by type" << endl;
            cout << "Enter choice: ";
            cin >> x;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

            if (x == 1)
            {
                List.printList(); 
            }
            else if (x == 2)
            {
                List.printNameIndexes(); 
            }
            else if (x == 3)
            {
                List.printEmailIndexes(); 
            }
            else if (x == 4)
            {
                string country;
                cout << "Enter the country: ";
                getline(cin, country); 
                List.printCountryList(country); 
            }
            else if (x == 5)
            {
                string type;
                cout << "Enter the type: ";
                getline(cin, type); 
                List.printTypeList(type); 
            }
            else
            {
                cout << "Invalid Input!" << endl; 
            }
}


        else if (c == 'e')
        {
            int ID;
            string complain;

            cout << "User ID: ";
            cin >> ID;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter your complaint: ";
            getline(cin, complain);

            complaints* complaint = new complaints(ID, complain);
            List.registerComplaint(complaint);
        }

        else if (c == 'f')
        {
            List.serviceComplaint();
        }

        else if (c == 'g') 
        {
            int y;
            cout << "Enter complaint ID: ";
            cin >> y;

            if (cin.fail()) // Check if input is not an integer
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter a valid integer ID." << endl;
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            List.increasePriority(y);
}


        else if (c == 'h')
        {
            int y;
            cout << "1:\tprint complaints of a specific user" << endl;
            cout << "2:\tprint all complaints of a specific country" << endl;
            cout << "Enter choice: ";
            cin >> y;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (y == 1)
            {
                int z;
                cout << "Enter user ID: ";
                cin >> z;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                List.printComplaints(z);
            }
            else if (y == 2)
            {
                string str;
                cout << "Enter the country: ";
                getline(cin, str);
                List.printCountryComplaints(str);
            }
            else
                cout << "Invalid Input!" << endl;
        }

        else if (c == 'i')
            flag = false;

        else
        {
            cout << "Invalid option. Please try again!" << endl;
        }
    }

    return 0;
}
