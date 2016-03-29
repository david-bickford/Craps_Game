/* 
 * File:   craps.c
 * Author: David Bickford
 * Email: drb56@pitt.edu
 *
 */
//various imports used
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/* randomRoll function
 * This function takes a file parameter and reads from the driver
 * 
 * @param: integer of a file
 * @return: random integer
 */
int randomRoll(int file)
{
    //new char variable
    char c = 0;
    //reads from a file
    read(file, &c, 1);
    //returns an integer casted character
    return (int)c;
}

/* main function
 */
int main() 
{
    //opening the device driver as read only
    int fd = open("/dev/dice", O_RDONLY);
    //various variables used
    int dice1 = 0;
    int dice2 = 0;
    int point = 0;
    int played = 0;
    int diceTotal = 0;
    int playing = 0;
    int won = 0;
    char userName[30];
    char userInput[15];
    //prints and scans the first messages and user input
    printf("Welcome to Dave's Casino!\n");
    printf("Please enter your name: ");
    scanf("%s", &userName);
    printf("\n");
    printf("%s, would you like to Play or Quit? ", userName);
    scanf("%s", &userInput);
    printf("\n");
    printf("\n");

    //sets playing to 0 if the user wants to play and 1 if the user wants
    //to quit.
    if(strncmp(userInput, "play", strlen(userInput)) == 0)
    {
        playing = 0;
    }
    else if(strncmp(userInput, "quit", strlen(userInput)) == 0)
    {
        playing = 1;
    }
    //while loop to continue if the playing variable is 0
    while(playing == 0)
    {
        //calling the randomRoll function and setting the value returned +1 to
        //its respective dice number.
        dice1 = randomRoll(fd) + 1;
        dice2 = randomRoll(fd) + 1;
        diceTotal = dice1 + dice2;
        //resetting the userInput
        strncpy(userInput, "", 15);
        //prints the dice rolls and dice rolls added up to user
        printf("You have rolled %d + %d = %d\n", dice1, 
                dice2, diceTotal);
        //if/else if to check if the user automatically wins or loses when 
        //played variable = 0.
        if(played == 0 && (diceTotal == 7 || diceTotal == 11))
        {
            printf("You Win!\n\n");
            won = 1;
        }
        else if(played == 0 && (diceTotal == 2 || 
                diceTotal == 3 || diceTotal == 12))
        {
            printf("You Lose!\n\n");
            won = 2;
        }
        else if(played == 0)
        {
            point = diceTotal;
            won = 0;
        }
        //if/else if to check if the user has more than 1 rolls and if they 
        //haven't won yet.
        if(played > 0 && won == 0)
        {
            //if/else if to check if the diceTotal is equal to the point
            if(diceTotal == point)
            {
                printf("You Win!\n\n");
                won = 1;
            }
            else if(diceTotal == 7)
            {
                printf("You Lose!\n\n");
                won = 2;
            }
            else
            {
                point = diceTotal;
                won = 0;
            }
        }
        //if/else if to ask the user if they want to play again if they 
        //win or lose the game.
        if(won == 1 || won == 2)
        {
            printf("Would you like to play again? ");
            scanf("%s", &userInput);
            printf("\n");
            printf("\n");
            //if/else if to check if the user inputs yes or no to continue game
            if(strncmp(userInput, "no", strlen(userInput)) == 0)
            {
                playing = 1;
                printf("Goodbye, %s\n", userName);
                break;
            }
            else if(strncmp(userInput, "yes", strlen(userInput)) == 0)
            {
                won = 0;
                playing = 0;
                played = 0;
                strncpy(userInput, "", 15);
            }
        }
        else if(won == 0)
        {
            played++;
        }
    }
    return 0;
}

