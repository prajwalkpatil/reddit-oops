#include "reddit.h"

int main()
{
    User u;
    try
    {
        u.registerUser();
    }
    catch (RegistrationError r)
    {
        r.printError();
        exit(-1);
    }
    catch (...)
    {
        cout << "Error!" << endl;
        exit(-1);
    }

    u.printDetails();
    return 0;
}
