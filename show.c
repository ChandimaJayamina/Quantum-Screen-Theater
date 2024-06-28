#include <stdio.h>
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

    /*
        Use to create label  -> showid_2024-12-12_7:30_am
    */
   // Use sprintf to concatenate the fields into the label
    sprintf(currentShow.label, "[%s_%s_%s]",
            currentShow.show_id_str,
            currentShow.date, currentShow.time);
    printf("label : %s", currentShow.label);


    /*  To do --------------------------------------------------------------------------------
    seat availableVIP[50];
    seat availableVVIP[50];
    seat availableEconomy[50];
    seat availableTwin[50];
    */

    /*
        Check is the time slot available by using regex pattern ≠–To do----------------------------------------------
    */
    char timeslot[30];
    sprintf(timeslot, "\\[.*%s_%s\\].*",
            currentShow.date, currentShow.time);
    printf("Timeslot : %s", timeslot);
    const char *regex = timeslot;
    if(checkTimeSlot("show_schedules.txt", regex)){
        printf("Time slot not found");
        writeShowToFile("show_schedules.txt", &currentShow);
    }else{
        printf("Time slot found");
    }


    /*
       if time slot available  Use to write data to file else check user enter another time slot or data else quit
    */





}

void displayTheatreSchedule(void){
    
}

void reserveSeat(void){

}

void displayTheatreReservation(void){

}






/*
    This function used in addTheater function to get the time slot availability
*/
int checkTimeSlot(const char *filename,const char *regex_pattern){
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }
    char line[256];
    pcre  *re_timeslot;
    const char *error;
    int erroffset;
    int ovector[30];

    re_timeslot = pcre_compile(regex_pattern, 0, &error, &erroffset, NULL); // get label regex patern
    if (re_timeslot == NULL) {
        printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file)) {
        if (pcre_exec(re_timeslot, NULL, line, strlen(line), 0, 0, ovector, 30) >= 0) {
            return 0;
        }
    }
    return 1;
    // Free the compiled regular expression
    pcre_free(re_timeslot);
    fclose(file);
}



void writeShowToFile(const char *filename, Show *show) {
    FILE *file = fopen(filename, "a"); // Append mode to write multiple entries
    if (!file) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\t%s\t%s\t%s\t%s\t", show->label, show->show_name_str,show->show_id_str,show->date,show->time);
    //Writing the hall data
    for (int i = 0; i < 17; i++) {
        for (int j = 0; j < 17; j++) {
            fprintf(file, "%s", show->hall.table[i][j].str);
            if (i != 16 || j != 16) {
                fprintf(file, " ");
            }
        }
    }
    // End of the line
    fprintf(file, "\t%d\n\n",show->revenue);


    fclose(file);
}

// Read data from file
void initializeShowFromFile(void) {

    char curlabel[20];
    // Getting the label
    printf("Please enter the label of the show : ");
    scanf(" %[^\n]", curlabel);
    printf("You entered: %s\n", curlabel);

    //Regex pattern creation
    char regex_pattern[30];
    sprintf(regex_pattern, "\\[%s\\].*",
            curlabel);

    FILE *file = fopen("show_schedules.txt", "r");
    if (!file) {
        perror("Failed to open file for reading");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    pcre  *re;
    const char *error;
    int erroffset;
    int ovector[30];

    re = pcre_compile(regex_pattern, 0, &error, &erroffset, NULL); // get label regex patern
    if (re == NULL) {
        printf("PCRE compilation failed at offset %d: %s\n", erroffset, error);
        exit(EXIT_FAILURE);
    }
    
     // Read each line from the file and match it against the pattern
    while (fgets(line, sizeof(line), file)) {
        if (pcre_exec(re, NULL, line, strlen(line), 0, 0, ovector, 30) >= 0) {
            printf("%s\n", line);

            // Tokenize the line based on tabs
            int MAX_TOKENS = 7;
            char *token;
            int token_count = 0;
            char *tokens[MAX_TOKENS]; // Array to hold tokens
            Show show;
            
            // Get the first token
            token = strtok(line, "\t");
            while (token != NULL && token_count < MAX_TOKENS) {
                // Store the token in the tokens array
                tokens[token_count++] = token;

                // Get next token
                token = strtok(NULL, "\t");
                printf("Tokens :%d", token_count);
            }
            printf("Test line3\n");
            // Process tokens
            strncpy(show.label, tokens[0], sizeof(show.label) - 1);
            show.label[sizeof(show.label) - 1] = '\0'; // Ensure null-terminated
            printf("label : %s\n",show.label);
            
            strncpy(show.show_name_str, tokens[1], sizeof(show.show_name_str) - 1);
            show.label[sizeof(show.show_name_str) - 1] = '\0'; // Ensure null-terminated
            printf("Name : %s\n",show.show_name_str);

            strncpy(show.show_id_str, tokens[2], sizeof(show.show_id_str) - 1);
            show.label[sizeof(show.show_id_str) - 1] = '\0'; // Ensure null-terminated
            printf("Id : %s\n",show.show_id_str);

            strncpy(show.date, tokens[3], sizeof(show.date) - 1);
            show.label[sizeof(show.date) - 1] = '\0'; // Ensure null-terminated
            printf("Date : %s\n",show.date);

            strncpy(show.time, tokens[3], sizeof(show.time) - 1);
            show.label[sizeof(show.time) - 1] = '\0'; // Ensure null-terminated
            printf("Time : %s\n",show.time);

            printf("Test line5\n");
        }
    }


    // Free the compiled regular expression
    pcre_free(re);
    fclose(file);

}



//     FILE *file = fopen(filename, "r");
//     if (file == NULL) {
//         perror("Unable to open file");
//         exit(1);
//     }

//     for (int i = 0; i < 17; i++) {
//         for (int j = 0; j < 17; j++) {
//             fscanf(file, "%2s", show->hall.table[i][j].str);
//         }
//     }

//     fclose(file);