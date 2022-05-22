#ifndef _REDDIT_INCLUDED_
#define _REDDIT_INCLUDED_

#include <iostream>
#include <string>
#include <exception>
#include <vector>
using namespace std;

//*>>>>>>>>>> Exception classes >>>>>>>>>>>>
class RegistrationError;
class MinAgeError;
class UserNameError;
class LengthError;
class SpaceError;
class VideoSizeError;

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

//* >>>>>>>>> Class declarations >>>>>>>>>>>>>
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
private:
    string email;

public:
    string name;
    string userId;
    int age;
    vector<Award *> awards;
    vector<Post *> posts;
    Inbox *userInbox;

    // TODO: Functions ------------------------------------------------------
    User() : email(""), name(""), userId(""), age(0){};
    User(string emailInput, string nameInput, string userIdInput, int ageInput) : email(emailInput), name(nameInput), userId(userIdInput), age(ageInput){};

    void registerUser();
    void printDetails();
    // TODO: Functions that use other classes
};

class Moderator : public User
{
public:
    string modId;
    Moderator() : User(), modId(0){};
    Moderator(string emailInput, string nameInput, string userIdInput, int ageInput, string modIdInput) : User(emailInput, nameInput, userIdInput, ageInput), modId(modIdInput){};

    void printDetails();
    void deletePost(/* Subreddit*s */)
    {
        // TODO: Function to delete a post from a subreddit
    }
};

class Subreddit
{
public:
    string name;
    vector<Post *> posts;
    vector<Moderator *> mods;
    vector<string> users;

    // TODO: Functions ----------------
    Subreddit() : name(""){};
    Subreddit(string nameInput) : name(nameInput){};

    void printPosts();
    void printUsers();
    void printMods();
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
    string date;
    string time;
    string userName;
    int score;
    vector<Comment *> comments;

    Post() : postTitle(""), date(""), time(""), userName(""), score(0) {}
    Post(string pt, string d, string t, string user) : postTitle(pt), date(d), time(t), userName(user), score(0) {}

    // TODO Uses Function Handling

    void printPost();
};

class Text : public Post
{
public:
    string postContent;
    Text() : Post(), postContent("") {}
    Text(string postTitleInput, string dateInput, string timeInput, string userNameInput, string pInput) : Post(postTitleInput, dateInput, timeInput, userNameInput), postContent(pInput) {}
    void printText();
};

class Image : public Post
{
public:
    double imageSize;
    string formate;
    Image() : Post(), imageSize(), formate("") {}
    Image(string postTitle, string date, string time, string userName, double i, string f) : Post(postTitle, date, time, userName), imageSize(i), formate(f) {}

    void printImageDetails();
};

class Video : public Post
{
public:
    double videoSize;
    string formate;
    Video() : Post(), videoSize(), formate("") {}
    Video(string postTitle, string date, string time, string userName, double i, string f) : Post(postTitle, date, time, userName), videoSize(i), formate(f) {}
    void printVideoDetails();
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
    string date;
    string time;

    Comment() : content(""), score(0), userName(""), date(""), time("") {}
    Comment(string con, int s, string user, string d, string t) : content(con), score(s), userName(user), date(d), time(t) {}

    ////TODO Uses Function Handling
    void printComment();
};

class Reply : public Comment
{
public:
    string toUserName;
    Reply() : Comment(), toUserName("") {}
    Reply(string con, int s, string user, string d, string t, string toUser) : Comment(con, s, user, d, t), toUserName(toUser) {}
    void printComment();
};

//*******************  CLASSES - END *****************************

#endif