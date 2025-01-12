#include <iostream>
#include<string>
#include<stack>
#include<fstream>
#include<math.h>


bool match_exist(char ch1, char ch2)
{
    if (ch1 == '(' && ch2 == ')')
        return true;

    if (ch1 == '{' && ch2 == '}')
        return true;

    if (ch1 == '[' && ch2 == ']')
        return true;

    return false;
}

int hierrachy(char ch)
{
    if (ch == '+' || ch == '-')
    {
        return 1;
    }
    if (ch == '*' || ch == '/')
    {
        return 2;
    }

    return 0;
}






bool balance_parenthesis(const std::string& infix)
{
    std::stack<char> stk;
    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[')
        {
            stk.push(infix[i]);
        }

        else if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']')
        {
            
            if (! stk.empty() && match_exist(stk.top(), infix[i]))
                stk.pop();

            else
                return false;
        }
    }

    return stk.empty();
}

bool balance_operator(const std::string& postfix)
{
    int no_of_operators = 0;
    int no_of_operands = 0;
    int i = 0;
    std::string data = "";

    while (i < postfix.length())
    {
        data = "";
        while (postfix[i] != ' ' && postfix[i] != '\0')
        {
            data += postfix[i];
            i++;
        }
        //skipping the space
        i++;

        
        if (data[0] >= '0' && data[0] <= '9')
        {
            //that means it is a digit
            no_of_operands++;

        }

        else
        {
            //means they are operators
            no_of_operators++;
        }
    }

    // in every case operands are equal to (operators+1)
    return  (no_of_operands - 1) == no_of_operators;
}


bool validate_expression(const std::string& infix)


{
    if (balance_parenthesis(infix))
    {
        for (int i = 0; i < infix.length(); i++)
        {
            if (infix[i] == '(' || infix[i] == '{' || infix[i] == '[')
            {
                continue;
            }

            else if (infix[i] == ')' || infix[i] == '}' || infix[i] == ']')
            {
                continue;
            }

            else if (infix[i] >= '0' && infix[i] <= '9')
            {
                continue;
            }

            else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
            {
                continue;
            }

            else if (infix[i] == ' ')

            {
                continue;
            }

            else
            {
                return false;
            }
        }

        return true;
    }
    else
    {
        std::cout << " Brackets not Balanced!\n";
        return false;
    }
}




const std::string postfix_notation(const std::string& infix)
{
    std::stack<char> stk;
    std::string postfix = "";
    char post;
    int size = 0;

    for (int i = 0; i < infix.length(); i++)
    {
        post = infix[i];

        // if a space is found write it in the postfix notation
        if (post == ' ' ||(post >='0' && post<='9'))
        {
            if (post == ' ' && postfix[size - 1] == ' ')
            {
                continue;
            }
            postfix += post;
            size++;
        }

        else if (post == '(')
        {
            stk.push(post);
        }



        else if (post == '+' || post == '-' || post == '*' || post == '/')
        {
            if (stk.empty())
            {
                stk.push(post);
            }
            else
            {
                while (!stk.empty() && hierrachy(stk.top()) >= hierrachy(post) )
                {
                    if (postfix[size-1] != ' ') {
                        postfix += ' ';
                        postfix += stk.top();
                        size += 2;
                    }
                    else
                    {
                        postfix += stk.top();
                        size += 1;
                    }
                    stk.pop();
                }
                stk.push(post);
            }

        }

        

        else if (post == ')')
        {
            while (stk.top() != '(')
            {
                if (postfix[size-1] != ' ') {
                    postfix += ' ';
                    postfix += stk.top();
                    size += 2;
                }
                else
                {
                    postfix += stk.top();
                    size += 1;
                }
                stk.pop();
            }
            // removing the opening brace (
            stk.pop();
        }

        else
        {
            throw "Something Wrong!";
        }
    }

    while (!stk.empty())
    {
        if (postfix[size-1] != ' ') {
            postfix += ' ';
            postfix += stk.top();
            size += 2;
        }
        else
        {
            postfix += stk.top();
            size += 1;
        }
        stk.pop();
    }

    return postfix;
}

int postfix_evaluate(const std::string& postfix)
{
    std::stack<std::string> stk;
    std::string data="";
    int result = 0;
    // 
    int i = 0;
    while (i<postfix.length())
    {
        data = "";
        while (postfix[i] != ' ' && postfix[i]!='\0')
        {
            data += postfix[i];
            i++;
        }
        //skip the ' ' (space)
        i++;

        if (data == "+" || data == "-" || data == "*" || data == "/")
        {
            char _operator = data[0];
            int second = stoi(stk.top());
            stk.pop();
            int first = stoi(stk.top());
            stk.pop();

            

            if (_operator == '+')
            {
                result = second + first;
                stk.push(std::to_string(result));
            }

            else if (_operator == '-')
            {
                result = first - second;
                stk.push(std::to_string(result));
            }

            else if (_operator == '*')
            {
                result = second * first;
                stk.push(std::to_string(result));
            }

            // which is the / operator
            else
            {
                if (second != 0)
                {
                    result = first / second;
                    stk.push(std::to_string(result));
                }
                else
                {
                    throw "Divison By Zero";
                }

            }
        }

        else
        {
            stk.push(data);
        }
    }

    return stoi(stk.top());
}


int main(int argc,char *argv[])
{
    std::string input="", postfix = "";
    int result = 0;
    char choice;
    bool flag;
    if (argc == 1)
    {
        std::cout << "Please Input Expression!: ";
        std::getline(std::cin, input);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            input += argv[i];
            input += ' ';
        }
    }
     

    if (validate_expression(input))
       {
            std::cout << " Your Expression is: " << input << "\n";
            try {
                postfix = postfix_notation(input);
                std::cout << " The Postfix: " << postfix << "\n";
            }
            catch (const std::string& msg)
            {
                std::cout << msg << " Error Occured!\n";
            }

            if (balance_operator(postfix)) {

                try {
                    result = postfix_evaluate(postfix);
                    std::cout << " The Resultant would be: " << result << "\n";
                }
                catch (const std::string& msg)
                {
                    std::cout << msg << " Error Occured!\n";
                }
            }
            else
            {
                std::cout << " Cant Evaluated Expression Becauses Operators or Operands are not correct!\n";
                return 1;
            }


            do {
                flag = true;
                std::cout << "\n\n--------------------------\n\n";
                std::cout << " MS    [1]: \n";
                std::cout << " MR    [2]: \n";
                std::cout << " M+    [3]: \n";
                std::cout << " Power [4]: \n";
                std::cout << " Log   [5]: ";

                std::cin >> choice;


                if (choice == '1') {
                    std::fstream file("Calculator.txt", std::ios::out);
                    file << result;
                    std::cout << " Result Saved!\n";
                    file.close();
                }

                else if (choice == '2')
                {
                    int data = 0;
                    std::fstream file("Calculator.txt", std::ios::in);
                    file >> data;
                    std::cout << " The Result is: " << data << " \n";
                }

                else if (choice == '3')
                {
                    std::fstream file("Calculator.txt", std::ios::in);
                    int data = 0;
                    file >> data;
                    file.close();
                    std::fstream file_("Calculator.txt", std::ios::out, std::ios::trunc);
                    data += result;
                    file_ << data;
                    file_.close();
                }

                else if (choice == '4')
                {
                    int e, b;
                    std::cout << " Enter Base: ";
                    std::cin >> b;
                    std::cout << " Enter Exponent: ";
                    std::cin >> e;

                    std::cout << b << " To the power of " << e << " is : " << std::pow(b, e);
                }

                else if (choice == '5')
                {
                    int num;
                    do {
                        std::cout << " Enter Number (Non-Negative): ";
                        std::cin >> num;
                    } while (num <= 0);

                    std::cout << "Log of " << num << " is : " << std::log(num) << "\n";
                }

                else
                {
                    flag = false;
                }
            } while (flag);

     }
    else
    {
        std::cout << " Please Input Valid Expression!";
    }

    




    
    return 0;
}

