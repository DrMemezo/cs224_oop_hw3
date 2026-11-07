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
    void update(int x, int y, char cell);
    
    char getCell(int x, int y) const;


    ~Grid();
};
