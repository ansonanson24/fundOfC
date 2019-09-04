/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Yat Ho Kwok
 * Student ID: 12879779
 * Date of submission: 19 Aug 2019
 * A brief statement on what you could achieve (less than 50 words):
 * 
 * 
 * A brief statement on what you could NOT achieve (less than 50 words):
 * 
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/
#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"

/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
struct date_time {
    int month;
    int day;
    int hour;
    int minute;
};
typedef struct date_time date_time_t;

struct flight {
    char flightcode[MAX_FLIGHTCODE_LEN + 1];
    date_time_t departure_dt;
    char arrival_city[MAX_CITYCODE_LEN + 1];
    date_time_t arrival_dt;
};
typedef struct flight flight_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void print_menu (void);
void addFlight(void);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    /* TODO */
    int userInput;

    print_menu();
    scanf("%d", &userInput);
    switch (userInput)
    {
    case 1:
        addFlight();
        break;
    
    default:
        break;
    }
    return 0;
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void print_menu (void)
{
    printf("\n"
    "1. add a flight\n"
    "2. display all flights to a destination\n"
    "3. save the flights to the database file\n"
    "4. load the flights from the database file\n"
    "5. exit the program\n"
    "Enter choice (number between 1-5)>\n");
}

void addFlight(void) {
    flight_t newFlight;

    printf("Enter flight code>\n");
    scanf("%s", &newFlight.flightcode);

    if(!isValid(newFlight.flightcode)) printf("Invalid input");
}