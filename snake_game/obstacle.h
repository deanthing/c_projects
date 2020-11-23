#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>


//Structure to hold properties of food
struct Obstacle {
  int x;
  int y;
  struct Obstacle* next;
};

typedef struct Obstacle Obstacle; 
 
//add to list
Obstacle* add_new_obstacle(Obstacle* obstacles, Obstacle* new_obstacles);
//check if it exists at xy
bool obstacle_exists(Obstacle* obstacles, int x, int y);
Obstacle* create_obstacle(int x, int y, int size);
// draw it on screen
void draw_obstacle(Obstacle *obstacle);

