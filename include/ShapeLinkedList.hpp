#pragma once

class Shape;
class Point;
class Grid;

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

    void unlink(Node* node);

    /// @brief Get the node by shape ID
    Node* getNodeByID(int ID);

public:
    ShapeLinkedList();
    /// @brief Adds the shape to the end of the list
    /// @param shape 
    void addShape(Shape* shape);
    /// @brief Removes the Shape from the list and returns its pointer
    /// @param ID the id of the shape to remove
    /// @return the shape pointer, or nullptr if its not found
    /// @attention it is upto the caller to safely delete the shape
    Shape* popShapeByID(int ID);

    /// @brief Get the pointer to the Shape object from its ID
    const Shape* getShapeByID(int ID);

    const Point* getPointByCoords(int x, int y);
    
    /// @brief Deletes the list AND all the shapes stored
    void clearList();

    void print_history() const;

    int getLenght() const;

    void drawAll(Grid& grid) const;
    
    // * There really should be no need for these methods.
    // * Still, to prevent the implicit definitions, and to make sure
    // * the compilers gives an error if this is used
    ShapeLinkedList(const ShapeLinkedList& other) = delete;
    ShapeLinkedList& operator=(const ShapeLinkedList& other) = delete;

    ~ShapeLinkedList();
};

