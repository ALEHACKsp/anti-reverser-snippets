#include <iostream>

using namespace std;
int* is_registered = new int;

void check_registration(const int reg_number, int* b)
{
	if (reg_number == 1337)
	{
		*b = 1;
	}
}

int main()
{
	auto reg_number = 0;

	cout << "regcode: \r\n";
	cin >> reg_number;

	*is_registered = 0;
	check_registration(reg_number, is_registered);
	try
	{
		if (*is_registered)
		{
			cout << "Registered\r\n";
		}
		else
		{
			cout << "Unregistered\r\n";
		}
	}
	catch (...)
	{
	}

	delete is_registered;
	system("pause");
}
