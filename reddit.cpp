#include "reddit.h"

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
    cout << "****************************" << endl;
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
    // TODO: print all Notification from Notification Class
}

void Inbox::clearInbox()
{
    notifs.clear();
}

void Post::printPost()
{
    cout << "*** POST DETAILS ***" << endl;
    cout << "Post Title : " << postTitle << endl;
    cout << "Date : " << date << endl;
    cout << "Time : " << time << endl;
    cout << "User : " << userName << endl;
    cout << "Score : " << score << endl;
}

void Text::printText()
{
    Post::printPost();
    cout << postContent << endl;
}

void Image::printImageDetails()
{
    Post::printPost();
    cout << imageSize << formate << endl;
}

void Video::printVideoDetails()
{
    Post::printPost();
    cout << videoSize << formate << endl;
}

void Award::printAward()
{
    cout << "Award : " << awardName << endl;
}

void Comment::printComment()
{
    cout << "*** COMMENT DETAILS ***" << endl;
    cout << "Comment : " << content << endl;
    cout << "User : " << userName << endl;
    cout << "Score : " << score << endl;
    cout << "Date : " << date << endl;
    cout << "Time : " << time << endl;
}

void Reply::printComment()
{
    Comment::printComment();
    cout << "ToUser : " << toUserName << endl;
}