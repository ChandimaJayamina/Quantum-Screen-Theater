#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "show.h"
#include "welcomescreen.h" 
#include "validations.h"

/*
    This function is defined to handle Add theter show to file 
*/
void addTheatreShow(void){
    printf("Came to addTheatreShow method\n");

    Show currentShow;
    initializeShow(&currentShow);

    /*
        Use to get show name
    */ 
    printf("Please enter the name of the show (max 49 characters): ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", currentShow.name);
    trimSpaces(currentShow.name);
    printf("You entered: %s\n", currentShow.name);

    /*
        Use to get date
    */ 
   do{
    // Prompt the user for input
    printf("Enter show date by year-month-date eg:2024-06-20: ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", currentShow.date);
    trimSpaces(currentShow.date);
    if(isValidDate(currentShow.date) == 0) {
        printf("%s is not a valid date.\n", currentShow.date);

     }
    } while (isValidDate(currentShow.date) == 0);

      printf("You entered: %s\n", currentShow.date);

    /*
        Use to get time
    */ 
    TimeSlot selectedSlot;
    // Display available time slots
    printf("Please select Time Slot:\n");
    printf("1. %s\n", timeSlotToString(SLOT_1));
    printf("2. %s\n", timeSlotToString(SLOT_2));
    printf("3. %s\n", timeSlotToString(SLOT_3));
    printf("4. %s\n", timeSlotToString(SLOT_4));
    printf("5. %s\n", timeSlotToString(SLOT_5));
    // Prompt user to select a time slot
    printf("Select a time slot (1-5): ");
    int choice;
    scanf("%d", &choice);
    // Validate user input
    switch(choice) {
        case 1: selectedSlot = SLOT_1; break;
        case 2: selectedSlot = SLOT_2; break;
        case 3: selectedSlot = SLOT_3; break;
        case 4: selectedSlot = SLOT_4; break;
        case 5: selectedSlot = SLOT_5; break;
        default:
            printf("Invalid selection. goes with slot1");
            selectedSlot = SLOT_1;
    }

    // Display selected time slot
    sprintf(currentShow.time, "%s",
            timeSlotToString(selectedSlot));
    printf("You selected: %s\n", currentShow.time);
    
    /*
        Use to get show id
    */ 
    sprintf(currentShow.id, "[%s_%s_%s]",
            currentShow.name,
            currentShow.date, currentShow.time);
    printf("ID : %s\n", currentShow.id);
    
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
        Check is the time slot available by using regex pattern 
    */
    if(checkTimeSlot("show_schedules.txt", currentShow.date, currentShow.time)){
        printf("Time slot not found");
        writeShowToFile("show_schedules.txt", &currentShow);
    }else{
        printf("Time slot found so not added the show to schedule");
    }
    goToMainPage();
}

/*
    This function is defined to give theater details to user by date
*/
void displayTheatreSchedule(void){
    /*
        Use to get date
    */ 
    char date[15];
    do{
    // Prompt the user for input
    printf("Enter date by year-month-date eg:2024-06-20: ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", date);
    trimSpaces(date);

    if(isValidDate(date) == 0) {
        printf("%s is not a valid date.\n", date);
    }
    } while (isValidDate(date) == 0);

    printf("You entered: %s\n", date); 
    // ------------------------------------- to do regex validate

    // Printing the output from the file
    FILE *file = fopen("show_schedules.txt", "r+b");
    if (file == NULL) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }
    Show show;

    while (fread(&show, sizeof(Show), 1, file)) {
        printf("File found %s %s", show.date, show.time);
        if (strcmp(show.date, date) == 0) {
            printf("\nShow : %s | Show ID : %s| Date : %s | Time : %s | Revenue : %d \n", show.name, show.id, show.date, show.time, show.revenue);
        }
    }
    fclose(file);
    goToMainPage();
}

/*
    This function is defined to handle theter seat reservation by given show id
*/
void reserveSeat(void){
    /*
        Use to get show id
    */ 
    char showId[15];
    printf("Please enter the id of the show (max 49 characters) to reserve seat : ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", showId);
    trimSpaces(showId);
    printf("You entered: %s\n", showId); 

    // Display Available Seats ---------------------------------------- todo
    FILE *file = fopen("show_schedules.txt", "r+b");  // Open file in read-write mode
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    Show show;
    long index = -1;
    while (fread(&show, sizeof(Show), 1, file)) {
        if (strcmp(show.id, showId) == 0) {
            printf("Show found\n");
            index = ftell(file) - sizeof(Show);
            break;
        }
    }
    printf("show date %s\n", show.date);
    printf("A1 seat : %s", show.hall.table[1][1].str);
    /*
        Use to get seat category
    */ 
    char seatCategory[15];
    printf("Please enter the Desired seat category (VVIP, VIP, Twin, Economy) : ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", seatCategory);
    printf("You entered: %s\n", seatCategory);

    // ---------------------------------------- print the available seats for the given category

    /*
        Use to get number of seatsss
    */ 
    int numberofSeats;
    printf("Please enter the  number of seats required: ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %d", &numberofSeats);
    printf("You entered: %d\n", numberofSeats); 


    /*
        Use to get seats
    */ 
    char seats[15];
    printf("Please enter the seats need to reserve by comma seperate (C5, E5): ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", seats);
    printf("You entered: %s\n", seats); 

     /*
        Use to get seat action
    */ 
    char action[5];
    toLowerString(action);
    printf("Please enter the action need to add (#: reserve with pay, o: reserve without pay, x : cancel reservation ): ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", action);
    printf("You entered: %s\n", action); 
    if ( strcmp(action, "#") == 0 ) {
        printf("Action is: reserve with pay\n");
    } else if (strcmp(action, "o") == 0 ){
        printf("Action is: reserve without pay\n");
    }else{
        printf("Cancel the reservation");
        goToMainPage();
    }
    // Move existing characters to make space for an additional character
    memmove(action + 1, action, strlen(action) + 1);
    // Set the first character to a space
    action[0] = ' ';



    //Get the array position
    // Tokenize the line based on comma
    int MAX_TOKENS = 7;                                     // ----------------------------need to change according to maximum seats for VIP or others
    char *token;
    int token_count = 0;
    char *tokens[MAX_TOKENS]; // Array to hold tokens
    int row[MAX_TOKENS], col[MAX_TOKENS]; // Add rows and cols to change
    int i = 0;
    while (i < MAX_TOKENS) { // Stop the loop if a 0 is encountered
            row[i] = 0;
            col[i] = 0;
            i++;
    }
    // Get the first token
    token = strtok(seats, ",");
    while (token != NULL && token_count < MAX_TOKENS) {
        // Store the token in the tokens array
        parseSeat(token, &row[token_count], &col[token_count]);
        printf("Token :%s\n", token);
        tokens[token_count++] = token;
        // Get next token
        token = strtok(NULL, ",");
    }
    printf("Index %ld\n", index);
    //Change seat
    if (index != -1) {
        printf("Before for loop\n");
        int i = 0;
        for (int i = 0; i < token_count; ++i) {
            int r = row[i];
            int c = col[i];
            strcpy(show.hall.table[r][c].str, action);
        }
        printf("Before for loop\n");
        // Seek to the position of the struct to modify
        fseek(file, index, SEEK_SET);
        printf("Before for loop\n");
        // Write the modified struct back to the file
        if (fwrite(&show, sizeof(Show), 1, file) != 1) {
            perror("Error writing to file");
        } else {
            printf("Write Success\n");
        }
    }
    fclose(file);
    goToMainPage();
}

/*
    This function is defined to handle Display theter reservation by given show id
*/
void displayTheatreReservation(void){
    char check[15];
    /*
        Use to get show id
    */ 
    printf("Please enter the id of the show (max 49 characters): ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", check);
    trimSpaces(check);
    printf("You entered: %s\n", check); 
    
    Show show;
    FILE *file = fopen("show_schedules.txt", "r+b");
    if (file == NULL) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }
    int flagFound = 1;
    while (fread(&show, sizeof(Show), 1, file)) {
        if (strcmp(show.id, check) == 0) {
            printf("Show found\n");
            flagFound = 0;
            printHall(&show.hall);
        }
    }
    if(flagFound){
        printf("Show not found\n");
    }
    fclose(file);
    goToMainPage();
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
/*
    This function is used by Display theter reservation by given show id
*/
void printHall(Theaterhall *hall) {
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            printf("%s ", hall->table[i][j].str);
        }
        printf("\n");
    }
}
/*
    This function is used by reserve seat function
*/
int charToNumber(char c) {
    return c - 'A' + 1;
}
/*
    This function is used by reserve seat function
*/
void removeWhiteSpacesandCapitalize(char *str) {
    char *p1 = str, *p2 = str;
    while (*p2 != '\0') {
        if (!isspace((unsigned char)*p2)) {
            *p1++ = *p2;
        }
        p2++;
    }
    *p1 = '\0';
    if (islower((unsigned char)str[0])) {
        str[0] = toupper((unsigned char)str[0]);
    }
}
/*
    This function is used by reserve seat function
    Function to convert a seat string (e.g., "A14") into row and column integers
*/
void parseSeat(char *seat, int *row, int *col) {
    removeWhiteSpacesandCapitalize(seat);       // Remove any white spaces from the seat string
    // Convert the row character to an integer (A -> 1, B -> 2, ..., Z -> 26)
    *row = seat[0] - 'A' + 1;
    // Convert the remaining part of the seat string to an integer for the column
    *col = atoi(seat + 1);
}

// This is used to lower the string inputs
void toLowerString(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

// Creation of 2D array
void initializeShow(Show *show) {
    // Initialize first row with numbers
    for (int j = 0; j < COLS; j++) {
        if (j == 0) {
            snprintf(show->hall.table[0][j].str, sizeof(show->hall.table[0][j].str), "  ");
        } else {
            snprintf(show->hall.table[0][j].str, sizeof(show->hall.table[0][j].str), "%02d", j);
        }
    }

    // Initialize subsequent rows with letters and '*'
    for (int i = 1; i < ROWS; i++) {
        snprintf(show->hall.table[i][0].str, sizeof(show->hall.table[i][0].str), "%c ", 'A' + (i - 1));
        for (int j = 1; j < COLS; j++) {
            snprintf(show->hall.table[i][j].str, sizeof(show->hall.table[i][j].str), " *");
        }
    }
}
// Function to convert TimeSlot enum to string
const char* timeSlotToString(TimeSlot slot) {
    switch(slot) {
        case SLOT_1: return "10:00 AM";
        case SLOT_2: return "12:00 PM";
        case SLOT_3: return "02:30 PM";
        case SLOT_4: return "04:00 PM";
        case SLOT_5: return "06:00 PM";
        default: return "Unknown";
    }
}

// Function to remove leading and trailing spaces
void trimSpaces(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    // All spaces?
    if (*str == 0) {
        str[0] = '\0';
        return;
    }

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';
}

//Function to redirect main page
void goToMainPage(void){ 
    char character;
    printf("\nPlease select one option \n 1: main page press M \n 2: quit press Q \n:");
    scanf(" %c", &character);  // Note the space before %c to consume any leftover newline
    switch (tolower(character)) {
        case 'm':
            printf("You will redirect to main page \n\n");
            welcome();
            break;
        case 'q':
            printf("Exit from application \n\n");
            break;
        default:
            printf("You have selected wrong option redirect to main menu\n\n");
            restart_program();
    }
}

void restart_program() {
    // Get the current program name and arguments
    char *argv[] = { "./app", NULL };
    
    // Replace the current process with a new instance of the same program
    execvp(argv[0], argv);
    
    // If execvp returns, it must have failed
    perror("execvp");
    exit(EXIT_FAILURE);
}
