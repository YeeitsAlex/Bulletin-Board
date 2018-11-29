#ifndef MESSAGE_H  //inclusion guards
#define MESSAGE_H  //includes
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Message {  // abstract base class
   protected:
     string author;
     string subject;
     string body;
     unsigned id;  // New !!
     vector<Message *> childList; // New !!
     void display(unsigned indent) const;	
   public:
     Message();
     Message(const string &athr, const string &sbjct, const string &body, unsigned id);
     virtual ~Message();
     virtual bool isReply() const = 0;	 
     virtual string toFormattedString() const = 0; // New!!
     void print(unsigned indentation) const; // New !!  //Base case, if child list is empty
     //Print will only print topics from the message list, replies will be printed by parent
     //Easier to do indentations with 
     const string & getSubject() const;
     unsigned getID() const; // New !!    
     void addChild(Message *child); // New !! 
     
};

#endif