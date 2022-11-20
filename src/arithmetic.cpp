// реализация функций и классов для вычисления арифметических выражений

#include "..\include\arithmetic.h"

Term::Term(double _num): numb(_num), TypeLexeme(1) {};

Term::Term(char _operation) 
{
	if ((_operation == '~') || (_operation == '+') || (_operation == '-') || (_operation == '*') || (_operation == '/') || (_operation == '(') || (_operation == ')'))
	{
		action = _operation;
		TypeLexeme = 2;
	}
	else
	{
		cout << endl;
		throw "Error: not correct symbol action";
	}
}

Term::Term(string _alternating)
{
	size_t tmp = true;
	for (size_t i = 0; i < _alternating.length(); i++)
	{ 
		if ((_alternating[i] < 'a') || (_alternating[i] > 'z'))
		{
			tmp = false;
			cout << endl;
			throw "Error: not correct symbol int variety-parameter";
		}
	}

	if (tmp == true)
	{
		alternate = _alternating;
		TypeLexeme = 3;
	}
}

double Term::getNumber()
{
	return numb;
}

char Term::getOperation()
{
	return action;
}

string Term::getAlternating()
{
	return alternate;
}

size_t Term::getTypeLexeme()
{
	return TypeLexeme;
}

size_t Term::getPriorityOperation()
{
	switch (action)
	{
	case '(':
	{
		return 0;
	}
	case ')':
	{
		return 0;
	}
	case '+':
	{
		return 1;
	}
	case '-':
	{
		return 1;
	}
	case '*':
	{
		return 2;
	}
	case '/':
	{
		return 2;
	}
	case '~':
	{
		return 3;
	}
	}
}

void Term::printT()
{
	switch (TypeLexeme)
	{
	case 1:
	{
		cout << numb << " ";
		break;
	}
	case 2:
	{
		cout << action << " ";
		break;
	}
	case 3:
	{
		cout << alternate << " ";
		break;
	}
	}
}

void Arithmetic::translateStrToTerm(string str)
{
	bool tmp = true;
	size_t countBrackets = 0;
	size_t dimension = str.dimension();
	size_t countSpace = 0;

	if ((str[0] == '+') || (str[0] == '*') || (str[0] == '/'))
	{
		throw "Error: binary opeartions is at first position";
	}

	if ((str[str.dimension() - 1] == '+') || (str[str.dimension() - 1] == '-') || (str[str.dimension() - 1] == '*') || (str[str.dimension() - 1] == '/'))
	{
		throw "Error: binary opeartions is at last position";
	}

	for (size_t i = 0; i < str.length();)
	{
		if (str[i] == ' ')
		{
			countSpace++;
			i++;
			continue;
		}

		if ((str[i] < '(') || (str[i] == ',') || ((str[i] > '/') && (str[i] < '0')) || ((str[i] > '9') && (str[i] < 'a')) || (str[i] > 'z'))
		{
			throw "Error: in str inccorect symbol";
		}

		if ((str[i] == '+') || (str[i] == '*') || (str[i] == '/'))
		{
			Term action(str[i]);
			term.push_back(action);
			i++;
			continue;
		}

		if (str[i] == '-')
		{
			if (i == 0)
			{
				Term un_minus('~');
				term.push_back(un_minus);
				i++;
				continue;
			}
			else
			{
				if ((term[i - countSpace - 1].getOperation() != ')') && (term[i - countSpace - 1].getTypeLexeme() == 2))
				{
					Term un_minus('~');
					term.push_back(un_minus);
					i++;
					continue;
				}
				else
				{
					Term minus('-');
					term.push_back(minus);
					i++;
					continue;
				}
			}
		}
			
		if ((str[i] >= 'a') && (str[i] <= 'z'))
		{
			string alternatings;
			while ((str[i] >= 'a') && (str[i] <= 'z'))
			{
				alternatings = alternatings + str[i];
				i++;
			}
			Term _alternatings(alternatings);
			term.push_back(alternatings);
			continue;
		}

		if ((str[i] >= '0') && (str[i] <= '9') || (str[i] == '.'))
		{
			string numbers;
			size_t tmpPoint = 0;
			while (str[i] >= '0' && str[i] <= '9' || (str[i] == '.'))
			{
				numbers = numbers + str[i];
				i++;
				if (str[i] == '.')
				{
					tmpPoint++;
				}
				if (tmpPoint > 1)
				{
					throw "Error: More then 1 point";
				}
				countSpace++;
			}

			double tmp = stof(numbers);
			Term _numbers(tmp);
			term.push_back(tmp);
			countSpace--;
			continue;
		}

		if (str[i] == '(')
		{
			countBrackets++;
			tmp = false;

			if ((i < dimension) && ((str[i + 1] == '+') || (str[i + 1] == '-') || (str[i + 1] == '*') || (str[i + 1] == '/')))
			{
				throw "Error: action is after openning bracket";
			}

			if (i != 0 && str[i - 1] >= '0' && str[i - 1] <= '9')
			{
				throw "Error: numb is before open bracket without action";
			}

			Term _bracket(str[i]);
			term.push_back(_bracket);
			i++;
			continue;
		}
		
		if (str[i] == ')')
		{
			countBrackets--;
			tmp = true;
			Term _bracket(str[i]);
			term.push_back(_bracket);
			i++;
			continue;
		}
	}

	if (tmp == false || countBrackets != 0)
	{
		throw "Error: More or Less brackets";
	}
}

void Arithmetic::TermToPolishNote()
{
	size_t dimension = term.dimension();
	Stack <Term> action;

	for (size_t i = 0; i < dimension; i++)
	{
		if (term[i].getTypeLexeme() == 1)
		{
			polishNote.push_back(term[i]);
			continue;
		}

		if (term[i].getTypeLexeme() == 3)
		{
			polishNote.push_back(term[i]);
			continue;
		}

		if (term[i].getOperation() == '(')
		{
			action.Push(term[i]);
			continue;
		}

		if (term[i].getOperation() == ')')
		{
			try
			{
			while (action.GetLastEl().getOperation() != '(')
			{
				polishNote.push_back(action.Pop());
			}
			action.Pop();
			continue;
			}
			catch (char* error)
			{
				if (error == "Stack is Empty")
				{
					throw "Error: havent allowing open bracket";
				}
			}
		}

		if (term[i].getOperation() == '~')
		{
			action.Push(term[i]);
		}

		if ((term[i].getOperation() == '+') ||( term[i].getOperation() == '-') || (term[i].getOperation() == '*') || (term[i].getOperation() == '/'))
		{
			while ((!action.IsEmpty()) && (action.GetLastEl().getPriorityOperation()) >= (term[i].getPriorityOperation()))
			{
				polishNote.push_back(action.Pop());
			}
			action.Push(term[i]);
		}
	}

	while (!action.IsEmpty())
	{
		polishNote.push_back(action.Pop());
	}
}

void Arithmetic::calculate()
{
	Stack <Term> numbers;
	Term termleftV, termrightV;
	double leftV = 0;
	double rightV = 0;
	double resultOperation = 0;

	unordered_map<string, double> value;

	for (size_t i = 0; i < polishNote.dimension(); i++)
	{
		
		if (polishNote[i].getTypeLexeme() == 3)
		{
			if (value.count(polishNote[i].getAlternating()) != 0)
			{
				double tmp = 0.0;
				tmp = value.at(polishNote[i].getAlternating());
				numbers.Push(tmp);
				continue;
			}
			else
			{
				cout << "Term has variable " << endl << " Give value " << polishNote[i].getAlternating() << ":";
				double tmp = 0.0;
				cin >> tmp;
				value.insert(unordered_map<string, int>::value_type(polishNote[i].getAlternating(), tmp));
				numbers.Push(tmp);
				continue;
			}
		}
		

		if (polishNote[i].getTypeLexeme() == 1)
		{
			numbers.Push(polishNote[i].getNumber());
			continue;
		}

		if (polishNote[i].getOperation() == '~')
		{
			resultOperation = (-1) * numbers.Pop().getNumber();
			numbers.Push(resultOperation);
			continue;
		}
		else
		{
			try
			{
			termrightV = numbers.Pop();
			termleftV = numbers.Pop();
			leftV = termleftV.getNumber();
			rightV = termrightV.getNumber();
			}
			catch (char* error)
			{
				if (error == "Stack is Empty")
				{
					throw "Error: opearand is miss";
				}
			}

			switch (polishNote[i].getOperation())
			{
			case '+':
			{
				resultOperation = leftV + rightV;
				break;
			}
			case '-':
			{
				resultOperation = leftV - rightV;
				break;
			}
			case '*':
			{
				resultOperation = leftV * rightV;
				break;
			}
			case '/':
			{
				if (rightV == 0)
				{
					throw "Division by zero";
				}
				resultOperation = leftV / rightV;
				break;
			}
			}

			numbers.Push(resultOperation);
		}
	}

		try
		{ 
		Term resultT = numbers.Pop();
		result = resultT.getNumber();
		cout << result;
		}
		catch (char* error)
		{
			throw "Error: term was empty";
		}
}

void Arithmetic::PrintVectP()
{
	for (size_t i = 0; i < polishNote.dimension(); i++)
	{
		polishNote[i].printT();
	}

	cout << endl;
}

void Arithmetic::PrintVecT()
{
	for (size_t i = 0; i < term.dimension(); i++)
	{
		term[i].printT();
	}
	cout << endl;
}

double Arithmetic::GetResult()
{
	return result;
}
