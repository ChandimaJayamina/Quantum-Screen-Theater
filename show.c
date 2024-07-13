#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "show.h"
#include "welcomescreen.h"
#include "validations.h"

/*
    This function is defined to handle adding a theater show to the file.
*/
void addTheatreShow(void)
{
    printf("----- Add Theatre Show ----- \n");

    Show currentShow;
    initializeShow(&currentShow);

    // Get show name
    printf("Please enter the name of the show (max 49 characters): ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", currentShow.name);
    trimSpaces(currentShow.name);
    printf("You entered: %s\n", currentShow.name);

    // Get date
    do
    {
        // Prompt the user for input
        printf("Enter date in format YYYY-MM-DD eg:2024-06-20: ");
        // Use scanf to read the input string until newline is encountered
        scanf(" %[^\n]", currentShow.date);
        trimSpaces(currentShow.date);
        if (isValidDate(currentShow.date) == 0)
        {
            printf("%s is not a valid date.\n", currentShow.date);
        }
    } while (isValidDate(currentShow.date) == 0);

    printf("You entered: %s\n", currentShow.date);

    // Get time slot
    TimeSlot selectedSlot;
    // Display available time slots
    printf("Please select Time Slot:\n");
    printf("1. %s\n", timeSlotToString(SLOT_1));
    printf("2. %s\n", timeSlotToString(SLOT_2));
    printf("3. %s\n", timeSlotToString(SLOT_3));
    printf("4. %s\n", timeSlotToString(SLOT_4));
    printf("5. %s\n", timeSlotToString(SLOT_5));
    printf("6. Go to main menu \n");
    // Prompt user to select a time slot
    int choice;
    int checkForFileWrite = 0;
    do
    {
        int validSelection = 0;
        do
        {
            printf("Select a time slot (1-5): ");
            scanf("%d", &choice);
            // Validate user input
            switch (choice)
            {
            case 1:
                selectedSlot = SLOT_1;
                validSelection = 1;
                break;
            case 2:
                selectedSlot = SLOT_2;
                validSelection = 1;
                break;
            case 3:
                selectedSlot = SLOT_3;
                validSelection = 1;
                break;
            case 4:
                selectedSlot = SLOT_4;
                validSelection = 1;
                break;
            case 5:
                selectedSlot = SLOT_5;
                validSelection = 1;
                break;
            case 6:
                goToMainPage();
                return;
            default:
                printf("Invalid selection. Try again.\n");
            }
        } while (!validSelection);
        // Display selected time slot
        sprintf(currentShow.time, "%s", timeSlotToString(selectedSlot));
        printf("You selected: %s\n", currentShow.time);

        // Check if the time slot is available
        if (checkTimeSlot("show_schedules.txt", currentShow.date, currentShow.time))
        {
            checkForFileWrite = 1;
        }
        else
        {
            printf("\nThere is a show for the given time slot. Please check another time slot. Here are the shows for the given date:\n");
            displayTheatreScheduleForDate(currentShow.date);
        }
    } while (!checkForFileWrite);

    // Generate show ID
    sprintf(currentShow.id, "[%s_%s_%s]", currentShow.name, currentShow.date, currentShow.time);
    printf("ID: %s\n", currentShow.id);

    // Initialize show revenue
    currentShow.revenue = 0;

    // Initialize seats
    initializeSeats(currentShow.availableTwin, sizeof(currentShow.availableTwin) / sizeof(currentShow.availableTwin[0]));
    initializeSeats(currentShow.availableVVIP, sizeof(currentShow.availableVVIP) / sizeof(currentShow.availableVVIP[0]));
    initializeSeats(currentShow.availableVIP, sizeof(currentShow.availableVIP) / sizeof(currentShow.availableVIP[0]));
    initializeSeats(currentShow.availableEconomy, sizeof(currentShow.availableEconomy) / sizeof(currentShow.availableEconomy[0]));
    populateSeats(&currentShow);

    // Write show to file if time slot is available
    if (checkForFileWrite)
    {
        printf("\nShow successfully added to schedule.\n");
        writeShowToFile("show_schedules.txt", &currentShow);
    }
    else
    {
        printf("\nError occurred when adding the show.\n");
    }
    goToMainPage();
}

/*
    This function is defined to give theater details to the user by date.
*/
void displayTheatreSchedule(void)
{
    printf("----- Display Theatre Schedule ----- \n");
    // Get date
    char date[15];
    do
    {
        // Prompt the user for input
        printf("Enter date in format YYYY-MM-DD eg:2024-06-20: ");
        // Use scanf to read the input string until newline is encountered
        scanf(" %[^\n]", date);
        trimSpaces(date);

        if (isValidDate(date) == 0)
        {
            printf("%s is not a valid date.\n", date);
        }
    } while (isValidDate(date) == 0);

    printf("You entered: %s\n", date);

    // Print the schedule from the file
    FILE *file = fopen("show_schedules.txt", "r+b");
    if (file == NULL)
    {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }
    Show show;
    int found = 0;
    while (fread(&show, sizeof(Show), 1, file))
    {
        if (strcmp(show.date, date) == 0)
        {
            printf("\nShow: %s | Show ID: %s | Date: %s | Time: %s | Revenue: %d \n", show.name, show.id, show.date, show.time, show.revenue);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No shows found for the specified date.\n");
    }
    fclose(file);
    goToMainPage();
}

/*
    This function is defined to handle theter seat reservation by given show id
*/
void reserveSeat(void)
{
    printf("----- Reserve Seat ----- \n");
    // Use to get show id
    char showId[15];
    printf("Please enter the show ID: ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %[^\n]", showId);
    trimSpaces(showId);
    printf("You entered: %s\n", showId);

    FILE *file = fopen("show_schedules.txt", "r+b"); // Open file in read-write mode
    if (file == NULL)
    {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    Show show;
    long index = -1;
    while (fread(&show, sizeof(Show), 1, file))
    {
        if (strcmp(show.id, showId) == 0)
        {
            printf("Show found\n");
            index = ftell(file) - sizeof(Show);
            break;
        }
    }

    // Use to get seat category
    char seatCategory[15];
    int validSelection = 0;
    do
    {
        printf("Please enter the desired seat category (VVIP, VIP, Twin, Economy): ");
        scanf(" %[^\n]", seatCategory);
        trimSpaces(seatCategory);
        toLowerString(seatCategory);
        // Validate user input
        validSelection = printAvailableSeats(&show, seatCategory);
    } while (!validSelection);
    printf("You entered: %s\n", seatCategory);

    //  Use to get number of seats
    int numberofSeats;
    printf("Please enter the number of seats required: ");
    // Use scanf to read the input string until newline is encountered
    scanf(" %d", &numberofSeats);
    printf("You entered: %d\n", numberofSeats);

    //  Use to get seats and validate those seats
    int seatValidation = 0;
    char checkseats[300];
    int MAX_TOKENS = 120; // Tokenize the line based on comma
    char *token;
    int token_count;
    char *tokens[MAX_TOKENS];             // Array to hold tokens
    int row[MAX_TOKENS], col[MAX_TOKENS]; // Add rows and cols to change
    int rowCounter;
    int userSeatConfirmation = 0; // Use to get confirmation of seats reservation before writing those to file
    int userChoice;
    char twinrow;
    int twincol;
    char nextSeat[5];
    do
    {
        if (strcmp(seatCategory, "twin") == 0)
        {
            printf("Since you need a twin seat, take note that booking one will select the pair! ");
        }
        printf("Please enter the seats need to reserve by comma separate (C5, E5): ");
        // Use scanf to read the input string until newline is encountered
        scanf(" %[^\n]", checkseats);
        printf("You entered: %s\n", checkseats);
        printf("Check for the seats availability for reservation ..............\n");
        token_count = 0;

        rowCounter = 0;
        while (rowCounter < MAX_TOKENS)
        { // Stop the loop if a 0 is encountered
            row[rowCounter] = 0;
            col[rowCounter] = 0;
            rowCounter++;
        }
        // Get the first token
        token = strtok(checkseats, ",");
        while (token != NULL && token_count < MAX_TOKENS)
        {
            // Check seat availability in array
            seatValidation = seatsAvailabiltyCheck(token, &show, seatCategory);
            // Store the token in the tokens array
            if (seatValidation)
            {
                if (strcmp(seatCategory, "twin") == 0)
                {
                    parseSeat(token, &row[token_count], &col[token_count]);
                    tokens[token_count++] = strdup(token);
                    // Parse the current seat into row and number
                    sscanf(token, "%c%d", &twinrow, &twincol);
                    twincol++;
                    // Format the next seat string
                    snprintf(nextSeat, 5, "%c%d", twinrow, twincol);
                    parseSeat(nextSeat, &row[token_count], &col[token_count]);
                    tokens[token_count++] = strdup(nextSeat);
                }
                else
                {
                    parseSeat(token, &row[token_count], &col[token_count]);
                    // Token is added to que
                    tokens[token_count++] = token;
                }
            }
            // Get next token
            token = strtok(NULL, ",");
        }
        if (token_count > 0)
        {
            printf("You can reserve only ");
            for (int i = 0; i < token_count; i++)
            {
                printf("%s, ", tokens[i]);
            }
            printf("\n1: Confirm seats for reservation\n");
            printf("2: Try again choose seats\n");
        }
        else
        {
            printf("\nThere are no seats available from given seats");
            printf("2: Try again choose seats\n");
            printf("3: exit to main page\n");
        }
        printf("\n");
        userChoice = 0;
        scanf(" %d", &userChoice);
        printf("You entered: %d\n", userChoice);
        if (userChoice == 1 && token_count > 0)
        {
            userSeatConfirmation = 1;
        }
        else if (userChoice == 3)
        {
            if (strcmp(seatCategory, "twin") == 0){
                for (int i = 0; i < token_count; i++)
                {
                    free(tokens[i]); // Free the allocated memory for each token
                }
            }
            goToMainPage();
        }
        else
        {
            userSeatConfirmation = 0;
            for (int i = 0; i < token_count; i++)
            {
                free(tokens[i]); // Free the allocated memory for each token
            }
        }
    } while (!userSeatConfirmation);

    /*
        Use to get seat action
    */
    char action[5];
    printf("Please enter the action you need (#: Reserve with pay, o: Reserve without pay, x: Cancel reservation): ");
    // Use scanf to read the input string until newline is encountered
    int actionValidateFlag = 0;
    do{
        scanf(" %[^\n]", action);
        toLowerString(action);
        printf("You entered: %s\n", action);
        if (strcmp(action, "#") == 0)
        {
            printf("Action is: Reserve with pay\n");
            if (strcmp(seatCategory, "vvip") == 0)
            {
                show.revenue += token_count * 5000;
            }
            else if (strcmp(seatCategory, "vip") == 0)
            {
                show.revenue += token_count * 2000;
            }
            else if (strcmp(seatCategory, "twin") == 0)
            {
                show.revenue += token_count * 1000;
            }
            else if (strcmp(seatCategory, "economy") == 0)
            {
                show.revenue += token_count * 500;
            }
            actionValidateFlag = 1;
        }
        else if (strcmp(action, "o") == 0 || strcmp(action, "0") == 0)
        {
            strcpy(action, "o");
            printf("Action is: Reserve without pay\n");
            actionValidateFlag = 1;
        }
        else if (strcmp(action, "x") == 0)
        {
            printf("Action is: Cancel reservation\n");
            if (strcmp(seatCategory, "twin") == 0)
            {
                for (int i = 0; i < token_count; i++)
                {
                    free(tokens[i]); // Free the allocated memory for each token
                }
            }
            goToMainPage();
        }
        else
        {
            printf("Character wasn't recognized");
        }
    } while(!actionValidateFlag);
    // Move existing characters to make space for an additional character
    memmove(action + 1, action, strlen(action) + 1);
    // Set the first character to a space
    action[0] = ' ';

    // Change seats in thater
    if (index != -1)
    {
        for (int i = 0; i < token_count; ++i)
        {
            int r = row[i];
            int c = col[i];
            strcpy(show.hall.table[r][c].str, action);
        }
        // Remove seats from available seats array
        for (int i = 0; i < token_count; ++i)
        {
            if (strcmp(seatCategory, "vvip") == 0)
            {
                removeSeatFromAvailableSeats(show.availableVVIP, 98, tokens[i]);
            }
            else if (strcmp(seatCategory, "vip") == 0)
            {
                removeSeatFromAvailableSeats(show.availableVIP, 120, tokens[i]);
            }
            else if (strcmp(seatCategory, "twin") == 0)
            {
                removeSeatFromAvailableSeats(show.availableTwin, 22, tokens[i]);
                i++; // Skip the next seat in the pair
            }
            else if (strcmp(seatCategory, "economy") == 0)
            {
                removeSeatFromAvailableSeats(show.availableEconomy, 80, tokens[i]);
            }
        }
        // Seek to the position of the struct to modify
        fseek(file, index, SEEK_SET);
        // Write the modified struct back to the file
        if (fwrite(&show, sizeof(Show), 1, file) != 1)
        {
            perror("Error writing to file");
        }
        else
        {
            printf("Write Success\n");
        }
    }
    fclose(file);
    if (strcmp(seatCategory, "twin") == 0)
    {
        for (int i = 0; i < token_count; i++)
        {
            free(tokens[i]); // Free the allocated memory for each token
        }
    }
    goToMainPage();
}

/*
    Function to remove a specific seat from an array of seats
*/
void removeSeatFromAvailableSeats(Seat *array, int size, char *seat)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(array[i].str, seat) == 0)
        {
            // Shift elements to the left to remove the seat
            for (int j = i; j < size - 1; j++)
            {
                strcpy(array[j].str, array[j + 1].str);
            }

            // Clear the last element
            strcpy(array[size - 1].str, "");
            break;
        }
    }
}

/*
    Function to display theater reservation details for a given show ID
*/
void displayTheatreReservation(void)
{
    char check[50];

    // Get show ID from user input
    printf("Please enter the ID of the show (max 49 characters): ");
    scanf(" %[^\n]", check);
    trimSpaces(check);
    printf("You entered: %s\n", check);

    Show show;
    FILE *file = fopen("show_schedules.txt", "r+b");
    if (file == NULL)
    {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }
    int showFound = 0;
    // Search for the show in the file
    while (fread(&show, sizeof(Show), 1, file))
    {
        if (strcmp(show.id, check) == 0)
        {
            printf("Show found\n");
            showFound = 1;
            printHall(&show.hall); // Print the seating hall for the show
            break;
        }
    }
    if (!showFound)
    {
        printf("Show not found\n");
    }
    fclose(file);
    goToMainPage(); // Redirect user to the main menu
}

/*
    Function to check if a given time slot is available on a specific date from a file
*/
int checkTimeSlot(const char *filename, const char *date, const char *time)
{
    FILE *file = fopen(filename, "r+b");
    if (file == NULL)
    {
        perror("Failed to open file for reading\n");
        exit(EXIT_FAILURE);
    }
    Show show;
    printf("Checking %s %s\n", date, time);
    // Check each show in the file for matching date and time
    while (fread(&show, sizeof(Show), 1, file))
    {
        if (strcmp(show.date, date) == 0 && strcmp(show.time, time) == 0)
        {
            fclose(file);
            return 0; // Time slot found
        }
    }
    fclose(file);
    return 1; // Time slot not found
}

/*
    Function to write a show's details to a file
*/
void writeShowToFile(const char *filename, Show *show)
{
    FILE *file = fopen(filename, "ab"); // Append mode to write multiple entries
    if (file == NULL)
    {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fwrite(show, sizeof(Show), 1, file); // Write show details to file

    fclose(file);
}

/*
    Function to print the seating hall layout
*/
void printHall(Theaterhall *hall)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%s ", hall->table[i][j].str); // Print each seat in the hall
        }
        printf("\n");
    }
}

/*
    Function to convert a character representing a row (A-Z) to a corresponding number (1-26)
*/
int charToNumber(char c)
{
    return c - 'A' + 1;
}

/*
    Function to remove white spaces from a string and capitalize the first character
*/
void removeWhiteSpacesandCapitalize(char *str)
{
    char *p1 = str, *p2 = str;
    // Remove white spaces
    while (*p2 != '\0')
    {
        if (!isspace((unsigned char)*p2))
        {
            *p1++ = *p2;
        }
        p2++;
    }
    *p1 = '\0'; // Add null terminator at the end
    // Capitalize the first character if it's a lowercase letter
    if (islower((unsigned char)str[0]))
    {
        str[0] = toupper((unsigned char)str[0]);
    }
}

/*
    This function is used by reserve seat function
    Function to convert a seat string (e.g., "A14") into row and column integers
*/
void parseSeat(char *seat, int *row, int *col)
{
    // Remove any white spaces from the seat string
    removeWhiteSpacesandCapitalize(seat);

    // Convert the row character to an integer (A -> 1, B -> 2, ..., Z -> 26)
    *row = seat[0] - 'A' + 1;

    // Convert the remaining part of the seat string to an integer for the column
    *col = atoi(seat + 1);
}

/*
    This is used to convert the string to lower case inputs
*/
void toLowerString(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

/*
    Function to initialize the seating layout of a show
*/
void initializeShow(Show *show)
{
    // Initialize first row with column numbers
    for (int j = 0; j < COLS; j++)
    {
        if (j == 0)
        {
            snprintf(show->hall.table[0][j].str, sizeof(show->hall.table[0][j].str), "  "); // Header for row and column
        }
        else
        {
            snprintf(show->hall.table[0][j].str, sizeof(show->hall.table[0][j].str), "%02d", j); // Column numbers
        }
    }

    // Initialize subsequent rows with row letters and '*' for each seat
    for (int i = 1; i < ROWS; i++)
    {
        snprintf(show->hall.table[i][0].str, sizeof(show->hall.table[i][0].str), "%c ", 'A' + (i - 1)); // Row letters
        for (int j = 1; j < COLS; j++)
        {
            snprintf(show->hall.table[i][j].str, sizeof(show->hall.table[i][j].str), " *"); // Seat indicator
        }
    }
}

/*
    Function to convert TimeSlot enum to string representation
*/
const char *timeSlotToString(TimeSlot slot)
{
    switch (slot)
    {
    case SLOT_1:
        return "10:00 AM";
    case SLOT_2:
        return "12:00 PM";
    case SLOT_3:
        return "02:30 PM";
    case SLOT_4:
        return "04:00 PM";
    case SLOT_5:
        return "06:00 PM";
    default:
        return "Unknown";
    }
}

/*
    Function to remove leading and trailing spaces from a string
*/
void trimSpaces(char *str)
{
    char *end;

    // Trim leading spaces
    while (isspace((unsigned char)*str))
        str++;

    // All spaces?
    if (*str == '\0')
    {
        return; // String is all spaces
    }

    // Trim trailing spaces
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    // Null-terminate the trimmed string
    end[1] = '\0';
}

/*
    Function to redirect to the main page or exit the application.
*/
void goToMainPage(void)
{
    char character;
    printf("\nPlease select one option \n M: To main page  \n Q: Exit  \n:");
    scanf(" %c", &character); // Note the space before %c to consume any leftover newline

    switch (tolower(character))
    {
    case 'm':
        printf("You will be redirected to the main page \n\n");
        welcome();
        break;
    case 'q':
        printf("Exiting the application \n\n");
        break;
    default:
        printf("Invalid option selected, redirecting to main menu\n\n");
        restart_program();
    }
}

/*
    This function restarts the current program.
*/
void restart_program()
{
    // Get the current program name and arguments
    char *argv[] = {"./app", NULL};

    // Replace the current process with a new instance of the same program
    execvp(argv[0], argv);

    // If execvp returns, it must have failed
    perror("execvp");
    exit(EXIT_FAILURE);
}

/*
    This function is used by addTheater to display the schedule of shows for a given date.
*/
void displayTheatreScheduleForDate(const char *date)
{
    printf("Check the Shows for Date: %s\n", date);

    // Open the file containing show schedules
    FILE *file = fopen("show_schedules.txt", "r+b");
    if (file == NULL)
    {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }

    Show show;
    int found = 0;

    // Read through the file and print shows that match the given date
    while (fread(&show, sizeof(Show), 1, file))
    {
        if (strcmp(show.date, date) == 0)
        {
            printf("\nShow: %s | Show ID: %s | Date: %s | Time: %s | Revenue: %d \n",
                   show.name, show.id, show.date, show.time, show.revenue);
            found = 1;
        }
    }

    // If no shows are found for the given date, print a message
    if (!found)
    {
        printf("No shows found for the specified date.\n");
    }

    // Close the file
    fclose(file);
}

/*
    This function initializes an array of seats by setting each seat's string to an empty string.
*/
void initializeSeats(Seat seats[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        strcpy(seats[i].str, "");
    }
}

/*
    This function initializes the Twin, VIP, VVIP, and Economy seats
    for a given show. It assigns seat strings to the respective seat categories.
*/
void populateSeats(Show *show)
{
    int vipCount = 0, vvipCount = 0, economyCount = 0, twinCount = 0;
    for (int row = 1; row < ROWS; row++)
    {
        for (int col = 1; col < COLS; col++)
        {
            char seat[5];
            formatSeat(row, col, seat);
            if ((row == 1 || row == 2) && col >= 4 && col <= 14)
            {
                // Twin seats (rows 1 and 2, columns 4 to 14)
                strcpy(show->availableTwin[twinCount++].str, seat);
                col++; // Skip the next column for twin seats
            }
            else if (row <= 6)
            {
                // VVIP seats (rows 1 to 6)
                strcpy(show->availableVVIP[vvipCount++].str, seat);
            }
            else if (row <= 12)
            {
                // VIP seats (rows 7 to 12)
                strcpy(show->availableVIP[vipCount++].str, seat);
            }
            else
            {
                // Economy seats (rows 13 and beyond)
                strcpy(show->availableEconomy[economyCount++].str, seat);
            }
        }
    }
}

/*
    This function converts row and column integers to a seat string.
*/
void formatSeat(int row, int col, char *seat)
{
    // Convert the row number to a letter (1 -> A, 2 -> B, ...)
    char rowLetter = 'A' + (row - 1);
    // Format the seat string
    snprintf(seat, 5, "%c%d", rowLetter, col);
}

/*
    This function prints the available seats for the given category.

    Returns:
    - 1 if the seat category is valid and seats are printed.
    - 0 if the seat category is invalid.
*/
int printAvailableSeats(Show *show, char *seatCategory)
{
    if (strcmp(seatCategory, "twin") == 0)
    {
        printf("Available Twin seats:\n");
        for (int i = 0; i < 22; i++)
        {
            if (strcmp(show->availableTwin[i].str, "") == 0)
            {
                continue;
            }
            printf("%s ", show->availableTwin[i].str);
        }
        printf("\n");
        return 1;
    }
    else if (strcmp(seatCategory, "vvip") == 0)
    {
        printf("Available VVIP seats:\n");
        for (int i = 0; i < 98; i++)
        {
            if (strcmp(show->availableVVIP[i].str, "") == 0)
            {
                continue;
            }
            printf("%s ", show->availableVVIP[i].str);
        }
        printf("\n");
        return 1;
    }
    else if (strcmp(seatCategory, "vip") == 0)
    {
        printf("Available VIP seats:\n");
        for (int i = 0; i < 120; i++)
        {
            if (strcmp(show->availableVIP[i].str, "") == 0)
            {
                continue;
            }
            printf("%s ", show->availableVIP[i].str);
        }
        printf("\n");
        return 1;
    }
    else if (strcmp(seatCategory, "economy") == 0)
    {
        printf("Available Economy seats:\n");
        for (int i = 0; i < 80; i++)
        {
            if (strcmp(show->availableEconomy[i].str, "") == 0)
            {
                continue;
            }
            printf("%s ", show->availableEconomy[i].str);
        }
        printf("\n");
        return 1;
    }
    else
    {
        printf("Invalid selection. Try again.\n");
        return 0;
    }
}

/*
    This function checks if the given user seats are available for reservation.
    Returns:
    - 1 if the seat is available for reservation.
    - 0 if the seat is not available for reservation.
*/
int seatsAvailabiltyCheck(char *seat, Show *show, char *seatCategory)
{
    // Remove any white spaces and capitalize the seat string
    removeWhiteSpacesandCapitalize(seat);

    if (strcmp(seatCategory, "twin") == 0)
    {
        printf("Checking Twin Seats........\n");
        for (int i = 0; i < 22; i++)
        {
            if (strcmp(seat, show->availableTwin[i].str) == 0)
            {
                printf("Seat number : %s is available for booking \n", seat);
                return 1;
            }
        }
        printf("Seat number : %s is not available for booking \n", seat);
        return 0;
    }
    else if (strcmp(seatCategory, "vvip") == 0)
    {
        printf("Checking VVIP Seats........\n");
        for (int i = 0; i < 98; i++)
        {
            if (strcmp(seat, show->availableVVIP[i].str) == 0)
            {
                printf("Seat number : %s is available for booking \n", seat);
                return 1;
            }
        }
        printf("Seat number : %s is not available for booking \n", seat);
        return 0;
    }
    else if (strcmp(seatCategory, "vip") == 0)
    {
        printf("Checking VIP Seats........\n");
        for (int i = 0; i < 120; i++)
        {
            if (strcmp(seat, show->availableVIP[i].str) == 0)
            {
                printf("Seat number : %s is available for booking \n", seat);
                return 1;
            }
        }
        printf("Seat number : %s is not available for booking \n", seat);
        return 0;
    }
    else if (strcmp(seatCategory, "economy") == 0)
    {
        printf("Checking Economy Seats........\n");
        for (int i = 0; i < 80; i++)
        {
            if (strcmp(seat, show->availableEconomy[i].str) == 0)
            {
                printf("Seat number : %s is available for booking \n", seat);
                return 1;
            }
        }
        printf("Seat number : %s is not available for booking \n", seat);
        return 0;
    }
    else
    {
        printf("Error in finding category\n");
        return 0;
    }
}
