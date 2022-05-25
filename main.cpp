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
    // runAllTestCases();
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
            cout << "6: Message a user" << endl;
            cout << "7: Comment on a post" << endl;
            cout << "8: Reply to a comment" << endl;
            cout << "9: Upvote/Downvote" << endl;
            cout << "10: Create Subreddit" << endl;
            cout << "11: View Inbox" << endl;
            cout << "12: Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            if (loggedInStatus != 1 && choice > 2 && !(choice >= 11))
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
                createPostGlobal(s);
                break;
            case 4:
                joinSubredditGlobal(s);
                break;
            case 5:
                s[0]->printSubreddit(s);
                break;
            case 6:
                messageUserGlobal(u);
                break;
            case 7:
                commentGlobal(s);
                break;
            case 8:
                replyGlobal(s);
                break;
            case 9:
                voteGlobal(s);
                break;
            case 10:
                createSubredditGlobal(s);
                break;
            case 11:
                inboxGlobal();
                break;
            default:
                l = l->getInstance();
                l->setLog("Reddit terminated successfully!\n\n");
                l->writeLog();
                exit(EXIT_SUCCESS);
                break;
            }
        }
        catch (RegistrationError r)
        {
            r.printError();
            continue;
        }
        catch (InvalidInput r)
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
