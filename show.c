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



void writeShowToFile(const char *filename, Show *show) {
    FILE *file = fopen(filename, "ab"); // Append mode to write multiple entries
    if (file == NULL) {
        perror("Failed to open file for writing");
        exit(EXIT_FAILURE);
    }
    
    fwrite(show, sizeof(Show), 1, file);

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
            char *token, *tok;
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

            
            // Parse the seat information from tokens[6]
            char *seat_info = tokens[6];
            char *seat_row = strtok(seat_info, " ");
            int row_index = 0;

            while (seat_row != NULL && row_index < 17) {
                for (int col_index = 0; col_index < 17; col_index++) {
                    if (strcmp(seat_row, "*") == 0) {
                        
                        strcpy(show.hall.table[row_index][col_index].str, "*");
                    } 
                    else if(strcmp(seat_row, "01") == 0){
                        strcpy(show.hall.table[row_index][col_index].str, " ");
                        strcpy(show.hall.table[row_index][++col_index].str, "01");
                    }
                    else {
                        // Assuming seats are marked as "A", "B", ..., "P"
                        strcpy(show.hall.table[row_index][col_index].str, seat_row);
                    }
                    // Move to the next seat information
                    seat_row = strtok(NULL, " ");
                    if (seat_row == NULL) break;
                }
                row_index++;
            }
            // while(tok!=NULL){
            //     if(tok==" "){
            //         tok = strtok(NULL, " ");
            //         continue;
            //     }
                // else if (tok >= '0' && tok <= '17'){
                //     // if(row == 0 && col == 0){
                //     //     strncpy(show.hall.table[row][col].str, " ", sizeof(show.hall.table[row][col].str) - 1);
                //     //     show.hall.table[row][col].str[sizeof(show.hall.table[row][col].str) - 1] = '\0'; // Null-terminate
                //     //     strncpy(show.hall.table[row][++col].str, tok, sizeof(show.hall.table[row][col].str) - 1);
                //     //     show.hall.table[row][col].str[sizeof(show.hall.table[row][col].str) - 1] = '\0'; // Null-terminate
                //     // } else{
                //     //     strncpy(show.hall.table[row][col].str, tok, sizeof(show.hall.table[row][col].str) - 1);
                //     //     show.hall.table[row][col].str[sizeof(show.hall.table[row][col].str) - 1] = '\0'; // Null-terminate
                //     // }
                //     printf("1 token %s", tok.str);
                //     col++;
                //     tok = strtok(NULL, " ");
                // }
                // else if(tok >= 'A' && tok <= 'P'){
                //     // strncpy(show.hall.table[row][col].str, tok, sizeof(show.hall.table[row][col].str) - 1);
                //     // show.hall.table[row][col].str[sizeof(show.hall.table[row][col].str) - 1] = '\0'; // Null-terminate
                //     printf("A token %s", tok.str);
                //     col++;
                //     tok = strtok(NULL, " ");
                // }
                // else if(tok.str == "*" || *tok.str == "#" || *tok.str =="0"){
                //     // strncpy(show.hall.table[row][col].str, tok, sizeof(show.hall.table[row][col].str) - 1);
                //     // show.hall.table[row][col].str[sizeof(show.hall.table[row][col].str) - 1] = '\0'; // Null-terminate
                //     printf("* token %s", tok.str);
                //     col++;
                //     tok = strtok(NULL, " ");
                // } 
                // else{
                //     printf("Not identified symbol %s", tok);
                //     return;
                // }
                
            //}
            

            printf("1st row 1 seat : %s\n", show.hall.table[2][1].str);
            printf("Test line5\n");
        }
    }


    // Free the compiled regular expression
    pcre_free(re);
    fclose(file);

}

