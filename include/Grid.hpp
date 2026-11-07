#pragma once

/// @brief Stores the 2D Character array that is displayed to the screen along 
/// with some helper methods
class Grid
{
private:
    char** _data;
    int _width;
    int _height;
    
public:
    Grid(int width, int height);
    /// @brief Clears the grid so that there is nothing
    void clear();
    /// @brief Prints out the grid to the console
    void display() const;
    /// @brief Updates a specific pixel in the grid. 0, 0 is the top left corner
    /// @param x The x-coordinate. 0 is leftmost
    /// @param y The y-coordinate. 0 is the topmost
    /// @param cell The character to put at (x, y)
    /// @throws invalid_argument if x or y is out of bounds
    void setCell(int x, int y, char cell);
    
    /// @brief Gets the value of cell at (x, y)
    /// @param x x-coordinate
    /// @param y y-coordinate
    /// @return value of the cell
    /// @throws invalid_argument if x or y is out of bounds
    char getCell(int x, int y) const;


    ~Grid();
};
