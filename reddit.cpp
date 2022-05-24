#include "reddit.h"

User *signedInUser = nullptr;
bool isLoggedIn = false;

void User::registerUser()
{
    cout << "********* REGISTER *********" << endl;
    cout << "Name: ";
    getline(cin, name);

    cout << "Email: ";
    cin >> email;
    //! Check if Email id contains @ and . - validation
    if (!(email.find('@') != std::string::npos && email.find('.') != std::string::npos))
        throw RegistrationError("Invalid email");

    cout << "UserId: ";
    cin >> userId;
    //! If space is found in userId - validation
    if (userId.find(' ') != std::string::npos)
        throw SpaceError("User name cannot contain spaces!");
    if (userId.size() > 15)
        throw LengthError("User name cannot exceed 15 characters");

    cout << "Age: ";
    cin >> age;
    //! Minimum age check - validation
    if (age < 13)
        throw MinAgeError("You must be atleast 13 to be able to register yourself!");
    cout << "Enter your password: ";
    cin >> password;
    cout << "****************************" << endl;
    Logger *l = l->getInstance();
    l->setLog("User registered in successfully!");
    l->writeLog();
}

void User::printDetails()
{
    cout << "********* DETAILS *********" << endl;
    cout << "Name: ";
    cout << name << endl;
    cout << "Email: ";
    cout << email << endl;
    cout << "UserId: ";
    cout << userId << endl;
    cout << "Age: ";
    cout << age << endl;
    cout << "***************************" << endl;
}

void Moderator::printDetails()
{
    User::printDetails();
    cout << "modId";
    cout << modId << endl;
}

void Subreddit::printPosts()
{
    cout << "*************** POSTS **************" << endl;
    for (auto i : posts)
    {
        i->printPost();
        cout << "************************************" << endl;
    }
}

void Subreddit::printUsers()
{
    cout << "*************** USERS **************" << endl;
    for (auto i : users)
    {
        cout << i << endl;
    }
    cout << "************************************" << endl;
}

void Subreddit::printMods()
{
    cout << "************ MODERATORS ************" << endl;
    for (auto i : mods)
    {
        i->printDetails();
    }
    cout << "************************************" << endl;
}

void Notification::printMsg()
{
    cout << msg << endl;
}

void Message::printMsg()
{
    cout << "User id : " << fromId << endl;
    cout << "Message : ";
    Notification::printMsg();
}

void Inbox::printInbox()
{
    cout << "No. Of Notification : " << noOfNotification << endl;
    ///// TODO: print all Notification from Notification Class
    for (auto i : notifs)
    {
        i->printMsg();
        cout << endl;
    }
}

void Inbox::clearInbox()
{
    notifs.clear();
}

void Post::printPost()
{
    cout << "*** POST DETAILS ***" << endl;
    cout << "Post Title : " << postTitle << endl;
    cout << "Date-Time: " << dateTime << endl;
    cout << "User : u/" << userName << endl;
    cout << "Score : " << score << endl;
}

void Text::printPost()
{
    Post::printPost();
    cout << postContent << endl;
}

void Image::printPost()
{
    Post::printPost();
    cout << "Image size : " << imageSize << "Mb" << endl;
    cout << "Image format : " << format << endl;
}

void Video::printPost()
{
    Post::printPost();
    cout << "Video size : " << videoSize << "Mb" << endl;
    cout << "Video format : " << format << endl;
}

void Award::printAward()
{
    cout << "Award : " << awardName << endl;
}

void Comment::printComment()
{
    cout << "*** COMMENT/REPLY DETAILS ***" << endl;
    cout << "Comment : " << content << endl;
    cout << "User : u/" << userName << endl;
    cout << "Score : " << score << endl;
    cout << "Date-Time : " << dateTime << endl;
}

void Reply::printComment()
{
    Comment::printComment();
    cout << "ToUser : u/" << toUserName << endl;
}

void User::join(Subreddit *&s)
{
    cout << "You will be joining r/" << s->name << endl;
    s->users.push_back(name);
    cout << "You've successfully joined r/" << s->name << endl;
}

void User::replyIt(Comment *&c)
{
    Reply *newReply = new Reply();
    cout << "You are replying to: " << endl;
    c->printComment();
    cout << endl;
    cout << "Enter your reply: " << endl;
    getline(cin, newReply->content);
    newReply->userName = userId;
    newReply->dateTime = getDateTime();
    newReply->toUserName = c->userName;
    c->replies.push_back(newReply);
}

void User::upvote(Post *&p)
{
    p->score++;
}

void User::downvote(Post *&p)
{
    p->score--;
}

void User::createPost(Subreddit *&s)
{
    int choice;
    Post *newPost;
    PostType t;
    cout << "You are posting on r/" << s->name << endl;
    cout << "What is the type of your post? " << endl;
    cout << "1: Text" << endl;
    cout << "2: Image" << endl;
    cout << "3: Video" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    getchar();
    switch (choice)
    {
    case 1:
        t = PT_TextPost;
        break;
    case 2:
        t = PT_ImagePost;
        break;
    case 3:
        t = PT_VideoPost;
        break;
    default:
        throw InvalidInput("Enter a valid choice.");
        break;
    }
    newPost = newPost->createPost(t);
    newPost->userName = userId;
    s->posts.push_back(newPost);
    posts.push_back(newPost);
    Logger *l = l->getInstance();
    l->setLog("Post created successfully!");
    l->writeLog();
}

void User::commentIt(Post *&p)
{
    Comment *newComment = new Comment();
    cout << "You are commenting to: " << endl;
    p->printPost();
    cout << "Enter your comment: " << endl;
    getline(cin, newComment->content);
    newComment->dateTime = getDateTime();
    newComment->userName = userId;
    p->comments.push_back(newComment);
}

string getDateTime()
{
    string temp;
    time_t _tm = time(NULL);
    struct tm *curtime = localtime(&_tm);
    temp = asctime(curtime);
    if (!temp.empty() && temp[temp.length() - 1] == '\n')
    {
        temp.erase(temp.length() - 1);
    }
    return temp;
}

Post *Post::createPost(PostType pType)
{
    Post *pNew;
    Text *textPost;
    Image *imagePost;
    Video *videoPost;
    if (pType == PT_TextPost)
    {
        textPost = new Text();
        cout << "Enter the post title: " << endl;
        getline(cin, textPost->postTitle);
        cout << "Enter the text content: " << endl;
        getline(cin, textPost->postContent);
        textPost->dateTime = getDateTime();
        return textPost;
    }
    else if (pType == PT_ImagePost)
    {
        imagePost = new Image();
        cout << "Enter the post title: " << endl;
        getline(cin, imagePost->postTitle);
        cout << "Enter the size of the image in Megabytes: ";
        cin >> imagePost->imageSize;
        cout << "Enter the format of the image: ";
        cin >> imagePost->format;
        imagePost->dateTime = getDateTime();
        return imagePost;
    }
    else if (pType == PT_VideoPost)
    {
        videoPost = new Video();
        cout << "Enter the post title: " << endl;
        getline(cin, videoPost->postTitle);
        cout << "Enter the size of the video in Megabytes: ";
        cin >> videoPost->videoSize;
        if (videoPost->videoSize > 20)
        {
            throw VideoSizeError("Video size cannot exceed 20Mb");
        }
        cout << "Enter the format of the video: ";
        cin >> videoPost->format;
        videoPost->dateTime = getDateTime();
        return videoPost;
    }
}

Logger *Logger::getInstance()
{
    if (!instance)
    {
        instance = new Logger();
    }
    return instance;
}

string Logger::getLog()
{
    return this->logMessage;
}

void Logger::setLog(string msg)
{
    this->logMessage = msg;
}

void Logger::writeLog()
{
    ofstream logFile;
    logFile.open("log.txt", std::ios_base::app);
    logFile << getDateTime();
    logFile << " | " << logMessage << endl;
    logFile.close();
}
Logger *Logger::instance = 0;

void display_logo()
{
    red();
    printf("    ____           __    ___ __\n"
           "   / __ \\___  ____/ /___/ (_) /_\n"
           "  / /_/ / _ \\/ __  / __  / / __/\n"
           " / _, _/  __/ /_/ / /_/ / / /_\n"
           "/_/ |_|\\___/\\__,_/\\__,_/_/\\__/\n");
    printf("\nThe front page of the internet.\n");
    reset();
}

void red()
{
    printf("\033[31m");
}

void reset()
{
    printf("\033[0m");
}

void init(vector<Subreddit *> &s, vector<User *> &u)
{
    // TODO: Insert Subreddits
    Subreddit *s_temp = new Subreddit("askreddit");
    s.push_back(s_temp);
    s_temp = new Subreddit("science");
    s.push_back(s_temp);
    s_temp = new Subreddit("technology");
    s.push_back(s_temp);
    s_temp = new Subreddit("cpp");
    s.push_back(s_temp);

    Logger *t = t->getInstance();
    t->setLog("Subreddits initialized!");
    t->writeLog();

    // TODO: Insert Users
    User *u_temp = new User("brockvillecircular@gmail.com", "Richard D", "brockvillecircular", 23, "123");
    u.push_back(u_temp);
    u_temp = new User("wombatphilips@gmail.com", "John M", "wombatphilips", 19, "123");
    u.push_back(u_temp);
    u_temp = new User("costlyhuge@gmail.com", "Rick Astley", "costlyhuge", 28, "123");
    u.push_back(u_temp);
    u_temp = new User("scholarstalk@gmail.com", "Henry Smith", "scholarstalk", 32, "123");
    u.push_back(u_temp);
    u_temp = new User("freakinginsane@gmail.com", "Prajwal Patil", "freakinginsane", 19, "123");
    u.push_back(u_temp);
    signedInUser = u_temp;
    t = t->getInstance();
    t->setLog("Users initialized!");
    t->writeLog();
}

void Subreddit::printSubreddit()
{
    cout << "*********************************" << endl;
    cout << "r/" << name << endl;
    cout << "*********************************" << endl;
    cout << endl;
    if (users.size() != 0)
        cout << "===== USERS =====" << endl;
    red();
    for (auto i : users)
    {
        cout << "u/" << i << endl;
    }
    reset();

    if (mods.size() != 0)
    {
        cout << endl;
        cout << endl;
        cout << "===== MODERATORS =====" << endl;
    }
    red();
    for (auto i : mods)
    {
        cout << "u/" << i->userId << " : " << i->modId << endl;
    }
    reset();
    if (posts.size() != 0)
    {
        cout << endl;
        cout << endl;
        cout << "===== POSTS =====" << endl;
    }
    for (auto i : posts)
    {
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        red();
        i->printPost();
        reset();
        cout << endl;
    }
    if (posts.size() != 0)
    {
        cout << endl;
        cout << endl;
    }
}

void Subreddit::printSubreddit(vector<Subreddit *> s)
{
    cout << endl;
    cout << "============ SUBREDDITS ============" << endl;
    cout << endl;
    for (auto i : s)
    {
        cout << endl;
        i->printSubreddit();
        cout << endl;
    }
}

int logIn(vector<User *> u)
{
    string temp_username;
    string temp_password;
    cout << "********* LOGIN *********" << endl;
    cout << "Username: ";
    cin >> temp_username;
    cout << "Password: ";
    cin >> temp_password;
    for (auto i : u)
    {
        if (i->userId == temp_username)
        {
            if (i->validatePassword(temp_password))
            {
                isLoggedIn = true;
                signedInUser = i;
                cout << "User logged in successfully!" << endl;
                Logger *l = l->getInstance();
                l->setLog("User logged in successfully!");
                l->writeLog();
                return 1;
            }
        }
    }
    Logger *l = l->getInstance();
    l->setLog("Log in failed!");
    l->writeLog();
    throw InvalidInput("Invalid Username!");
    return 0;
}
bool User::validatePassword(string pass)
{
    if (password == pass)
    {
        return true;
    }
    return false;
}

void createPostGlobal(vector<Subreddit *> &s)
{
    int status = 0;
    int i;
    string subName;
    cout << "=================== CREATE POST =====================";
    cout << "Enter the subreddit on which you want to post: ";
    cin >> subName;
    for (i = 0; i < s.size(); i++)
    {
        if (s[i]->name == subName)
        {
            status = 1;
            break;
        }
    }
    if (status == 0)
    {
        cout << "Requested Subreddit not found!";
        throw InvalidInput("Invalid Subreddit name!");
        return;
    }
    signedInUser->createPost(s[i]);
}

void createSubredditGlobal(vector<Subreddit *> &s)
{
    string subredditName;
    Subreddit *subredditTemp;
    cout << "Enter the name of subreddit: ";
    cin >> subredditName;
    subredditTemp = new Subreddit(subredditName);
    Moderator *tempMod = tempMod->createMod(signedInUser);
    subredditTemp->mods.push_back(tempMod);
    s.push_back(subredditTemp);
    Logger *l = l->getInstance();
    l->setLog("Subreddit created successfully!");
    l->writeLog();
}

void joinSubredditGlobal(vector<Subreddit *> &s)
{
    int status = 0;
    int i;
    string subName;
    s[0]->printSubreddit(s);
    cout << "=================== JOIN SUBREDDIT =====================";
    cout << "Enter the subreddit on which you want to join: ";
    cin >> subName;
    for (i = 0; i < s.size(); i++)
    {
        if (s[i]->name == subName)
        {
            status = 1;
            break;
        }
    }
    if (status == 0)
    {
        cout << "Requested Subreddit not found!";
        throw InvalidInput("Invalid Subreddit name!");
        return;
    }
    s[i]->users.push_back(signedInUser->userId);
}

void messageUserGlobal(vector<User *> &u)
{
    int status = 0;
    string tempUser;
    int i;
    cout << "Enter the user name of Recipient: ";
    cin >> tempUser;
    for (i = 0; i < u.size(); i++)
    {
        if (u[i]->userId == tempUser)
        {
            status = 1;
            break;
        }
    }
    if (status != 1)
    {
        cout << "User not found!" << endl;
        return;
    }
    Message *m = new Message();
    m->fromId = signedInUser->userId;
    cout << "Enter a message: ";
    cin >> m->msg;
    u[i]->userInbox->notifs.push_back(m);
    cout << "Message sent successfully!" << endl;
}

void commentGlobal(vector<Subreddit *> &s)
{
    int status = 0;
    int i;
    int choice;
    string subName;
    cout << "Enter the subreddit on which you want to comment: ";
    cin >> subName;
    for (i = 0; i < s.size(); i++)
    {
        if (s[i]->name == subName)
        {
            status = 1;
            break;
        }
    }
    if (status == 0)
    {
        cout << "Requested Subreddit not found!";
        throw InvalidInput("Invalid Subreddit name!");
        return;
    }
    if (s[i]->posts.size() == 0)
    {
        cout << "There are no posts in this subreddit!" << endl;
        return;
    }
    int j = 0;
    for (j = 0; j < s[i]->posts.size(); j++)
    {
        cout << " ******************************************** " << endl;
        s[i]->posts[j]->printPost();
        cout << " ____________________________________________ " << endl;
        cout << "1: Comment on this" << endl;
        cout << "2: Next post" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 2 && j >= s[i]->posts.size() - 1)
        {
            cout << "No more posts to show!" << endl;
            cout << " ******************************************** " << endl;
            return;
        }
        if (choice == 1)
        {
            signedInUser->commentIt(s[i]->posts[j]);
            cout << "Comment added successfully!" << endl;
            cout << " ******************************************** " << endl;
            return;
        }
        cout << " ******************************************** " << endl;
    }
}

void replyGlobal(vector<Subreddit *> &s)
{
}