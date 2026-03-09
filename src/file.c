#include <stdio.h>
#include "../header/contact.h"
#include "../header/file.h"

/* ----------- Save Contacts to File ----------- */
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr;

    // Open the file in write mode ("w") to overwrite previous data
    fptr = fopen("contacts.csv", "w");

    if(fptr == NULL)
    {
        // File couldn't be opened, print error message
        printf("File not opened!!\n");
        return;
    }
  
    // Loop through all contacts in the address book
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        // Skip contacts with empty name, phone, or email
        if (strlength(addressBook->contacts[i].name) == 0 ||
            strlength(addressBook->contacts[i].phone) == 0 ||
            strlength(addressBook->contacts[i].email) == 0) {
            continue; 
        }

        // Write contact information in CSV format: name,phone,email
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    // Close the file after writing
    fclose(fptr);
}

/* ----------- Load Contacts from File ----------- */
void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.csv", "r");

    if (fptr == NULL) 
    {
        // No saved contacts found, start with empty address book
        printf("Note: No saved contacts found. Starting fresh.\n");
        return;
    }

    // Initialize contact count
    addressBook->contactCount = 0;

    // Read each line in CSV format: name,phone,email
    while (fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[addressBook->contactCount].name,
                  addressBook->contacts[addressBook->contactCount].phone,
                  addressBook->contacts[addressBook->contactCount].email) == 3) 
    {
        // Only count valid contacts (non-empty fields)
        if (strlength(addressBook->contacts[addressBook->contactCount].name) > 0 &&
            strlength(addressBook->contacts[addressBook->contactCount].phone) > 0 &&
            strlength(addressBook->contacts[addressBook->contactCount].email) > 0) 
        {
            addressBook->contactCount++;
        }

        // Prevent exceeding the maximum allowed contacts
        if (addressBook->contactCount >= MAX_CONTACTS) 
        {
            printf("Warning: Maximum contact limit reached while loading from file.\n");
            break;
        }
    }

    // Close the file after reading
    fclose(fptr);
}
