#include "string.h"
#include <iostream>

//
//overload of default strlen from ctring
//
inline size_t strlen(const char * str)
{
  unsigned int i = 0;
  while (str[i] != '\0') {
    ++i;
  }
  return i;
}

String::String(void) :
  string()
{
  this->setString("");
}

String::String(const String &str) :
  String()
{
  this->string = str.string;
}

String::String(const char * const str) :
  String()
{
  setString(str);
}

String::~String(void) {}

String &String::operator=(const char *rhv)
{
  setString(rhv);
  return *this;
}

const char &String::operator[](const int index) const
{
  assert(index < this->size());
  return string[index];
}

char &String::operator[](const int index)
{
  return const_cast<char &>(
    static_cast<const String&>(*this)[index]
  );
}

char const * const &String::cstring() const
{
  return string.getPtr();
}

char * const &String::cstring()
{
  return const_cast<char * &>(
    static_cast<const String&>(*this).cstring()
  );
}

std::ostream &operator<<(std::ostream& outs, const String &str)
{
  outs << str.cstring();
  return outs;
}

std::istream &operator>>(std::istream& ins, String &S)
{
  char * input = new char[100];
  ins.getline(input, 100);
  int inputLenght = static_cast<int>(strlen(input));
  S.string.resize(inputLenght + 1);
  for (int i = 0; i < inputLenght; ++i) {
    S.string[i] = input[i];
  }
  S.string[inputLenght] = '\0';
  delete[] input;
  return ins;
}

bool operator==(const String &lhs, const String &rhs)
{
  if (lhs.string == rhs.string) {
    return true;
  }

  if (lhs.size() != rhs.size()) {
    return false;
  }

  for (int i = 0; i < lhs.string.size(); ++i)
  {
    if (lhs.string[i] != rhs.string[i])
      return false;
  }
  return true;
}

const int String::size() const
{
  return this->string.size() - 1;
}

void String::setString(const char * const &str)
{
  this->string.clear();
  this->string.append(str, static_cast<int>(strlen(str)) + 1/*null terminator*/);
  this->string.shrink();
}
