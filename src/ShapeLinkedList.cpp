#include "ShapeLinkedList.hpp"
#include "Shape.hpp"
#include "Point.hpp"
#include "Grid.hpp"

#include <iostream>
#include <stdexcept>

using std::cout;
using std::endl;

ShapeLinkedList::ShapeLinkedList()
    : head(nullptr), tail(nullptr), lenght(0)
{
}

void ShapeLinkedList::unlink(Node* node) {
    if (node -> prevNode) {
        node -> prevNode -> nextNode = node -> nextNode;
    }
    if (node -> nextNode) {
        node -> nextNode -> prevNode = node -> prevNode;
    }
}

void ShapeLinkedList::addShape(Shape* shape) {
    
    Node* newNode = new Node;
    newNode -> prevNode = tail;
    newNode -> nextNode = nullptr;
    newNode -> shape = shape;

    if (lenght == 0) { // CASE: Empty list, update head 
        head = newNode;
    }
    else {
        tail -> nextNode = newNode;
    }

    tail = newNode;
    lenght++;

}
Shape* ShapeLinkedList::popShapeByID(int ID) {

    Node* this_node = getNodeByID(ID);

    if (!this_node) return nullptr;

    unlink(this_node);

    Shape* to_return = this_node -> shape;
    delete this_node;
    lenght--;

    return to_return;

}

ShapeLinkedList::Node* ShapeLinkedList::getNodeByID(int ID) {
    Node* traversal = head;

    while (traversal && traversal -> shape -> getID() != ID) 
        traversal = traversal -> nextNode; // Keep moving forward until end or you find the thing

    return traversal;
}

Shape* ShapeLinkedList::getShapeByID(int ID) {
    Node* node = getNodeByID(ID);
    if (!node) return nullptr;
    return node -> shape;
}

int ShapeLinkedList::getLenght() const {
    return lenght;
}

void ShapeLinkedList::clearList() {
    Node* traversal = head;
    while (traversal != nullptr) {
        Node* next_node = traversal -> nextNode;
        traversal -> shape -> destroy(true);
        delete traversal;
        traversal = next_node;
        lenght--;
    }

    head = nullptr;
    tail = nullptr;
}

ShapeLinkedList::~ShapeLinkedList() {
    clearList();
}

void ShapeLinkedList::drawAll(Grid& grid) const {
    
    grid.clear();
    Node* traveral = head;

    while (traveral) {
        traveral -> shape -> draw(grid);
        traveral = traveral -> nextNode;
    }

}
void ShapeLinkedList::print_history() const {
    
    if (!head) {
        cout << "No shapes in history..." << endl;
        return;
    }

    Node* traversal = head;

    while (traversal)
    {
        const Shape* this_shape = traversal -> shape;
        cout << this_shape -> to_string() << endl;
        
        traversal = traversal -> nextNode;
    }
    
}

const Point* ShapeLinkedList::getPointByCoords(int x, int y) {
  Node* traversal = head;

  while (traversal) {
    if (const Point* p = dynamic_cast<Point*>(traversal -> shape)) {
      if ( p->getX() == x && p->getY() == y) {
        return p;
      }
    }

    traversal = traversal -> nextNode;
  }

  return nullptr;
}

