#include <iostream>

template<typename Type>
struct Node{
    Type data;
    Node<Type>* next;
};

template<typename Type>
class CircleList{
public:
    CircleList();
    void pushBack(Type data);
    void popBack();
    unsigned int size();
    bool isEmptyList();
    

}


