// connor mahern & dean allen 
// mileston 2


#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "food.h"
#include "game_window.h"
#include "key.h"
#include "game.h"
#include "obstacle.h"

void generate_points(int *food_x, int *food_y, int width, int height, int x_offset, int y_offset){
    *food_x = rand() % width + x_offset;
    *food_y = rand() % height + y_offset;
}

void game(){
    enum State state = INIT; // Set the initial state
    static int x_max, y_max; //Max screen size variables
    static int x_offset, y_offset; // distance between the top left corner of your screen and the start of the board
    gamewindow_t *window; // Name of the board
    gamewindow_t *over_window; // Name of the board
    Snake *snake, *enemySnake; // The snake
    Snake *new_tail;
    Food *foods,*new_food; // List of foods (Not an array)
    Obstacle *obstacles, *new_obstacle;

    int height = 30; 
    int width = 70;
    char ch;
    char prev_ch;
    char removed_type;
    char start_input = 'h';
    char quit_input = 'h';
    char pause_input = 'h';
    int isValid = 0; 
    int points;
    int speed_increase = 0;
    int size_count = 0;
    int temp_width = 0;
    int temp_height = 0;
    int save_count = 0 ;
    char save_name[100];
    int food_amount = 10;
    int o_amount = 1;
    int lives = 3;
    char d_setting;
    int  enemyPrevMove = 1;

    struct timespec timeret;
    timeret.tv_sec = 0;
    timeret.tv_nsec = 999999999/4;
    while(state != EXIT){
        switch(state){
        case INIT:
            initscr();
            start_color();
            nodelay(stdscr, TRUE); //Dont wait for char
            noecho(); // Don't echo input chars
            getmaxyx(stdscr, y_max, x_max);
            keypad(stdscr, TRUE); // making keys work
            curs_set(0); // hide cursor
            timeout(100);
	    // init colors
            init_pair(1, COLOR_RED, COLOR_BLACK);
    	    init_pair(2, COLOR_GREEN, COLOR_BLACK);
            init_pair(3, COLOR_YELLOW, COLOR_BLACK);
            init_pair(4, COLOR_CYAN, COLOR_BLACK);
            //init_pair(5, COLOR_GREEN, COLOR_BLACK);
		
            // Setting height and width of the board
            x_offset = (x_max / 2) - (width / 2);
            y_offset = (y_max / 2) - (height / 2);
            
            //Init board
            window = init_GameWindow(x_offset, y_offset, width, height);
            draw_Gamewindow(window);

            // Init snake
            enemySnake = init_snake(x_offset + (width / 2), y_offset + (height / 2)-5);
	    snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));
            
            // Init foods
            int food_x, food_y, i;
            enum Type type;
	    
	    //Start Screen and Difficutly
	    mvprintw(25,85, "Welcome to Snake!");
	    mvprintw(30,80, "Press 'E' for easy, 'H' for hard, 'A' for advanced!");
	    mvprintw(35,85, "Then press 's' to start the game!");

	    refresh();
		
	    //Checking for dificultly setting
	    scanf("%c", &d_setting);
	    
	    switch(d_setting) {
		case ('E') :
			//Easy nothing changes
			break;	


		case('H') :
			//Hard, spee increase by 1.5, 5 more food, obstacels * 2
			snake->speed = (snake->speed * 1.5);
			food_amount += 5;
			o_amount += 2;
			break;
		
		case('A') :
			// advanced mode, speed 1.75
			snake->speed = (snake->speed * 1.75);
			food_amount += 10;
			o_amount += 3;
			break;
	    }
		
	    	// start game with s input
            while( start_input != 's'){
		scanf("%c", &start_input);
	    }



            // generate foods
            generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
            type = (rand() > RAND_MAX/2) ? Increase : Decrease; // Randomly deciding type of food
            foods = create_food(food_x, food_y, type);
            for(i = 1; i < food_amount; i++){
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                type = (rand() > RAND_MAX/2) ? Increase : Decrease;
                new_food = create_food(food_x, food_y, type);
                foods = add_new_food(foods, new_food);
            }
           
	//init obstacle
    	obstacles = create_obstacle(food_x, food_y, 1);
    	// random num of obstacle between 3 and 10
    	int numObstacles = (rand() % (10 - 3 + 1)) + 3;
	int o_adj = numObstacles * o_amount;
    	//iterate through obstacles to create
    	for(i = 0; i < o_adj; i++){
        	// obstacle size
        	int obstacleSize = (rand() % (4 - 1 + 1)) + 1;
        	//generate some points
        	generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
        	//while theres no obstacle, populate row and collumns of obstracle
            	while (obstacle_exists(obstacles,food_x, food_y))
                	generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
            	int topLeftX = food_x;
           	int topLeftY = food_y;
            	int k = 0;
            	int l = 0;
            	while(k	<= obstacleSize) {
                	while(l <= obstacleSize) {
                    	int newX = topLeftX + l;
                    	int newY = topLeftY + k;
                    	// create obstacle
                    	// add obstacle
                    	new_obstacle = create_obstacle(newX, newY, obstacleSize);
                    	obstacles = add_new_obstacle(obstacles, new_obstacle);
                   	l++;
                      }
                     k++;
                  }
	        }


            state = ALIVE;
            break;

        case ALIVE:
	
	 

	//Check to see if snake has hit boundies
	
	if (snake->x <= x_offset || snake->y <= y_offset){
		state = DEAD;
	} else if (snake->x >= x_offset + width || snake->y >= y_offset + height){
		state = DEAD;
	}

	//Check if length of snake is less than 1
	if (len(snake) < 1){
	    state = DEAD;
	}

	//Check if hit obstacel
	if(obstacle_exists(obstacles,snake->x, snake->y)){
		state = DEAD;
	}
	
	//if collide with enemy snake
	if(snake->x == enemySnake->x && snake->y == enemySnake->y) {
        	state = DEAD;
		break;
    	}	


	//Check if there is no input to the ch
	//Sets it to the previous selection
	
	    if ( (int) ch != -1 ) {
	        prev_ch = ch;	    
	    }
	
            ch = get_char();

      	//Check if eating itself
	//if (eat_itself(snake) && len(snake) > 1){
	//    state = DEAD;
	//}	

	    
	    //Check for pause
/*
	    if(ch == 'p' || 'P'){
		while(pause_input){
			scanf("%c", &pause_input);
			if(pause_input == 'p' || pause_input == 'P'){
				break;
			}
		}
	    }
*/

	    //Checking for quit
	    if (ch == 'q' || ch == 'Q'){
	        state = EXIT;
		refresh();
		sleep(1); 
		endwin();
		exit(1);
	    }
	
	save_count = 1;
        if(ch == 'f' || ch == 'F') {
            clear();
            mvprintw(25,85, "Enter which slot you want to save the game in:");
            int saveSpot;
            scanf(" %d", &saveSpot);
            refresh();
            snprintf(save_name, 100, "./saves/save_%d.game", saveSpot);
            FILE* output;
            output = fopen(save_name, "wb");
            scr_dump(save_name);
            fclose(output);
        }	   
	
	   if(ch == '-'){
		if(size_count < 3){
			size_count += 1;
			temp_width = width - (size_count * 5);
                        temp_height = height - (size_count * 5);
			window = changeGameWindow(x_offset, y_offset, temp_width, temp_height, window);
	   	} 
	    }
	
	    if(ch == '+'){
		int neg_count = -3;
		if(size_count > neg_count){
			size_count -= 1;
			temp_width = width - (size_count * 5);
			temp_height = height - (size_count * 5);
			window = changeGameWindow(x_offset, y_offset, temp_width, temp_height, window);	
		}
             } 

	    if(ch == 'p' || ch == 'P') {
                char cont = 's';
                while(1) {
			clear();
                        mvprintw(20,20, "Pause Menu:");
                        mvprintw(21,22, "Enter 1 for loading a saved game. 2 for loading top 10 scores. 3 to quit. Press p or P to return to game");
                        refresh();
			char pauseInp;
                        scanf(" %c", &pauseInp);
                        if(pauseInp == '1') {
                                clear();
                                mvprintw(22,22, "Enter number of save game you want to load (1-10)");
                                refresh();
                                char loadGame;
                                scanf(" %c", &loadGame);
				int x = loadGame - '0';
                                char load_name[100];
				snprintf(load_name, 100, "./saves/save_%d.game", x);
                                //mvprintw(24,22, "loc: %s", load_name);
				//refresh();
				//while(1){}
				clear();
				scr_init(load_name);
				doupdate();
				refresh();
                        } else if(pauseInp=='3') {
				state = EXIT;
                		refresh();
                		sleep(1);
                		endwin();
                		exit(1);
               		} else if(pauseInp=='2') {
				int intCount;
    				int array[11];
    				FILE *fp;
    				fp = fopen("./saves/saves_best_10.game", "r");
				if (fp !=NULL) {
    					while(fscanf(fp, "%d", &array[intCount]) == 1) {
        					intCount++;
    					}
    					clear();
    					mvprintw(26,85, "10 best scoresare: %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", array[0], array[1], array[2], array[3], array[4], array[5], array[6], array[7], array[8], array[9]);
					mvprintw(27,85, "press p to return");
					refresh();
					while(1) {
						scanf(" %c", &pauseInp);
						if(pauseInp=='p' || pauseInp=='P')
							break;
					}	
				}
			} else if(pauseInp == 'p' || pauseInp == 'P')
				break;
		 }
            }
	    if(ch == 'l' || ch =='L') {
				clear();
                                mvprintw(22,22, "Enter number of save game you want to load (1-10)");
                                refresh();
                                char loadGame;
                                scanf(" %c", &loadGame);
                                int x = loadGame - '0';
                                char load_name[100];
                                snprintf(load_name, 100, "./saves/save_%d.game", x);
                                //mvprintw(24,22, "loc: %s", load_name);
                                //refresh();
                                //while(1){}
                                clear();
                                scr_init(load_name);
                                doupdate();
                                refresh();
	    }


            /* Write your code here */
		//Movement Constraints
		//Left Case
	    if(prev_ch == 1 && (int)ch == 2){ 
		isValid = 0;
		//Right Case
            } else if (prev_ch == 2 && (int)ch == 1) {
		isValid = 0;
		//Up Case
            } else if (prev_ch == 3 && (int)ch == 4) {
		isValid = 0;
		//Down Case
            } else if (prev_ch == 4 && (int)ch == 3) {
		isValid = 0;
            } else {
		//ch is entered as a vaild move
		isValid = 1;
	    }	   
	   
	//Check if this is a valid move to make
	   if (isValid == 1){
		//Make Move
		snake = move_snake(snake, ch);
	   } else {
		//if not valid move, make ch prev char so it will stay in the same location
	   	ch = prev_ch;
	   }

	   //move enemy snake

	int isValMove = 0;
        int randMoveEnemy;
        while(isValMove != 1 ) {
            randMoveEnemy = (rand() % (4 - 1 + 1)) + 1;

            if(enemyPrevMove == 1 && randMoveEnemy != 2){ 
                isValMove = 1;
            //Right Case
            } else if (enemyPrevMove == 2 && randMoveEnemy != 1) {
                isValMove = 1;
            //Up Case
            } else if (enemyPrevMove == 3 && randMoveEnemy != 4) {
                isValMove = 1;
            //Down Case
            } else if (enemyPrevMove == 4 && randMoveEnemy != 3) {
                isValMove = 1;
            } 
        } 

        enemyPrevMove = randMoveEnemy;
        enemySnake = move_snake(enemySnake, randMoveEnemy);

			
	//Removing foods, while the snake is at the location of the food		  	 
	   while (food_exists(foods, snake->x, snake->y)){
		
		//Getting type of removed food		
		removed_type = get_type(foods, snake->x, snake->y);
				

		//generate points
		generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                //Remove the food
		foods = remove_eaten_food(foods, snake->x, snake->y);
				
		
		//Adding new random food
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                //Check if that point already has a food at it
		while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
		//Assign random type
                type = (rand() > RAND_MAX/2) ? Increase : Decrease;
		//Add new food
                new_food = create_food(food_x, food_y, type);
                foods = add_new_food(foods, new_food);


		//Check type of	removed	food and add points respectivly	
		//Check type of removed food and add points respectivly
                if(removed_type == 'O' || removed_type == '+'){
                    speed_increase += 20;
                    points += 20;
                    //Adding new tail to the snake
                    new_tail = create_tail(snake->x, snake->y);
                    new_tail->next = snake;
                    snake = new_tail;
                } else if(removed_type == 'X' || removed_type == '-') {
                    speed_increase -= 10;
                    points -= 10;
                    //Removing Tail from snake
                    snake = remove_tail(snake);
                }		
		
		//Check if points is 100
		if(speed_increase >= 100){
			speed_increase = 0;
			snake->speed = (snake->speed * 1.5);
		}

            }

		while (food_exists(foods, enemySnake->x, enemySnake->y)){

                //Getting type of removed food
                removed_type = get_type(foods, enemySnake->x, enemySnake->y);


                //generate points
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                //Remove the food
                foods = remove_eaten_food(foods, enemySnake->x, enemySnake->y);


                //Adding new random food
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                //Check if that point already has a food at it
                while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                //Assign random type
                type = (rand() > RAND_MAX/2) ? Increase : Decrease;
                //Add new food
                new_food = create_food(food_x, food_y, type);
                foods = add_new_food(foods, new_food);
                //Getting type of removed food
                removed_type = get_type(foods, enemySnake->x, enemySnake->y);


                //generate points
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                //Remove the food
                foods = remove_eaten_food(foods, enemySnake->x, enemySnake->y);


                //Adding new random food
                generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                //Check if that point already has a food at it
                while (food_exists(foods,food_x, food_y))
                    generate_points(&food_x, &food_y, width, height, x_offset, y_offset);
                //Assign random type
                type = (rand() > RAND_MAX/2) ? Increase : Decrease;
                //Add new food
                new_food = create_food(food_x, food_y, type);
                foods = add_new_food(foods, new_food);


                //Check type of removed food and add points respectivly
                //Check type of removed food and add points respectivly
                if(removed_type == 'O' || removed_type == '+'){
                    //Adding new tail to the enemySnake
                    new_tail = create_tail(enemySnake->x, enemySnake->y);
                    new_tail->next = enemySnake;
                    enemySnake = new_tail;
                } else if(removed_type == 'X' || removed_type == '-') {

                    //Removing Tail from enemySnake
                    enemySnake = remove_tail(enemySnake);
                }
           }

	    // Draw everything on the screen
	    clear();
	    mvprintw(11,30, "LIVES: %d", lives);
            mvprintw(20,20, "Key entered: %c", ch);
            mvprintw(25,20, "Current Points : %d", points);
	    //mvprintw(30,20, "Previous Char : %d", prev_ch);
	    //mvprintw(32,20, "Size Count : %d", size_count );
	    //mvprintw(35,20, "X : %d Y : %d", x_offset, y_offset); 
	    //mvprintw(40,20, "X : %d Y : %d", snake->x, snake->y); 
            draw_Gamewindow(window);
	    attron(COLOR_PAIR(4));
	    draw_obstacle(obstacles);
	    attron(COLOR_PAIR(2));
            draw_snake(snake);
	    attron(COLOR_PAIR(1));
	    draw_snake(enemySnake);
	    attron(COLOR_PAIR(3));
            draw_food(foods);
	    attroff(COLOR_PAIR(3));
	    break;

        case DEAD:
	//Game Over Case
	   if(lives >1) {
		lives--;
		snake = init_snake(x_offset + (width / 2), y_offset + (height / 2));
		state = ALIVE;
		break;
	   }
           clear();
	   over_window = init_GameWindow(x_offset, y_offset, width, height);
           draw_Gamewindow(over_window);

	   mvprintw(25,85, "Game Over.....");
	   mvprintw(30,85, "Points Scored : %d", points);
	   mvprintw(35,85, "Press Q to quit");
           refresh();
	   
	// open fle to read
	FILE* bs;
	bs = fopen("./saves/save_best_10.txt", "r");
	int s[10];
	// read file to array
	fscanf(bs, "%d%d%d%d%d%d%d%d%d%d", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9], s[10]);
	fclose(bs);
	//sort scores
	i = 0;
	int count = 0;	
	int temp, j;
	for(i=count;i>=0;i--){
		for(j=0;j<=i;j++){
			if(s[j]>s[j+1]){
				temp=s[j];
				s[j]=s[j+1];
				s[j+1]=temp;
			}
		}
	}
	//open in write mode


	bs = fopen("./saves/save_best_10.game","w");	
	if (points > s[9]){
    		s[9] = points;
	}
	//write in sorted order
	fprintf(bs,"%d %d %d %d %d %d %d %d %d %d", s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[8], s[9]);
	//close stream
	fclose(bs);

           while( quit_input != 'q'){
               scanf("%c", &quit_input);
           }
          
	   state = EXIT;
           refresh();
           sleep(1);
           endwin();
           exit(1);

        }
        refresh();
        nanosleep(&timeret, NULL);
    }

   	
    

	
}
