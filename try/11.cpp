#include <iostream>
int main ()
{
	int a = 10;
	int b = 0;
	try
	{
		if (b == 0)
		{
			throw "Division by zero!";
		}
		std::cout << "Result: " << a / b << std::endl;
	}
	catch (const char* msg)
	{
		std::cerr << "Error: " << msg << std::endl;
	}
	return 0;
}