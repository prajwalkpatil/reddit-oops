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
    getchar();
    Comment *c = new Comment("Hello everyone", "freakinginsane", "2003 8:47");
    Subreddit *s = new Subreddit("askreddit");
    u.createPost(s);
    s->printPosts();
    // u.replyIt(c);
    cout << "**********************************" << endl;

    c->replies[0]->printComment();
    // u.printDetails();
    return 0;
}
