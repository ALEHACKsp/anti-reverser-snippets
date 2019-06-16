    #include <iostream>
    #include <future>
    #include <vector>

    void CheckRegistration(int RegNumber, bool* b)
    {
        *b = false;
    }

    int main()
    {
        int RegNumber = 0; 
        bool* IsRegistered = new bool;
        *IsRegistered = true;
        CheckRegistration(RegNumber, IsRegistered);
        if ((*IsRegistered)) {
            std::cout << "Registered";
        }
        else {
            std::cout << "Unregistered";
        }
        delete IsRegistered;
    }
