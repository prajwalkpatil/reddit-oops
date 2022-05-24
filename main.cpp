#include "reddit.h"

int main()
{
    int choice;
    int loggedInStatus = 0;
    vector<Subreddit *> s;
    vector<User *> u;
    User *tempUser = nullptr;
    display_logo();
    cout << endl;
    Logger *l = l->getInstance();
    l->setLog("Reddit opened successfully!");
    l->writeLog();
    init(s, u);
    while (1)
    {
        try
        {
            cout << "============ MAIN MENU =============" << endl;
            cout << "1: Register" << endl;
            cout << "2: Login" << endl;
            cout << "3: Post" << endl;
            cout << "4: Join Subreddit" << endl;
            cout << "5: Open Feed" << endl;
            cout << "6: Create Subreddit" << endl;
            cout << "7: Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            if (loggedInStatus != 1 && choice > 2 && !(choice >= 7))
            {
                cout << "You must log-in first!" << endl;
                continue;
            }
            switch (choice)
            {
            case 1:
                tempUser = new User();
                tempUser->registerUser();
                u.push_back(tempUser);
                break;
            case 2:
                loggedInStatus = logIn(u);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                s[0]->printSubreddit(s);
                break;
            case 6:
                break;
            default:
                l = l->getInstance();
                l->setLog("Reddit terminated successfully!\n\n");
                l->writeLog();
                exit(0);
                break;
            }
        }
        catch (RegistrationError r)
        {
            r.printError();
            continue;
        }
        catch (...)
        {
            cout << "Error!" << endl;
            continue;
        }
    }
    return 0;
}
