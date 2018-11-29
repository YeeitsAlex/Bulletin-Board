//User.h
#ifndef USER_H   //Inclusion guards
#define USER_H
#include <string>

using namespace std;
 
class User {
 private:
  string username;
  string password;
 public:
  User();
  User(const string& uname, const string& pass);
  string getUsername() const;
  bool check(const string &uname, const string &pass) const;
  bool setPassword(const string &oldpass, const string &newpass);
};

#endif