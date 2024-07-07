// Define the number of rows and columns
#define ROWS 17
#define COLS 21

typedef struct {
    char str[5];
} Seat;

typedef struct {
    Seat table[ROWS][COLS];
} Theaterhall;


typedef struct{
    char id[50];       
    char name[50];  
    char time[10] ;        
    char date[15];

    Seat availableTwin[22];
    Seat availableVVIP[98];
    Seat availableVIP[120];
    Seat availableEconomy[80];

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
void restart_program(void);
void displayTheatreScheduleForDate(const char *date);


void formatSeat(int row, int col, char *seat);
FILE* getFile(char *action);
void findAvailableSeats(Theaterhall *hall);
void populateSeats(Show *show);
void printAvailableSeats(Show *show, char *seatCategory);
//Show updateAvailableSeatsAndRevenue(char *seat, Show *show, char *seatCategory);
