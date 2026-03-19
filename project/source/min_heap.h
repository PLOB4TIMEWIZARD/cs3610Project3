#include <vector>
#include <algorithm>
using namespace std;

template <typename T>
struct HeapNode {
  HeapNode(const T data, const int key) : data(data), key(key) {}
  bool operator<(const HeapNode<T>& rhs) {return this->key < rhs.key;}
  bool operator<=(const HeapNode<T>& rhs) {return this->key <= rhs.key;}

  T data;
  int key;
};

template <typename T>
class MinHeap {
public:
  MinHeap() {}
  ~MinHeap() {}

  void insert(const T data, const int key);
  T extract_min();
  T peek() const {T data; return data;}; // need to implement this function

  int size() const { return 0;};         // need to implement this function

private:
  vector<HeapNode<T> > heap;
};


template <typename T>
void MinHeap<T>::insert(const T data, const int key) {  
  heap.push_back(HeapNode<T>(data, key)); // insert new node at end of vector

  for(size_t i = heap.size() - 1; i > 0;){
    size_t parent = (i - 1) / 2; // calculate parent index
    if(heap[i] <= heap[parent]) { // if new node is smaller than parent, swap
      swap(heap[i], heap[parent]);
      i = parent; // update i to parent index and continue loop
    }
    else break; // if new node is not smaller than parent, stop loop
  }
}

template <typename T>
T MinHeap<T>::extract_min(){       // if heap is empty, return default value of T                    
  if(this -> heap.empty()){
    return T();
  }
  T data = this -> heap[0].data; // store data of minimum node (root of heap)

  if(this -> size() == 1){ // if heap has only one node, remove it and return data
    this -> heap.pop_back();
    return data;
  }

  this -> heap[0] = this -> heap.back(); // replace root with last node

  this -> heap.pop_back(); // remove last node

  int i = 0; // start at root index
  while(true){
    int left = 2 * i + 1; // calculate left child index
    int right = 2 * i + 2; // calculate right child index
    int smallest = i; // initialize smallest index to current index

    if(left < this -> size() && this -> heap[left] < this -> heap[smallest]){ // if left child is smaller than current smallest, update smallest index
      smallest = left;
    }
    if(right < this -> size() && this -> heap[right] < this -> heap[smallest]){ // if right child is smaller than current smallest, update smallest index
      smallest = right;
    }
    if(smallest != i){ // if smallest index is not current index, swap and continue loop
      swap(this -> heap[i], this -> heap[smallest]);
      i = smallest; // update i to smallest index and continue loop
    }
    else break; // if smallest index is current index, stop loop
  }
  
   return data;
}

template <typename T>
T MinHeap<T>::peek() const{
  if(this -> heap.empty()){
    return T();
  }
  return this -> heap[0].data; // return data of minimum node (root of heap)
  
}
