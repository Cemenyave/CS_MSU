#include <iostream>
#include "string.h"
#include "darray.h"
#include <stdlib.h>

bool compare(const String &lhs, const String &rhs)
{
  if (lhs == rhs)
    return true;

  struct Date {
    int day = 0;
    int month = 0;
    int year = 0;

    Date(const String &str)
    {
      enum {
        day_reading,
        month_reading,
        year_reading,
        finish_state
      };

      if (!str.size())
        return;

      int num = 0;
      int state = day_reading;
      for (int i = 0, s = str.size(); i < s; ++i) {
        if (str[i] == '.') {
          switch (state) {
            case day_reading:
              this->day = num;
              break;
            case month_reading:
              this->month = num;
              break;
            case finish_state:
            default:
              assert(0);
              return;
          }
          num = 0;
          ++state;
          continue;
        }
        num = num * 10 + (str[i] - '0');
      }
      this->year = num % 100;
    }
  } dateL(lhs), dateR(rhs);

  if (dateL.year != dateR.year) {
    return dateL.year <= dateR.year;
  }

  if (dateL.month != dateR.month) {
    return dateL.month <= dateR.month;
  }

  return dateL.day <= dateR.day;
}

void simpleSelectionSorting(Darray<String> &arr)
{
  for (int i = arr.size() - 1; i >= 0; --i) {
    int greatest = 0;
    for (int j = 0; j <= i; ++j) {
      if (compare(arr[greatest], arr[j])) {
        greatest = j;
      }
    }
    String temp = arr[greatest];
    arr[greatest] = arr[i];
    arr[i] = temp;
  }
}

enum SortingMode
{
  NONDECREASE = 1,
  NONINCREASE = 2,
  CROSSWISE   = 3,
  RANDOMONE   = 4,
  RANDOMTWO   = 5,

  SM_COUNT
};

int main (int argc, char ** argv)
{
  int len = 10;
  SortingMode sm = NONDECREASE;

  if (argc > 1) {
    int i = 0;
    len = 0;

    while (argv[1][i] != '\0') {
      len *= 10;
      len += argv[1][i] - '0';
      ++i;
    }
  }

  if (argc > 2) {
    switch (argv[2][0]) {
      case '1':
        sm = NONDECREASE;
        break;

      case '2':
        sm = NONINCREASE;
        break;

      case '3':
        sm = CROSSWISE;
        break;

      case '4':
        sm = RANDOMONE;
        break;

      case '5':
        sm = RANDOMTWO;
        break;
    }
  }

  if (sm == RANDOMTWO)
    srand (1);
  else
    srand (0);

  Darray<String> arr;
  for (int i = 0; i < len; ++i)
  {
    char buff[11];
    int day = rand() % 31 + 1;
    int month = rand() % 12 + 1;
    int year = 1900 + rand() % 100;
    sprintf_s(buff, "%02d.%02d.%d", day, month, year);
    arr.push(buff);
  }

  if (sm < RANDOMONE) {
    simpleSelectionSorting(arr);
  }

  for (int i = 0, l = arr.size(); i < l; ++i) {
    if (sm == NONINCREASE) {
      std::cout << arr[l - i - 1] << std::endl;
    } else if (sm == CROSSWISE) {
      if (i % 2) {
        std::cout << arr[l - i] << std::endl;
      } else {
        std::cout << arr[i] << std::endl;
      }
    } else {
      std::cout << arr[i] << std::endl;
    }
  }

  return 0;
}
