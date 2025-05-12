#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#define PASSWORD_LENGTH 30
#define TRUE_PASSWORD "abcd1234"
#define PASSWORD_ATTEMPTS_ALLOWED 3
#define MAX_SLOTS 10

void loadingIllusion();
void clearScreen();
void userEntryWait();

int auth();
void input();
void delete_record();
void searchCar();
void displayAllCars();
int getAvailableSlot();
int isSlotAvailable();

int main()
{
    auth();
    clearScreen();
    int choice;
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
        printf("\n\n\t\t\t  5. Search for a Car");
        printf("\n\n\t\t\t  6. Display All Parked Cars");
        printf("\n\n\t\t\t  7. Exit Program");
        printf("\n\n\t\t\t  8. Display Available Slots");
        printf(" \n\t\t\t======================\n\n");
        printf("\t\t\t Select Your Choice :: ");
        if (scanf(" %d", &choice) != 1)
        {
            printf("Invalid input. Please enter a valid choice.\n");
            fflush(stdin);
            userEntryWait();
            continue;
        }
        switch (choice)
        {
        case 1:
        {
            if (!isSlotAvailable())
            {
                printf("\n\n\t\tParking Full! No slots available.\n");
                userEntryWait();
                break;
            }
            clearScreen();
            input();
            userEntryWait();
            break;
        }
        case 2:
        {
            clearScreen();
            printf("\n\n\t\t=== View the Records in the Parking Database ===\n");
            displayAllCars();
            userEntryWait();
            break;
        }
        case 3:
        {
            FILE *infile;
            infile = fopen("parkingProjectFile.txt", "r");
            int currentVehicleNumber, slotNumber;
            float currentTimeCount;
            char currentDriverName[15], currentMembershipStatus;
            while (fscanf(infile, "%d %f %s %c %d", &currentVehicleNumber, &currentTimeCount, currentDriverName, &currentMembershipStatus, &slotNumber) != EOF)
            {
                printf("\n\n\t\tThe Car No : %d\n", currentVehicleNumber);
                float cost = (currentMembershipStatus == 'y' || currentMembershipStatus == 'Y') ? currentTimeCount * 20 : currentTimeCount * 25;
                printf("\t\tParking Cost: %.2f rupees\n", cost);
                printf("\t\tDriver Name: %s\n", currentDriverName);
                printf("\t\tSlot Number: %d\n", slotNumber);
            }
            fclose(infile);
            userEntryWait();
            break;
        }
        case 4:
        {
            delete_record();
            userEntryWait();
            break;
        }
        case 5:
        {
            searchCar();
            userEntryWait();
            break;
        }
        case 6:
        {
            displayAllCars();
            userEntryWait();
            break;
        }
        case 8:
        {
            clearScreen();
            int usedSlots[MAX_SLOTS] = {0};
            FILE *file = fopen("parkingProjectFile.txt", "r");
            int v, slot;
            float t;
            char d[15], m;
            while (file && fscanf(file, "%d %f %s %c %d", &v, &t, d, &m, &slot) != EOF)
            {
                if (slot >= 1 && slot <= MAX_SLOTS)
                    usedSlots[slot - 1] = 1;
            }
            if (file)
                fclose(file);
            int availableSlots = 0;
            for (int i = 0; i < MAX_SLOTS; i++)
            {
                if (!usedSlots[i])
                    availableSlots++;
            }
            printf("\n\n\t\tAvailable Slots: %d\n", availableSlots);
            userEntryWait();
            break;
        }
        case 7:
        {
            char confirmExit;
            printf("\n\n\t\tAre you sure you want to exit? (y/n): ");
            while (scanf(" %c", &confirmExit) != 1 || (confirmExit != 'y' && confirmExit != 'Y' && confirmExit != 'n' && confirmExit != 'N'))
            {
                printf("Invalid input. Please enter y or n only: ");
                while (getchar() != '\n');
            }
            if (confirmExit == 'y' || confirmExit == 'Y')
            {
                clearScreen();
                printf("\n\n\n\t\t\tThank you for using our software \n");
                loadingIllusion();
                exit(0);
            }
            break;
        }
        default:
        {
            printf("\n\n\t\tInvalid input. Please enter a valid choice.\n");
        }
        }
        getchar();
    }
}

void delete_record()
{
    int vehicleNumberToDelete;
    clearScreen();
    printf("\n\n\t\tEnter the car no you want to get depart : ");
    scanf("%d", &vehicleNumberToDelete);
    FILE *inputFile;
    inputFile = fopen("parkingProjectFile.txt", "r");
    FILE *outputFile;
    outputFile = fopen("temp.txt", "w");
    int currentVehicleNumber, slotNumber;
    float currentTimeCount;
    char currentDriverName[15], currentMembershipStatus;
    int found = 0;
    while (fscanf(inputFile, "%d %f %s %c %d", &currentVehicleNumber, &currentTimeCount, currentDriverName, &currentMembershipStatus, &slotNumber) != EOF)
    {
        if (currentVehicleNumber != vehicleNumberToDelete)
        {
            fprintf(outputFile, "%d %.2f %s %c %d\n", currentVehicleNumber, currentTimeCount, currentDriverName, currentMembershipStatus, slotNumber);
        }
        else
        {
            found = 1;
        }
    }
    if (found)
        printf("\n\n\t\tParking Record Deleted\n");
    else
        printf("\n\n\t\tNo such car found.\n");
    fclose(inputFile);
    fclose(outputFile);
    remove("parkingProjectFile.txt");
    rename("temp.txt", "parkingProjectFile.txt");
}

void input()
{
    char driverName[15];
    int vehicleNumber;
    float timeCount;
    char membershipStatus;

    printf("\n\n\t\tEnter the name of driver : ");
    while (1)
    {
        fgets(driverName, sizeof(driverName), stdin);
        size_t len = strlen(driverName);
        if (len > 0 && driverName[len - 1] == '\n')
        {
            driverName[len - 1] = '\0'; // Remove trailing newline
        }
        if (strlen(driverName) > 0)
        {
            break;
        }
        printf("\n\n\t\tInvalid input. Please enter a valid name: ");
    }
    printf("\n\n\t\tEnter the car no : ");
    while (scanf("%d", &vehicleNumber) != 1)
    {
        printf("\n\n\t\tInvalid input. Please enter a valid car number: ");
        while (getchar() != '\n')
            ;
    }
    printf("\n\n\t\tEnter the no of hours of stay : ");
    while (scanf("%f", &timeCount) != 1)
    {
        printf("\n\n\t\tInvalid input. Please enter a valid number of hours: ");
        while (getchar() != '\n')
            ;
    }
    if (timeCount < 0)
    {
        printf("\n\n\t\tThe car cannot be parked for negative hours.");
        printf("\n\n\t\tParking not possible!!");
        userEntryWait();
        return;
    }
    else if (timeCount < 8)
    {
        printf("\n\n\t\tAre you a V.I.P: y/n ");
        while (scanf(" %c", &membershipStatus) != 1 || (membershipStatus != 'y' && membershipStatus != 'Y' && membershipStatus != 'n' && membershipStatus != 'N'))
        {
            printf("Invalid input. Please enter y or n only: ");
            while (getchar() != '\n')
                ;
        }
        FILE *f1 = fopen("parkingProjectFile.txt", "a");
        int slot = getAvailableSlot();
        fprintf(f1, "%d %.2f %s %c %d\n", vehicleNumber, timeCount, driverName, membershipStatus, slot);
        fclose(f1);
        printf("\n\n\t\tCar parked at slot number: %d\n", slot);
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
    char enteredPassword[PASSWORD_LENGTH];
    char ch;
    int i = 0;

    printf("\n\n\n\n\n\n\n\t\t\t\tCar Parking Reservation System Login");
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\tEnter Password: ");

    while (i < PASSWORD_LENGTH - 1)
    {
        ch = getchar();

        if (ch == '\r' || ch == '\n') // check for Enter key
        {
            enteredPassword[i] = '\0'; // null character to end string
            break;
        }
        else if (ch == '\b' && i > 0) // check for backspace
        {
            printf("\b \b"); // to erase the character from screen
            i--;             // move back cursor
        }
        else if (ch != '\b') // storing password
        {
            enteredPassword[i] = ch;
            i++;
            printf("*"); // to show * instead of entered character
        }
    }

    printf("\n\n\n\n\n");

    if (strcmp(enteredPassword, TRUE_PASSWORD) == 0)
    {
        printf("Authentication Successful. Proceeding ");

#ifdef _WIN32
        Sleep(500);
#else
        usleep(500000);
#endif

        loadingIllusion();
        clearScreen();
        return 0;
    }
    else
    {
        static int passwordAttemptsEntered = PASSWORD_ATTEMPTS_ALLOWED;
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
            Sleep(500);
#else
            usleep(500000);
#endif
            loadingIllusion();
            clearScreen();
            exit(0);
        }
    }
}

void loadingIllusion()
{
    for (int i = 0; i < 10; i++)
    {
        printf(".");
#ifdef _WIN32
        Sleep(500);
#else
        usleep(500000);
#endif
    }
}

void clearScreen()
{
    printf("\033[2J\033[H");
}

void userEntryWait()
{
    printf("Press Enter to continue . . .");
    while (getchar() != '\n'); // Wait for Enter key
}

int isSlotAvailable()
{
    int usedSlots[MAX_SLOTS] = {0};
    FILE *file = fopen("parkingProjectFile.txt", "r");
    int v, slot;
    float t;
    char d[15], m;
    while (file && fscanf(file, "%d %f %s %c %d", &v, &t, d, &m, &slot) != EOF)
    {
        if (slot >= 1 && slot <= MAX_SLOTS)
            usedSlots[slot - 1] = 1;
    }
    if (file)
        fclose(file);
    for (int i = 0; i < MAX_SLOTS; i++)
        if (!usedSlots[i])
            return 1;
    return 0;
}

int getAvailableSlot()
{
    int usedSlots[MAX_SLOTS] = {0};
    FILE *file = fopen("parkingProjectFile.txt", "r");
    int v, slot;
    float t;
    char d[15], m;
    while (file && fscanf(file, "%d %f %s %c %d", &v, &t, d, &m, &slot) != EOF)
    {
        if (slot >= 1 && slot <= MAX_SLOTS)
            usedSlots[slot - 1] = 1;
    }
    if (file)
        fclose(file);
    for (int i = 0; i < MAX_SLOTS; i++)
        if (!usedSlots[i])
            return i + 1;
    return -1;
}

void displayAllCars()
{
    FILE *file = fopen("parkingProjectFile.txt", "r");
    int v, slot;
    float t;
    char d[15], m;
    printf("\n%-10s %-10s %-15s %-10s %-10s\n", "Car No", "Hours", "Driver Name", "VIP", "Slot");
    printf("-------------------------------------------------------------\n");
    while (file && fscanf(file, "%d %f %s %c %d", &v, &t, d, &m, &slot) != EOF)
    {
        printf("%-10d %-10.2f %-15s %-10c %-10d\n", v, t, d, m, slot);
    }
    if (file)
        fclose(file);
}

void searchCar()
{
    int searchType;
    printf("\nSearch by: 1. Vehicle Number  2. Driver Name\nEnter choice: ");
    scanf("%d", &searchType);
    FILE *file = fopen("parkingProjectFile.txt", "r");
    int v, slot, found = 0;
    float t;
    char d[15], m;
    if (searchType == 1)
    {
        int searchNo;
        printf("Enter vehicle number: ");
        scanf("%d", &searchNo);
        while (file && fscanf(file, "%d %f %s %c %d", &v, &t, d, &m, &slot) != EOF)
        {
            if (v == searchNo)
            {
                printf("\nFound: Car No: %d, Driver: %s, Hours: %.2f, VIP: %c, Slot: %d\n", v, d, t, m, slot);
                found = 1;
            }
        }
    }
    else if (searchType == 2)
    {
        char searchName[15];
        printf("Enter driver name: ");
        scanf("%s", searchName);
        while (file && fscanf(file, "%d %f %s %c %d", &v, &t, d, &m, &slot) != EOF)
        {
            if (strcmp(d, searchName) == 0)
            {
                printf("\nFound: Car No: %d, Driver: %s, Hours: %.2f, VIP: %c, Slot: %d\n", v, d, t, m, slot);
                found = 1;
            }
        }
    }
    if (!found)
        printf("\nNo matching record found.\n");
    if (file)
        fclose(file);
}