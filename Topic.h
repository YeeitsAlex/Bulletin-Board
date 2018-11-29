#ifndef TOPIC_H
#define TOPIC_H
#include "Message.h"
#include <iostream>
#include <string>

using namespace std; 


class Topic : public Message {   
   // no new member variables
   public:
     Topic();
     Topic(const string &athr, const string &sbjct, const string &body, unsigned id);
     virtual bool isReply() const;  // Returns false
     virtual string toFormattedString() const;  // New !!
};

#endif


