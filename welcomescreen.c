#include "welcomescreen.h" 
#include "show.h"

char character;


// User option categarizer
void operationIdentifier(void){
    switch (tolower(character)) {
        case 'a':
            printf("You have selected option a \n\n");
            addTheatreShow();
            break;
        case 'b':
            printf("You have selected option b \n\n");
            //Display Theatre Schedule
            break;
        case 'c':
            printf("You have selected option c \n\n");
            //Display Theatre Reservations
            break;
        case 'd':
            printf("You have selected option d \n\n");
            //Reserve Seats
            break;
        case 'e':
            printf("You have selected option e \n\n");
            void exit(int status);
            break;
        case 'f':
            printf("You have selected option f \n\n");
            initializeShowFromFile();
            break;
        default:
            printf("You have selected wrong option please select an option given in menu\n\n");
            scanf(" %c", &character);
            operationIdentifier();
    }
}


// Function definition
void welcome(void) {
    printf("\n\n******** Welcome to Quantum Screen Theater ********\n\n");
    printf("Here are the options : \n");
    printf("a: Add Theatre Show\n");
    printf("b: Display Theatre Schedule\n");
    printf("c: Display Theatre Reservations\n");
    printf("d: Reserve Seats\n");
    printf("e: Exit\n\n");
    
    printf("Enter the option you like to proceed ");
    scanf(" %c", &character);  // Note the space before %c to consume any leftover newline
    printf("You entered: %c\n", character);

    operationIdentifier();
    

}