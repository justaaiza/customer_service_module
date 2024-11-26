#ifndef USERLIST_H
#define USERLIST_H

#include<iostream>
#include<list>
#include<forward_list>
#include<string>
#include <cstdlib>  
#include <ctime>  
#include<utility>
using namespace std;

#include"AVL.h"
#include"groupAVL.h"
#include"user.h"
#include"complaints.h"
#include"priorityQueue.h"

enum type
{
	platinum = 1,
	gold = 2,
	silver = 3,
	regular = 4,
	New = 5
};

int getTypeFromString(const string& src)
{
	if (src == "platinum") return platinum;
	if (src == "gold") return gold;
	if (src == "silver") return silver;
	if (src == "regular") return regular;
	if (src == "New") return New;

}

class userList
{
private:

	static int ID; 
	list<user*> List;
	AVL<int> IdIndexes;
	AVL<string> NameIndexes;
	AVL<string> EmailIndexes;
	groupAVL<string, list<user*>::iterator> CountryIndexes;
	groupAVL<string, list<user*>::iterator> TypeIndexes;
	priorityQueue<pair<int, complaints*>>  complaintsHeap;
	groupAVL<int, complaints*> complaintsGroup;

public:

	void addUser(user*& newUser)
	{

		int numb = ID++;
		newUser->setID(numb);

		IdIndexes.insert(numb, newUser, List);
		list<user*>::iterator itr = find(List.begin(), List.end(), newUser);

		NameIndexes.nameAndEmailInsert(newUser->getName(), newUser, List);
		EmailIndexes.nameAndEmailInsert(newUser->getEmail(), newUser, List);
		CountryIndexes.insert(newUser->getCountry(), itr);
		TypeIndexes.insert(newUser->getType(), itr);

		cout << "\nUser added :)" << endl;
	}

	/*void createNameIndexes()
	{
		list<user*>::iterator itr = List.begin();

		while (itr != List.end())
		{
			user* obj = *(itr);
			NameIndexes.nameAndEmailInsert(obj->getName(), obj, List);
			itr++;
		}

	}

	void createEmailIndexes()
	{
		list<user*>::iterator itr = List.begin();

		while (itr != List.end())
		{
			user* obj = *(itr);
			EmailIndexes.nameAndEmailInsert(obj->getEmail(), obj, List);
			itr++;
		}

	}

	void createCountryIndexes()
	{
		list<user*>::iterator itr = List.begin();

		while (itr != List.end())
		{
			user* obj = *(itr);
			CountryIndexes.insert(obj->getCountry(), itr);
			itr++;
		}
	}

	void createTypeIndexes()
	{
		list<user*>::iterator itr = List.begin();

		while (itr != List.end())
		{
			user* obj = *(itr);
			TypeIndexes.insert(obj->getType(), itr);
			itr++;
		}
	}*/

	void search(int x)
	{
		user* findUser = IdIndexes.searchR(x);

		if (findUser == nullptr)
			cout << "User not found :(" << endl;
		else
			cout << *(findUser) << endl;
	}

	void searchUsingName(string x)
	{
		user* findUser = NameIndexes.searchR(x);

		if (findUser == nullptr)
			cout << "User not found :(" << endl;
		else
			cout << *(findUser) << endl;
	}

	void searchUsingEmail(string x)
	{
		user* findUser = EmailIndexes.searchR(x);

		if (findUser == nullptr)
			cout << "User not found :(" << endl;
		else
			cout << *(findUser) << endl;
	}

	void deleteUser(int x)
	{
		user* obj = IdIndexes.searchR(x);
		if(obj)
		{
			list<user*>::iterator itr = find(List.begin(), List.end(), obj);

			
			NameIndexes.deleteNameAndEmail(obj->getName());
			EmailIndexes.deleteNameAndEmail(obj->getEmail());
			CountryIndexes.deleteFromList(obj->getCountry(), itr);
			TypeIndexes.deleteFromList(obj->getType(), itr);
			IdIndexes.deleteR(x, List);

			delete obj;
			obj = nullptr;
		}
		else 
			cout << "\nUser not found :(" << endl;
	}

	void deleteUsingName(string x)
	{
		user* obj = NameIndexes.searchR(x);
		if (obj)
		{
			deleteUser(obj->getID());
			cout << "\nUser deleted!" << endl;
		}
		else
			cout << "\nUser not found :(" << endl;
	}

	void deleteUsingEmail(string x)
	{	
		user* obj = EmailIndexes.searchR(x);
		if (obj)
		{
			deleteUser(obj->getID());
			cout << "\nUser deleted!" << endl;
		}
		else
			cout << "\nUser not found :(" << endl;
	}

	void deleteUsingCountry(string x)
	{
		forward_list<list<user*>::iterator>* SLL = CountryIndexes.returnList(x);

		if (SLL)
		{
			auto itr = SLL->begin();
			while (itr != SLL->end())
			{
				user*& obj = **itr;
				NameIndexes.deleteNameAndEmail(obj->getName());
				EmailIndexes.deleteNameAndEmail(obj->getEmail());
				TypeIndexes.deleteFromList(obj->getType(), *itr);
				CountryIndexes.deleteR(x);

				itr++;

				IdIndexes.deleteR(obj->getID(), List);

				obj = nullptr;

				cout << "\nUsers deleted!" << endl;

			}
		}
		else
			cout << "\nCountry not found :(" << endl;
	}

	void deleteUsingType(string x) 
	{
		forward_list<list<user*>::iterator>* SLL = TypeIndexes.returnList(x);

		if (SLL)
		{
			auto itr = SLL->begin();
			while (itr != SLL->end())
			{
				user*& obj = **itr;
				NameIndexes.deleteNameAndEmail(obj->getName());
				EmailIndexes.deleteNameAndEmail(obj->getEmail());
				CountryIndexes.deleteFromList(obj->getType(), *itr);
				TypeIndexes.deleteR(x);

				itr++;

				IdIndexes.deleteR(obj->getID(), List);

				obj = nullptr;

				cout << "\nUsers deleted!" << endl;
			}
		}
		else
			cout << "\nType not found :(" << endl;
	}

	void printCountryList(string x)
	{
		forward_list<list<user*>::iterator>* SLL = CountryIndexes.returnList(x);

		if (SLL)
		{
			forward_list<list<user*>::iterator>::iterator itr = SLL->begin();

			while (itr != SLL->end())
			{
				if (**itr)
				{
					cout << (***itr) << endl;
					itr++;
				}
			}
		}

		else
			cout << "Index not found :(" << endl;
	}

	void printTypeList(string x)
	{
		forward_list<list<user*>::iterator>* SLL = TypeIndexes.returnList(x);
		
		if (SLL)
		{
			forward_list<list<user*>::iterator>::iterator itr = SLL->begin();

			while (itr != SLL->end())
			{
				if (**itr)
				{
					cout << (***itr) << endl;
					itr++;
				}
			}
		}

		else
			cout << "Index not found :(" << endl;
	}

	void printComplaints(int ID)
	{
		user* obj = IdIndexes.searchR(ID);

		if (obj)
		{
			forward_list<complaints*>* SLL = complaintsGroup.returnList(ID);

			if (SLL)
			{
				forward_list<complaints*>::iterator itr = SLL->begin();

				while (itr != SLL->end())
				{
					if (*itr)
					{
						cout << (**itr) << endl;
						itr++;
					}
				}
			}

			else
				cout << "No complaints :)" << endl;
		}

		else
			cout << "\n\nUser does not exists!" << endl;
	}

	void printList()
	{
		if (!List.empty())
		{
			list<user*>::iterator itr;

			for (itr = List.begin(); itr != List.end(); itr++)
			{
				cout << **(itr) << endl;
			}
		}
		else
			cout << "\nList is empty" << endl;
	}

	void printEmailIndexes()
	{
		if (!EmailIndexes.isEmpty())
		{
			EmailIndexes.print();
		}
		else
			cout << "\nNo users found" << endl;
	}

	void printNameIndexes()
	{
		if (!NameIndexes.isEmpty())
		{
			NameIndexes.print();
		}
		else
			cout << "\nNo users found" << endl;
	}

	void printCountryIndexes()
	{
		if (!CountryIndexes.isEmpty())
		{
			CountryIndexes.print();
		}
		else
			cout << "\nNo users found" << endl;
	}

	void printTypeIndexes()
	{
		if (!TypeIndexes.isEmpty())
		{
			TypeIndexes.print();
		}
		else
			cout << "\nNo users found" << endl;
	}

	void registerComplaint(complaints*& Complaint)
	{
		int ID = Complaint->getUserID();
		user* User = IdIndexes.searchR(ID);
		if (User)
		{
			int type = getTypeFromString(User->getType());

			complaintsHeap.insert({ type, Complaint });
			complaintsGroup.insert(ID, Complaint);

			cout << "\nComplaints registered!" << endl;
		}
		else
			cout << "\n\nUser does not exists!" << endl;
	}

	void serviceComplaint()
	{
		if (!complaintsHeap.isEmpty())
		{
			pair<int, complaints*> obj = complaintsHeap.getMin();

			cout << "Completing the task:" << endl;
			cout << *(obj.second) << endl;

			complaintsGroup.deleteFromList(obj.second->getUserID(), obj.second);

			complaintsHeap.deleteMin();

			cout << "\nTask completed :)" << endl;
		}
		else
			cout << "\nNo complaints exist :)" << endl;
	}

	void increasePriority(int complainID)
	{
		complaints* Complaint = complaintsHeap.searchComplaint(complainID);

		if (Complaint)
		{
			
			complaintsHeap.increasePriority(Complaint);
			
		}
		else
			cout << "\nNo such complaints found." << endl;
	}

	void printCountryComplaints(string x)
	{
		forward_list<list<user*>::iterator>* SLL = CountryIndexes.returnList(x);

		if (SLL)
		{
			forward_list<list<user*>::iterator>::iterator itr = SLL->begin();

			while (itr != SLL->end())
			{
				if (**itr)
				{
					cout << "\n\n----------------------------------" << endl;
					cout << "Complaints by " << (***itr).getName() << ":" << endl;
					cout << "----------------------------------" << endl;

					printComplaints((***itr).getID());
					itr++;
				}
			}
		}

		else
			cout << "\nNo complaints exist!" << endl;
	}
};

int userList::ID = 0;

#endif 


