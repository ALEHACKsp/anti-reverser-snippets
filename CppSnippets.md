    #include <iostream>
    #include <future>
    #include <vector>

    void CheckRegistration(int RegNumber, bool* b)
    {
        if (RegNumber == 1488)
        {
            *b = true;

        }
        else {
            *b = false;
        }
    }

    int main()
    {
        int RegNumber = 0; 
        std::cout << "regcode: ";
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

   Ida Pro decompile
   

    int main()
    {
      const char *v2; // edx
      int v4; // [esp+8h] [ebp-8h]
      v4 = 0;
      ...
      sub_4010A0(std::cout, "regcode: ");
      std::basic_istream<char,std::char_traits<char>>::operator>>(std::cin, &v4);
    ...
      if ( v4 == 1488 )
      {
        *v0 = 1;
        v2 = "Registered";
      }
      else
      {
        v2 = "Unregistered";
      } 
    }
