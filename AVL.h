#ifndef AVL_H
#define AVL_H

#include<iostream>
#include<queue>
#include<list>
#include<algorithm> //for using find for list
using namespace std;

#include"user.h"
#include"userList.h"

template<class T>
class AVL
{
private:
	class Node
	{
	public:
		T data;
		list<user*>::iterator itr;
		int height;
		Node* right;
		Node* left;

		Node(T d, Node* r = nullptr, Node* l = nullptr)
		{
			data = d;
			right = r;
			left = l;
			height = 0;
		}
	};

	Node* root;


	user* searchR(T d, Node* ptr)
	{
		if (ptr == nullptr)
			return nullptr;

		else if (ptr->data == d)
			return *(ptr->itr);

		else if (d > ptr->data)
			return searchR(d, ptr->right);

		else if (d < ptr->data)
			return searchR(d, ptr->left);
	}

	void deleteR(T d, Node*& node, list<user*>& List)
	{
		if (node)
		{
			if (d > node->data)
				deleteR(d, node->right, List);

			else if (d < node->data)
				deleteR(d, node->left, List);

			else if(d == node->data)
			{
				
				List.erase(node->itr);
				deleteNode(node);
				return;
			}

			balance(node);
		}
	}

	void deleteNameAndEmail(T d, Node*& node)
	{
		if (node)
		{
			if (d > node->data)
				deleteNameAndEmail(d, node->right);

			else if (d < node->data)
				deleteNameAndEmail(d, node->left);

			else
				deleteNode(node);


			balance(node);
		}
	}

	Node*& insert(T d, Node*& ptr, Node*& prev, char& c)
	{
		if (ptr == nullptr)
		{
			ptr = new Node(d);
			return prev;
		}
		else if (d > ptr->data)
		{
			c = 'R';
			return insert(d, ptr->right, ptr, c);
		}
		else if (d < ptr->data)
		{
			c = 'L';
			return insert(d, ptr->left, ptr, c);
		}

		balance(ptr);
	}

	Node*& insertEmailAndName(T d, Node*& ptr)
	{
		if (ptr == nullptr)
		{
			ptr = new Node(d);
			return ptr;
		}
		else if (d > ptr->data)
		{
			return insertEmailAndName(d, ptr->right);
		}
		else if (d < ptr->data)
		{
			return insertEmailAndName(d, ptr->left);
		}

		balance(ptr);
	}


public:

	AVL()
	{
		root = nullptr;
	}



	void insert(T d, user*& newUser, list<user*>& List)
	{
		char c;

		Node* parent = insert(d, root, root, c);

		if (c == 'R')
		{
			list<user*>::iterator afterParent = parent->itr;
			++afterParent;

			if (afterParent == List.end())
			{
				List.push_back(newUser);
				afterParent = List.end();
				--afterParent;
				parent->right->itr = afterParent;
			}

			else
			{
				parent->right->itr = List.insert(afterParent, newUser);
			}

		}
		else if (c == 'L')
		{
			parent->left->itr = List.insert(parent->itr, newUser);
		}
		else
		{
			List.push_front(newUser);
			parent->itr = List.begin();
		}
	}

	void nameAndEmailInsert(string x, user*& User, list<user*>& List)
	{
		Node* ptr = insertEmailAndName(x, root);
		list<user*>::iterator itr = find(List.begin(), List.end(), User);

		ptr->itr = itr;
	}

	user* searchR(T d)
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

			cout << temp->data << endl;

			if (temp->left)
				q.push(temp->left);
			if (temp->right)
				q.push(temp->right);

			q.pop();
		}

	}

	bool isEmpty()
	{
		if (root == nullptr)
			return true;
		else
			return false;
	}

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
			node->itr = temp->itr;

			if (prev == node)
				prev->left = temp->left;

			else
				prev->right = temp->left;
		}

		delete temp;
		temp = nullptr;
	}

	void deleteR(T d, list<user*>& List)
	{
		deleteR(d, root, List);
	}

	void deleteNameAndEmail(T d)
	{
		deleteNameAndEmail(d, root);
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


