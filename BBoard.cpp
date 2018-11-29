#include "Message.h"
#include "User.h"
#include "BBoard.h"
#include "Topic.h"
#include "Reply.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


// class BBoard {
//  private:
//     string title;
//     vector<User> userList;
//     const User* currentUser;
//     vector<Message*> messageList;

//  public:
    // Constructs a board with a default title, 
    // empty user & message lists, 
    // and the "default" User
BBoard::BBoard(){
    title = "default";
    currentUser = nullptr;
}

// Same as the default constructor except 
// it sets the title of the board
BBoard::BBoard(const string & t){
    title = t; 
    currentUser = nullptr;
}

BBoard::~BBoard(){
    for(unsigned i = 0; i < messageList.size(); i++){
        delete messageList.at(i);
    }
}

// Imports all the authorized users from an input file, 
// storing them as User objects in the vector userList
// The name of the input file is passed in as a parameter to this function.
// Returns true if the file opened, false if it did not. 
// See specifications for file format.
bool BBoard::loadUsers(const string & file){
    ifstream fin;
    string users, uPass;
    fin.open(file);
    
    if(!fin.is_open()){
        //cout << "Error opening " << file << endl;
        return false; //return false here i thnk
    }
    //Not sure if else, authorized = true is needed; 
    
    //Need to read contents to file into vector userLists?
    //What about the passwords? Parallel vectors?? Do I need to make a new vector to hold the password?
    while(fin >> users >> uPass){    //Populate userList vector
        userList.push_back(User(users, uPass)); //Construct user object and pass to userlist
    }
    
    fin.close();  //Close the file 
    return true; //Return the bool
}

// Asks for and validates a user/password.-
// Always asks for both user and password combo unless 'q' or 'Q' entered. -
// Checks userList to validate user and password. -
// If valid, sets currentUser to this User, outputs welcome message, - 
// then returns true. -
// Otherwise outputs error message and then repeats request - Assuming the conditional is correct 
// for username/password. 
// Continues until valid user/password 
// or until 'q' or 'Q' is entered for username. 
// If 'q' or 'Q' is entered, does not ask for password, outputs "Bye!" -
// and then returns false. -
bool BBoard::login(){
    string user;
    string pass;
    bool confirmed = false;
    
    cout << "Welcome to " << title; 
    cout << endl;
    cout << "Enter your username ('Q' or 'q' to quit): ";
    cin >> user;
    //cout << endl; ///Commented out endline edit 1   <----------- Successful
    while(!(user == "Q") && !(user == "q")){ //while(user != 'Q' || user != 'q')
        cout << "Enter your password: ";
        cin >> pass;
        // cout << endl;   //COMMENTED OUT
         // the user class has a check function returning a bool: userList.at(i).check(user,pass);
        if(getUser(user,pass)){
            currentUser = getUser(user,pass);   //Needs editing 
            confirmed = true;
            cout << endl;
            cout << "Welcome back " << currentUser->getUsername() << '!';
            cout << endl;
            return confirmed;
        }
        
        if(confirmed == false){
            cout << "Invalid Username or Password!"; 
            cout << endl;
            cout << endl;
            cout << "Enter your username ('Q' or 'q' to quit): ";
            cin >> user;
            // cout << endl;
        }
        // Need to check for password 
    }
    if(user == "Q" || user == "q"){
        //confirmed = false; not sure if this is needed here to if I should put the return in this else 
        cout << "Bye!" << endl;
        currentUser = nullptr;
    }
    return confirmed;
    //Need condidion for Q or q to terminate the program 
}

// Contains main loop of Bulletin Board.
// First verifies a User has been logged in before calling this function.
// (Do not call login function within this function.)
// Returns from **function** immediately if no User logged in (Default User).
// Continues to display menu options to user and performs requested action
// until user chooses to quit.
// See output samples for exact format of menu.
void BBoard::run(){ //Need to change menu options
    string choice = "";
    
    if(currentUser == nullptr){
        return;
    }
    
    while(!(choice == "Q") && !(choice == "q")) { //This loop is probably incorrect, need to find a way to loop then menu wil also checking for Q or q
        cout << endl;
        cout << "Menu";
        cout << endl;
        cout << "- Display Messages ('D' or 'd')";
        cout << endl;
        cout << "- Add New Topic ('N' or 'n')"; 
        cout << endl;
        cout << "- Add Reply to a Topic ('R' or 'r')";
        cout << endl;
        cout << "- Quit ('Q' or 'q')";
        cout << endl;
        cout << "Choose an action: ";
        cin >> choice;
        // if(choice != "Q" || choice != "q"){
        //     cout << endl; 
        // }
        if(choice == "D" || choice == "d"){
            cout << endl;
            display();
        }
        if(choice == "N" || choice == "n"){
            addTopic();
        }
        if(choice == "R" || choice == "r"){
            addReply();
        }
        //Need to make conditionals for each option, each will most likely have a function call, display will print out the messagelist vector
        //Need to think about how to loop through the vector to find the specific message for the user
        //Add new message will add a message to the message list vector, push_back()? 
        //Need a coniditionl to break out of the loop when the user inputs Q or q
    }
    currentUser = nullptr;
    cout << "Bye!";
    cout << endl;
}

// void BBoard::addMessage(){  //No longer needed for this assignment ( from older BBoard)
//     string body, subject, author;
//     author = currentUser->getUsername();
    
//     cin.ignore();
//     cout << "Enter Subject: ";
//     getline(cin, subject);
//     cout << endl;
//     cout << "Enter Body: ";
//     getline(cin, body);
//     cout << endl;
//     messageList.push_back(Message(author,subject,body));
//     cout << "Message Recorded!";
//     cout << endl;
// }

void BBoard::display() const{   //What to do if the message list is empty //Need to make changes 
    unsigned i;
    
    if(messageList.size() == 0){
        cout << "Nothing to Display.";
        cout << endl;
        return;
    }
    for(i = 0; i< messageList.size(); i++){
        if(!messageList.at(i)->isReply()){
            cout << "---------------------------------------------------------";
            cout << endl;
            messageList.at(i)->print(0);
        }
    }
    // cout << endl;
    cout << "---------------------------------------------------------";
    cout << endl;
}

// This function gets a filename (datafile) of a file that stores the messages from previous sessions in the given format (See File Format Specs).
// It opens and reads the file, creating Topic and Reply objects as appropriate, 
// and fills the messageList vector (note: remember that messageList is a vector of Message pointers, not Messages).
// If an error occurs when opening the file, it returns false. Returns true otherwise.
bool BBoard::loadMessages(const string &datafile){
    ifstream fin;
    fin.open(datafile);
    
    string input, subj = "", body = "", athr, child;
    unsigned ID;
    bool mType(false); //true = topic, false = reply
    vector <string> v;
    if(!fin.is_open()){
        return false;
    }
    
    while(fin >> input){
        // if(input == "0")   Commented out to try and fix message0.txt
        //     return false;
        if(input == "<begin_topic>"){
            mType = true; 
        }
        if(input == ":id:"){
            fin >> ID;
        }
        if(input == ":subject:"){
            getline(fin, input);
            subj = input.substr(1);
        }
        if(input == ":from:"){
            fin >> athr;
        }
        if(input == ":children:"){
            getline(fin, input);
            child = input.substr(1);
        }
        if(input == ":body:"){
            fin >> input;
            body += input;
            getline(fin, input);
            while(input != "<end>"){
                body += input;
                getline(fin, input);
                if (input != "<end>")
                    body += "\n";
            }
        }
        if(input == "<end>"){
            //make object
            v.push_back(child);
            if (mType){
                Topic *p = new Topic(athr, subj, body, ID);   //author(athr), subject(sbjct), body(body), id(id){}
                messageList.push_back(p);
            }
            else{
                Reply *r = new Reply(athr, subj, body, ID);
                messageList.push_back(r);
            }
            // istringstream iS(child);
            // int temp;
            // while(iS >> temp){
            //     messageList.at(counter)->addChild(messageList.at(temp-1)); 
            // }
            body = "";
            child = "";
            mType = false;
        }
    }
    parseForChildren(messageList, v);
    fin.close();
    return true;
}


void BBoard::parseForChildren(vector <Message*> messageList, vector<string> c){
    unsigned id;
    for(unsigned i = 0; i < c.size(); i++){
        if(c.at(i) != ""){
            istringstream ss(c.at(i));
            while(ss >> id){
                messageList.at(i)->addChild(messageList.at(id - 1));
            }
        }
    } 
}


// This is the final action of the bulletin board before closing:
// It gets a filename (datafile) of a file that will store all of the the messages, 
// and after opening the file writes the messages into it with the same format (See File Format Specs).
// If an error occurs when opening the file, it returns false. Returns true otherwise.
// (Note: Since you will be opening the file for writing - i.e. an ofstream - "file not found" is NOT an error; a new file will simply be created for you).
bool BBoard::saveMessages(const string &datafile){
    ofstream save;
    save.open(datafile);
    if (!save.is_open()){
        return false;
    }
        
    save << messageList.size() << endl;     
    for (unsigned i=0; i<messageList.size(); ++i){
        save << messageList.at(i)->toFormattedString();
    }
    return true;
}

// This function asks the user to create a new Topic (i.e. the first message of a new discussion "thread"). Every Topic includes a subject (single line), 
//and a body that may consist of  multiple lines. e.g.,

// Subject: "Thanks"
// Body: "I would like to thank you for this awesome board.
//       I'll visit here regularly."


// The body ends when the user enters an empty line (i.e. a "double enter").  
//Each Topic also stores the username of currentUser; and a message id, which is (index of its Message* + 1)

// For example, the first message on the board will be a Topic whose pointer will be stored at index 0 of the messageList vector, so
//its message id will be (0 + 1) = 1 (there are better ways of establishing unique ids for a set of objects, but for now this will work fine)
// Once the Topic has been constructed, a pointer to it is added to messageList.  
// Hint: Do you need pointers to automatic or dynamic Topics?

void BBoard::addTopic(){ // New !!!
    cin.ignore();
    string athr, bdy = "", sub; //author, getUsername()?
    unsigned mId(messageList.size() + 1);
    string input;
    cout << "Enter Subject: ";
    getline(cin, sub);
    // cout << endl;   //COMMENTED OUT
    cout << "Enter Body: "; 
    while (getline(cin, input) && !input.empty()){
        bdy += "\n" + input ;
    }
    bdy = bdy.substr(1);
    athr = currentUser->getUsername();
    
    Topic *t = new Topic(athr, sub, bdy, mId);
    messageList.push_back(t);
}


// This function asks the user to enter a reply to a given Message (which may be either a Topic or a Reply, so we can handle nested replies).
// The addReply function first asks the user for the id of the Message to which they are replying; if the number provided is greater than the size of 
//messageList it should output an error message and loop back,
//continuing to ask for a valid Message id number until the user enters either -1 (or any negative number, to return to the menu); or a valid id.
// If the id is valid, then the function asks for the body of the new message, and constructs the Reply, pushing back a pointer to it on the messageList
// The subject of the Reply is a copy of the parent Topic's subject with the "Re: " prefix.
// e.g., suppose the subject of message #9 was "Thanks", and a user is replying to that message:

void BBoard::addReply(){ //New !!!
    unsigned sID;
    string sub = "", bdy = "";
    string athr = currentUser->getUsername();
    string input;
    
    cout << "Enter Message ID (-1 for Menu): ";
    cin >> sID;
    while(sID > messageList.size()){
            cout << "Invalid Message ID!!" << endl;
            cout << "Enter Message ID (-1 for Menu): ";
            cin >> sID;
        }
        
    cout << "Enter message for body: ";
    cin.ignore();
    while (getline(cin, input) && !input.empty()){
        bdy += "\n" + input ;
    }
    bdy = bdy.substr(1);  
    
    sub += "Re: " + messageList.at(sID - 1)->getSubject();
    Reply *r = new Reply(athr, sub, bdy, messageList.size() + 1);
    messageList.at(sID - 1)->addChild(r);
    messageList.push_back(r);
}


// This function includes the functionality of the old "user_exists" helper:
// It traverses the userList, testing for the existence of a User with the given name and password; 
//if this User is NOT found, the function returns 0 (or nullptr); otherwise it returns a pointer to the identified User
// (the statement return &userList.at(i) will work - make sure you understand why!!)
// This function may be used by login() to set the currentUser (which is now, obviously, a pointer, not an object).
// There must be no other way to set currentUser to anything other than 0 (or nullptr).
// 
const User * BBoard::getUser(const string &name, const string &pw) const{
    unsigned i;
    for(i = 0; i < userList.size(); i++){ // the user class has a check function returning a bool: userList.at(i).check(user,pass);
        if(userList.at(i).check(name,pw)){
            return &userList.at(i);
        }
    }
    return nullptr; 
}

//Helper function should help with current user assignment
