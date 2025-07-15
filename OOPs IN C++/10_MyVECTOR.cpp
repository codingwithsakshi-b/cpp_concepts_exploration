#define _WIN32_WINNT 0x0600 //for running the file rang.hpp for colored output
#include <iostream>
#include "rang.hpp"
using namespace rang;
using namespace std;

class Vector
{
public:
    int size;
    int capacity;
    int* arr;

    //Default Constructor with Default values
    Vector()
    {
        size = 0;
        capacity = 1;
        arr = new int[1];
    }

    //Function for adding values in vector
    void add(int i)//i is element
    {
        if(size == capacity)
        {
            capacity *= 2;
            int* arr2 = new int[capacity];
            for(int i = 0; i<size; i++)
            {
                arr2[i] = arr[i];
            }
            delete[] arr;
            arr = arr2;
        }
        arr[size++] = i; //Post Increment 
    }

    //Function for Printing Whole Array
    void Print()
    {
        if(size == 0)
        {
            cout << "Array is Empty" << endl;
            return;
        }

        cout<< "Vector Elements: ";
        for(int i=0; i<size; i++)
        {
            cout<< arr[i] << " ";
        }
        cout<<endl;
    }

    //For getting value at particular index
    int get(int idx)
    {   
        if(size == 0)
        {
            cout << "Array is Empty" << endl;
            return -1;
        }

        if(idx>=size || idx<0)
        {
            cout<< "Invalid Index"<<endl;
            return -1;
        }

        return arr[idx];
    }

    //for removing values from last
    void remove()
    {
        if(size == 0)
        {
            cout << "Array is Empty" << endl;
        }
        else
        {
            cout<< "Last Element removed!"<<endl;
            size--;
        }
    }

    //Insert Value at Some Index
    void Insert(int idx, int val)
    {
        if(idx < 0 || idx > size)
        {
            cout<< "Invalid Index for Insertion" << endl;
            return;
        }

        if(size == capacity)
        {
            capacity *= 2;
            int* arr2 = new int[capacity];
            for (int i = 0; i < size; i++) {
                arr2[i] = arr[i];
            }
            delete[] arr;
            arr = arr2;
        }

        for(int i = size; i > idx; i--)
        {
            arr[i] = arr[i-1];
        }

        arr[idx] = val;
        size++;

        cout<< "Inserted "<< val << " at index " << idx << endl;
    }

    //Clear Vector
    void clear()
    {
        char s;
        cout << "Are You sure you want to clear the vector? (y/n): ";
        cin >> s;

        if(s == 'y' || s == 'Y')
        {
            size = 0;
            cout << "Vector Cleared!"<<endl;
        }
        else
        {
            cout << "Clear Operation canceled."<<endl;
        }
    }

    //check if vector contain a value or not
    bool Contain(int val)
    {
        for(int i = 0; i<size; i++)
        {
            if(arr[i] == val)
            {
                return true;
            }
        }
        return false;
    }

    //Find Index of first occurence
    int find(int val)
    {
        for(int i=0; i<size; i++)
        {
            if(arr[i] == val)
                return i;
        }
        return -1;
    }

};

int main()
{
    system("chcp 65001");//for getting emojis in terminal output

    Vector v;
    v.add(10);
    v.add(20);
    v.add(30);
    v.Insert(1, 15); // ➡️ 10 15 20 30
    v.Print();

    cout << "Contains 20? " << (v.Contain(20) ? "Yes" : "No") << endl;
    cout << "Index of 30: " << v.find(30) << endl;

    v.clear();
    v.Print();
    return 0;
}