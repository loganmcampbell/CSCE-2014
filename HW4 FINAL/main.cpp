#include <iostream>
#include <cmath>
#include "Vector.h"
#include <stack>
#include <cstdlib>

using namespace std;

bool isOperator(const string& str)
{
    return str == "*" || str == "/" || str == "+" || str == "-";
}

int precedence(string str) 
{
    int priority = 0;
    if (str == "*" || str == "/")
    {
        priority = 2;
    
    }
    else if (str == "+" || str == "-")
    {
            priority = 1;
    }
    
    return priority;
}

bool shuntingYard(const Vector<string>& expression, Vector<string>& postfix)
{
//S T A C K
    stack <string> output;
    
    
//{-------------------------------------------------------------> S T A R T    L O O P     
    // L O O P   4   E X P R E S S I O N
    for (int x = 0; x < expression.getSize(); x++)
    {
        //R E A D   T O K E N
        string token = expression.get(x);
        
        
        //C O N D I T I O N S :  I F ' x ' = + / * -
        if (isOperator(token))
        {
            while (!output.empty() && precedence(output.top()) >= precedence(token))
            {
                postfix.pushBack(output.top());
                output.pop();
            }
                output.push(token);
        }

        //C O N D I T I O N : L E F T   P A R E N T
        else if ( token == "(")
         {
            output.push(token);
         }
         
        //C O N D I T I O N : R I G H T  P A R E N T
         else if ( token == ")")
         {
            // make sure it doesn't reach left parent and it is not empty
            while (!output.empty() && output.top() != "(" )
            {
                //push operator(s) (through loop) in stack (within the parent)
                postfix.pushBack(output.top());
                output.pop();
            }
            cout << "top before pop : " << output.top();
                output.pop();
         }
        else
        {
            //C O N D I T I O N   :    #   O R   D O U B L E
            postfix.pushBack(token);
        }
    }
//}-------------------------------------------------------------> E N D    L O O P     
    
    
//{ A S S I G N  T H E   R E S T   T O   O U T P U T
        while (!output.empty()) 
        {
            postfix.pushBack(output.top());
            output.pop();
        }
                cout << "postfix : "; postfix.print();

//}-------------------------------------------------
    
    
//{ S T A R T   C H E C K I N G
    
    
//{------------->   P A R E N T H E S I S   R A T I O   C H E C K
    for (int x = 0; x < postfix.getSize(); x++)
    {
        if (postfix.get(x) == "(" || postfix.get(x) == ")")
        {
            cout << "\t* P A R E N T H E S I S   M I S M A T C H E D *" << endl;
            return false;
        }
    }
    
    
//}---------<<<<<<<
    
    
//{------------->   N U M B E R  2   O P E R A T O R     R A T I O   C H E C K
    int numbers = 0;
    int operators = 0;
    for (int x = 0; x < postfix.getSize(); x++)
    {
        if (isOperator(postfix.get(x)))
            operators++;
    }
    numbers = postfix.getSize() - operators;
    
//    cout << "S I Z E : " << postfix.getSize() << endl;
//    cout << "N U M B E R S : " << numbers << endl;
//    cout << "O P E R A T O R S : " << operators << endl;
    
    if (numbers % 2 == 0 && operators % 2 == 1)
    {
        // EVEN AMOUNT OF NUMBERS to ODD AMOUNT OF OPERATORS
        return true;
    }
    else if ((numbers % 2 == 1 && operators % 2 == 0 ) && numbers != 1)
    { 
        // ODD AMOUNT OF NUMBERS TO EVEN AMOUNT OF OPERATORS && IT IS NOT JUST 1 NUMBER
        return true;
    }
  
    else if (numbers == 1 && operators == 0)
    {
        // IF IT IS ONLY ONE NUMBER NO OPERATOR
            return true;
    }
    else
    {
        // OTHERWISE IT'S A BAD EQUATION
        cout << "\t* E X P R E S S I O N    U N A U T H O R I Z E D *" << endl;
        return false;
    }
//}-----------<<<<
    
    
//}============
    return true;
}

bool evaluatePostfix(const Vector<string>& postfix, double& result)
{
    stack <double> conduct;
    
    for (int x = 0; x < postfix.getSize(); x++)
    {

        cout << " t o k e n [" << x << "] : " << postfix[x] << endl;
        cout << endl;

        if (isOperator(postfix[x]))
        {

            double left = conduct.top();
            conduct.pop();
            double right = conduct.top();
            conduct.pop();
            
            if (postfix[x] == "+")
            {
                
                conduct.push(right + left);
                cout << "   a d d : " << left << " + " << right << endl;
            }
            else if (postfix[x] == "-")
            {
                conduct.push( right - left);
                cout << "   s u b : " << left << " - " << right << endl;
            }
            else if (postfix[x] == "*")
            {
                conduct.push( right * left);
                cout << "   m u l : " << left << " * " << right << endl;
            }
            else if (postfix[x] == "/")
            {
                if (left == 0)
                {
                    cout << "\ncannot divde by zero" << endl;
                    result = 0;
                    return false;
                }
                    conduct.push( right / left );
                    cout << "   d i v : " << left << " / " << right << endl;
                }
        }
        
        else
        {
            // Number
            conduct.push(atof(postfix[x].c_str()));
        }

    }
    
    result = conduct.top();
    return true;
}

int main()
{
    bool run = true;
    while (run != false)
    {
        cout << "\t\trudimentary mathematical expression calculator\t" << endl;
        cout << "\t\t==============================================\t" << endl;
        cout <<"\nenter an infix equation: ";
        Vector<string> expression;
        string token;         
        while (cin >> token)
        {
            expression.pushBack(token);
        }

        cout << "\n\tinfix equation: "; 
        expression.print();
        cout << endl;
        
        Vector<string> postfix;
        if (shuntingYard(expression, postfix))
        {
            cout << "\tpostfix conversion: "; 
            postfix.print();
            cout << endl;
            double result;
            evaluatePostfix(postfix, result);        
            cout << "\n\tevaluation: " << result << endl;
        }
    
        cout << "\n\n\trun again? y/n : ";
        char repeat;
        cin.clear();
        cin >> repeat;
        
        while ( repeat != 'y' && repeat != 'n')
        {
            cin >> repeat;
        }
        
        if (repeat == 'y')
        {
            cout << "\nR U N : A G A I N : " << endl;
            run = true;
        }
        else
        {
            cout << ".. T E R M I N A T I N G ..." << endl;
            run = false;
        }
    }
    
        
    return 0;

    
}

