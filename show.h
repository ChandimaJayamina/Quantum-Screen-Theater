#include <pcre.h>

// Define a structure to identify seat
typedef struct {
    char str[3];
}Seat;

// Define theater hall
typedef struct {
    Seat table[17][17];
} Theaterhall;


typedef struct{
    char show_name_str[50];   //The Merchant of Venice
    char show_id_str[50];     //SHAKE_VEN_16_07
    char time[10] ;          // we are not store it in am and pm it will handle by 24 hours and print will handle it
    char date[15];
    char label[50];           // show_id + date + time this for regex identification

    Seat availableVIP[50];    //can be linked list
    Seat availableVVIP[50];
    Seat availableEconomy[50];
    Seat availableTwin[50];

    Theaterhall hall;

    int revenue;

}Show;

// int getPosition(char ch) ;

// Add show to file
void addTheatreShow(void);
int checkTimeSlot(const char *filename,const char *regex_pattern);
void writeShowToFile(const char *filename, Show *show);


void displayTheatreSchedule(void);



void reserveSeat(void);


// Use for play to read data from file and save it to show
void initializeShowFromFile(void);