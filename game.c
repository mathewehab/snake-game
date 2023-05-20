#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int start =0;
int cont =0;
int Level =1;
int LevelUpCheck =0;
int lost = 0;
int prevScore = 0;
int gameOver = 0;                               // Loop controller
int x_HeadPosition, y_HeadPosition;                                       // Position of snake head
int score;                                      // Player score
int incX, incY;                                 // Value for increment the player position
int comX, comY;                                 // Food position
int tailX[MAXCALDA], tailY[MAXCALDA], tailLength;   // Array for tail in x_HeadPosition and y_HeadPosition, size of tail
int wallCollision;                              // Wall collision flag
int record;                                     // For the height score

// Function for setup everything

void newRecord(){
		
		record=score;  
		print("********************\r\n");
		print("***  NEW RECORD  ***\r\n");
		print("********************\r\n");
		print("NEW RECORD: ");
		print_idec(record);
		
}
void setUp(){

		x_HeadPosition = rand() % (SCREENSIZE - 1);            // x_HeadPosition position
    y_HeadPosition = rand() % (SCREENSIZE - 1);            // y_HeadPosition position
    incX = 0;
    incY = 0;
	do{
    comX = rand() % (SCREENSIZE - 1);         						//food
    comY = rand() % (SCREENSIZE - 1);         						//food
	}while(x_HeadPosition==comX && y_HeadPosition==comY);
	  score = 0;
	  Level = 1;
    tailLength = 0;
    wallCollision = 1;                      							// Enable wall collision
}

// Draw the map
void map_draw(){
    int i, j, k;
    for(i = 0; i < SCREENSIZE + 2; i++){
        print("#");
    }
    print("\r\n");
    for(i = 0; i < SCREENSIZE; i++){
        for(j = 0; j < SCREENSIZE; j++){
            if(j == 0){
                print("#");
            }
            if(j == x_HeadPosition && i == y_HeadPosition){
                print("O");
            }
            else if(j == comX && i == comY){
                print("@");
            }else{
                int rend_space = 0;
                for(k = 0; k < tailLength; k++){
                    if(tailX[k] == j && tailY[k] == i){
                        print("o");
                        rend_space = 1;
                    }
                }
                if(rend_space != 1){
                    print(" ");
                }
            }
            if(j == SCREENSIZE - 1){
                print("#");
            }
        }
        print("\r\n");
    }
    for(i = 0; i < SCREENSIZE + 2; i++){
        print("#");
    }
		print("\r\nscore: ");
    print_idec(score);
		print("\rrecord: ");
    print_idec(record);
	  print("\rlevel: ");
    print_idec(Level);  
		print("\r");

}

// input of keyboard
void input(char comand){
	
        switch(comand){
            case 'w':
                incX = 0;
                incY = -1;
                break;
            case 's':
                incX = 0;
                incY = 1;
                break;
            case 'a':
                incX = -1;
                incY = 0;
                break;
            case 'd':
                incX = 1;
                incY = 0;
                break;
            case 'z':
                gameOver = 1;
                break;
						case 't':
							  start=1;
								setUp();
								break;
						case 'p':
							if(LevelUpCheck == 1){
								if(score > record){
								newRecord();							
								}
								LevelUpCheck  =0;
								prevScore =0;
							}
							  cont =1;
                setUp();
								gameOver=0;
                break;
						case 'b':
								cont =1;
                gameOver = 1;
                break;
						case 'l':
							if(LevelUpCheck == 1){
								LevelUpCheck  =0;
						    cont = 1;
						    score = WINSCORE*(Level-1);
                gameOver = 0;
							}
                break;
        }
    }
// Game logic
void logic(){

    int i;
    int posCalX, posCalY;                   				// the position of the tail behind the head
    int posSeguiCalX, posSeguiCalY;         				// help variable for change the positions
    posCalX = x_HeadPosition;
    posCalY = y_HeadPosition;
    for(i = 0; i < tailLength; i++){            		// like a "bubbleSort" for tail caldas
        posSeguiCalX = posCalX;
        posSeguiCalY = posCalY;
        posCalX = tailX[i];
        posCalY = tailY[i];
        tailX[i] = posSeguiCalX;
        tailY[i] = posSeguiCalY;
    }
    
    x_HeadPosition += incX;
    y_HeadPosition += incY;
    if(!wallCollision){
        if (x_HeadPosition < 0)
            x_HeadPosition = SCREENSIZE - 1;
        if(x_HeadPosition > SCREENSIZE - 1)
            x_HeadPosition = 0;
        if(y_HeadPosition < 0)
            y_HeadPosition = SCREENSIZE - 1;
        if(y_HeadPosition > SCREENSIZE - 1)
            y_HeadPosition = 0;
    }else{
        if ((x_HeadPosition < 0) || (x_HeadPosition > SCREENSIZE - 1) || (y_HeadPosition < 0) || (y_HeadPosition > SCREENSIZE - 1)){
				  gameOver = 1;
					lost = 1;
				}

    }
    if(x_HeadPosition == comX && y_HeadPosition == comY){
        score += 10;
        comX = rand() % (SCREENSIZE - 1);
        comY = rand() % (SCREENSIZE - 1);
        tailLength++;
    }
    for(i = 0; i < tailLength; i++){
        if (tailX[i] == x_HeadPosition && tailY[i] == y_HeadPosition){
            gameOver = 1;
						lost = 1;

        }
    }
		if(score%WINSCORE == 0 && score != 0 && prevScore != score){
			Level++;
			gameOver = 1;
		}
}

// main function
void mainloop()
{
				if(lost){
					      if(score > record){
								newRecord();							

	

            }
						
            else {
                print("!!!!!!!!!!!!!!!!!\r\n");
                print("!!! GAME OVER !!!\r\n");
                print("!!!!!!!!!!!!!!!!!\r\n");
                print("SCORE: ");
								print_idec(score);
                if(score != record){
                    print("RECORD: ");
										print_idec(record);
                }
            }
						Level = 1;
					  lost = 0;
						prevScore = 0;

							print("KEY SHORTCUTS: \r\n press 'p' to Restart \r\n press 'b' to Quit \r\n");
				}

				else{
					if (score%WINSCORE == 0 && score != 0 && prevScore != score){
								print("********************\r\n");
								print("****  LEVEL UP  ****\r\n");
								print("********************\r\n");
								print("PROMOTED TO LEVEL: ");
			          print_idec(Level);
							  prevScore = score;
							  LevelUpCheck = 1;
								print("KEY SHORTCUTS: \r\n press 'l' to Level Up  \r\n press 'p' to Restart \r\n press 'b' to Quit \r\n");


						}
				} 
				
				while(cont == 0);
				cont = 0 ; 
    
    return;
}

