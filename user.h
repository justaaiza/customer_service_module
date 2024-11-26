#ifndef USER_H
#define USER_H

#include<iostream>
#include<string>
using namespace std;

class user {

	friend ostream& operator<<(ostream& out, const user& obj);

private:
	int userID = 0;
	string name;
	string email;
	string country;
	string type;

public:
	user(string n, string e, string c, string t)
	{
		name = n;
		email = e;
		country = c;
		type = t;
	}

	void setID(int numb)
	{
		userID = numb;
	}

	int getID()
	{
		return userID;
	}

	string getName()
	{
		return name;
	}

	string getEmail()
	{
		return email;
	}

	string getCountry()
	{
		return country;
	}

	string getType()
	{
		return type;
	}

	~user()
	{

	}
};

inline ostream& operator<<(ostream& out, const user& obj)
{
	out << "---------------------------------" << endl;
	out << "UserID: " << obj.userID << endl;
	out << "User name: " << obj.name << endl;
	out << "User email: " << obj.email << endl;
	out << "User country: " << obj.country << endl;
	out << "User type: " << obj.type << endl;
	out << "---------------------------------" << endl;

	return out;
}

#endif 
