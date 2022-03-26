#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }

    capacity_ = capacity;
    data_ = new int[capacity];
    for (int i = 0; i <= capacity; i++) {
      data_[i] = 0;
    }
  }

  DynamicArray::~DynamicArray() {
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
  }

  void DynamicArray::Add(int value){
    int oldsize = size_;
    if (size_ == 0){
      size_ += 1;
      data_[0] = value;
    }
    else {
      for (int i = 0; i <= oldsize; i++){
        if (i == size_){
          if (size_ == capacity_){
            Resize(capacity_ + kCapacityGrowthCoefficient);
            size_ += 1;
            data_[i] = value;
          }
          else{
            size_ += 1;
            data_[i] = value;
          }
        }
      }
    }
  }

  bool DynamicArray::Insert(int index, int value) {
    int* arr = new int[capacity_];
    std::copy(data_, data_ + size_, arr);
    if (index <= size_ and index >= 0){
      if (size_ < capacity_) {
        int how_much_elems_above = size_ - index;
        for (int i = 0; i < how_much_elems_above; i++) {
          data_[index + i + 1] = arr[index + i];
        }
        data_[index] = value;
        size_ += 1;
        //delete[] arr;
        return true;
      }
      int how_much_elems_above = size_ - index;
      for (int i = 0; i < how_much_elems_above; i++) {
        data_[index + i + 1] = arr[index + i];
      }
      Resize(capacity_ + kCapacityGrowthCoefficient);
      data_[index] = value;
      size_ += 1;
      //delete[] arr;
      return true;
    }
    //delete[] arr;
    return false;
  }

  bool DynamicArray::Set(int index, int new_value) {
    if (size_ == 0) {
      return false;
    }
    if (index >= 0 and index < size_){
      data_[index] = new_value;
      return true;
    }
    return false;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    if (index >= 0 and index < size_) {
      int answer = data_[index];

      for (int i = index; i < size_; i++) {
        data_[i] = data_[i + 1];
        size_ -= 1;
        return answer;
      }
    }
    return std::nullopt;
  }

  void DynamicArray::Clear() {
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if (index >= 0 and index < size_) {
      return data_[index];
    }
    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for (int i = 0; i < size_; i++) {
      if (data_[i] == value) {
        return true;
      }
    }
    return false;
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if (new_capacity > capacity_){
      int *array = new int[new_capacity]{};
      for (int i; i <= capacity_; i++) {
        array[i] = data_[i];
      }
      capacity_ = new_capacity;
      delete[] data_;
      data_ = array;
      return true;
    }
    return false;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment