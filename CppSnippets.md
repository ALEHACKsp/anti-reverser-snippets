    #include <iostream>
    #include <future>
    #include <vector>

    void CheckRegistration(int RegNumber, bool* b)
    {
      *b = true;
    }

    int main()
    {
      int RegNumber = 0; 
      bool* IsRegistered = new bool;
      *IsRegistered = false;
      CheckRegistration(RegNumber, IsRegistered);
      if ((*IsRegistered)) {
        std::cout << "Registered";
      }
      delete IsRegistered;
    }
