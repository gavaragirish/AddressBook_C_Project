/*
Name: Gavara Girish (25026_214)
Date: 29/10/2025
Description: This project is a C-based Address Book Management System that allows users to efficiently manage contact information. 
            It supports creating, displaying, searching, editing, deleting, saving, and loading contacts.
            Each contact includes a name, mobile number, and email, with built-in input validation and uniqueness checks to prevent duplicates.
            The data is stored in a text (CSV) file, ensuring persistence even after program closure.
 */
#include "header.h"
int main()
{
    struct address a;
    a.contact_count=0;
    load(&a,&a.contact_count);
    int choice;
    printf("Enter the choice: \n");
    do
    {
        printf("1.Create contact\n");
        printf("2.Display contact\n");
        printf("3.Save contact\n");
        printf("4.Edit contact\n");
        printf("5.Search contact\n");
        printf("6.Delete contact\n");
        printf("7.Exit contact\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
            create(&a,&a.contact_count);
            break;
            case 2:
            display(&a);
            break;
            
            case 3:
            save(&a);
            break;
            case 4:
            edit(&a);
            break;
             
            case 5:
            search(&a);
            break;
            case 6:
            delete(&a);
            break;
           
            case 7:
            printf("Exiting.....\n");
            return 0;
        }
    }
    while(choice !=7);
    return 0;
}