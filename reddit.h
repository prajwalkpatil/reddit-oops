#ifndef _REDDIT_INCLUDED_
#define _REDDIT_INCLUDED_

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;

enum PostType
{
    PT_TextPost,
    PT_ImagePost,
    PT_VideoPost
};

//*>>>>>>>>>> Exception classes >>>>>>>>>>>>
class RegistrationError;
class MinAgeError;
class UserNameError;
class LengthError;
class SpaceError;
class VideoSizeError;
class InvalidInput;

//*>>>>>>>>>> Regular classes >>>>>>>>>>>>>>
class User;
class Moderator;
class Subreddit;
class Notification;
class Message;
class Inbox;
class Post;
class Text;
class Image;
class Video;
class Award;
class Comment;
class Reply;
class Logger;

string getDateTime();
void display_logo();
void red();
void reset();
int logIn(vector<User *> u);
void init(vector<Subreddit *> &s, vector<User *> &u);
void createPostGlobal(vector<Subreddit *> &s);
void createSubredditGlobal(vector<Subreddit *> &s);
void joinSubredditGlobal(vector<Subreddit *> &s);
void messageUserGlobal(vector<User *> &u);
void commentGlobal(vector<Subreddit *> &s);
void replyGlobal(vector<Subreddit *> &s);
void inboxGlobal();
void voteGlobal(vector<Subreddit *> &s);
//* >>>>>>>>> Class declarations >>>>>>>>>>>>>
class InvalidInput
{
public:
    string msg;
    InvalidInput() : msg("") {}
    InvalidInput(string a) : msg(a) {}
    void printError()
    {
        cout << msg << endl;
    }
};

class RegistrationError
{
public:
    string msg;
    RegistrationError() : msg("") {}
    RegistrationError(string a) : msg(a) {}
    void printError()
    {
        cout << msg << endl;
    }
};

class MinAgeError : public RegistrationError
{
public:
    MinAgeError(string msg) : RegistrationError(msg) {}
};

class UserNameError : public RegistrationError
{
public:
    UserNameError(string msg) : RegistrationError(msg) {}
};

class LengthError : public UserNameError
{
public:
    LengthError(string msg) : UserNameError(msg) {}
};

class SpaceError : public UserNameError
{
public:
    SpaceError(string msg) : UserNameError(msg) {}
};

class VideoSizeError
{
public:
    string message;
    VideoSizeError(string m) : message(m) {}
    void printError()
    {
        cout << message << endl;
    }
};

//******************* EXCEPTION CLASSES - END *****************************

//*******************  CLASSES - START ************************************

class User
{
protected:
    string email;
    string password;

public:
    string name;
    string userId;
    int age;
    vector<Award *> awards;
    vector<Post *> posts;
    Inbox *userInbox;

    ///// TODO: Functions ------------------------------------------------------
    User() : email(""), name(""), userId(""), age(0), password(""){};
    User(string emailInput, string nameInput, string userIdInput, int ageInput, string passwordInput) : email(emailInput), name(nameInput), userId(userIdInput), age(ageInput), password(passwordInput){};

    void registerUser();
    /////// TODO: Functions that use other classes
    void createPost(Subreddit *&s);
    void join(Subreddit *&s);
    void replyIt(Comment *&c);
    void commentIt(Post *&p);
    void upvote(Post *&p);
    void upvote(Comment *&p);
    void downvote(Post *&p);
    void downvote(Comment *&p);
    void printDetails();
    bool validatePassword(string pass);
};

class Moderator : public User
{
public:
    string modId;
    Moderator() : User(), modId(0){};
    Moderator(string emailInput, string nameInput, string userIdInput, int ageInput, string modIdInput, string passwordInput) : User(emailInput, nameInput, userIdInput, ageInput, passwordInput), modId(modIdInput){};
    void printDetails();
    Moderator *createMod(User *u)
    {
        Moderator *temp = new Moderator();
        temp->age = u->age;
        temp->name = u->name;
        temp->userId = u->userId;
    }
};

class Subreddit
{
public:
    string name;
    vector<Post *> posts;
    vector<Moderator *> mods;
    vector<string> users;

    ///////////TODO: Functions ----------------
    Subreddit() : name(""){};
    Subreddit(string nameInput) : name(nameInput){};

    void printPosts();
    void printUsers();
    void printMods();
    void printSubreddit();
    void printSubreddit(vector<Subreddit *> s);
};

class Notification
{
public:
    string msg;

    Notification() : msg("") {}
    Notification(string m) : msg(m) {}

    void printMsg();
};

class Message : public Notification
{
public:
    string fromId;

    Message() : Notification(), fromId("") {}
    Message(string m, string id) : Notification(m), fromId(id) {}

    void printMsg();
};

class Inbox
{
public:
    int noOfNotification;
    vector<Notification *> notifs;

    Inbox() : noOfNotification(0) {}
    Inbox(int n) : noOfNotification(n) {}

    void printInbox();
    void clearInbox();
};

class Post
{
public:
    string postTitle;
    string dateTime;
    string userName;
    int score;
    vector<Comment *> comments;

    Post() : postTitle(""), dateTime(""), userName(""), score(0) {}
    Post(string pt, string dt, string user) : postTitle(pt), dateTime(dt), userName(user), score(0) {}

    // TODO Uses Function Handling
    static Post *createPost(PostType pType);
    virtual void printPost();
};

class Text : public Post
{
public:
    string postContent;
    Text() : Post(), postContent("") {}
    Text(string postTitleInput, string dateTimeInput, string userNameInput, string pInput) : Post(postTitleInput, dateTimeInput, userNameInput), postContent(pInput) {}
    void printPost();
};

class Image : public Post
{
public:
    double imageSize;
    string format;
    Image() : Post(), imageSize(0), format("") {}
    Image(string postTitle, string dateTime, string userName, double i, string f) : Post(postTitle, dateTime, userName), imageSize(i), format(f) {}

    void printPost();
};

class Video : public Post
{
public:
    double videoSize;
    string format;
    Video() : Post(), videoSize(0), format("") {}
    Video(string postTitleInput, string dateTimeInput, string userNameInput, string pInput, double i, string f) : Post(postTitleInput, dateTimeInput, userNameInput), videoSize(i), format(f) {}
    void printPost();
};

class Award
{
public:
    string awardName;
    void printAward();
};

class Comment
{
public:
    string content;
    int score;
    string userName;
    string dateTime;
    vector<Comment *> replies;
    Comment() : content(""), score(0), userName(""), dateTime("") {}
    Comment(string con, string user, string dt) : content(con), score(0), userName(user), dateTime(dt) {}

    ////TODO Uses Function Handling
    void printComment();
};

class Reply : public Comment
{
public:
    string toUserName;
    Reply() : Comment(), toUserName("") {}
    Reply(string con, string user, string dt, string toUser) : Comment(con, user, dt), toUserName(toUser) {}
    void printComment();
};

class Logger
{
private:
    static Logger *instance;
    string logMessage;
    Logger() : logMessage("") {}

public:
    static Logger *getInstance();
    string getLog();
    void setLog(string msg);
    void writeLog();
};

//*******************  CLASSES - END *****************************

#endif