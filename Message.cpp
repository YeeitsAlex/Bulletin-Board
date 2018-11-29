#include "Message.h"
#include <iostream>
#include <string>
#include <vector>

//   protected:
//      string author;
//      string subject;
//      string body;
//      unsigned id;  // New !!
//      vector<Message *> childList; // New !!
//   public:
Message::Message(){}

Message::Message(const string &athr, const string &sbjct, const string &body, unsigned id)
: author(athr), subject(sbjct), body(body), id(id){}

// Be very careful here: some Messages will have two pointers to 
// them, stored in very different places!
// Where are they, and who should be responsible for deleting 
// them?
Message::~Message(){}
    
// } Do not need to implement because virtual function


/* This function is responsible for printing the Message 
* (whether Topic or Reply), and and all of the Message's 
* "subtree" recursively:
* After printing the Message with indentation n and appropriate 
* format (see output details), it will invoke itself 
* recursively on all of the Replies in its childList,
* incrementing the indentation value at each new level.
* Note: Each indentation increment represents 2 spaces. e.g. if 
* indentation == 1, the reply should be indented 2 spaces, if 
* it's 2, indent by 4 spaces, etc.
*/       
void Message::print(unsigned indentation) const{ // New !!
    display(indentation);
    
    if(childList.size() > 0){
        // cout << endl; //this one is added, endline # 2
        for(unsigned i = 0; i < childList.size(); i++){
            // if(childList.size() > 1){     //Conditional added to try and please endlines for test # 13, multiple variations of # of children
            cout << endl;
            childList.at(i)->print(1 + indentation);
        }
    }
}

//returns the subject string.
const string & Message::getSubject() const{
    return subject;
}

unsigned Message::getID() const{
    return id;
}

//Adds a pointer to the child to the parent's childList. 
void Message::addChild(Message *child){ // New !!
    childList.push_back(child);
}


void Message::display(unsigned indent) const{
    string temp = "";
    char temp2 = '\n';
    unsigned i;
    
    for(i = 0; i < indent; i++){
        temp += "  ";
    }
    cout << temp << "Message #" << id << ": " << subject;
    cout << endl;
    cout << temp <<"from " << author << ": ";
    for(i = 0; i < body.size(); i++){
        if(body.at(i) == temp2){   //Check for newline, if so, indentation is needed (recommended by the prof)
            cout << endl;
            cout << temp;
        }
        else{
            cout << body.at(i);
        }
    }
    cout << endl;
}

/*
:id: 4
:subject: single line
:from: author
:children: 5 6 [this line should not be printed if there are no children.]
:body: multiple lines - line 1
line 2
line 3
<end>
* line starting with :children: has the ID's of all children (See file specs. 
* for details)
* This function should not assume the last character in body is a newline.
* In other words, this function must manually add a newline after the last    
* line of the body (line 3 in this example).
* Also, the last character in the string must be a newline.
*/
string Message::toFormattedString() const{
    string format = "";
    format += ":id: " + to_string(id) + "\n";
    format += ":subject: " + subject + "\n";
    format += ":from: " + author + "\n";
    if(childList.size() > 0){
        format += ":children:"; 
        for(unsigned i = 0; i < childList.size(); i++){
            format += " " + to_string(childList.at(i)->getID());    
        }
        format += "\n";
    }
    format += ":body: " + body + "\n";
    format += "<end>";
    format += "\n"; 
    
    return format;
}