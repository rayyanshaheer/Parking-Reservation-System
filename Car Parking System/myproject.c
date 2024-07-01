#include <stdio.h>
#include <string.h>
#include <stdlib.h> //for system functions
#include <conio.h>  //for getch

// to check which system is program running on
#ifdef _WIN32
#include <windows.h> //for Sleep function
#else
#include <unistd.h> //for sleep function
#endif
// above notice the capitilization in name of sleep and Sleep function both have different meangning and are used for different systems.

#define PASSWORD_LENGTH 30          // length of password
#define TRUE_PASSWORD "abcd1234"    // password for authentication
#define PASSWORD_ATTEMPTS_ALLOWED 3 // number of attempts allowed for password

void loadingIllusion(); // function to show loading illusion
void clearScreen();     // function to clear screen
void userEntryWait();   // function to wait for user input

int auth();            // function to authenticate user
void input();          // function to add cars to parking
void costcalculator(); // function to calculate cost of parking
void delete_record();  // function to delete record of car

int timeCount = 0;                     // to store count of cars
char driverName[15], membershipStatus; // to store driver name, membership status
int vehicleNumber;                     // to store vehicle number

int main()
{
    auth(); // authenticate user
    clearScreen();
    int choice; // to store user choice
    while (1)
    {
        clearScreen();
        printf("\n\n\t\t ====== CAR PARKING RESERVATION SYSTEM ======");
        printf("\n\n                                          ");
        printf(" \n\t\t\t======================");
        printf("\n\n\t\t\t  1. Arrival of a Car");
        printf("\n\n\t\t\t  2. Total no of cars Arrived");
        printf("\n\n\t\t\t  3. Total parking charges of all cars with details");
        printf("\n\n\t\t\t  4. Departure of the car");
        printf("\n\n\t\t\t  5. Exit Program");
        printf(" \n\t\t\t======================\n\n");
        printf("\t\t\t Select Your Choice :: ");
        if (scanf(" %d", &choice) != 1)
        {
            printf("Invalid input. Please enter a valid choice.\n");
            fflush(stdin); // clear input buffer
            userEntryWait();
            continue;
        }
        switch (choice)
        {
        case 1:
        {

            FILE *f1;
            f1 = fopen("parkingProjectFile.txt", "a");
            clearScreen();
            input();
            fprintf(f1, "%d %.2f %s %c\n", vehicleNumber, timeCount, driverName, membershipStatus);
            fclose(f1);
            break;
        }
        case 2:
        {
            clearScreen();
            printf("\n\n\t\t=== View the Records in the Parking Database ===");
            printf("\n");
            FILE *readingfile;
            readingfile = fopen("parkingProjectFile.txt", "r");
            int currentVehicleNumber;
            float currentTimeCount;
            char currentDriverName[15], currentMembershipStatus;
            int carPosition = 1;
            while (fscanf(readingfile, "%d %f %s %c %s", &currentVehicleNumber, &currentTimeCount, currentDriverName, &currentMembershipStatus) != EOF)
            {
                clearScreen();
                printf("\n");
                printf("\n\n\tThe Car position in parking lot : %d", carPosition);
                carPosition++;
                printf("\n\n\t\tThe Driver Name : %s\n", currentDriverName);
                printf("\n\n\t\tThe Car No : %d\n", currentVehicleNumber);
                printf("\n\n\t\tThe Hours Of Stay : %.2f", currentTimeCount);
                printf("\n\n\n\n");
                userEntryWait();
                printf("\n");
            }
            fclose(readingfile);
            break;
        }
        case 3:
        {
            FILE *infile;
            infile = fopen("parkingProjectFile.txt", "r");
            int currentVehicleNumber;
            float currentTimeCount;
            char currentDriverName[15], currentMembershipStatus;
            while (fscanf(infile, "%d %f %s %c %s", &currentVehicleNumber, &currentTimeCount, currentDriverName, &currentMembershipStatus) != EOF)
            {
                printf("\n");
                printf("\n\n\t\tThe Car No : %d\n", currentVehicleNumber);
                costcalculator();
                printf("\n\n\t\tThe Driver Name : %s\n", currentDriverName);
                printf("\n\n\t\tThe Car No : %d\n", currentVehicleNumber);
                printf("\n\n\t\tThe Hours Of Stay : %.2f", currentTimeCount);
                printf("\n\n");
            }
            fclose(infile);
            break;
        }
        case 4:
        {
            delete_record();
            break;
        }
        case 5:
        {
            clearScreen();
            printf("\n\n\n\t\t\tThank you for using our software \n");
            loadingIllusion();
            exit(0);
            break;
        }
        default:
        {
            printf("\n\n\t\tInvalid input. Please enter a valid choice.\n");
        }
        }                                                                          
        getch();
    }
}

void delete_record()
{
    int vehicleNumberToDelete;
    clearScreen();
    printf("\n\n\t\tEnter the car no you want to get depart : ");
    scanf("%d", &vehicleNumberToDelete);
    FILE *inputFile;
    inputFile = fopen("parkingProjectFile.txt", "r"); // file to read the data of the cars
    FILE *outputFile;
    outputFile = fopen("temp.txt", "w"); // temp file to store the data of the cars which are not to be deleted
    int currentVehicleNumber;
    float currentTimeCount;
    char currentDriverName[15], currentMembershipStatus;
    while (fscanf(inputFile, "%d %f %s %c %s", &currentVehicleNumber, &currentTimeCount, currentDriverName, &currentMembershipStatus) != EOF)
    {
        if (currentVehicleNumber != vehicleNumberToDelete) // if the car number is not the one to be deleted then write it to the temp file
        {
            fprintf(outputFile, "%d %.2f %s %c %s\n", currentVehicleNumber, currentTimeCount, currentDriverName, currentMembershipStatus); // write the data to the temp file which is not to be deleted
        }
    }
    printf("\n\n\t\t Parking Record Deleted");
    fclose(inputFile);
    fclose(outputFile);
    remove("parkingProjectFile.txt");
    rename("temp.txt", "parkingProjectFile.txt"); // rename keyword is used to rename the file from temp.txt to parkingProjectFile.txt
}

void costcalculator()
{
    printf("\n\n\t\tAre you a V.I.P: y/n ");
    if (scanf(" %c", &membershipStatus) != 1)// check if the input is valid or not
    {
        printf("Invalid input. Please enter a valid character.\n");
        userEntryWait();
    }
    if (membershipStatus == 'y' || membershipStatus == 'Y')
    {
        clearScreen();
        printf("\n\n\t\tThe total expense during parking  ");
        printf("%.2f rupees", timeCount * 20);
    }
    else if (membershipStatus == 'n' || membershipStatus == 'N')
    {
        clearScreen();
        printf("\n\n\t\tThe total expenses during parking  ");
        printf("%.2f rupees", timeCount * 25);
    }
    else
    {
        printf("\n\n\t\tInvalid input. Please enter y or n only.");
        costcalculator();
    }
}

void input()
{

    char tempDriverName[100]; // Temporary variable for driver name
    int tempVehicleNumber;    // Temporary variable for car number
    float tempTimeCount;      // Temporary variable for hours of stay

    printf("\n\n\t\tEnter the name of driver : ");
    while (scanf("%s", tempDriverName) != 1)
    {
        printf("\n\n\t\tInvalid input. Please enter a valid name: ");
        fflush(stdin); // clear input buffer
    }
    printf("\n\n\t\tEnter the car no : ");
    while (scanf("%d", &tempVehicleNumber) != 1)
    {
        printf("\n\n\t\tInvalid input. Please enter a valid car number: ");
        fflush(stdin); // clear input buffer
    }
    printf("\n\n\t\tEnter the no of hours of stay : ");
    while (scanf("%f", &tempTimeCount) != 1)
    {
        printf("\n\n\t\tInvalid input. Please enter a valid number of hours: ");
        fflush(stdin); // clear input buffer
    }

    if (tempTimeCount < 0)
    {
        printf("\n\n\t\tThe car cannot be parked for negative hours.");
        printf("\n\n\t\tParking not possible!!");
        userEntryWait();
        return;
    }
    else if (tempTimeCount < 8)
    {
        // Store values only if count is less than 8 using the temporary variables
        strcpy(driverName, tempDriverName); // copy temp_dname to dname
        vehicleNumber = tempVehicleNumber;
        timeCount = tempTimeCount;

        printf("\n\n\t\tParking Available! You can park your car. ");
        printf("\n\n\t\tCar got parked!!");
    }
    else
    {
        printf("\n\n\t\tThe car cannot be parked for more than 8 hours.");
        printf("\n\n\t\tParking not possible!!");
        userEntryWait();
    }
}

int auth()
{
    char enteredPassword[PASSWORD_LENGTH]; // to store entered password
    char ch;                               // to store entered character
    int i = 0;

    printf("\n\n\n\n\n\n\n\t\t\t\t\tCar Parking Reservation System Login");
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\tEnter Password: ");

    while (i < PASSWORD_LENGTH - 1)
    {
        ch = getch();

        if (ch == '\r' || ch == '\n') // check for Enter key
        {
            enteredPassword[i] = '\0'; // null character to end string
            break;
        }
        else if (ch == '\b' && i > 0) // check for backspace
        {
            printf("\b \b"); // to erase the character from screen
            i--;             // with this line of code the cursor moves back to the previous position and then the character is then overwriten
        }
        else if (ch != '\b') // storing password
        {
            enteredPassword[i] = ch;
            i++;
            printf("*"); // to show * instead of entered character aka passsword masking
        }
    }

    printf("\n\n\n\n\n");

    /*
    strcmp function returns three values:
    0 If both the strings are identical (equal)
    positive value: If the ASCII value of the first unmatched character is greater in the first string than the second string.
    negative value: If the ASCII value of the first unmatched character is less in the first string than the second string.
    */
    if (strcmp(enteredPassword, TRUE_PASSWORD) == 0)
    {
        printf("Authentication Successful. Proceeding ");

#ifdef _WIN32
        Sleep(500); // sleep for 0.5 second (500 milliseconds) on Windows
                    // in above code Sleep with capital s is used which is used in windows systems only and sleep with small s is used in other systems like linux and mac os
#else
        usleep(500000); // sleep for 0.5 second (500000 microseconds) on systems other than windows
#endif

        loadingIllusion();
        clearScreen();
        return 0;
    }
    else
    {
        static int passwordAttemptsEntered = PASSWORD_ATTEMPTS_ALLOWED; // static variable to store number of attempts
        passwordAttemptsEntered--;

        if (passwordAttemptsEntered > 0)
        {
            printf("Authentication Failed. %d attempts remaining.\n", passwordAttemptsEntered);
            clearScreen();
            return auth();
        }
        else
        {
            printf("Authentication Failed. Exiting");
#ifdef _WIN32
            Sleep(500); // sleep for 0.5 second (500 milliseconds) on Windows
#else
            usleep(500000); // sleep for 0.5 second (500000 microseconds) on systems other than windows
#endif
            loadingIllusion();
            clearScreen();
            exit(0);
        }
    }
}

// random functions
void loadingIllusion()
{
        for (int i = 0; i < 10; i++)
        {
            printf(".");
    // fflush(stdout); //flush output buffer to display dots immediately
    // uncomment above if code shows dots after 0.5 seconds delay instead of showing dots immediately
    // not needed in this case as dots are shown immediately without this line of code just for record
    #ifdef _WIN32
            Sleep(500); // sleep for 0.5 second (500 milliseconds) on Windows
    #else
            usleep(500000); // sleep for 0.5 second (500000 microseconds) on systems other than windows
    #endif
        }
}

void clearScreen()
{
    printf("\033[2J\033[H");
    /*
    \033[2J clears the entire screen
    \033[H moves the cursor to the top-left corner of the screen
    */
}

void userEntryWait()
{
    printf("Press any key to continue . . .");
    getch();
}