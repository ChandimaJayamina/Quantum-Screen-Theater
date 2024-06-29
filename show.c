#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "show.h"

/*
    This function is defined to get lower case charater from any
*/
// int getPosition(char ch) {
//     // Convert character to uppercase to handle both cases
//     char upperCh = toupper(ch);

//     // Check if the character is a valid alphabet
//     if (upperCh >= 'A' && upperCh <= 'Z') {
//         return upperCh - 'A' + 1; // Calculate position
//     } else {
//         return -1; // Return -1 if not a valid alphabet character
//     }
// }


/*
    This function is defined to handle Add theter show to file 
*/
void addTheatreShow(void){
    printf("Came to addTheatreShow method\n");
    Show currentShow = {
        .hall = {
            .table = {
        {{"  "},{"01"},{"02"},{"03"},{"04"},{"05"},{"06"},{"07"},{"08"},{"09"},{"10"},{"11"},{"12"},{"13"},{"14"},{"15"},{"16"}},
        {{"A "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"B "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"C "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"D "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"E "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"F "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"G "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"H "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"I "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"J "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"K "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"L "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"M "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"N "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"O "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}},
        {{"P "},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"},{" *"}}
        }
        }
    };
    // asign seat -> currentShow.hall.table[1][1] = (seat){" #"};  A5
    // printf("Seat at Row 1, Seat 1: '%s'\n", currentShow.hall.table[1][1].str);
    
    /*
        Use to get show name
    */ 
    printf("Please enter the name of the show (max 49 characters): ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", currentShow.show_name_str);
    printf("You entered: %s\n", currentShow.show_name_str);

    /*
        Use to get show id
    */ 
    printf("Please enter the id of the show (max 49 characters): ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", currentShow.show_id_str);
    printf("You entered: %s\n", currentShow.show_id_str);

    /*
        Use to get date
    */ 
    // Prompt the user for input
    printf("Enter show date by year-month-date eg:2024-06-20: ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", currentShow.date);
    printf("You entered: %s\n", currentShow.date);

    /*
        Use to get time
    */ 
    // Prompt the user for input
    printf("Enter hours minutes and am/pm eg:8:30am : ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", currentShow.time);
    printf("You entered: %s\n", currentShow.time);

    /*
        Use to calculate revenue
    */
   currentShow.revenue = 0;

    /*  To do --------------------------------------------------------------------------------
    seat availableVIP[50];
    seat availableVVIP[50];
    seat availableEconomy[50];
    seat availableTwin[50];
    */

    /*
        Check is the time slot available by using regex pattern ≠–To do----------------------------------------------
    */
    if(checkTimeSlot("show_schedules.txt", currentShow.date, currentShow.time)){
        printf("Time slot not found");
        writeShowToFile("show_schedules.txt", &currentShow);
    }else{
        printf("Time slot found so not added the show to schedule");
    }
}



void displayTheatreSchedule(void){
    char check[15];
    /*
        Use to get show id
    */ 
    printf("Please enter the id of the show (max 49 characters): ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", check);
    printf("You entered: %s\n", check); 
    
    Show show;
    FILE *file = fopen("show_schedules.txt", "r+b");
    if (file == NULL) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }
    while (fread(&show, sizeof(Show), 1, file)) {
        if (strcmp(show.show_id_str, check) == 0) {
            printf("Show found\n");
            printHall(&show.hall);
        }
    }
    fclose(file);
}

void printHall(Theaterhall *hall) {
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            printf("%s ", hall->table[i][j].str);
        }
        printf("\n");
    }
}


void reserveSeat(void){

}



void displayTheatreReservation(void){

}






/*
    This function used in addTheater function to get the time slot availability
*/
int checkTimeSlot(const char *filename, const char *date, const char *time){
    FILE *file = fopen(filename, "r+b");
    if (file == NULL) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }
    Show show;
    printf("Checking %s %s", date,time);
    while (fread(&show, sizeof(Show), 1, file)) {
        printf("File found %s %s", show.date, show.time);
        if (strcmp(show.date, date) == 0 && strcmp(show.time, time) == 0) {
            return 0;
        }
    }
    fclose(file);
    return 1;
}
/*
    This function used in addTheater function to get the time slot availability
*/
void writeShowToFile(const char *filename, Show *show) {
    FILE *file = fopen(filename, "ab"); // Append mode to write multiple entries
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    
    fwrite(show, sizeof(Show), 1, file);

    fclose(file);
}

