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

void User::registerUser(string emailInput, string nameInput, string userIdInput, int ageInput, string passwordInput)
{
    email = emailInput;
    name = nameInput;
    userId = userIdInput;
    age = ageInput;
    password = passwordInput;

    //! Check if Email id contains @ and . - validation
    if (!(email.find('@') != std::string::npos && email.find('.') != std::string::npos))
        throw RegistrationError("Invalid email");
    //! If space is found in userId - validation
    if (userId.find(' ') != std::string::npos)
        throw SpaceError("User name cannot contain spaces!");
    if (userId.size() > 15)
        throw LengthError("User name cannot exceed 15 characters");
    //! Minimum age check - validation
    if (age < 13)
        throw MinAgeError("You must be atleast 13 to be able to register yourself!");
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
    cout << endl;
    cout << "Message : ";
    cout << msg << endl;
}

void Message::printMsg()
{
    cout << endl;
    cout << "User id : u/" << fromId << endl;
    Notification::printMsg();
}

void Inbox::printInbox()
{
    cout << "No. Of Notification : " << noOfNotification << endl;
    for (int i = 0; i < notifs.size(); i++)
    {
        notifs[i]->printMsg();
        cout << endl;
    }
}

void Inbox::clearInbox()
{
    notifs.clear();
    noOfNotification = 0;
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
    cout << "Post Content: " << endl;
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
    cout << "To User : u/" << toUserName << endl;
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

void User::upvote(Comment *&p)
{
    p->score++;
}

void User::downvote(Post *&p)
{
    p->score--;
}

void User::downvote(Comment *&p)
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

void User::createPost(Subreddit *&s, int choiceInp, string titleInp, string textInp, int sizeInp = 0, string formatInp = ".png")
{
    int choice;
    Post *newPost;
    PostType t;
    choice = choiceInp;
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
    newPost = newPost->createPost(t, titleInp, textInp, sizeInp, formatInp);
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
Post *Post::createPost(PostType pType, string titleInp, string textInp, int sizeInp, string formatInp)
{
    Post *pNew;
    Text *textPost;
    Image *imagePost;
    Video *videoPost;
    if (pType == PT_TextPost)
    {
        textPost = new Text();
        textPost->postTitle = titleInp;
        textPost->postContent = textInp;
        textPost->dateTime = getDateTime();
        return textPost;
    }
    else if (pType == PT_ImagePost)
    {
        imagePost = new Image();
        imagePost->postTitle = titleInp;
        imagePost->imageSize = sizeInp;
        imagePost->format = formatInp;
        imagePost->dateTime = getDateTime();
        return imagePost;
    }
    else if (pType == PT_VideoPost)
    {
        videoPost = new Video();
        videoPost->postTitle = titleInp;
        videoPost->videoSize = sizeInp;
        if (videoPost->videoSize > 20)
        {
            throw VideoSizeError("Video size cannot exceed 20Mb");
        }
        videoPost->format = formatInp;
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
    User *u_temp = new User("siddaraj@gmail.com", "Siddaraj H", "siddaraj", 20, "123");
    u.push_back(u_temp);
    u_temp = new User("anirudh@gmail.com", "Anirudh K", "anirudh", 19, "123");
    u.push_back(u_temp);
    u_temp = new User("kishor@gmail.com", "Kishor Kumar", "kishor", 20, "123");
    u.push_back(u_temp);
    u_temp = new User("vinayak@gmail.com", "Vinayak M", "vinayak", 21, "123");
    u.push_back(u_temp);
    u_temp = new User("prajwal@gmail.com", "Prajwal Patil", "prajwal", 19, "123");
    u.push_back(u_temp);
    u[0]->createPost(s[1], 1, "Bugs Are Evolving to Eat Plastic, Study Finds", "This is really interesting");
    u[1]->createPost(s[1], 1, "Meta-analysis of 15 studies on depression suggests significant mental health benefits from being physically active", "https://www.psypost.org/2022/05/");
    u[2]->createPost(s[2], 1, "Bill Gates said, I will always choose a lazy person to do a difficult job because a lazy person will find an easy way to do it. What's a real-life example of this?", "Any comments?");
    u[3]->createPost(s[3], 1, "James Web Space Telescope runs on C++ code.", "Watch on Youtube");
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
        cout << "*********************************" << endl;
        cout << "r/" << i->name << endl;
        cout << "*********************************" << endl;
        for (auto j : i->posts)
        {
            j->printPost();
            for (auto k : j->comments)
            {
                k->printComment();
                cout << "**** REPLIES *****" << endl;
                for (auto l : k->replies)
                {
                    l->printComment();
                    cout << endl;
                }
                cout << endl;
            }
            cout << endl;
        }
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
    cout << "=================== CREATE POST =====================" << endl;
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
    cout << "=================== JOIN SUBREDDIT =====================" << endl;
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
    cout << "Joined subreddit successfully!" << endl;
}

void messageUserGlobal(vector<User *> &u)
{
    int status = 0;
    string tempUser;
    int i;
    cout << "=================== MESSAGE USER =====================" << endl;
    cout << "Enter the user name of Recipient: ";
    cin >> tempUser;
    getchar();
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
    getchar();
    cout << "Enter a message: ";
    getline(cin, m->msg);
    if (!u[i]->userInbox)
    {
        u[i]->userInbox = new Inbox();
    }
    u[i]->userInbox->notifs.push_back(m);
    u[i]->userInbox->noOfNotification++;
    cout << "Message sent successfully!" << endl;
    getchar();
}

void commentGlobal(vector<Subreddit *> &s)
{
    int status = 0;
    int i;
    int choice;
    string subName;
    cout << "=================== COMMENT A POST =====================" << endl;
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
        getchar();
        if (choice == 2 && j >= s[i]->posts.size() - 1)
        {
            cout << "No more comments to show!" << endl;
            cout << " ******************************************** " << endl;
            return;
        }
        if (choice == 1)
        {
            signedInUser->commentIt(s[i]->posts[j]);
            cout << "Comment was added successfully!" << endl;
            cout << " ******************************************** " << endl;
            return;
        }
        cout << " ******************************************** " << endl;
    }
    cout << "No comment was added!" << endl;
}

void replyGlobal(vector<Subreddit *> &s)
{
    int status = 0;
    int i;
    int j = 0;
    int k = 0;
    int choice;
    string subName;
    cout << "=================== REPLY A COMMENT =====================" << endl;
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
    for (j = 0; j < s[i]->posts.size(); j++)
    {
        cout << " ******************************************** " << endl;
        s[i]->posts[j]->printPost();
        cout << " ____________________________________________ " << endl;
        cout << "1: Reply to a comment of this" << endl;
        cout << "2: Next post" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        getchar();
        if (choice == 2 && j >= s[i]->posts.size() - 1)
        {
            cout << "No more posts to show!" << endl;
            cout << " ******************************************** " << endl;
            return;
        }
        if (choice == 1)
        {
            cout << "=================== COMMENTS =====================" << endl;
            for (k = 0; k < s[i]->posts[j]->comments.size(); k++)
            {
                cout << " ******************************************** " << endl;
                s[i]->posts[j]->comments[k]->printComment();
                cout << " ____________________________________________ " << endl;
                cout << "1: Reply this" << endl;
                cout << "2: Next comment" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                getchar();
                if (choice == 2 && k >= s[i]->posts[j]->comments.size() - 1)
                {
                    cout << "No more comments to show!" << endl;
                    cout << " ******************************************** " << endl;
                    return;
                }
                if (choice == 1)
                {
                    signedInUser->replyIt(s[i]->posts[j]->comments[k]);
                    cout << "Reply was successfully added!" << endl;
                    cout << "******************************************** " << endl;
                    return;
                }
            }
        }
    }
    cout << "No reply was added!" << endl;
}

void inboxGlobal()
{
    int choice;
    cout << "======= INBOX =======" << endl;
    if (!signedInUser->userInbox)
    {
        return;
    }
    signedInUser->userInbox->printInbox();
    cout << endl;
    cout << "1: Clear Inbox" << endl;
    cout << "2: Exit" << endl;
    cout << "Enter the choice: ";
    cin >> choice;
    if (choice == 1)
    {
        signedInUser->userInbox->clearInbox();
        cout << "Inbox cleared successfully!" << endl;
    }
    return;
}

void voteGlobal(vector<Subreddit *> &s)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int status = 0;
    int choice;
    if (s.size() == 0)
    {
        cout << "No subreddits!" << endl;
        return;
    }
    string subName;
    cout << "=================== VOTE A POST/COMMENT/REPLY =====================" << endl;
    cout << "Enter the subreddit on which you want to vote: ";
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
        cout << "Requested Subreddit not found!" << endl;
        throw InvalidInput("Invalid Subreddit name!");
        return;
    }
    for (j = 0; j < s[i]->posts.size(); j++)
    {
        cout << " ******************************************** " << endl;
        s[i]->posts[j]->printPost();
        cout << " ____________________________________________ " << endl;
        cout << "1: Upvote this post" << endl;
        cout << "2: Downvote this post" << endl;
        cout << "3: Upvote/Downvote Comments/Replies of this post" << endl;
        cout << "4: Next post" << endl;
        cout << "5: Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 4 && j >= s[i]->posts.size() - 1)
        {
            cout << "No more posts to show!" << endl;
            return;
        }
        if (choice == 1)
        {
            signedInUser->upvote(s[i]->posts[j]);
            cout << "You have successfully upvoted the post" << endl;
        }
        else if (choice == 2)
        {
            signedInUser->downvote(s[i]->posts[j]);
            cout << "You have successfully downvoted the post" << endl;
        }
        else if (choice == 3)
        {
            for (k = 0; k < s[i]->posts[j]->comments.size(); k++)
            {
                cout << " ******************************************** " << endl;
                s[i]->posts[j]->comments[k]->printComment();
                cout << " ____________________________________________ " << endl;
                cout << "1: Upvote this comment" << endl;
                cout << "2: Downvote this comment" << endl;
                cout << "3: Upvote/Downvote Replies of this comment" << endl;
                cout << "4: Next comment" << endl;
                cout << "5: Exit" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                if (choice == 4 && k >= s[i]->posts[j]->comments.size() - 1)
                {
                    cout << "No more comments to show!" << endl;
                    return;
                }
                if (choice == 1)
                {
                    signedInUser->upvote(s[i]->posts[j]->comments[k]);
                    cout << "You have successfully upvoted this comment" << endl;
                    return;
                }
                else if (choice == 2)
                {
                    signedInUser->downvote(s[i]->posts[j]->comments[k]);
                    cout << "You have successfully downvoted this comment" << endl;
                    return;
                }
                else if (choice == 3)
                {
                    for (l = 0; l < s[i]->posts[j]->comments[k]->replies.size(); l++)
                    {
                        cout << " ******************************************** " << endl;
                        s[i]->posts[j]->comments[k]->replies[l]->printComment();
                        cout << " ____________________________________________ " << endl;
                        cout << "1: Upvote this reply" << endl;
                        cout << "2: Downvote this reply" << endl;
                        cout << "3: Next comment" << endl;
                        cout << "4: Exit" << endl;
                        cout << "Enter your choice: ";
                        cin >> choice;
                        if (choice == 3 && l >= s[i]->posts[j]->comments[k]->replies.size() - 1)
                        {
                            cout << "No more replies!" << endl;
                            return;
                        }
                        if (choice == 1)
                        {
                            signedInUser->upvote(s[i]->posts[j]->comments[k]->replies[l]);
                            cout << "You have successfully upvoted this reply" << endl;
                            return;
                        }
                        else if (choice == 2)
                        {
                            signedInUser->downvote(s[i]->posts[j]->comments[k]->replies[l]);
                            cout << "You have successfully downvoted this reply" << endl;
                            return;
                        }
                    }
                    return;
                }
            }
            return;
        }
        else if (choice == 5)
        {
            return;
        }
    }
}

void testcase1()
{
    cout << endl;
    cout << "========== RUNNING TESTCASE 1 ===========" << endl;
    cout << "Name: Raghav Kumar" << endl;
    cout << "Email: raghavkumargmail" << endl;
    cout << "UserId: RaghavKumar" << endl;
    cout << "Age: 20" << endl;
    User *u = new User();
    u->registerUser("raghavkumargmail", "Raghav Kumar", "RaghavKumar", 20, "123");
    cout << "Test Case 1 Passed!" << endl;
}

void testcase2()
{
    cout << endl;
    cout << "========== RUNNING TESTCASE 2 ===========" << endl;
    cout << "Name: Raghav Kumar" << endl;
    cout << "Email: raghavkumar@gmail" << endl;
    cout << "UserId: RaghavKumar" << endl;
    cout << "Age: 20" << endl;
    User *u = new User();
    u->registerUser("raghavkumar@gmail", "Raghav Kumar", "RaghavKumar", 20, "123");
    cout << "Test Case 2 Passed!" << endl;
}

void testcase3()
{
    cout << endl;
    cout << "========== RUNNING TESTCASE 3 ===========" << endl;
    cout << "Name: Raghav Kumar" << endl;
    cout << "Email: raghavkumargmail.com" << endl;
    cout << "UserId: RaghavKumar" << endl;
    cout << "Age: 20" << endl;
    User *u = new User();

    u->registerUser("raghavkumargmail.com", "Raghav Kumar", "RaghavKumar", 20, "123");
    cout << "Test Case 3 Passed!" << endl;
}

void testcase4()
{
    cout << endl;
    cout << "========== RUNNING TESTCASE 4 ===========" << endl;
    cout << "Name: Raghav Kumar" << endl;
    cout << "Email: raghavkumar@gmail.com" << endl;
    cout << "UserId: RaghavKumar" << endl;
    cout << "Age: 20" << endl;
    User *u = new User();

    u->registerUser("raghavkumar@gmail.com", "Raghav Kumar", "RaghavKumar", 20, "123");
    cout << "Test Case 4 Passed!" << endl;
}

void testcase5()
{
    cout << endl;
    cout << "========== RUNNING TESTCASE 5 ===========" << endl;
    cout << "Name: Raghav Kumar" << endl;
    cout << "Email: raghavkumar@gmail.com" << endl;
    cout << "UserId: Raghav Kumar" << endl;
    cout << "Age: 20" << endl;
    User *u = new User();

    u->registerUser("raghavkumar@gmail.com", "Raghav Kumar", "Raghav Kumar", 20, "123");
    cout << "Test Case 5 Passed!" << endl;
}

void testcase6()
{
    cout << endl;
    cout << "========== RUNNING TESTCASE 6 ===========" << endl;
    cout << "Name: Raghav Kumar" << endl;
    cout << "Email: raghavkumar@gmail.com" << endl;
    cout << "UserId: RaghavKumar" << endl;
    cout << "Age: 20" << endl;
    User *u = new User();

    u->registerUser("raghavkumar@gmail.com", "Raghav Kumar", "RaghavKumar", 20, "123");
    cout << "Test Case 6 Passed!" << endl;
}

void testcase7()
{
    cout << endl;
    cout << "========== RUNNING TESTCASE 7 ===========" << endl;
    cout << "Name: Raghav Kumar" << endl;
    cout << "Email: raghavkumar@gmail.com" << endl;
    cout << "UserId: RaghavKumar1234567890" << endl;
    cout << "Age: 20" << endl;
    User *u = new User();

    u->registerUser("raghavkumar@gmail.com", "Raghav Kumar", "RaghavKumar1234567890", 20, "123");
    cout << "Test Case 7 Passed!" << endl;
}

void testcase8()
{
    cout << endl;
    cout << "========== RUNNING TESTCASE 8 ===========" << endl;
    cout << "Name: Raghav Kumar" << endl;
    cout << "Email: raghavkumar@gmail.com" << endl;
    cout << "UserId: RaghavKumar" << endl;
    cout << "Age: 12" << endl;
    User *u = new User();

    u->registerUser("raghavkumar@gmail.com", "Raghav Kumar", "RaghavKumar", 12, "123");
    cout << "Test Case 8 Passed!" << endl;
}

void runTestCase(void (*func)())
{
    try
    {
        func();
    }
    catch (RegistrationError r)
    {
        r.printError();
        return;
    }
    catch (InvalidInput r)
    {
        r.printError();
        return;
    }
    catch (...)
    {
        cout << "Error! " << endl;
        return;
    }
}

void runAllTestCases()
{
    try
    {
        testcase1();
    }
    catch (RegistrationError r)
    {
        r.printError();
    }
    catch (InvalidInput r)
    {
        r.printError();
    }
    catch (...)
    {
        cout << "Error! " << endl;
    }
    try
    {
        testcase2();
    }
    catch (RegistrationError r)
    {
        r.printError();
    }
    catch (InvalidInput r)
    {
        r.printError();
    }
    catch (...)
    {
        cout << "Error! " << endl;
    }

    try
    {
        testcase3();
    }
    catch (RegistrationError r)
    {
        r.printError();
    }
    catch (InvalidInput r)
    {
        r.printError();
    }
    catch (...)
    {
        cout << "Error! " << endl;
    }

    try
    {
        testcase4();
    }
    catch (RegistrationError r)
    {
        r.printError();
    }
    catch (InvalidInput r)
    {
        r.printError();
    }
    catch (...)
    {
        cout << "Error! " << endl;
    }

    try
    {
        testcase5();
    }
    catch (RegistrationError r)
    {
        r.printError();
    }
    catch (InvalidInput r)
    {
        r.printError();
    }
    catch (...)
    {
        cout << "Error! " << endl;
    }

    try
    {
        testcase6();
    }
    catch (RegistrationError r)
    {
        r.printError();
    }
    catch (InvalidInput r)
    {
        r.printError();
    }
    catch (...)
    {
        cout << "Error! " << endl;
    }

    try
    {
        testcase7();
    }
    catch (RegistrationError r)
    {
        r.printError();
    }
    catch (InvalidInput r)
    {
        r.printError();
    }
    catch (...)
    {
        cout << "Error! " << endl;
    }

    try
    {
        testcase8();
    }
    catch (RegistrationError r)
    {
        r.printError();
    }
    catch (InvalidInput r)
    {
        r.printError();
    }
    catch (...)
    {
        cout << "Error! " << endl;
    }
}