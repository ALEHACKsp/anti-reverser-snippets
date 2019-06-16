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
