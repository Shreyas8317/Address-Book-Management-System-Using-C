#ifndef CONTACT_H
#define CONTACT_H

/* ----------- Maximum Limits ----------- */
#define MAX_CONTACTS 100  // Maximum number of contacts allowed in AddressBook

/* ----------- Contact Structure ----------- */
typedef struct
{
    char name[50];   // Contact's full name
    char phone[20];  // Contact's phone number
    char email[50];  // Contact's email address
} Contact;

/* ----------- Address Book Structure ----------- */
typedef struct
{
    int contactCount;       // Current number of contacts in the address book
    Contact contacts[100];  // Array storing all contacts
} AddressBook;

/* ----------- Custom String Utility Functions ----------- */
int strcompare(const char *str1, const char *str2); // Compare two strings (like strcmp)
void strcopy(char *dest, const char *src);          // Copy string from src to dest
int strlength(const char *str);                     // Calculate length of string

/* ----------- Validation Functions ----------- */
int isValidName(char name[]);   // Check if name contains only letters, spaces, or hyphens
int isValidPhone(char phone[]); // Check if phone number is 10 digits
int isValidEmail(char email[]); // Check if email is valid (basic format validation)

/* ----------- Duplicate Check Functions ----------- */
int isDuplicateName(AddressBook *addressBook, char name[]);   // Check if name already exists
int isDuplicatePhone(AddressBook *addressBook, char phone[]); // Check if phone already exists
int isDuplicateEmail(AddressBook *addressBook, char email[]); // Check if email already exists

/* ----------- Search Functions ----------- */
void searchbyname(AddressBook *addressBook, char searchName[]);   // Search contact by name
void searchbyphone(AddressBook *addressBook, char searchPhone[]); // Search contact by phone
void searchbyemail(AddressBook *addressBook, char searchEmail[]); // Search contact by email

/* ----------- Edit Functions ----------- */
void editName(AddressBook *addressBook,int index);  // Edit contact name at given index
void editPhone(AddressBook *addressBook,int index); // Edit contact phone at given index
void editEmail(AddressBook *addressBook,int index); // Edit contact email at given index

/* ----------- CRUD Functions ----------- */
void createContact(AddressBook *addressBook); // Add a new contact
void searchContact(AddressBook *addressBook); // Search for a contact (menu-driven)
void editContact(AddressBook *addressBook);   // Edit an existing contact (menu-driven)
void deleteContact(AddressBook *addressBook); // Delete a contact
void listContacts(AddressBook *addressBook);  // List all contacts with formatting
void initialize(AddressBook *addressBook);    // Initialize AddressBook and load from file
void saveContactsToFile(AddressBook *addressBook); // Save all contacts to file
void saveAndBack(AddressBook *addressBook);        // Save and exit program

#endif
