## **Проверка регистрационных ключей**
Используя `t1ha`  hash function

    #include "t1ha.h"
    #include <iostream>
    
    #pragma comment(lib, "t1ha-static.lib")
    
    //https://github.com/leo-yuriev/t1ha/issues/33#issuecomment-502691098
    inline uint64_t t1ha0(const char* cstr, const uint64_t seed) {
    	return t1ha0(cstr, strlen(cstr), seed);
    }
    inline uint64_t t1ha0(const std::string& str, const uint64_t seed) {
    	return t1ha0(str.data(), str.size(), seed);
    }
    
    // генерация случайного сида для t1ha 
    uint64_t rand_uint64() {
    	uint64_t r = rand();
    	r = r << 30 | rand();
    	r = r << 30 | rand();
    	return r;
    }
    
    void CheckRegistration(std::string RegNumber, bool* b)
    {
    	if (t1ha0(RegNumber, 10376313370251892926) == 7530078511373767546)
    	{
    		*b = true;
    	}
    	else {
    		*b = false;
    	}
    }
    
    int main()
    {
    	std::string RegNumber;
    	std::cout << "regcode: "; // valid key 1488
    	std::cin >> RegNumber;
    	bool* IsRegistered = new bool;
    	*IsRegistered = false;
    
    	CheckRegistration(RegNumber, IsRegistered);
    
    	if ((*IsRegistered)) {
    		std::cout << "Registered";
    	}
    	else {
    		std::cout << "Unregistered";
    	}
    	delete IsRegistered;
    
    	system("pause");
    }
