/**
 * Linked List C++ implementation
 * Copyright (C) 2021 Vincenzo Palazzo vincenzopalazzodev@gmail.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cassert>
#include <memory>
#include <vector>

namespace cpstl {

/**
 * Implementation of the class Node, that it is used to
 * managed the pointer inside the data-stucture.
 */
template <class T>
class LinkedList;

namespace internal {
/**
 * Implementation of the class Node, that it is used to
 * managed the pointer inside the data-stucture.
 */
template <class T>
class Node {
 private:
  T value;
  std::shared_ptr<Node<T>> next = nullptr;
  std::shared_ptr<Node<T>> prev = nullptr;
  friend cpstl::LinkedList<T>;

 public:
  Node(T const &value) : value(value) {}

  Node(T const &value, std::shared_ptr<Node<T>> const &next,
       std::shared_ptr<Node<T>> const &prev)
      : value(value), next(next), prev(prev) {}
};
};  // namespace internal

/**
 * LinkedList implementation, it offer an implementation of the
 * LinkedList double linked.
 */
template <class T>
class LinkedList {
 private:
  std::size_t size_list;
  std::shared_ptr<internal::Node<T>> head = nullptr;
  std::shared_ptr<internal::Node<T>> tail = nullptr;

 public:
  constexpr LinkedList() : size_list(0) {}

  /**
   * Adding the value to the end of the list.
   * Cost of the operation O(1).
   */
  void add(T const &value) {
    auto node = std::make_shared<internal::Node<T>>(value);
    if (!head) {
      this->head = node;
      this->tail = node;
      return;
    }
    node->prev = this->tail;
    this->tail->next = node;
    this->tail = node;
  }

  /**
   * Remove the first instance find inside list,
   * in according with the insert order.
   */
  void remove(T const &value) {
        Node* temp = head;
        Node* previous= nullptr;

        // if head value matches value, delete head node
        if (head.value == value)
        {
            head = value -> next;
            delete temp;
            return;
        }
        // iterate until node value matches the value
        while (temp.value != value)
        {
            previous = temp;
            temp = temp -> next
        }
        // set prev next to deleted node's next, then delete node
        previous -> next = temp -> next;
        delete temp;
  }

  /**
   * Remove the element at the index,
   */
  void remove_at(std::size_t index) {
  // if linked list is empty
        if (head == nullptr)
            return;

        Node* temp = head;

        if (index == 0) // if first element, remove from head
        {
            head = temp -> next;
            delete temp;
            return;
        }
        for (int i = 0; temp != nullptr && i < position - 1; i++) // loop until reach index position
            temp = temp -> next;

        if (temp == nullptr || temp -> next == nullptr) // index not in linked list
            return;

        // remove element at index position
        Node* next = temp -> next -> next;
        delete temp -> next;
        temp -> next = next;
  }

  /**
   * Swap two element in the list
   */
  void swap(std::size_t x, std::size_t y)
  {
        // no swap if they are the same value
        if (x == y)
            return;

        Node* prevX = nullptr;
        Node* tempX = head;
        while (tempX && tempX -> data != x) // find node with x value
        {
            prevX = tempX;
            tempX = tempX -> next;
        }

        Node* prevY = nullptr;
        Node* tempY = head;
        while (tempY && tempY -> data != y) // find node with y value
        {
            prevY = tempY;
            tempY = tempY -> next;
        }

        if (tempX == nullptr || tempY == nullptr) // one or both values not found
            return;

        if (prevX != nullptr)
            prevX -> next = tempY; // apply x prev next node to y
        else
            head = tempY; // else apply to head if there is no prev of x

        if (prevY != nullptr) // apply y prev next node to x
            prevY -> next = tempX;
        else
            head = tempX; // else apply to head if there is no prev of y

        // switch x and y next nodes
        Node* temp = tempY -> next;
        tempY -> next = tempX -> next;
        tempX -> next = temp;
  }

  std::vector<T> to_vector() {
    if (!head) return {};

    // This time we use the for to iterate over the list
    std::vector<T> result;
    result.reserve(size_list);
    bool has_next = this->head != nullptr;
    auto node = *head;
    while (has_next) {
      result.push_back(node.value);
      has_next = node.next != nullptr;
      if (has_next) node = *node.next;
    }
    return result;
  }

  std::string to_string(std::string seperator = ", ") {
    if (!this->head) return "";
    auto start = *this->head;
    bool has_next = true;
    std::string concatenation = "";
    while (has_next) {
      std::string result = std::to_string(start.value);
      has_next = start.next != nullptr;
      if (has_next) {
        start = *start.next;
        result += seperator;
      }
      concatenation += result;
    }
    return concatenation;
  }

  /**
   * Adding a value in position index of the list
   * this operation takes just O(N) there here in the
   * worst case the N is the size of the list.
   */
  void add_at(T const &value, std::size_t index) { assert(index < size_list); }

  internal::Node<T> back() { return this->tail; }

  internal::Node<T> *begin() { return this->head; }
};
};  // namespace cpstl

#endif
