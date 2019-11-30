//==============================================
// Name:           Phu Thong Pham
// Student Number: 106455199
// Email:          ptpham4@myseneca.ca
// Section:        NNN
// Date:           November 23, 2019
//==============================================
// Assignment:     2
// Milestone:      4
//==============================================

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// This source file needs to "know about" the SYSTEM string library functions.
// HINT: The library name is string.h.
//       #include the string.h header file on the next line:
#include <string.h>
// -------------------------------
// Include your contactHelpers header file on the next line:
#include "contactHelpers.h"

// -------------------------------
// define MAXCONTACTS for sizing contacts array (5):
#define MAXCONTACTS 5
#define OPTION_MAX 6
#define PHONENUM_LENGTH 10

//--------------------------------
// Function Definitions
//--------------------------------

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        function definitions below...            |
// +-------------------------------------------------+

// clearKeyboard
void clearKeyboard(void)
{
    while (getchar() != '\n')
        ; // empty execution code block on purpose
}

// pause
void pause(void)
{
    printf("(Press Enter to Continue)");
    clearKeyboard();
}

// getInt
int getInt(void)
{
    int integer;
    char newline;
    do
    {
        scanf("%d%c", &integer, &newline);
        if (newline != '\n')
        {
            clearKeyboard();
            printf("*** INVALID INTEGER *** <Please enter an integer>: ");
        }
    } while (newline != '\n');
    return integer;
}

// getIntInRange
int getIntInRange(int min, int max)
{
    int validInteger;
    do
    {
        validInteger = getInt();
        if (validInteger < min || validInteger > max)
        {
            printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
        }
    } while (validInteger < min || validInteger > max);
    printf("\n");
    return validInteger;
}

// yes
int yes(void)
{
    int valid;
    char answer, newline;
    do
    {
        scanf("%c%c", &answer, &newline);
        if (newline == '\n')
        {
            if (answer == 'y' || answer == 'Y' || answer == 'n' || answer == 'N')
            {
                valid = 1;
            }
            else
            {
                valid = 0;
                printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
            }
        }
        else
        {
            valid = 0;
            clearKeyboard();
            printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
        }
    } while (valid == 0);
    valid = (answer == 'y' || answer == 'Y') ? 1 : 0;
    return valid;
}

// menu
int menu(void)
{
    printf("Contact Management System\n");
    printf("-------------------------\n");
    printf("1. Display contacts\n");
    printf("2. Add a contact\n");
    printf("3. Update a contact\n");
    printf("4. Delete a contact\n");
    printf("5. Search contacts by cell phone number\n");
    printf("6. Sort contacts by cell phone number\n");
    printf("0. Exit\n\n");
    printf("Select an option:> ");
    return getIntInRange(0, OPTION_MAX);
}

// contactManagerSystem
void contactManagerSystem(void)
{
    int exit = 0;
    struct Contact theWalkingDeadContacts[MAXCONTACTS] =
        {
            {{"Rick", {'\0'}, "Grimes"},
             {11, "Trailer Park", 0, "A7A 2J2", "King City"},
             {"4161112222", "4162223333", "4163334444"}},
            {{"Maggie", "R.", "Greene"},
             {55, "Hightop House", 0, "A9A 3K3", "Bolton"},
             {"9051112222", "9052223333", "9053334444"}},
            {{"Morgan", "A.", "Jones"},
             {77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough"},
             {"7051112222", "7052223333", "7053334444"}},
            {{"Sasha", {'\0'}, "Williams"},
             {55, "Hightop House", 0, "A9A 3K3", "Bolton"},
             {"9052223333", "9052223333", "9054445555"}},
        };

    do
    {
        switch (menu())
        {
        case 1:
            displayContacts(theWalkingDeadContacts, MAXCONTACTS);
            pause();
            printf("\n");
            break;

        case 2:
            addContact(theWalkingDeadContacts, MAXCONTACTS);
            printf("\n");
            pause();
            printf("\n");
            break;

        case 3:
            updateContact(theWalkingDeadContacts, MAXCONTACTS);
            printf("\n");
            pause();
            printf("\n");
            break;

        case 4:
            deleteContact(theWalkingDeadContacts, MAXCONTACTS);
            printf("\n");
            pause();
            printf("\n");
            break;

        case 5:
            searchContacts(theWalkingDeadContacts, MAXCONTACTS);
            printf("\n");
            pause();
            printf("\n");
            break;

        case 6:
            sortContacts(theWalkingDeadContacts, MAXCONTACTS);
            printf("\n");
            pause();
            printf("\n");
            break;
        
        case 0:
            printf("Exit the program? (Y)es/(N)o: ");
            exit = yes();
            printf("\n");
            break;
        }
    } while (exit == 0);
    printf("Contact Management System: terminated\n");
}

// +-------------------------------------------------+
// | NOTE:  Copy/Paste your Assignment-2 Milestone-3 |
// |        empty function definitions below...      |
// +-------------------------------------------------+

// getTenDigitPhone:
void getTenDigitPhone(char phoneNum[])
{
    int needInput = 1;
    int i;

    while (needInput == 1)
    {
        scanf("%10s", phoneNum);
        clearKeyboard();

        // (String Length Function: validate entry of 10 characters)
        if (strlen(phoneNum) == PHONENUM_LENGTH)
        {
            needInput = 0;
            // Numerical digit validation
            for (i = 0; i < PHONENUM_LENGTH && needInput == 0; i++)
            {
                if (phoneNum[i] < '0' || phoneNum[i] > '9')
                {
                    needInput = 1;
                    printf("Enter a 10-digit phone number: ");
                }
            }
        }
        else
            printf("Enter a 10-digit phone number: ");
    }
}

// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
    int index = -1;
    int i;
    for (i = 0; i < size && index == -1; i++)
    {
        if (strcmp(contacts[i].numbers.cell, cellNum) == 0)
        {
            index = i;
        }
    }
    return index;
}

// displayContactHeader
void displayContactHeader(void)
{
    printf("+-----------------------------------------------------------------------------+\n");
    printf("|                              Contacts Listing                               |\n");
    printf("+-----------------------------------------------------------------------------+\n");
}

// displayContactFooter
void displayContactFooter(int count)
{
    printf("+-----------------------------------------------------------------------------+\n");
    printf("Total contacts: %d\n\n", count);
}

// displayContact:
void displayContact(const struct Contact *contact)
{
    if (contact->name.middleInitial[0] != '\0')
    {
        printf(" %s %s %s\n", contact->name.firstName, contact->name.middleInitial, contact->name.lastName);
    }
    else
    {
        printf(" %s %s\n", contact->name.firstName, contact->name.lastName);    
    }
    
    printf("    C: %-10s H: %-10s B: %-10s\n", contact->numbers.cell, contact->numbers.home, contact->numbers.business);

    if (contact->address.apartmentNumber > 0)
    {
        printf("       %d %s, Apt# %d, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.apartmentNumber, contact->address.city, contact->address.postalCode);
    }
    else
    {
       printf("       %d %s, %s, %s\n", contact->address.streetNumber, contact->address.street, contact->address.city, contact->address.postalCode); 
    }
    
}

// displayContacts:
void displayContacts(const struct Contact contacts[], int size)
{
    int validContacts = 0;
    int i;

    displayContactHeader();
    for (i = 0; i < size; i++)
    {
        if (contacts[i].numbers.cell[0] != '\0')
        {    
            displayContact(&contacts[i]);
            validContacts++;
        }
    }
    displayContactFooter(validContacts);
}

// searchContacts:
void searchContacts(const struct Contact contacts[], int size)
{
    int index;
    char phoneNum[PHONENUM_LENGTH + 1] = {'\0'};

    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(phoneNum);
    index = findContactIndex(contacts, size, phoneNum);
    if (index >= 0)
    {
        printf("\n");
        displayContact(&contacts[index]);
    }
    else
    {
        printf("*** Contact NOT FOUND ***\n");
    }
}

// addContact:
void addContact(struct Contact contacts[], int size)
{
    int index = findContactIndex(contacts, size, "");
    if (index >= 0)
    {
        contacts[index].numbers.home[0] = '\0';
        getContact(&contacts[index]);
        printf("--- New contact added! ---\n");
    }
    else
    {
        printf("*** ERROR: The contact list is full! ***\n");
    }
}

// updateContact:
void updateContact(struct Contact contacts[], int size)
{
    int index;
    char phoneNum[PHONENUM_LENGTH + 1] = {'\0'};

    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(phoneNum);
    index = findContactIndex(contacts, size, phoneNum);
    if (index >= 0)
    {
        printf("\nContact found:\n");
        displayContact(&contacts[index]);
        printf("\nDo you want to update the name? (y or n): ");
        if (yes())
        {
            getName(&contacts[index].name);
        }
        printf("Do you want to update the address? (y or n): ");
        if (yes())
        {
            getAddress(&contacts[index].address);
        }
        printf("Do you want to update the numbers? (y or n): ");
        if (yes())
        {
            getNumbers(&contacts[index].numbers);
        }
        printf("--- Contact Updated! ---\n");
    }
    else
    {
        printf("*** Contact NOT FOUND ***\n");
    }
}

// deleteContact:
void deleteContact(struct Contact contacts[], int size)
{
    int index;
    char phoneNum[PHONENUM_LENGTH + 1] = {'\0'};

    printf("Enter the cell number for the contact: ");
    getTenDigitPhone(phoneNum);
    index = findContactIndex(contacts, size, phoneNum);
    if (index >= 0)
    {
        printf("\nContact found:\n");
        displayContact(&contacts[index]);
        printf("\nCONFIRM: Delete this contact? (y or n): ");
        if (yes())
        {
            contacts[index].numbers.cell[0] = '\0';
            printf("--- Contact deleted! ---\n");
        }
    }
    else
    {
        printf("*** Contact NOT FOUND ***\n");
    }
}
// sortContacts:
void sortContacts(struct Contact contacts[], int size)
{
   int i, j;
   struct Contact placeholder;

   for (i = 0; i < size - 1; i++)
   {
       for (j = 0; j < size - i - 1; j++)
       {
           if (strcmp(contacts[j].numbers.cell, contacts[j + 1].numbers.cell) > 0)
           {
               placeholder = contacts[j];
               contacts[j] = contacts[j + 1];
               contacts[j + 1] = placeholder;
           }
       }
   }
   printf("--- Contacts sorted! ---\n");
}