//Don't forget inclusion guard!!
//BBoard.h
#ifndef BBOARD_H
#define BBOARD_H

#include <string>
#include <vector>
using namespace std;

#include "Message.h"
#include "User.h"

class BBoard {
 private:
    string title;
    vector<User> userList;
    const User* currentUser;
    vector<Message*> messageList;
 public:
    BBoard();
    BBoard(const string &);
    ~BBoard();  //Good idea to use the BBoard destructor to deallocate memory, not message's destructor  
    bool loadUsers(const string &);
    bool loadMessages(const string &datafile);
    bool saveMessages(const string &datafile); 
    bool login();
    void run(); //Small change to run function, need to change from Add Message to Add reply, and add "Add Topic"
 private:
    void display() const;
    void addTopic(); // New !!!
    void addReply(); //New !!!
    const User * getUser(const string &name, const string &pw) const; //New!! Helper function for login
    //bool userExists(const string &, const string &) const; Not used
    void parseForChildren(vector <Message*> messageList, vector<string> c);
};

#endif