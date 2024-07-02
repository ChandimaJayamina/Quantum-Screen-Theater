#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "show.h"

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
/*
    This function is defined to handle Add theter show to file 
*/
void addTheatreShow(void){
    printf("----- Add Theatre Show ----- \n");

    Show currentShow;
    initializeShow(&currentShow);

    /*
        Use to get show name
    */ 
    printf("Please enter the name of the show (max 49 characters): ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", currentShow.name);
    printf("You entered: %s\n", currentShow.name);

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
            // todo - for invalid selection let's show the current shows for that date and ask again?
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


    populateSeats(&currentShow);

    /*
        Check is the time slot available by using regex pattern 
    */
    if(checkTimeSlot("show_schedules.txt", currentShow.date, currentShow.time)){
        printf("Time slot is available!\n");
        printf("Adding show to the schedule.\n");
        writeShowToFile("show_schedules.txt", &currentShow);
    }else{
        printf("Time slot is already booked for another show.\n");
        // todo - Should we ask if they want to overide this time?
    }
}

/*
    This function is defined to give theater details to user by date
*/
void displayTheatreSchedule(void){
    printf("----- Display Theatre Schedule ----- \n");
    /*
        Use to get date
    */ 
    char date[15];
    // Prompt the user for input
    printf("Enter date in format YYYY-MM-DD eg:2024-06-20: ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", date);
    printf("You entered: %s\n", date); 
    // ------------------------------------- to do regex validate

    // Printing the output from the file
    FILE *file = fopen("show_schedules.txt", "r+b");
    if (file == NULL) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }

    Show show;
    Show matchingShows[5]; // Only 5 time slots are available per day.
    int count = 0;
    while (fread(&show, sizeof(Show), 1, file)) {
        if (strcmp(show.date, date) == 0) {
            if (count < 5) {
                matchingShows[count++] = show;
            } else {
                printf("Too many matching shows on this date; some may be omitted.\n");
                break;
            }
        }
    }

    if (count == 0) {
        printf("No shows found on this date!\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("\nShow : %s | Show ID : %s| Date : %s | Time : %s | Revenue : %d \n", show.name, show.id, show.date, show.time, show.revenue);
        }
    }

    fclose(file);
}

/*
    This function is defined to handle theter seat reservation by given show id
*/
void reserveSeat(void){
    char showId[15];
    printf("Please enter the show ID : ");
    scanf(" %[^\n]", showId); // todo - trim whitespace

    char requiredSeatNumber[3];  // maximum allowed seat bookings will be 340
    printf("Please enter number of seats required : ");
    scanf(" %[^\n]", requiredSeatNumber);

   
    // Define the array of seat category options
    char seatCategory[15];

    printf("Please enter the Desired seat category (VVIP, VIP, Twin, Economy') : ");
    scanf(" %[^\n]", seatCategory);
    // todo add validation for these

    FILE *file = getFile("r+b");
    Show show;
    long index = -1;
    while (fread(&show, sizeof(Show), 1, file)) {
        if (strcmp(show.id, showId) == 0) {
            printf("\nShow : %s | Show ID : %s| Date : %s | Time : %s | Revenue : %d \n", show.name, show.id, show.date, show.time, show.revenue);
            findAvailableSeats(&show.hall);
            index = ftell(file) - sizeof(Show);

            printAvailableSeats(&show, seatCategory);

            char seats[15];
            printf("Please enter the seats need to reserve seprated by comma (C5, E5): ");
            // Use scanf to read the input string until newline is encountered
            scanf(" %[^\n]", seats);
            printf("You entered: %s\n", seats); 
            
            char action[5];
            printf("Please enter the action need to add (#: reserve with pay, o: reserve without pay, x : cancel reservation ): ");
            // Use scanf to read the input string until newline is encountered
            scanf(" %[^\n]", action);
            printf("You entered: %s\n", action); 

            // Move existing characters to make space for an additional character
            memmove(action + 1, action, strlen(action) + 1);
            // Set the first character to a space
            action[0] = ' ';

            //Get the array position
            // Tokenize the line based on comma
            const int max_tokens = 200; //update with maximum for the type
            int row[max_tokens]; // Initialize row array with zeros
            int col[max_tokens]; // Initialize col array with zeros

            int i = 0;
            while(i < max_tokens){
                row[i] = 0;
                col[i] = 0;
                i++;
            }

            char *token;
            int token_count = 0;
            
            // Tokenize the seats string based on commas
            token = strtok(seats, ",");
            while (token != NULL && token_count < max_tokens) {
                parseSeat(token, &row[token_count], &col[token_count]);
                token_count++;
                token = strtok(NULL, ",");
                
                if(strcmp(seatCategory, "twin") == 0){
                    for (int i = 0; i < 22; ++i) {
                        if (strcmp(token, show.availableTwin[i].str) == 0) {
                            strcpy(show.availableTwin[i].str, "");
                            // todo allow only booking as doubles
                            show.revenue += 1000;
                            break;
                        }
                    }
                } else if(strcmp(seatCategory, "vvip") == 0){
                    for (int i = 0; i < 98; i++) {
                        if (strcmp(token, show.availableVVIP[i].str) == 0) {
                            strcpy(show.availableVVIP[i].str, "");
                            show.revenue += 5000;
                            break;
                        }
                    }
                } else if(strcmp(seatCategory, "vip") == 0){
                    for (int i = 0; i < 120; i++) {
                        if (strcmp(token, show.availableVIP[i].str) == 0) {
                            strcpy(show.availableVIP[i].str, "");
                            show.revenue += 2000;
                            break;
                        }
                    }
                } else if(strcmp(seatCategory, "economy") == 0){
                    for (int i = 0; i < 80; i++) {
                        if (strcmp(token, show.availableEconomy[i].str) == 0) {
                            strcpy(show.availableEconomy[i].str, "");
                            show.revenue += 500;
                            break;
                        }
                    }
                }
            }

            // Change seats if a valid index is provided
            if (index != -1) {
                for (int i = 0; i < token_count; ++i) {
                    int r = row[i];
                    int c = col[i];
                    strcpy(show.hall.table[r][c].str, action);
                }
                // Seek to the position of the struct to modify
                fseek(file, index, SEEK_SET);

                writeShowToFile("show_schedules.txt", &show);
            }

            printf("\nShow : %s | Show ID : %s| Date : %s | Time : %s | Revenue : %d \n", show.name, show.id, show.date, show.time, show.revenue);
            findAvailableSeats(&show.hall);
            break;
        }

        printf("No show available by this ID!");
    }
   
    fclose(file);
}

void findAvailableSeats(Theaterhall *hall) {
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 21; j++) {
            printf("%s ", hall->table[i][j].str);
        }
        printf("\n");
    }
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
    printf("You entered: %s\n", check); 
    // --- -----------------------------------to do remove spaces front and end
    
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
}


/*
    This function used in addTheater function to get the time slot availability
*/
int checkTimeSlot(const char *filename, const char *date, const char *time){
    FILE *file = fopen(filename, "r+b");
    if (file == NULL) {
        perror("Failed to open file for reading\n");
        exit(EXIT_FAILURE);
    }
    Show show;
    printf("Checking %s %s\n", date,time);
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
        for (int j = 0; j < 21; j++) {
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

/*
    This function is used for initialization of show
    to convert row and column integers to the seat string
*/
void formatSeat(int row, int col, char *seat) {
    // Convert the row number back to a character (1 -> A, 2 -> B, ..., 26 -> Z)
    seat[0] = 'A' + row - 1;
    // Convert the column number to a string and concatenate it
    sprintf(seat + 1, "%d", col);
    seat[4] = '\0'; // Ensure the seat string is null-terminated
}

/*
    Open and fetch file
*/
FILE* getFile(char *action) {
    FILE *file = fopen("show_schedules.txt", action);  // Open file in read-write mode
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    return file;
}

void populateSeats(Show *show) {
    int vipCount = 0, vvipCount = 0, economyCount = 0, twinCount = 0;

    for (int row = 1; row < ROWS; row++) {
        for (int col = 1; col < COLS; col++) {
            char seat[5];
            formatSeat(row, col, seat);

            if ((row == 0 || row == 1) && col >= 4 && col <= 14) {
                // Twin seats
                strcpy(show->availableTwin[twinCount++].str, seat);
            } else if (row <= 5) {
                // VVIP seats
                strcpy(show->availableVVIP[vvipCount++].str, seat);
            } else if (row <= 11) {
                // VIP seats
                strcpy(show->availableVIP[vipCount++].str, seat);
            } else {
                // Economy seats
                strcpy(show->availableEconomy[economyCount++].str, seat);
            }
        }
    }
}

void printAvailableSeats(Show *show, char *seatCategory){

    if(strcmp(seatCategory, "twin") == 0){
        printf("Available Twin seats:\n");
        for (int i = 0; i < 22; i++) {
            printf("%s ", show->availableTwin[i].str);
        }
        printf("\n");
        return;
    }

    if(strcmp(seatCategory, "vvip") == 0){
        printf("Available VVIP seats:\n");
        for (int i = 0; i < 98; i++) {
            printf("%s ", show->availableVVIP[i].str);
        }
        printf("\n");
        return;
    }

    if(strcmp(seatCategory, "vip") == 0){
        printf("Available VIP seats:\n");
        for (int i = 0; i < 120; i++) {
            printf("%s ", show->availableVIP[i].str);
        }
        printf("\n");
        return;
    }

    if(strcmp(seatCategory, "economy") == 0){
        printf("Available Economy seats:\n");
        for (int i = 0; i < 80; i++) {
            printf("%s ", show->availableEconomy[i].str);
        }
        printf("\n");
        return;
    }
}