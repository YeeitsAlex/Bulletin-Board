#ifndef REPLY_H
#define REPLY_H
#include "Message.h"
#include <iostream>
#include <string>

using namespace std;

class Reply : public Message {
   // no new member variables
   public:
    Reply();
    Reply(const string &athr, const string &sbjct, const string &body, unsigned id);
    virtual bool isReply() const; // Returns true
    virtual string toFormattedString() const; // New !!
};

#endif

