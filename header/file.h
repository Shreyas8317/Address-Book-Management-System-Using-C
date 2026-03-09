#ifndef FILE_H      // Include guard start: prevents multiple inclusion
#define FILE_H      

#include "contact.h" // Include contact definitions (AddressBook type)


// Function to save all contacts from the address book into a CSV file
void saveContactsToFile(AddressBook *addressBook);

// Function to load contacts from the CSV file into the address book
void loadContactsFromFile(AddressBook *addressBook);

#endif               // Include guard end
