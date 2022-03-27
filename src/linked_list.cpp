#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node *node = new Node(value);
    if (front_ == nullptr){
      front_ = node;
      back_ = front_;
    }
    else{
      back_ -> next = node;
      back_ = node; //????????????
    }
    size_ += 1;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index >= 0 and index <= size_) {
      Node* node = new Node(value);
      if (index == 0) {
        node->next = front_;
        front_ = node;
        if (size_ == 0) {
          back_ = front_;
        }
        size_ += 1;
        return true;
      }
      else{
        if (index == size_) {
          back_->next = node;
          back_ = node;
          size_ += 1;
          return true;
        }
        else {
          Node* curr_node = front_;
          for (int i = 0; i < index-1; i++) {
            curr_node = curr_node->next;
          }
          node->next = curr_node->next;
          curr_node->next = node;
          size_ += 1;
          return true;
        }
      }
    }
    return false;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index >= 0 and index < size_){
      Node* node = front_;
      for (int i = 0; i < index; i++){
        node = node -> next;
      }
      node -> value = new_value;
      return true;
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= 0 and index < size_){
      if (index == 0){
        int value1 = front_ -> value;
        front_ = front_ -> next;
        size_ -= 1;
        return value1;
      }
      Node* node = front_;
      for (int i = 0; i < index - 1; i++){
        node = node -> next;
      }
      int value1 = node -> next -> value;
      node -> next = node -> next -> next;
      size_ -= 1;
      return value1;
    }
    return std::nullopt;
  }

  void LinkedList::Clear() {
    for (int i = 0; i < size_; i++){
      Node* node = front_;
      front_ = nullptr;
      size_ -= 1;
    }
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    Node* node = front_;
    if (index >= 0 and index < size_){
      for (int i = 0; i < index; i++){
        node = node -> next;
      }
      return node -> value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* node = front_;
    for (int i = 0; i < size_; i++){
      if (node -> value == value){
        return i;
      }
      node = node -> next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    return IndexOf(value) != std::nullopt;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr){
      return front_ ->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr){
      return back_ -> value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index >= 0 and index < size_){
      Node* node = front_;
      for (int i = 0; i < index; i++){
        node = node -> next;
      }
      return node;
    }
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment