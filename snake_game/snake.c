/* snake.c -------
 *
 * Filename: snake.c
 * Description:
 * Author: Rishabh Agrawal
 * Maintainer:
 * Created: Sun Sep 13 9:12:30 2020
 * Last-Updated: September 13 22:40 2020
 *           By: Rishabh Agrawal
 *
 */

/* Commentary:
 *
 *
 *
 */

/* Change log:
 *
 *
 */

/* Copyright (c) 2016 The Trustees of Indiana University and
 * Indiana University Research and Technology Corporation.
 *
 * All rights reserved.
 *
 * Additional copyrights may follow
 */


#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "snake.h"
#include "key.h"
#include <ncurses.h>


// Initialize snake
Snake* init_snake(int x, int y){
  Snake* head = create_tail(x, y);
  Snake* tail1 = create_tail(x-1, y);
  Snake* tail2 = create_tail(x-2, y);
  tail1->next = tail2;
  head->next = tail1;
  return head;
}

// Creates one tail
Snake* create_tail(int x, int y){
  Snake* snake = malloc(sizeof(snake));
  snake->speed = 1;
  snake->color[0] = 0;
  snake->color[1] = 0;
  snake->color[2] = 255;
  /* snake->color = {0, 0, 255}; */
  snake->symbol = '#';
  snake->next = NULL;
  snake->x = x;
  snake->y = y;
  return snake;
}

// Moves the snake in the input direction

Snake* move_snake(Snake* snake, int direction){
  Snake* new_head = malloc(sizeof(new_head));
  new_head->x = snake->x;
  new_head->y = snake->y;
  switch(direction) { 
    case UP:
      new_head->y = snake->y - snake->speed;
      break;
    case DOWN:
      new_head->y = snake->y + snake->speed;
      break;
    case RIGHT:
      new_head->x = snake->x + snake->speed;
      break;
    case LEFT:
      new_head->x = snake->x - snake->speed;
      break;
  }
  
  new_head->next = snake; //Setting new head as the new head
  //Adding all the features to the new cell
  new_head->speed = snake->speed;
  memcpy(new_head->color, snake->color, sizeof(new_head->color));
  new_head->symbol = snake->symbol;

  // Deleting the last cell in the entire snake
  /* Snake* end = new_head; */
  /* while(end->next->next){ */
  /*   end = end->next; */
  /* } */
  /* end->next = NULL; */

  new_head = remove_tail(new_head);
  
  return new_head;
}


Snake* remove_tail(Snake* snake){
    Snake* end = snake;
    while(end->next->next)
        end = end->next;
    free(end->next);
    end->next = NULL;
    return snake;
}

int len(Snake* snake){
    int length = 0;
    while(snake){
        length++;
        snake = snake->next;
    }
    return(length);
}
/*
Snake* move_snake(Snake* snake, int dir){ 
     Snake* new_head = snake; 
     new_head->x = snake->x; 
     new_head->y = snake->y; 
     while(new_head->next->next){ 
       switch(dir) { 
         case UP: 
           new_head->y = snake->y - snake->speed; 
           break; 
         case DOWN: 
           new_head->y = snake->y + snake->speed; 
           break; 
         case RIGHT: 
           new_head->x = snake->x + snake->speed; 
           break; 
         case LEFT: 
           new_head->x = snake->x - snake->speed; 
           break; 
       } 
       new_head = new_head->next; 
     } 
       mvprintw(40,40, "%d\t%d", new_head->x, new_head->y); 
       refresh(); 
     return snake; 
}
*/

// draws the snake on the board
void draw_snake(Snake* snake){
  while(snake){
    mvprintw(snake->y, snake->x, "%c", snake->symbol);
    snake = snake->next;
  }
}

// checks if it eats itself, if it does, then return true
bool eat_itself(Snake* snake){
  Snake* head = snake;
  Snake* tail = snake->next;

  while (tail->next){
    if (head->x == tail->x && head->y == tail->y){
      return true;
    }
    tail = tail->next;
  }
  return false;
}

