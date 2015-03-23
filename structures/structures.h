#ifndef structures
#define structures

typedef struct Grid Grid;
struct Grid {
    int** data;  // Will be used as a 2D grid to store the position of the tetrominoes.
    int size_x;
    int size_y;
};

typedef struct WindowSize WindowSize;
struct WindowSize {
    int width;
    int height;
};

#endif
