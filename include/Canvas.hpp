#pragma once

// TODO: Try making singleton
// There will only be 1 Canvas at a time

class Canvas {
    private:
        int height;
        int width;
        char** data;

        void destroy();
        void copy(const Canvas&);

        // TODO: Have a LinkedList history
    public:
        Canvas(int width);
        ~Canvas();
        void display() const;
};
