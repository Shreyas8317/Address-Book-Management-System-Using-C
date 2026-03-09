/*
Name       : Shreyas Santosh Pawangadkar
Batch Id   : 25021_308
Project    : AddressBook Management System
Date       : 17/09/2025

Description:
This project implements a simple AddressBook that allows users to:
- Create contacts with Name, Phone, and Email
- Search contacts by Name, Phone, or Email
- Edit existing contacts
- Delete contacts
- List all contacts with optional sorting
- Save contacts to a CSV file and load them automatically on startup

Input:  
- User selects options from the menu (1–7)
- Provides Name, Phone, and Email when creating or editing contacts

Sample Menu:
========================
 Address Book Menu
========================
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save contacts
7. Exit
========================
Enter your choice (1–7): 

Output:
- Confirmation messages on creating, editing, deleting contacts
- Sorted contact list when listing
- Search results for matching contacts
- Error messages for invalid input or duplicates
- Automatic saving and loading of contacts

*/


#include <stdio.h>
#include <stdlib.h>
#include "./header/contact.h"

/* Colors for styling */
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define MAGENTA "\033[1;35m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
#define BOLD    "\033[1m"

void printMenu()
{
    printf(CYAN "\n================= Address Book Menu =================\n" RESET);
    printf(MAGENTA "1. Create contact\n" RESET);
    printf(MAGENTA "2. Search contact\n" RESET);
    printf(MAGENTA "3. Edit contact\n" RESET);
    printf(MAGENTA "4. Delete contact\n" RESET);
    printf(MAGENTA "5. List all contacts\n" RESET);
    printf(MAGENTA "6. Save contacts\n" RESET);
    printf(MAGENTA "7. Exit\n" RESET);
    printf(CYAN "=====================================================\n" RESET);
}

int main()
{
    int choice = 0;
    AddressBook addressBook;
    initialize(&addressBook);

    do
    {
        printMenu();

        /* Input validation loop */
        while (1)
        { 
            printf(YELLOW "Enter your choice (1-7): " RESET);
            if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 7)
            {
                while (getchar() != '\n'); // clear buffer
                break; // valid choice
            }
            else
            {
                printf(RED "Invalid input! Please enter a number between 1 and 7.\n" RESET);
                while (getchar() != '\n'); // clear invalid input
            }
        }

        /* Handle menu choice */
        switch (choice)
        {
        case 1: 
            createContact(&addressBook); 
            break;
        case 2: 
            searchContact(&addressBook); 
            break;
        case 3: 
            editContact(&addressBook); 
            break;
        case 4: 
            deleteContact(&addressBook); 
            break;
        case 5: 
            listContacts(&addressBook); 
            break;
        case 6: 
            saveAndBack(&addressBook);
            printf(BLUE "✔ Contacts saved successfully!\n" RESET);
            break;
        case 7: 
            printf(BLUE "Exiting program... Goodbye!\n" RESET);
            break;
        }

    } while (choice != 7);

    return 0;
}
