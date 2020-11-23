/*food.c -------
*
* Filename: food.c
* Description:
* Author: Manisha Suresh Kumar
* Maintainer:
* Created: Sat Sep 12 13:16:12 2020
* Last-Updated: September 12 16:51 2020
*	  By: Manisha Suresh Kumar
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

/*Copyright (c) 2016 The Trustees of Indiana University and
* Indiana University Research and Technology Corporation.
*
* All rights reserved.
*
* Additional copyrights may follow
*/

#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "food.h"


//Create new food
Food* create_food(int x, int y, enum Type type){
    Food* new_food = malloc(sizeof(Food));
     
    new_food->x = x;
    new_food->y = y;
    if (type == Increase){
	new_food->type = (rand() > RAND_MAX/2) ? 'O' : '+'; // Randomly deciding type of food
        //new_food->type = 'O';
    }
    else if(type == Decrease){
	new_food->type = (rand() > RAND_MAX/2) ? 'X' : '-'; // Randomly deciding type of food
        //new_food->type = 'X';
    }
    new_food->next = NULL;

    return new_food;
}

//Check if food exists at coordinates
bool food_exists(Food* foods, int x, int y){
    Food* temp = foods;
    while(temp){
        if(temp->x == x && temp->y == y)
            return true;
        temp = temp->next;
    }
    return false;
}

//Add new food to end of food list
Food* add_new_food(Food* foods, Food* new_food){
    Food* temp = foods;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = new_food;
    return foods;
}

//Remove food eaten by the snake
Food* remove_eaten_food(Food* foods, int x, int y){
    Food* temp = foods;
    //enum Type type;

    if(temp->x == x && temp->y == y){
        //type = foods->type;
        foods = temp->next;
        free(temp);
        return foods;
    } else {
	while(temp->next) {
	   if (temp->next->x == x && temp->next->y == y){
		break;	   
	   } else {
		temp = temp->next;
	   }
	}
    }


    Food* clear_food = temp->next;
    //type = clear_food->type;
    temp->next = temp->next->next;
    free(clear_food);
    return foods;
    
}

// Display all the food
void draw_food (Food *foods)
{   Food* temp = foods;
    while(temp) {
        mvprintw(temp->y, temp->x, "%c", temp->type);
        temp = temp->next;
    }
}


char get_type(Food *foods, int x, int y){
    Food* temp = foods;
    while(temp) {
	if(temp->x == x && temp->y == y){
		return temp->type;
	}

        temp = temp->next;
    }
}

