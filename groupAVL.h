#ifndef GROUPAVL_H
#define GROUPAVL_H

#include<iostream>
#include<queue>
#include<list>
#include<forward_list>
#include<algorithm> //for using find for list
using namespace std;

#include"user.h"
#include"complaints.h"
//#include"userList.h"

template<class T1, class T2>
class groupAVL
{
private:
	class Node
	{
	public:
		T1 data;
		forward_list<T2>* sll;
		int height;
		Node* right;
		Node* left;

		Node(T1 d, T2 obj = nullptr, Node* r = nullptr, Node* l = nullptr)
		{
			data = d;
			sll = new forward_list<T2>();
			sll->push_front(obj);
			right = r;
			left = l;
			height = 0;
		}
	};

	Node* root;


	Node* searchR(T1 d, Node*& ptr)
	{
		if (ptr == nullptr)
			return nullptr;

		else if (ptr->data == d)
			return ptr;

		else if (d > ptr->data)
			return searchR(d, ptr->right);

		else if (d < ptr->data)
			return searchR(d, ptr->left);
	}

	forward_list<T2>* returnList(T1 d, Node* node)
	{
		if (node == nullptr) {

			return nullptr;
		}

		if (d > node->data) {
			return returnList(d, node->right);
		}
		else if (d < node->data) {
			return returnList(d, node->left);
		}
		else {
			
			return node->sll;
		}
	}

	void deleteR(T1 d, Node*& node)
	{
		if (node)
		{
			if (d > node->data)
				deleteR(d, node->right);

			else if (d < node->data)
				deleteR(d, node->left);
			else
			{
				deleteNode(node);
				return;
			}

			balance(node);
		}
	}


	Node*& insert(T1 d, Node*& ptr, T2& obj)
	{
		if (ptr == nullptr)
		{
			ptr = new Node(d, obj);
			return ptr;
		}
		else if (d > ptr->data)
		{
			return insert(d, ptr->right, obj);
		}
		else if (d < ptr->data)
		{
			return insert(d, ptr->left, obj);
		}

		balance(ptr);
	}




public:

	groupAVL()
	{
		root = nullptr;
	}



	void insert(T1 d, T2 obj)
	{
		Node* ptr = searchR(d);

		if (ptr == nullptr)
			insert(d, root, obj);

		else
		{
			if (ptr->sll == nullptr)
			{
				ptr->sll = new forward_list<T2>();
				ptr->sll->push_front(obj);
			}
			else 
				ptr->sll->push_front(obj);
		}
	}



	Node* searchR(T1 d)
	{
		return searchR(d, root);
	}

	void print()
	{
		Node* temp = root;

		queue<Node*> q;

		q.push(temp);

		while (!q.empty())
		{
			temp = q.front();

			for (auto itr = temp->sll->begin(); itr != temp->sll->end(); ++itr) {
				if (**itr) {
					cout << (***itr) << endl;
				}
			}


			if (temp->left)
				q.push(temp->left);
			if (temp->right)
				q.push(temp->right);

			q.pop();
		}

	}

	/*void printList(string x)
	{
		Node* ptr = searchR(x);

		if (ptr)
		{
			auto itr = (ptr->sll)->begin();

			while (itr != (ptr->sll)->end())
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
	}*/

	void deleteNode(Node*& node)
	{
		Node* temp = node;

		if (node->left == nullptr)
			node = node->right;

		else if (node->right == nullptr)
			node = node->left;

		else
		{
			temp = node->left;
			Node* prev = node;

			while (temp->right != nullptr)
			{
				prev = temp;
				temp = temp->right;
			}

			node->data = temp->data;
			if (prev == node)
				prev->left = temp->left;

			else
				prev->right = temp->left;
		}

		delete temp;

	}

	forward_list<T2>* returnList(T1 d)
	{
		return returnList(d, root);
	}

	void deleteFromList(T1 d, T2& obj) 
	{
		Node* ptr = searchR(d);

		if (!ptr || !ptr->sll) 
		{
			throw runtime_error("Node or list not found in deleteFromList");
		}

		ptr->sll->remove(obj); 
		if (ptr->sll->empty()) {
			delete ptr->sll;
			ptr->sll = nullptr;
		}
	}

	bool isEmpty()
	{
		if (root == nullptr)
			return true;
		else
			return false;
	}

	void deleteR(T1 d)
	{
		deleteR(d, root);
	}

	int height(Node* ptr)
	{
		if (ptr == nullptr)
			return -1;

		int lno = -1, rno = -1;

		lno = height(ptr->left);
		rno = height(ptr->right);

		return max(lno, rno) + 1;

	}

	void rotateRight(Node*& x)
	{
		Node* orphan = x->left->right;
		Node* y = x->left;
		y->right = x;
		x->left = orphan;

		x->height = height(x);
		y->height = height(y);

		x = y;
	}

	void rotateLeft(Node*& x)
	{
		Node* orphan = x->right->left;
		Node* y = x->right;
		y->left = x;
		x->right = orphan;

		x->height = height(x);
		y->height = height(y);

		x = y;
	}

	void rotateLeftRight(Node*& x)
	{
		rotateLeft(x->left);
		rotateRight(x);
	}

	void rotateRightLeft(Node*& x)
	{
		rotateRight(x->right);
		rotateLeft(x);
	}

	void balance(Node*& x)
	{
		if (x == nullptr)
			return;

		if (getHeight(x->right) - getHeight(x->left) > 1)
		{
			if (getHeight(x->right->left) > getHeight(x->right->right))
				rotateRightLeft(x);

			else
				rotateLeft(x);
		}

		else if (getHeight(x->right) - getHeight(x->left) < -1)
		{
			if (getHeight(x->left->right) > getHeight(x->left->left))
				rotateLeftRight(x);
			else
				rotateRight(x);
		}

		x->height = max(height(x->right), height(x->left)) + 1;
	}

	int getHeight(Node* node)
	{
		if (node)
		{
			return node->height;
		}
		else
			return -1;
	}
};

#endif
