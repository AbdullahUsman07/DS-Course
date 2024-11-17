#include<iostream>
#include<string>
#include<stack>

// The logic is nearly same as the postfix evaluation
// in this case stack would be of type string .
//
// 1- First push all the Alphanumeric characters untill the operator is found
// 2- When operator is found pop the the two string objects from the stack and 
//   wrap them around braces and write the operator betwen them and push back to string
// 3- Contine this until the '/0'
// 4- At last the top of the stack gives us the infix expression

std::string convert_to_infix(std::string& postfix)
{
	std::stack<std::string> stk;

	for (int i = 0; i < postfix[i]; i++)
	{
		char ch = postfix[i];

		if (isalnum(ch))
		{
			stk.push(std::string(1, ch));
		}

		else
		{
			if (stk.size()<2)
			{
				throw "Error Occured!";
			}

			std::string operand_2 = stk.top();
			stk.pop();
			std::string operand_1 = stk.top();
			stk.pop();

			std::string subexp = "( " + operand_1 + " " + ch + " " + operand_2 + " )";
			stk.push(subexp);
		}
	}

	if (stk.size() != 1)
	{
		throw "Error!";
	}
	return stk.top();
}
// A*(B+C)/(D-E)+F*G

int main()
{
	std::string postfix = "ABC+*DE-/FG*+";
	std::string infix = convert_to_infix(postfix);
	std::cout << " Postfix: " << postfix << "\n" << " Infix: " << infix << "\n";
}

