

// Define the number of rows and columns
#define ROWS 17
#define COLS 20

typedef struct {
    char str[5];
} Seat;

typedef struct {
    Seat table[ROWS][COLS];
} Theaterhall;


typedef struct{
    char id[50];     //SHAKE_VEN_16_07    
    char name[50];   //The Merchant of Venice 
    char time[10] ;          // we are not store it in am and pm it will handle by 24 hours and print will handle it
    char date[15];

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
int checkTimeSlot(const char *filename, const char *date, const char *time);
void writeShowToFile(const char *filename, Show *show);
void initializeShow(Show *show);

void displayTheatreSchedule(void);

void displayTheatreReservation(void);
void printHall(Theaterhall *hall);


void reserveSeat(void);
int charToNumber(char c);
void removeWhiteSpacesandCapitalize(char *str);
void parseSeat(char *seat, int *row, int *col);


// Define an enumeration for time slots
typedef enum {
    SLOT_1, // 10:00 AM
    SLOT_2, // 12:00 PM
    SLOT_3, // 02:30 PM
    SLOT_4, // 04:00 PM
    SLOT_5  // 06:00 PM
} TimeSlot;

const char* timeSlotToString(TimeSlot slot);
void toLowerString(char *str);
void initializeShow(Show *show);
const char* timeSlotToString(TimeSlot slot);
void trimSpaces(char *str);
void goToMainPage(void);
