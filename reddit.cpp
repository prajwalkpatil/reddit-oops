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
    Text *textPost;
    Image *imagePost;
    Video *videoPost;
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
        textPost = new Text();
        cout << "Enter the post title: " << endl;
        getline(cin, textPost->postTitle);
        cout << "Enter the text content: " << endl;
        getline(cin, textPost->postContent);
        textPost->userName = userId;
        textPost->dateTime = getDateTime();
        s->posts.push_back(textPost);
        break;
    case 2:
        imagePost = new Image();
        cout << "Enter the post title: " << endl;
        getline(cin, imagePost->postTitle);
        cout << "Enter the size of the image in Megabytes: ";
        cin >> imagePost->imageSize;
        cout << "Enter the format of the image: ";
        cin >> imagePost->format;
        imagePost->userName = userId;
        imagePost->dateTime = getDateTime();
        s->posts.push_back(imagePost);
        break;
    case 3:
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
        videoPost->userName = userId;
        videoPost->dateTime = getDateTime();
        s->posts.push_back(videoPost);
        break;
    default:
        throw InvalidInput("Enter a valid choice.");
        break;
    }
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
    time_t _tm = time(NULL);
    struct tm *curtime = localtime(&_tm);
    return asctime(curtime);
}