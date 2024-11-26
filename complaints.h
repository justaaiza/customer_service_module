#ifndef COMPLAINTS_H
#define COMPLAINTS_H

#include<iostream>
#include<string>
using namespace std;


class complaints
{
	friend ostream& operator<<(ostream& out, const complaints& obj);

private:
	static int complaintNumb;
	string complain;
	int complainID = 0;
	int userID;

public:
	complaints(int ID, string x)
	{
		userID = ID;
		complain = x;
		complainID = complaintNumb++;
	}

	int getcomplainID()
	{
		return complainID;
	}

	int getUserID()
	{
		return userID;
	}
};

int complaints::complaintNumb = 0;

inline ostream& operator<<(ostream& out, const complaints& obj)
{
	cout << "\n\nComplaint registered by user: " << obj.userID << endl;
	cout << "Complain: " << obj.complain << endl;
	

	return out;
}

#endif