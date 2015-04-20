#include "debug.h"

#include <iostream>
#include "darray.h"
#include "linckedList.h"
#include "string.h"

///
/// Returns true if lhs <= rhs
///
bool compare(const String &lhs, const String &rhs);

void simpleSelectionSorting(Darray<String> &arr);
void naturalMergeSorting(LinckedList<String> * &head);


void useSimpleSelection()
{
  Darray<String> arr = Darray<String>();
  for (String input = String(); std::cin >> input && input.size(); ) {
    arr.push(input);
  }

  simpleSelectionSorting(arr);
}

void useNaturalMerge()
{
  LinckedList<String> * head = 0;
  for (String input = String(); std::cin >> input && input.size(); ) {
    head = pushHead<String>(head, input);
  }

  head = getHead<String>(head);
  naturalMergeSorting(head);
}

int compareCounter = 0;
int moveCounter = 0;

int main (int argc, char **argv)
{
  if (argc == 1) {
    std::cout << "Error! Sorting method not specified!" << std::endl
              << "Specify sorting methon in input arguments" << std::endl
              << "1 - selection sort of array" << std::endl
              << "2 - natural two-way merge of list" << std::endl;
    return 0;
  }

  switch (argv[1][0]) {
    case '1':
    useSimpleSelection();
    std::cout << "moveCounter:    " << moveCounter << std::endl;
    std::cout << "compareCounter: " << compareCounter << std::endl;
    break;

    case '2':
    useNaturalMerge();
    std::cout << "moveCounter:    " << moveCounter << std::endl;
    std::cout << "compareCounter: " << compareCounter << std::endl;
    break;

    default:
    std::cout << "Wrong sorting method specified!!!" << std::endl;
    break;
  }

  return 0;
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
    ++moveCounter;
    String temp = arr[greatest];
    arr[greatest] = arr[i];
    arr[i] = temp;
  }
}

void naturalMergeSorting(LinckedList<String> * &head)
{
  struct NaturalMergeHelpers
  {
    ///
    /// Append @source element after @dest element and fix pointers in @source.
    /// After that set next element after @source as new head sebsequence first
    /// element.
    ///
    void moveFromHead(LinckedList<String> * &source,
                      LinckedList<String> * &dest,
                      bool to_head)
    {
      ++moveCounter;
      LinckedList<String> * newSource = source->next;
      dest = to_head
             ? pushTail<String>(dest, source)
             : pushHead<String>(dest, source);
      source = newSource;
    }

    ///
    /// Append @source element after @dest element and fix pointers in @source.
    /// After that set previous element before @source as new tail sebsequence
    /// last element.
    ///
    void moveFromTail(LinckedList<String> * &source,
                      LinckedList<String> * &dest,
                      bool to_head)
    {
      ++moveCounter;
      LinckedList<String> * newSource = source->prev;
      dest = to_head
             ? pushTail<String>(dest, source)
             : pushHead<String>(dest, source);
      source = newSource;
    }

    ///
    /// @return true if @current_element > @next_elementh because we merge
    /// nondecreasing sequence
    ///
    bool isStepReached(LinckedList<String> * &current_element,
                   LinckedList<String> * &next_elementh)
    {
      if (!next_elementh) {
        return true;
      } else {
        return !compare(current_element->data, next_elementh->data);
      }
    }
  } helpers;

  bool finished = true;
  bool toHead = true;

  LinckedList<String> * destHeadSubseq = 0; //list of elements which will be
                                            //placed to the begining of
                                            //resulting sequence

  LinckedList<String> * destTailSubseq = 0; //list of elements which will be
                                            //placed to the end of
                                            //resulting sequence

  LinckedList<String> * headSubseq = head;
  LinckedList<String> * tailSubseq = getTail<String>(head);

  LinckedList<String> * currentDest = 0;

  for ( ; ; ) {
    if (compare(headSubseq->data, tailSubseq->data)) {
      helpers.moveFromHead(headSubseq, currentDest, toHead);
      if (helpers.isStepReached(currentDest, headSubseq)) {
        if (headSubseq) {
          for ( ; ; ) {
            if (!tailSubseq) {
              break;
            }
            helpers.moveFromTail(tailSubseq, currentDest, toHead);
            if (helpers.isStepReached(currentDest, tailSubseq)) {
              break;
            }
          }
        }
      } else {
        continue;
      }
    } else if (tailSubseq) {
      helpers.moveFromTail(tailSubseq, currentDest, toHead);
      if (helpers.isStepReached(currentDest, tailSubseq)) {
        if (tailSubseq) {
          for ( ; ; ) {
            if (!headSubseq) {
              break;
            }
            helpers.moveFromHead(headSubseq, currentDest, toHead);
            if (helpers.isStepReached(currentDest, headSubseq)) {
              break;
            }
          }
        }
      } else {
        continue;
      }
    }

    if (toHead) {
      currentDest = getHead<String>(currentDest);
      destHeadSubseq = concatList<String>(destHeadSubseq, currentDest);
      destHeadSubseq = getTail<String>(destHeadSubseq);
    } else {
      currentDest = getTail<String>(currentDest);
      destTailSubseq = concatList<String>(currentDest, destTailSubseq);
    }
    currentDest = 0;
    toHead = !toHead;

    if (headSubseq && tailSubseq) {
      finished = false;
    } else {
      break;
    }
  }

  destHeadSubseq = concatList<String>(destHeadSubseq, destTailSubseq);
  destHeadSubseq = getHead<String>(destHeadSubseq);

  if (!finished) {
    naturalMergeSorting(destHeadSubseq);
  }

  head = destHeadSubseq;
}

bool compare(const String &lhs, const String &rhs)
{
  ++compareCounter;
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
