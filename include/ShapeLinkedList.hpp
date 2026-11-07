#pragma once

class Shape;

class ShapeLinkedList
{
private:
    struct Node {
        Node* prevNode;
        Node* nextNode;
        Shape* shape;
    };
    int lenght;
    Node* head;
    Node* tail;

    /// @brief Deletes the given node
    /// @param prevNode 
    /// @param toDelete 
    /// @attention Assumes that prevNode and toDelete are correct.
    /// hence, why its private
    void deleteNode(Node*& prevNode, Node* toDelete);
    void addNode(Node*& prevNode, Node* toAdd);

public:
    ShapeLinkedList();
    void addShape(const Shape* shape);
    void removeShape(const Shape* shape);
    
    ShapeLinkedList(const ShapeLinkedList& other);
    ShapeLinkedList& operator=(const ShapeLinkedList& other);
    ~ShapeLinkedList();
};

