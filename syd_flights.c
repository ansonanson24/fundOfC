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
void addFlight(flight_t flights[], int nFlights);
int isValidFlightCode(char code[]);
int isValidDt(date_time_t dt);
int isValidArrivalCode(char code[]);
void displayFlights(flight_t flights[], int nFlights);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    /* TODO */
    int userInput;
    flight_t flights[MAX_NUM_FLIGHTS];
    int numOfFlights = 0;
    while (userInput != 5) {
        print_menu();
        scanf("%d", &userInput);
        switch (userInput)
        {
            case 1: {
                addFlight(flights, numOfFlights);
                numOfFlights++;
            }
            break;
            case 2: displayFlights(flights, numOfFlights);
            break;
    
            default:
            break;
        }
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

void addFlight(flight_t flights[], int nFlights) {
    if (nFlights < MAX_NUM_FLIGHTS) {
        flight_t newFlight;
        int flightCodeIsValid, departureDtIsValid, arrivalCodeIsValid, arrivalDtIsValid;

        flightCodeIsValid = 0;
        departureDtIsValid = 0;
        arrivalCodeIsValid = 0;
        arrivalDtIsValid = 0;

        while (!flightCodeIsValid) {
            printf("Enter flight code>\n");
            scanf("%s", newFlight.flightcode);

            flightCodeIsValid = isValidFlightCode(newFlight.flightcode);
            if (!flightCodeIsValid) printf("Invalid input\n");
        }
        
        while (!departureDtIsValid) {
            printf("Enter departure info for the flight leaving SYD.\n");
            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", &newFlight.departure_dt.month, &newFlight.departure_dt.day, &newFlight.departure_dt.hour, &newFlight.departure_dt.minute);

            departureDtIsValid = isValidDt(newFlight.departure_dt);
            if (!departureDtIsValid) printf("Invalid input\n");
        }

        while (!arrivalCodeIsValid) {
            printf("Enter arrival city code>\n");
            scanf("%s", newFlight.arrival_city);

            arrivalCodeIsValid = isValidArrivalCode(newFlight.arrival_city);
            if (!arrivalCodeIsValid) printf("Invalid input\n");
        }
        
        while (!arrivalDtIsValid) {
            printf("Enter arrival info.\n");
            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", &newFlight.arrival_dt.month, &newFlight.arrival_dt.day, &newFlight.arrival_dt.hour, &newFlight.arrival_dt.minute);

            arrivalDtIsValid = isValidDt(newFlight.arrival_dt);
            if (!arrivalDtIsValid) printf("Invalid input\n");
        }
        

        flights[nFlights] = newFlight;
    } else printf("Cannot add more flights - memory full\n");
}

int isValidFlightCode(char code[]) {
    return strlen(code) < MAX_FLIGHTCODE_LEN + 1;
}

int isValidDt(date_time_t dt) {
    return (dt.month >= 1 && dt.month <= 12 && 
            dt.day >= 1 && dt.day <= 31 && 
            dt.hour >= 0 && dt.hour <= 23 && 
            dt.minute >= 0 && dt.minute <= 59);
}

int isValidArrivalCode(char code[]) {
    return strlen(code) < MAX_CITYCODE_LEN + 1;
}

void displayFlights(flight_t flights[], int nFlights) {
    int index;

    printf("Enter arrival city code or enter * to show all destinations>\n");
    for (index = 0; index < nFlights; index++) {
        flight_t eachFlight = flights[index];
        printf("%s SYD %02d-%02d %02d:%02d %s %02d-%02d %02d:%02d", eachFlight.flightcode, 
                                                                    eachFlight.departure_dt.month, eachFlight.departure_dt.day, 
                                                                    eachFlight.departure_dt.hour, eachFlight.departure_dt.minute, 
                                                                    eachFlight.arrival_city,
                                                                    eachFlight.arrival_dt.month, eachFlight.arrival_dt.day,
                                                                    eachFlight.arrival_dt.hour, eachFlight.arrival_dt.minute);
    }

    /* if none: "No flights" */
}