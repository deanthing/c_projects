#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "obstacle.h"


//Create new obstacle
Obstacle* create_obstacle(int x, int y, int size){
    Obstacle* new_obstacle = malloc(sizeof(Obstacle));
     
    new_obstacle->x = x;
    new_obstacle->y = y;
    
    new_obstacle->next = NULL;

    return new_obstacle;
}

//Check if food exists at coordinates
bool obstacle_exists(Obstacle* obstacles, int x, int y){
    Obstacle* temp = obstacles;
    while(temp){
        if(temp->x == x && temp->y == y)
            return true;
        temp = temp->next;
    }
    return false;
}

//Add individial block of obstacle
Obstacle* add_new_obstacle(Obstacle* obstacles, Obstacle* new_obstacle){
    Obstacle* temp = obstacles;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = new_obstacle;
    return obstacles;
}

// Display all the obstacles
void draw_obstacle (Obstacle *obstacles)
{   Obstacle* temp = obstacles;
    while(temp) {
        mvprintw(temp->y, temp->x, "%c", '=');
        temp = temp->next;
    }
}
