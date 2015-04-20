#pragma once
#ifndef _LINCKEDLIST_IONCE
#define _LINCKEDLIST_IONCE

///
/// Simple double linked list data structure
///
template <class T>
struct LinckedList
{
  T data;
  LinckedList<T> * next;
  LinckedList<T> * prev;

  LinckedList(T data) :
    data(),
    next(0),
    prev(0)
  {
    this->data = data;
  }
};

///
/// @returns pointer to head element of list
///
template <class T>
LinckedList<T> * getHead(LinckedList<T> * list)
{
  if (!list)
    return list;

  LinckedList<T> * head = list;
  while (head->prev) {
    head = head->prev;
  }
  return head;
}

///
/// @returns pointer to tail element of list
///
template <class T>
LinckedList<T> * getTail(LinckedList<T> * list)
{
  if (!list)
    return list;

  LinckedList<T> * tail = list;
  while (tail->next) {
    tail = tail->next;
  }
  return tail;
}

///
/// Create new element which contents @element and push it to lists head
/// @return pointer to that element
///
template <class T>
LinckedList<T> * pushHead(LinckedList<T> * head, T element)
{
  LinckedList<T> * newHead = new LinckedList<T>(element);

  if (!head)
    return newHead;

  newHead->next = head;
  head->prev = newHead;

  return newHead;
}

///
/// Push existing @element to lists head
/// @return pointer to thet element
///
template <class T>
LinckedList<T> * pushHead(LinckedList<T> * head,
                          LinckedList<T> * element)
{
  if (element->prev) {
    element->prev->next = 0;
    element->prev = 0;
  }
  if (element->next) {
    element->next->prev = 0;
    element->next = 0;
  }

  if (head) {
    head->prev = element;
    element->next = head;
  }

  return element;
}

///
/// Create new element which contents @element and push it to lists tail
/// @return pointer to that element
///
template <class T>
LinckedList<T> * pushTail(LinckedList<T> * tail, T element)
{
  LinckedList<T> * newTail = new LinckedList<T>(element);

  if (!tail) {
    return newTail;
  }

  newTail->prev = tail;
  tail->next = newTail;

  return newTail;
}

///
/// Push existing @element to lists tail
/// @return pointer to thet element
///
template <class T>
LinckedList<T> * pushTail(LinckedList<T> * tail,
                          LinckedList<T> * element)
{
  if (element->prev) {
    element->prev->next = 0;
    element->prev = 0;
  }
  if (element->next) {
    element->next->prev = 0;
    element->next = 0;
  }

  if (tail) {
    tail->next = element;
    element->prev = tail;
  }

  return element;
}


///
/// Concatenate two lists in one and return pointer to head of resulting list
///
template <class T>
LinckedList<T> * concatList(LinckedList<T> * head_last,
                            LinckedList<T> * tail_first)
{
  // implement concutenation with null element
  if (!head_last) {
    return tail_first;
  }

  if (tail_first) {
    head_last->next = tail_first;
    tail_first->prev = head_last;
  }

  return getHead<T>(head_last);
}

#endif
