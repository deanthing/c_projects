/* key.c -------
 *
 * Filename: key.c
 * Description:
 * Author: Rishabh Agrawal
 * Maintainer:
 * Created: Sun Sep 13 20:29:30 2020
 * Last-Updated: September 13 22:39 2020
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


#include <ncurses.h>
#include <stdlib.h>
#include "key.h"

int get_char(){
  int ch = getch();
  switch(ch){
    case KEY_LEFT:
      return LEFT;
      break;
    case KEY_RIGHT:
      return RIGHT;
      break;
    case KEY_UP:
      return UP;
      break;
    case KEY_DOWN:
      return DOWN;
      break;
    default:
      return(ch);
      break;
  }
}

