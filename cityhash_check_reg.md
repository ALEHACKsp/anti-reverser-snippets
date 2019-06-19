## **Проверка регистрационных ключей**
Используя `CityHash`  hash function

    #include <iostream>
    #include "city/city.h"
    
    void CheckRegistration(std::string reg_number, bool* b)
    {
    	//const uint64 hashed = CityHash64(RegNumber.data(), strlen(RegNumber.data()));
    
    	if (CityHash64(reg_number.data(), strlen(reg_number.data())) == 6659734414415773158)
    	{
    		*b = true;
    	}
    	else {
    		*b = false;
    	}
    }
    
    int main()
    {
    	std::string reg_number;
    	std::cout << "regcode: "; // valid key 1488
    	std::cin >> reg_number;
    	const auto is_registered = new bool;
    	*is_registered = false;
    
    	CheckRegistration(reg_number, is_registered);
    
    	if (*is_registered) {
    		std::cout << "Registered";
    	}
    	else {
    		std::cout << "Unregistered";
    	}
    
    	delete is_registered;
    
    	system("pause");
    }
