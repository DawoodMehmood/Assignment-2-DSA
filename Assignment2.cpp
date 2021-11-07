#include <iostream>
#include <algorithm>
using namespace std;

//defining MAX size of stack to be 100
#define MAX 100

//implementation of stack class through array
class Stack
{
    //                      private members

    int top;         //to keep track of most recent entry in stack
    char stack[MAX]; //declaring array of characters with MAX size

    //function to check if stack is full
    bool isFull()
    {
        return (top == MAX - 1);
    }

    //                          public members
public:

//default constructor
    Stack()
    {
        top = -1; //setting initially to '-1'
    }

     //function to check if stack is empty
    bool isEmpty()
    {
        return (top < 0);
    }


    //function to push an element in stack
    void push(char str)
    {
        //checking if stack is already full
        if (isFull())
        {
            cout << "\nStack has reached its Maximum size of : " << MAX << endl;
            return;
        }
        //else incrementing 'top' +1 and adding the element in stack
        stack[++top] = str;
    }

    //funciton to get the most recent or top most entry of stack and then removing it from stack
    char pop()
    {
        //checking if stack is empty
        if (isEmpty())
        {
            cout << "\nStack is empty for now. Nothing can be popped.\n";
            exit(EXIT_FAILURE);
        }
        //else returning the top element and decrementing 'top' -1
        return stack[top--];
    }

   //function to get the top most entry of stack
    int peak()
    {
        return stack[top];
    }
};//end class Stack
