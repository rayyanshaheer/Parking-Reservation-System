#include<stdio.h>
#include<string.h>
#include<stdlib.h>//for system functions
#include<conio.h>//for getch

//to check which system is program running on
#ifdef _WIN32
    #include <windows.h> //for Sleep function
#else
    #include <unistd.h> //for sleep function
#endif
//above notice the capitilization in name of sleep and Sleep function both have different meangning and are used for different systems.

#define PASSWORD_LENGTH 30 //length of password
#define TRUE_PASSWORD "abcd1234" //password for 
#define PASSWORD_ATTEMPTS_ALLOWED 3 

int auth();//function to authenticate user
void loadingIllusion();//function to show loading illusion
void clearScreen();//function to clear screen

void input();//function to add cars to parking //still developing

int main()
{
    printf("\n\n\t\t\t\tCar Parking System\n");
    if(auth()!=0)
    {
        return 1;
    }

    printf("Welcome to the Car Parking System\n");
    
    
    return 0;
}

int auth()
{
    char enteredPassword[PASSWORD_LENGTH];//to store entered password
    char ch;//to store entered character
    int i = 0;
    
    printf("\n\nEnter password:");
    
    while(i<PASSWORD_LENGTH-1)
    {
        ch = getch();
        
        if(ch == '\r' || ch =='\n' )//check for Enter key 
        {
            enteredPassword[i] = '\0';//null character to end string
            break;
        }
        else if(ch == '\b' && i > 0)// check for backspace
        {
            printf("\b \b");//to erase the character from screen
            i--;
        }
        else if(ch != '\b')//storing password
        {
            enteredPassword[i] = ch;
            i++;
            printf("*");//to show * instead of entered character aka passsword masking
        }
    }
    
    printf("\n");

    /*
    strcmp function returns three values:
    0 If both the strings are identical (equal)
    positive value: If the ASCII value of the first unmatched character is greater in the first string than the second string.
    negative value: If the ASCII value of the first unmatched character is less in the first string than the second string.
    */
    if(strcmp(enteredPassword, TRUE_PASSWORD) == 0)
    {
        printf("Authentication Successful. Proceeding ");

        #ifdef _WIN32
            Sleep(500);//sleep for 0.5 second (500 milliseconds) on Windows
            //in above code Sleep with capital s is used which 
        #else
            usleep(500000);//sleep for 0.5 second (500000 microseconds) on systems other than windows
        #endif

        loadingIllusion();
        clearScreen();
        return 0;
    }
    else
    {
        static int passwordAttemptsEntered = PASSWORD_ATTEMPTS_ALLOWED;//static variable to store number of attempts
        passwordAttemptsEntered--;
        
        if(passwordAttemptsEntered > 0)
        {
            printf("Authentication Failed. %d attempts remaining.\n", passwordAttemptsEntered);
            return auth();
        }
        else
        {
            printf("Authentication Failed. Exiting");
            #ifdef _WIN32
                Sleep(500);//sleep for 0.5 second (500 milliseconds) on Windows
            #else
                usleep(500000);//sleep for 0.5 second (500000 microseconds) on systems other than windows
            #endif
            loadingIllusion();
            clearScreen();
            return 1;
        }
    }
}

void loadingIllusion()
{
    for (int i=0;i<10;i++)
    {
        printf(".");
        //fflush(stdout); //flush output buffer to display dots immediately
        //uncomment above if code shows  undefined behaviour
        #ifdef _WIN32
            Sleep(500);//sleep for 0.5 second (500 milliseconds) on Windows
        #else
            usleep(500000);//sleep for 0.5 second (500000 microseconds) on systems other than windows
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

void input()
{
    clearScreen();
    char tempDName[100];
}
