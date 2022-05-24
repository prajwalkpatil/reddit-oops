#include "reddit.h"

int main()
{
    /*
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
    getchar();
    Comment *c = new Comment("Hello everyone", "freakinginsane", "2003 8:47");
    Subreddit *s = new Subreddit("askreddit");
    u.createPost(s);
    s->printPosts();
    // u.replyIt(c);
    cout << "**********************************" << endl;

    c->replies[0]->printComment();
    // u.printDetails();

    Logger *l = l->getInstance();
    l->setLog("Successfully opened!");
    l->writeLog();
    */
    int choice;
    vector<Subreddit *> s;
    vector<User *> u;
    display_logo();
    cout << endl;
    Logger *l = l->getInstance();
    l->setLog("Reddit opened successfully!");
    l->writeLog();
    cout << "============ MAIN MENU =============" << endl;
    init(s, u);
    cout << "1: Register" << endl;
    cout << "2: Login" << endl;
    cout << "3: Post" << endl;
    cout << "4: Join Subreddit" << endl;
    cout << "5: Create Subreddit" << endl;
    cout << "6: Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        break;
    case 2:
        logIn(u);
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    default:
        l = l->getInstance();
        l->setLog("Reddit terminated successfully!");
        l->writeLog();
        exit(0);
        break;
    }
    s[0]->printSubreddit(s);
    return 0;
}
