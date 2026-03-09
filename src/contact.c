#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/contact.h"  // Header containing Contact struct and MAX_CONTACTS
#include "../header/file.h"     // Header containing file read/write functions

/* ----------- Colors for Terminal Output ----------- */
#define RESET   "\033[0m"       // Reset console color
#define YELLOW  "\033[1;33m"    // Yellow for prompts
#define CYAN    "\033[1;36m"    // Cyan for headings
#define RED     "\033[1;31m"    // Red for errors
#define GREEN   "\033[1;32m"    // Green for success messages

/* ----------- Utility Functions ----------- */

// Print a horizontal line for tables
void printLine() {
    printf("+------+----------------------+-----------------+------------------------------+\n");
}

/* ----------- Swap Helper Function ----------- */

// Swap two contacts (used in sorting)
void swapContacts(Contact *a, Contact *b) {
    Contact temp = *a;
    *a = *b;
    *b = temp;
}

/* ----------- Sorting Functions ----------- */

// Bubble sort contacts by Name
void sortByName(AddressBook *addressBook) {
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
            if (strcompare(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) {
                swapContacts(&addressBook->contacts[j], &addressBook->contacts[j + 1]);
            }
        }
    }
}

// Bubble sort contacts by Phone
void sortByPhone(AddressBook *addressBook) {
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
            if (strcompare(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone) > 0) {
                swapContacts(&addressBook->contacts[j], &addressBook->contacts[j + 1]);
            }
        }
    }
}

// Bubble sort contacts by Email
void sortByEmail(AddressBook *addressBook) {
    for (int i = 0; i < addressBook->contactCount - 1; i++) {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++) {
            if (strcompare(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0) {
                swapContacts(&addressBook->contacts[j], &addressBook->contacts[j + 1]);
            }
        }
    }
}

// Ask user which field to sort and perform sort
void sortContacts(AddressBook *addressBook) {
    int choice;
    if (addressBook->contactCount == 0) {
        printf(RED "No contacts to sort.\n" RESET);
        return;
    }

    printf(CYAN "\n--- Sort Contacts ---\n" RESET);
    printf("1. Sort by Name\n2. Sort by Phone\n3. Sort by Email\n4. Exit\n");

    while (1) {
        printf(YELLOW "Enter your choice: " RESET YELLOW);
        fflush(stdout);
        if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 4) {
            printf(RESET);
            while (getchar() != '\n'); // Clear input buffer
            break;
        } else {
            printf(RESET RED "Invalid input! Please enter 1–4.\n" RESET);
            while (getchar() != '\n'); // Clear invalid input
        }
    }

    switch (choice) {
        case 1: sortByName(addressBook); printf(GREEN "Sorted by Name.\n" RESET); break;
        case 2: sortByPhone(addressBook); printf(GREEN "Sorted by Phone.\n" RESET); break;
        case 3: sortByEmail(addressBook); printf(GREEN "Sorted by Email.\n" RESET); break;
        case 4: return;
    }
}

/* ----------- List Contacts ----------- */

// List all contacts with sorting option
void listContacts(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf(RED "No contacts available.\n" RESET);
        return;
    }

    sortContacts(addressBook); // Ask user how to sort

    printLine();
    printf("| %-4s | %-20s | %-15s | %-28s |\n", "S.No", "Name", "Phone", "Email");
    printLine();

    for (int i = 0; i < addressBook->contactCount; i++) {
        char name[21], phone[16], email[29];

        strncpy(name, addressBook->contacts[i].name, 20);
        name[20] = '\0';

        strncpy(phone, addressBook->contacts[i].phone, 15);
        phone[15] = '\0';

        strncpy(email, addressBook->contacts[i].email, 28);
        email[28] = '\0';

        printf("| %-4d | %-20s | %-15s | %-28s |\n",
               i + 1, name, phone, email);
    }

    printLine();
}

/* ----------- Initialize and Save ----------- */

// Initialize address book and load from file
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

// Save contacts to file and exit program
void saveAndBack(AddressBook *addressBook) {
    saveContactsToFile(addressBook);
    return;
}

/* ----------- Custom String Functions ----------- */

// Compare two strings
int strcompare(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) return str1[i] - str2[i];
        i++;
    }
    return str1[i] - str2[i];
}

// Copy string from src to dest
void strcopy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Return length of string
int strlength(const char *str) {
    int length = 0;
    while (str[length] != '\0') length++;
    return length;
}

/* ----------- Validation Functions ----------- */

// Validate name (letters, space, hyphen)
int isValidName(char name[]) {
    int k = 0;
    do {
        if (!((name[k] >= 'A' && name[k] <= 'Z') ||
              (name[k] >= 'a' && name[k] <= 'z') ||
              name[k] == ' ' || name[k] == '-'))
            return 0;
        k++;
    } while (name[k] != '\0');
    return 1;
}

// Validate phone (10 digits)
int isValidPhone(char phone[]) {
    if (strlength(phone) != 10) return 0;
    int p = 0;
    do {
        if(phone[0] == '0') return 0; // First digit should not be 0
        if (!(phone[p] >= '0' && phone[p] <= '9')) return 0;
        p++;
    } while (phone[p] != '\0');
    return 1;
}

// Validate email format
int isValidEmail(char email[]) {
    if (email[0] == '@' || email[0] == '\0') return 0;

    int len = strlength(email);
    if (!(len >= 4 &&
          email[len - 4] == '.' &&
          email[len - 3] == 'c' &&
          email[len - 2] == 'o' &&
          email[len - 1] == 'm'))
        return 0;

    int atCount = 0, i = 0;
    do {
        if ((email[i] >= 'a' && email[i] <= 'z') ||
            (email[i] >= '0' && email[i] <= '9') ||
            email[i] == '.' || email[i] == '_' ||
            email[i] == '@' || email[i] == '-') {
            if (email[i] == '@') atCount++;
        } else return 0;
        i++;
    } while (email[i] != '\0');

    if (atCount != 1) return 0;

    int index1 = -1, index2 = -1;
    i = 0;
    do {
        if (email[i] == '@') index1 = i;
        if (index1 != -1 && email[i] == '.') {
            index2 = i;
            break;
        }
        i++;
    } while (email[i] != '\0');

    if (index1 == -1 || index2 == -1) return 0;
    if (index2 - index1 <= 1) return 0;

    return 1;
}

/* ----------- Duplicate Checks ----------- */

// Check if phone exists
int isDuplicatePhone(AddressBook *addressBook, char phone[]) {
    for (int j = 0; j < addressBook->contactCount; j++) {
        if (strcompare(addressBook->contacts[j].phone, phone) == 0)
            return 1;
    }
    return 0;
}

// Check if email exists
int isDuplicateEmail(AddressBook *addressBook, char email[]) {
    for (int c = 0; c < addressBook->contactCount; c++) {
        if (strcompare(addressBook->contacts[c].email, email) == 0)
            return 1;
    }
    return 0;
}

/* ----------- Create Contact ----------- */

void createContact(AddressBook *addressBook) {
    char name[50], phone[20], email[50];

    if (addressBook->contactCount >= MAX_CONTACTS) {
        printf(RED "Address book is full. Cannot add more contacts.\n" RESET);
        return;
    }

    // Input name
    do {
        printf("Enter name: ");
        scanf(" %[^\n]", name);
        if (!isValidName(name)) {
            printf(RED "Invalid name. Enter valid name.\n" RESET);
            continue;
        }
        break;
    } while (1);

    // Input phone
    do {
        printf("Enter phone: ");
        scanf(" %[^\n]", phone);
        if (!isValidPhone(phone)) {
            printf(RED "Invalid phone number.\n" RESET);
            continue;
        }
        if (isDuplicatePhone(addressBook, phone)) {
            printf(RED "Phone already exists.\n" RESET);
            continue;
        }
        break;
    } while (1);

    // Input email
    do {
        printf("Enter email: ");
        scanf(" %[^\n]", email);
        if (!isValidEmail(email)) {
            printf(RED "Invalid email.\n" RESET);
            continue;
        }
        if (isDuplicateEmail(addressBook, email)) {
            printf(RED "Email already exists.\n" RESET);
            continue;
        }
        break;
    } while (1);

    // Save contact
    strcopy(addressBook->contacts[addressBook->contactCount].name, name);
    strcopy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcopy(addressBook->contacts[addressBook->contactCount].email, email);

    addressBook->contactCount++;
    printf(GREEN "Contact added successfully!\n" RESET);
}

/* ----------- Search Contact ----------- */

// Print header for table
void printHeader() {
    printLine();
    printf("| %-4s | %-20s | %-15s | %-28s |\n", "S.No", "Name", "Phone", "Email");
    printLine();
}

// Print single contact row
void printContactRow(int index, Contact c) {
    char name[21], phone[16], email[29];

    strncpy(name, c.name, 20); name[20] = '\0';
    strncpy(phone, c.phone, 15); phone[15] = '\0';
    strncpy(email, c.email, 28); email[28] = '\0';

    printf("| %-4d | %-20s | %-15s | %-28s |\n", index + 1, name, phone, email);
}

// Search by Name
void searchByName(AddressBook *addressBook, char searchName[]) {
    int found = 0;
    printHeader();
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcompare(addressBook->contacts[i].name, searchName) == 0) {
            printContactRow(i, addressBook->contacts[i]);
            found = 1;
        }
    }
    if (!found) printf(RED "Contact not found.\n" RESET);
    printLine();
}

// Search by Phone
void searchByPhone(AddressBook *addressBook, char searchPhone[]) {
    int found = 0;
    printHeader();
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcompare(addressBook->contacts[i].phone, searchPhone) == 0) {
            printContactRow(i, addressBook->contacts[i]);
            found = 1;
        }
    }
    if (!found) printf(RED "Contact not found.\n" RESET);
    printLine();
}

// Search by Email
void searchByEmail(AddressBook *addressBook, char searchEmail[]) {
    int found = 0;
    printHeader();
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcompare(addressBook->contacts[i].email, searchEmail) == 0) {
            printContactRow(i, addressBook->contacts[i]);
            found = 1;
        }
    }
    if (!found) printf(RED "Contact not found.\n" RESET);
    printLine();
}

// General search interface
void searchContact(AddressBook *addressBook) {
    int choice;
    char query[50];

    do {
        printf(CYAN "\n--- Search Contact ---\n" RESET);
        printf("1. Search By Name\n2. Search By Phone Number\n3. Search By Email\n4. Exit\n");

        while (1) {
            printf(YELLOW "Enter your choice: " RESET YELLOW);
            fflush(stdout);
            if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 4) {
                printf(RESET);
                while (getchar() != '\n');
                break;
            } else {
                printf(RESET RED "Invalid input! Please enter 1–4.\n" RESET);
                while (getchar() != '\n');
            }
        }

        switch (choice) {
            case 1:
                printf("Enter name to search: ");
                scanf(" %[^\n]", query);
                searchByName(addressBook, query);
                return;
            case 2:
                printf("Enter phone number to search: ");
                scanf(" %[^\n]", query);
                searchByPhone(addressBook, query);
                return;
            case 3:
                printf("Enter email to search: ");
                scanf(" %[^\n]", query);
                searchByEmail(addressBook, query);
                return;
            case 4:
                return;
        }
    } while (choice != 4);
}

/* ----------- Edit Contact ----------- */

// Edit Name
void editName(AddressBook *addressBook, int index) {
    char newInput[50];
    do {
        printf("Enter new name: ");
        scanf(" %[^\n]", newInput);
        if (!isValidName(newInput)) {
            printf(RED "Invalid name. Please try again.\n" RESET);
            continue;
        }
        strcopy(addressBook->contacts[index].name, newInput);
        printf(GREEN "Name updated successfully.\n" RESET);
        break;
    } while (1);
}

// Edit Phone
void editPhone(AddressBook *addressBook, int index) {
    char newInput[20];
    do {
        printf("Enter new phone number: ");
        scanf(" %[^\n]", newInput);
        if (!isValidPhone(newInput)) {
            printf(RED "Invalid phone number.\n" RESET);
            continue;
        }
        if (isDuplicatePhone(addressBook, newInput)) {
            printf(RED "Phone number already exists.\n" RESET);
            continue;
        }
        strcopy(addressBook->contacts[index].phone, newInput);
        printf(GREEN "Phone updated successfully.\n" RESET);
        break;
    } while (1);
}

// Edit Email
void editEmail(AddressBook *addressBook, int index) {
    char newInput[50];
    do {
        printf("Enter new email: ");
        scanf(" %[^\n]", newInput);
        if (!isValidEmail(newInput)) {
            printf(RED "Invalid email.\n" RESET);
            continue;
        }
        if (isDuplicateEmail(addressBook, newInput)) {
            printf(RED "Email already exists.\n" RESET);
            continue;
        }
        strcopy(addressBook->contacts[index].email, newInput);
        printf(GREEN "Email updated successfully.\n" RESET);
        break;
    } while (1);
}

// Edit contact interface
void editContact(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf(RED "No contacts to edit.\n" RESET);
        return;
    }

    searchContact(addressBook);

    char confirm;
    printf(YELLOW "\nWas the contact found in the list above? (y/n): " RESET);
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
    printf(RED "Edit cancelled. No valid contact selected.\n" RESET);
    return;
    }


    int index;
    printf("\nEnter serial number of contact to edit: ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= addressBook->contactCount) {
        printf(RED "Invalid serial number.\n" RESET);
        return;
    }

    int choice;
    do {
        printf(CYAN "\n--- Edit Contact ---\n" RESET);
        printf("1. Edit Name\n2. Edit Phone\n3. Edit Email\n4. Exit\n");

        while (1) {
            printf(YELLOW "Enter your choice: " RESET YELLOW);
            fflush(stdout);
            if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 4) {
                printf(RESET);
                while (getchar() != '\n');
                break;
            } else {
                printf(RESET RED "Invalid input! Please enter 1–4.\n" RESET);
                while (getchar() != '\n');
            }
        }

        switch (choice) {
            case 1: editName(addressBook, index); break;
            case 2: editPhone(addressBook, index); break;
            case 3: editEmail(addressBook, index); break;
            case 4: return;
        }
    } while (choice != 4);
}

/* ----------- Delete Contact ----------- */

void deleteContact(AddressBook *addressBook) {
    if (addressBook->contactCount == 0) {
        printf(RED "No contacts to delete.\n" RESET);
        return;
    }

    searchContact(addressBook);

    char confirm;
    printf(YELLOW "\nWas the contact found in the list above? (y/n): " RESET);
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
    printf(RED "Delete cancelled. No valid contact selected.\n" RESET);
    return;
    }

    int index;
    printf("Enter serial number of contact to delete: ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= addressBook->contactCount) {
        printf(RED "Invalid serial number.\n" RESET);
        return;
    }

    for (int i = index; i < addressBook->contactCount - 1; i++) {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;
    printf(GREEN "Contact deleted successfully.\n" RESET);
}
