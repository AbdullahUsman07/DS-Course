#include<iostream>
#include<string>
#include<stack>


 //Converting Infix to Postfix Notation
 //Steps---
 //1- Travserse through the String untill the operand is found push it into the stack
 //2- On pushing there are some steps
 // i- Check if the stack is empty then push it as it is
 // ii-Check if any prev operator in Stack compare its precedence.
 // iii If the Precedence is lower or greater pop the operator and write it in the output exp
 //  else push in on the top
 //
 //3- When the String travsersal is Completed Pop all the oprands untill Stack empty and write them in output 
 //
 //Some Special Case for Brackets
 //if Opeing Brace is Found Push it in the Stack which can only be removed by Closing brace
 //When the closing brace is found pop all the operands and write them in the output untill the
 //opening brace is found!
 
double evaluate_postfix(const std::string& postfix)
{
	std::stack<double> stk;

	for (int i = 0; i < postfix.length(); i++)
	{
		char ch=postfix[i];

		if (isdigit(ch))
		{
			stk.push(ch - '0');
		}

		else
		{
			if (stk.size() < 2)
			{
				throw"Invalid Expression!";
			}

			double operand_2 = stk.top();
			stk.pop();
			double operand_1 = stk.top();
			stk.pop();

			switch (ch)
			{
			case'+':
				stk.push(operand_1 + operand_2);
				break;

			case'-':
				stk.push(operand_1 - operand_2);
				break;

			case'*':
				stk.push(operand_1 * operand_2);
				break;

			case'/':
				if (operand_2 == 0)
				{
					throw "Division By Zero Error";
				}
				stk.push(operand_1 / operand_2);
				break;

			case'^':
				stk.push(pow(operand_1, operand_2));
				break;

			default:
				throw"Invalid Operator!";
			}
		}
	}

	if (stk.size() != 1)
	{
		throw" Error Occured!";
	}

	return stk.top();
}

int precendece(char op)
{
	if (op == '+' || op == '-')
		return 1;

	if (op == '*' || op == '/')
		return 2;

	if (op == '^')
		return 3;

	return 0;
}

std::string postfix_convert(const std::string& infix)
{
	std::string output;
	std::stack<char> stk;
	char ch;

	for (int i = 0; i < infix.length(); i++)
	{
		ch = infix[i];
		if (isalnum(ch))
		{
			output += ch;
		}

		else if (ch == '(')
		{
			stk.push(ch);
		}

		else if (ch == ')')
		{
			while (!stk.empty() && stk.top() != '(')
			{
				output += stk.top();
				stk.pop();
			}

			// pop the ) operator
			stk.pop();
		}

		else
		{
			while (!stk.empty() && (precendece(stk.top()) >= precendece(ch)))
			{
				output += stk.top();
				stk.pop();
			}
			// it will add operators in stack
			stk.push(ch);
		}
		

	}


	// now add the remaining operators untill the stack is empty
	while (!stk.empty())
	{
		output += stk.top();
		stk.pop();
	}

	return output;
	
}


//int main()
//{
//	std::string infix = "A*(B+C)/(D-E)+F*G";
//	std::string postfix = postfix_convert(infix);
//	std::cout << " Infix: " << infix << "\n" << " Postfix: " << postfix << "\n";
//}