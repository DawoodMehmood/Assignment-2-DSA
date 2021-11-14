#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//defining MAX size of stack to be 100
#define MAX 100

//implementation of character stack class through array
class CharStack
{
    //----------------------private members----------------------

    int top;         //to keep track of most recent entry in stack
    char stack[MAX]; //declaring array of characters with MAX size

    //function to check if stack is full
    bool isFull()
    {
        return (top == MAX - 1);
    }

    //-----------------------public members-----------------------
public:
    //default constructor
    CharStack()
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
    char peak()
    {
        return stack[top];
    }
}; //end class CharStack

//implementation of integer stack class through array
class intStack
{
    //----------------------private members----------------------

    int top;        //to keep track of most recent entry in stack
    int stack[MAX]; //declaring array of characters with MAX size

    //function to check if stack is full
    bool isFull()
    {
        return (top == MAX - 1);
    }

    //-----------------------public members-----------------------
public:
    //default constructor
    intStack()
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
    int pop()
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
}; //end class intStack

//class that evaluates an expression using stack
class ExpressionEvaluation
{

    //----------------------private members----------------------

private:
    double result; //to store the result of evaluated expression

    //function to check for a valid operand
    bool isOperand(char C)
    {
        if (C >= '0' && C <= '9')
            return true;
        if (C >= 'a' && C <= 'z')
            return true;
        if (C >= 'A' && C <= 'Z')
            return true;
        return false;
    }

    //function to check for a valid operator symbol
    bool isOperator(char C)
    {
        if (C == '+' || C == '-' || C == '*' || C == '/' || C == '$' || C == '^')
            return true;

        return false;
    }

    //function to check for right associativity given by '$' symbol
    bool isRightAssociative(char op)
    {
        if (op == '$')
            return true;
        return false;
    }

    // function to get weight of an operator. Higher the weight, higher the precedence
    int weight(char op)
    {
        int weight = -1;
        switch (op)
        {
        case '+':
        case '-':
            weight = 1; //same precedence for +, -
        case '*':
        case '/':
            weight = 2; //same precedence for *, /
        case '$':
            weight = 3;
        case '^':
            weight = 4;
        }
        return weight;
    }

    // function to check for precedence of two operators, returns true if first operator has higher precedence
    bool precedence(char op1, char op2)
    {
        //getting weights of operator through 'weight' function
        int op1_weight = weight(op1);
        int op2_weight = weight(op2);

        //if both operators have same precedence then we will check for right associativity
        if (op1_weight == op2_weight)
        {
            if (isRightAssociative(op1))
                return false;
            else
                return true;
        }
        return op1_weight > op2_weight ? true : false;
    }

    //function to check if brackets in the expression are balanced
    bool areBracketsBalanced(string string)
    {
        CharStack S; //for brackets

        //iterating over the expression to check for a balanced expression
        for (int i = 0; i < string.length(); i++)
        {
            if (string[i] == '{' || string[i] == '}' || string[i] == '[' || string[i] == ']')
            {
                cout << "\nInvalid expression: " << string[i] << " not allowed.\n";
                return false;
            }
            //checking for opening brackets and pushing them in stack and their position in other stack
            if (string[i] == '(')
            {
                S.push(string[i]);
            }

            //checking for closing brackets and evaluating for balance
            else if (string[i] == ')')
            {
                //checking if stack is empty
                if (S.isEmpty())
                {
                    cout << "\nThis expression is NOT correct e.g., '" << string[i] << "' - not opened.\n";
                    return false;
                }

                //taking the recent of bracket in stack
                int open_bracket = S.peak();

                //checking for matching brackets and popping from respective stacks
                if (string[i] == ')' && open_bracket == '(')
                {
                    S.pop();
                }

                //if not a matching pair
                else
                {
                    cout << "\nThis expression is NOT correct e.g., '" << (char)S.peak() << "' - not closed.\n";
                    return false;
                }
            }
        }

        //checking if stack is not empty because if something must not have been matched
        if (!S.isEmpty())
        {
            cout << "\nThis expression is NOT correct e.g., '" << (char)S.peak() << "' - not closed.\n";
            return false;
        }

        //if stack is empty at the last then bracket would have got its match
        return true;

    } //end function areBracketsBalanced

    // function changes infix expression to postfix and returns the postfix expression
    string infixToPostfix(string expr)
    {
        CharStack S;
        string postfix = ""; //initializing empty string to store the formed postfix expression

        //traversing the expression from left for each token
        for (int i = 0; i < expr.length(); i++)
        {
            //if there is whitespace or comma then ignore
            if (expr[i] == ' ' || expr[i] == ',')
                continue;

            //if current token is an operator
            else if (isOperator(expr[i]))
            {
                while (!S.isEmpty() && S.peak() != '(' && precedence(S.peak(), expr[i]))
                {
                    postfix += S.peak();
                    S.pop();
                }
                S.push(expr[i]);
            }

            //if current token is an operand
            else if (isOperand(expr[i]))
            {
                string temp = "";
                while (isdigit(expr[i]))
                {
                    temp += expr[i];
                    i++;
                }
                postfix += temp;
                postfix += " ";
                i--;
            }

            //if current token is an opening bracket
            else if (expr[i] == '(')
            {
                S.push(expr[i]);
            }

            //if current token is an closing bracket, everything between opening will goto postfix expression
            else if (expr[i] == ')')
            {
                while (!S.isEmpty() && S.peak() != '(')
                {
                    postfix += S.peak();
                    S.pop();
                }
                S.pop();
            }
        }

        //after whole traversal, anything left in stack will goto postfix expression
        while (!S.isEmpty())
        {
            postfix += S.peak();
            S.pop();
        }

        return postfix;
    } //end function infixToPostfix

    // function returns after performing operation between symbol and operands
    void calculate(char symbol, int operand1, int operand2)
    {
        if (symbol == '+')
            result = operand1 + operand2;
        else if (symbol == '-')
            result = operand1 - operand2;
        else if (symbol == '*')
            result = operand1 * operand2;
        else if (symbol == '/')
            result = operand1 / operand2;
        else if (symbol == '^')
            result = pow(operand1, operand2);

        return;
    }

    //----------------------public members----------------------

public:
    bool evaluatePostfix(string expression, int *p)
    {
        intStack S;

        if (!areBracketsBalanced(expression))
        {
            return false;
        }

        string expr = infixToPostfix(expression);
        //traversing the expression from left for each token
        for (int i = 0; i < expr.length(); i++)
        {
            //if there is whitespace or comma then ignore
            if (expr[i] == ' ' || expr[i] == ',')
                continue;

            //if current token is an operator then performing operation accordingly over the operands
            else if (isOperator(expr[i]))
            {
                //taking 2 top most values
                int operand2 = S.peak();
                S.pop();
                int operand1 = S.peak();
                S.pop();

                // Perform operation
                calculate(expr[i], operand1, operand2);
                //Pushing back the result of operation in stack
                S.push(result);
            }
            else if (isdigit(expr[i]))
            {
                // taking the numeric operand from the string
                // Keep incrementing 'i' as long as you are getting a numeric digit to cater multi digit number
                int operand = 0;
                while (i < expr.length() && isdigit(expr[i]))
                {
                    //to incorporate multi digit number, making every right digit encountered
                    //as multiple of 10 and adding in the one complete operand
                    operand = (operand * 10) + (expr[i] - '0');
                    i++;
                }
                i--; //decrementing so indexing remains correct to traverse whole expression

                S.push(operand);
            }
        }

        // the last value in the stack would be our answer after whole expression has been traversed
        *p = S.peak();
        return true;
    } //end function evaluate
};    //end class ExpressionEvaluation

int main()
{
    ExpressionEvaluation e;
    int answer;
    int *p = &answer;
    string expression;
    cout << "\nEnter the expression (only paranthesis are allowed) : ";
    getline(cin, expression);

    if (e.evaluatePostfix(expression, p))
    {
        cout << "Answer of the evaluated expression: " << answer;
    }
    else
    {
        e.evaluatePostfix(expression, p);
    }
}
