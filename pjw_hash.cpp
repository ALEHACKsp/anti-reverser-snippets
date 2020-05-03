#include <iostream>
#include <string>

using namespace std;
int* is_registered = new int;

static unsigned int pjw_hash(std::string value)
{
	const auto bits_in_unsigned_int = static_cast<unsigned int>(sizeof(unsigned int) * 8);
	const auto three_quarters = static_cast<unsigned int>(bits_in_unsigned_int * 3 / 4);
	const auto one_eighth = static_cast<unsigned int>(bits_in_unsigned_int / 8);
	const auto high_bits = static_cast<unsigned int>(0xFFFFFFFF) << static_cast<int>(bits_in_unsigned_int - one_eighth);
	unsigned int hash = 0;
	unsigned int test = 0;
	const unsigned int len = value.length();

	for (unsigned int i = 0; i < len; i++)
	{
		hash = (hash << static_cast<int>(one_eighth)) + value[i];

		if ((test = hash & high_bits) != 0)
		{
			hash = (hash ^ test >> static_cast<int>(three_quarters)) & ~high_bits;
		}
	}

	return hash;
}


void check_registration(const string& reg_number, int* b)
{
	if (pjw_hash(reg_number) == 1921)
	{
		*b = 1;
	}
}

int main()
{
	// valid reg_number "qq"
	std::string reg_number;
	cout << "regcode: \r\n";
	cin >> reg_number;

	*is_registered = 0;
	check_registration(reg_number, is_registered);
	try
	{
		if (*is_registered)
		{
			cout << "registered\r\n";
		}
		else
		{
			cout << "unregistered\r\n";
		}
	}
	catch (...)
	{
	}

	delete is_registered;
	system("pause");
}
