    #include <iostream>
    #include <string>
    #include <future>
    #include <vector>

    static unsigned int PJWHash(std::string str) {
      const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
      const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
      const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
      const unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (int)(BitsInUnsignedInt - OneEighth);
      unsigned int hash = 0;
      unsigned int test = 0;
      unsigned int i = 0;
      unsigned int len = str.length();

      for (i = 0; i < len; i++)
      {
        hash = (hash << (int)OneEighth) + (str[i]);

        if ((test = hash & HighBits) != 0)
        {
          hash = ((hash ^ (test >> (int)ThreeQuarters)) & (~HighBits));
        }
      }

      return hash;
    }

    void CheckRegistration(std::string RegNumber, bool* b)
    {
      if (PJWHash(RegNumber) == 214968)
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
      std::cout << "regcode: ";
      std::cin >> RegNumber;
      bool* IsRegistered = new bool;
      *IsRegistered = false;

      //std::string data = "1488";
      //unsigned int value = PJWHash(data);

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
