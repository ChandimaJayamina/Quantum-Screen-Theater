#include "welcomescreen.h"
#include "show.h"



// Function definition
void welcome(void)
{
    printf("\n\n******** Welcome to Quantum Screen Theater ********\n\n");
    printf("Here are the options : \n");
    printf("a: Add Theatre Show\n");
    printf("b: Display Theatre Schedule\n");
    printf("c: Display Theatre Reservations\n");
    printf("d: Reserve Seats\n");
    printf("e: Exit\n\n");

    printf("Enter the option you like to proceed ");
    int validMenuSelect = 0;
    char character;
    do{
        scanf(" %c", &character); // Note the space before %c to consume any leftover newline
        printf("You entered: %c\n", character);
        toLowerString(&character);
        switch (character)
        {
            case 'a':
                printf("You have selected option a \n\n");
                // Add theatar show
                addTheatreShow();
                validMenuSelect = 1;
                break;
            case 'b':
                printf("You have selected option b \n\n");
                // Display Theatre Schedule
                displayTheatreSchedule();
                validMenuSelect = 1;
                break;
            case 'c':
                printf("You have selected option c \n\n");
                // Display Theatre Reservations
                displayTheatreReservation();
                validMenuSelect = 1;
                break;
            case 'd':
                printf("You have selected option d \n\n");
                // Reserve Seats
                reserveSeat();
                validMenuSelect = 1;
                break;
            case 'e':
                printf("You have selected option e \n\n");
                void exit(int status);
                validMenuSelect = 1;
                break;
            default:
                printf("You have selected wrong option please select an option given in menu\n\n");
        }
    }while (!validMenuSelect);
    
}


void toLowerString(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}
