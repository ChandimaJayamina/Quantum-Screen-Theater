#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure from test branch
// Define a structure to store date
typedef struct {
    int hours;
    int minutes;
    char am_pm[2];
} Time;

// Define a structure to store date
typedef struct {
    int day;
    int month;
    int year;
} Date;


// Define a structure to identify seat
typedef struct {
    char str[3];
}seat;

// Define theater hall
typedef struct {
    seat table[17][17];
} theaterhall;


struct show {

    char show_name_str[50];   //The Merchant of Venice
    char show_id_str[50];     //SHAKE_VEN_16_07
    Time showtime;          // we are not store it in am and pm it will handle by 24 hours and print will handle it
    Date showdate;
    char label[50];           // show_id + date + time this for regex identification

    seat availableVIP[50];
    seat availableVVIP[50];
    seat availableEconomy[50];
    seat availableTwin[50];

    theaterhall hall;

    int revenue;

}show;

// Driver program
int main()
{
	FILE* infile;
	infile = fopen("storage.txt", "wb+");
	if (infile == NULL) {
		fprintf(stderr, "\nError opening file\n");
		exit(1);
	}

	struct show write_struct_1 = {"The Merchant of Venice", "SHAKE_VEN_16_07"};

	// writing to file
	fwrite(&write_struct_1, sizeof(write_struct_1), 1, infile);

	struct show write_struct_2 = {"The Merchant of Paris", "SHAKE_VEN_13_23"};

	fwrite(&write_struct_2, sizeof(write_struct_2), 1, infile);

	// setting pointer to start of the file
	rewind(infile);


	while( fread(&show, sizeof(show), 1, infile) == 1 )
    {
		printf("Checking ID: %s \n", show.show_id_str);
		//Searching for 1 out of the two shows by Id
		if( strcmp(show.show_id_str, "SHAKE_VEN_13_23") == 1 ){
			 printf("Found our show: %s \n", show.show_name_str);
			 break;
		}
       
    }

	// close file
	fclose(infile);

	return 0;
}
