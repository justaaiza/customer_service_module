#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include<iostream>
#include<vector>
#include<string>
#include <utility> 
using namespace std;

#include"complaints.h"

template<class T>
class priorityQueue
{
private:
    vector<T> data;

public:
    priorityQueue()
    {}

    priorityQueue(T* arr, int N)
    {
        for (int i = 0; i < N; i++)
            data.push_back(arr[i]);

        buildMinHeap();
    }

    void buildMinHeap()
    {
        for (int i = ((data.size() / 2) - 1); i >= 0; i--)
            bubble_down(i);
    }

    bool compareType(const T& c1, const T& c2)
    {
        if (c1.first == c2.first)
        {
            if ((c1.second)->getcomplainID() > (c2.second)->getcomplainID())
                return true;
        }

        else if (c1.first > c2.first)
            return true;

        else
            return false;
    }

    void bubble_up(int i)
    {
        int parent;
        if (i > 0)
        {
            parent = (i - 1) / 2;

            if (compareType(data[parent],data[i]))
            {
                swap(data[parent], data[i]);
                bubble_up(parent);
            }
        }
    }

    void bubble_down(int i)
    {
        int minChild, rightChild, leftChild;
        leftChild = 2 * i + 1;
        rightChild = 2 * i + 2;
        if (leftChild <= data.size() - 1)
        {

            if (leftChild == data.size() - 1)
                minChild = leftChild;
            else {
                if (compareType(data[leftChild],data[rightChild]))

                    minChild = rightChild;

                else

                    minChild = leftChild;

            }
            if (compareType(data[i],data[minChild])) 
            {
                swap(data[i], data[minChild]);
                bubble_down(minChild);
            }
        }
    }

    void insert(const T& x)
    {
        data.push_back(x);
        bubble_up(data.size() - 1);
    }

    bool isEmpty() const
    {
        return data.empty();
    }

    const T& getMin() const
    {
        return data[0];
    }

    void deleteMin()
    {
        if(!data.empty())
        {
            swap(data[0], data[data.size() - 1]);
            data.pop_back();

            if (!data.empty())
                bubble_down(0);
        }
    }


    bool deleteAll(T key)
    {
        bool found = false;

        for (int i = 0; i < data.size(); i++)
        {
            if (key == data[i])
            {
                found = true;

                data[i] = data[data.size() - 1];
                data.pop_back();

                bubble_down(i);
            }
        }

        return found;
    }

    void print()
    {
        for (int i = 0; i < data.size(); i++)
            cout << data[i] << " ";
    }

    int search(complaints* toFind)
    {
        for (int i = 0; i < data.size(); i++)
        {
            if (data[i].second == toFind)
                return i;
        }

        return -1;
    }

    complaints* searchComplaint(int ID)
    {
        if (!data.empty())
        {
            for (int i = 0; i < data.size(); i++)
            {
                if ((data[i].second)->getcomplainID() == ID)
                    return data[i].second;
            }
        }

        else
            return nullptr;
    }

    void increasePriority(complaints* c)
    {
        int x = search(c);

        if (x == -1)
        {
            cout << "Complaint not found :(" << endl;
        }
        else
        {
            swap(data[x], data[0]);
            deleteMin();
        }
       
    }

};

#endif
