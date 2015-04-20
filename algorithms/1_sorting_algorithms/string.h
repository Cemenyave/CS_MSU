#pragma once
#ifndef _STRING_IONCE
#define _STRING_IONCE
#include "darray.h"
#include <iosfwd> // forward declaration for std::ostream and std::istream

class String
{
private:
  Darray<char> string;

public:
  String(void);
  String(const String &);
  String(const char *);
  ~String(void);

  String &operator=(const char *);
  const char &operator[](const int) const;
        char &operator[](const int);
  friend bool operator==(const String &, const String &);

  friend std::ostream& operator<<(std::ostream&, const String&);
  friend std::istream& operator>>(std::istream&,       String&);

  char const * const &cstring() const;
  char * const &cstring();

  const int size() const;

private:
  void setString(const char * const &);
};

#endif
