    #include <iostream>
    #include <future>
    #include <vector>

    bool* CheckRegistration(int RegNumber)
    {
      return false;
    }

    int main()
    {
      int RegNumber;
      bool* IsRegistered = new bool;

      if (!&IsRegistered) {
        int ads = 123;
        IsRegistered = CheckRegistration(RegNumber);
      }
      else {
        int ad2s = 213;
        //exit(0);
      }

        std::cout << "Hello World!\n";
    }
