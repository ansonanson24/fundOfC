/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 2
 * Name: Yat Ho Kwok
 * Student ID: 12879779
 * Date of submission: 19 Aug 2019
 * A brief statement on what you could achieve (less than 50 words):
 * Was able to pass test 1 - 7 & 9.
 * 
 * A brief statement on what you could NOT achieve (less than 50 words):
 * Was not able to pass test 8, 10 & 11 even my program produces the same results.
 * 
*******************************************************************************/

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/
#include <stdio.h> /* printf, scanf */
#include <string.h> /* strlen, strcmp */
#include <stdlib.h> /* fopen, fwrite, feof, fread, fclose */

/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/
#define MAX_FLIGHTCODE_LEN 6
#define MAX_CITYCODE_LEN 3
#define MAX_NUM_FLIGHTS 5
#define DB_NAME "database"
#define ORIGIN_NAME "SYD"

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
void printAllFlights(flight_t flights[], int nFlights);
void printFlights(flight_t flights[], int nFlights, char input[]);
void printFlight(flight_t flight);
void printHeader(void);
void printSpace(char code[], int length);
void printFlightDt(date_time_t dt);
void saveFlights(flight_t flights[], int nFlights);
int loadFlights(flight_t flights[]);
void printInvalidMessage(void);
void printNoFlightsMessage(void);

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void)
{
    /* TODO */
    int userInput = 0;
    flight_t flights[MAX_NUM_FLIGHTS];
    int numOfFlights = 0;
    while (userInput != 5) {
        print_menu();
        scanf("%d", &userInput);
        switch (userInput)
        {
            case 1: {
                if (numOfFlights < MAX_NUM_FLIGHTS) {
                    addFlight(flights, numOfFlights);
                    numOfFlights++;
                } else printf("Cannot add more flights - memory full\n");
            }
            break;
            case 2: displayFlights(flights, numOfFlights);
            break;
            case 3: saveFlights(flights, numOfFlights);
            break;
            case 4: numOfFlights = loadFlights(flights);
            break;
            case 5:
            break;
            default: printf("Invalid choice\n");
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

/*******************************************************************************
 * This function creates a flight object with from user input and adds it to the
 * list of flights.
 * inputs:
 * - flights[]: list of flights
 * - nFlights: number of existing flights
 * outputs:
 * - none
*******************************************************************************/
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
            if (!flightCodeIsValid) printInvalidMessage();
        }
        
        printf("Enter departure info for the flight leaving SYD.\n");
        while (!departureDtIsValid) {
            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", &newFlight.departure_dt.month, 
                                 &newFlight.departure_dt.day, 
                                 &newFlight.departure_dt.hour, 
                                 &newFlight.departure_dt.minute);

            departureDtIsValid = isValidDt(newFlight.departure_dt);
            if (!departureDtIsValid) printInvalidMessage();
        }

        while (!arrivalCodeIsValid) {
            printf("Enter arrival city code>\n");
            scanf("%s", newFlight.arrival_city);

            arrivalCodeIsValid = isValidArrivalCode(newFlight.arrival_city);
            if (!arrivalCodeIsValid) printInvalidMessage();
        }
        
        printf("Enter arrival info.\n");

        while (!arrivalDtIsValid) {
            printf("Enter month, date, hour and minute separated by spaces>\n");
            scanf("%d %d %d %d", &newFlight.arrival_dt.month, 
                                 &newFlight.arrival_dt.day, 
                                 &newFlight.arrival_dt.hour, 
                                 &newFlight.arrival_dt.minute);
            arrivalDtIsValid = isValidDt(newFlight.arrival_dt);
            if (!arrivalDtIsValid) printInvalidMessage();
        }
        
        flights[nFlights] = newFlight;
    }
}

/*******************************************************************************
 * This function checks if the flight code entered is valid according to the rules
 * specified in the assessment outline.
 * inputs:
 * - code[]: flight code
 * outputs:
 * - 1: flight code is valid
 * - 0: flight code is invalid
*******************************************************************************/
int isValidFlightCode(char code[]) {
    if (strlen(code) > MAX_FLIGHTCODE_LEN || strlen(code) < 3) return 0;
    else if (code[0] < 'A' || code[0] > 'Z') return 0;
    else if (code[1] < 'A' || code[1] > 'Z') return 0;
    else {
        int codeIndex;
        for (codeIndex = 2; codeIndex < strlen(code); codeIndex++) {
            if ((int)code[codeIndex] < '0' || (int)code[codeIndex] > '9') return 0;
        }
    }
    return 1;
}

/*******************************************************************************
 * This function checks if the date & time entered is within the specified range.
 * inputs:
 * - dt: date & time
 * outputs:
 * - 1: date & time is valid
 * - 0: date & time is invalid
*******************************************************************************/
int isValidDt(date_time_t dt) {
    return (dt.month >= 1 && dt.month <= 12 && 
            dt.day >= 1 && dt.day <= 31 && 
            dt.hour >= 0 && dt.hour <= 23 && 
            dt.minute >= 0 && dt.minute <= 59);
}

/*******************************************************************************
 * This function checks if the arrival city code entered follows the 
 * specifications.
 * inputs:
 * - code[]: arrival city code
 * outputs:
 * - 1: arrival city code is valid
 * - 0: arrival city code is invalid
*******************************************************************************/
int isValidArrivalCode(char code[]) {
    return strlen(code) < MAX_CITYCODE_LEN + 1;
}

/*******************************************************************************
 * This function handles option 2 in the menu.
 * inputs:
 * - flights[]: list of flights
 * - nFlights: number of existing flights
 * outputs:
 * - none
*******************************************************************************/
void displayFlights(flight_t flights[], int nFlights) {
    char input[MAX_CITYCODE_LEN + 1];
    int arrivalCodeIsValid = 0;

    while (!arrivalCodeIsValid) {
        printf("Enter arrival city code or enter * to show all destinations>\n");
        scanf("%s", input);

        arrivalCodeIsValid = isValidArrivalCode(input);
        if (arrivalCodeIsValid) {
            if (nFlights == 0) printNoFlightsMessage();
            else if (strcmp(input, "*") == 0) {
                printAllFlights(flights, nFlights);
            } else printFlights(flights, nFlights, input);
        } else printInvalidMessage();
    }
}

/*******************************************************************************
 * This function prints all existing flights in the list.
 * inputs:
 * - flights[]: list of flights
 * - nFlights: number of existing flights
 * outputs:
 * - none
*******************************************************************************/
void printAllFlights(flight_t flights[], int nFlights) {
    int index = 0;
    
    if (nFlights > 0) {
        printHeader();
        for (index = 0; index < nFlights; index++) {
            flight_t eachFlight = flights[index];
            printFlight(eachFlight);
        }
    }
}

/*******************************************************************************
 * This function prints all flights which destination matches the inputted
 * arrival city code.
 * inputs:
 * - flights[]: list of existing flights
 * - nFlights: number of existing flights
 * - input[]: inputted arrival city code
 * outputs:
 * - none
*******************************************************************************/
void printFlights(flight_t flights[], int nFlights, char input[]) {
    int index, isFound;
    index = 0;
    isFound = 0;
    if (nFlights > 0) {
        for (index = 0; index < nFlights; index++) {
            flight_t thisFlight = flights[index];
            if (strcmp(thisFlight.arrival_city, input) == 0) {
                if (!isFound) {
                    printHeader();
                    isFound = 1;
                }
                printFlight(thisFlight);
            }
        }
        if (!isFound) printNoFlightsMessage();
    } else printNoFlightsMessage();
}

/*******************************************************************************
 * This function prints the entered flight.
 * inputs:
 * - flight: flight to be printed
 * outputs:
 * - none
*******************************************************************************/
void printFlight(flight_t flight) {
    printf("%s ", flight.flightcode);
    printSpace(flight.flightcode, MAX_FLIGHTCODE_LEN);

    printf("%s ",ORIGIN_NAME);
    printFlightDt(flight.departure_dt);

    printf(" %s ", flight.arrival_city);
    printSpace(flight.arrival_city, MAX_CITYCODE_LEN);

    printFlightDt(flight.arrival_dt);

    printf("\n");
}

/*******************************************************************************
 * This function prints the remaining space needed of a flight to make the 
 * correct alignment in the display of flights.
 * inputs:
 * - code[]: flight/arrival city code to be checked
 * - length: length of the message needed
 * outputs:
 * - none
*******************************************************************************/
void printSpace(char code[], int length) {
    int spaceLength = length - strlen(code);
    int index;
    for (index = 0; index < spaceLength; index++) {
        printf(" ");
    }
}

/*******************************************************************************
 * This function prints the date & time in required format.
 * inputs:
 * - dt: date & time
 * outputs:
 * - none
*******************************************************************************/
void printFlightDt(date_time_t dt) {
    printf("%02d-%02d %02d:%02d", dt.month, dt.day, dt.hour, dt.minute);
}

/*******************************************************************************
 * This function prints the header in display flights.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printHeader(void) {
    printf("Flight Origin          Destination\n");
    printf("------ --------------- ---------------\n");
}

/*******************************************************************************
 * This function saves all existing flights to a file "database", if the file
 * exists, the function overwrites it.
 * inputs:
 * - flights[]: list of flights
 * - nFlight: number of existing flights
 * outputs:
 * - none
*******************************************************************************/
void saveFlights(flight_t flights[], int nFlights) {
    FILE *saveFile = fopen(DB_NAME, "w");

    int index = 0;
    for (index = 0; index < nFlights; index++) {
        fwrite(&flights[index], sizeof(flight_t), 1, saveFile);
    }
    fclose(saveFile);
}

/*******************************************************************************
 * This function loads previously saved flights from a "database" file in the 
 * same directory into list of flights.
 * inputs:
 * - flights[]: list of flights
 * outputs:
 * - number of flights saved in the file
*******************************************************************************/
int loadFlights(flight_t flights[]) {
    FILE *loadFile = fopen(DB_NAME, "rb");

    int index = 0;
    if (loadFile) {
        while(!feof(loadFile)) {
            fread(&flights[index], sizeof(flight_t), 1, loadFile);
            index ++;
        }
        fclose(loadFile);
    } else printf("Read error\n");

    return index - 1;
}

/*******************************************************************************
 * This function prints invalid input message.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printInvalidMessage(void) {
    printf("Invalid input\n");
}

/*******************************************************************************
 * This function prints a message when no flights are found.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printNoFlightsMessage(void) {
    printf("No flights\n");
}