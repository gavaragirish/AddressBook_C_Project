#include "header.h"

int valid(struct contact *c,int mode)
{
    
        if (mode == 1) // Name validation
        {
             for(int i=0;c->name[i] !='\0';i++)
            {
                 if(!isalpha(c->name[i]) && c->name[i] !=' ')
                {
                    printf("Invalid name..! Enter a valid name\n");
                    
                    return 0;
                   
                }
            }
            return 1;
        }
   
    else if (mode==2) // Mobile number validation
    {   
        int len =strlen(c->mobile);

       
        if(len != 10)
        {
            printf("Invalid mobile number.\n");
            
            return 0;
        }
       
            for(int i=0; i<len;i++)
            {
                if(!isdigit(c->mobile[i]))
                {
                    printf("Invalid number.\n");
                   
                    return 0;
                 }
            }   
            return 1;
        
        
    }
   
    else if (mode==3)// Email validation
    {
        for(int i=0; c->mail[i]!= '\0';i++)
        {
            char ch =c->mail[i];
            if(!(islower(ch)|| isdigit(ch)|| ch == '@'||ch == '.'))// Email must contain '@' and '.' symbols
            {
                printf("Invalid Email..! Only lowercase,'@','.' allowed\n");
                
                return 0;
            }
        }
       
            if(strchr (c->mail,'@')==NULL||strchr (c->mail,'.')==NULL)
            {
                printf("Invalid Email ID.It must contain '@' & '.' \n");
                
                return 0;
            }
            return 1;
        
    }   
    return 0; 
    
}

void create(struct address *a,int *contact_count)
{
    if (*contact_count >= 100)
    {
        printf("Address book full! Cannot add more contacts.\n");
        return;
    }
    struct contact *c=&a->arr[*contact_count]; 
    // Get and validate Name until valid and unique
    while (1)
    {
        printf("Enter name: ");
        scanf(" %[^\n]", c->name);
        
        if (valid(c,1)&& unique(a,c,1,-1))  
            break;
    }
    // Get and validate Mobile until valid and unique
    while (1)
    {
        printf("Enter mobile number: ");
        scanf("%s", c->mobile);
      
        if (valid(c,2)&& unique(a,c,2,-1))  
            break;
    }
    // Get and validate Email until valid and unique
    while (1)
    {
        printf("Enter email: ");
        scanf("%s", c->mail);
       
        if (valid(c,3)&& unique(a,c,3,-1))  // validates only email part
            break;
    }
    a->contact_count++;
    printf("Contact added successfully!\n");
    // Save after adding successfully
    //save(a);
}


void display(struct address *a)
{
    if (a->contact_count == 0) {
        printf("No contacts to display.\n");
        return;
    }
    printf("\n------------------------------------------------------------------------\n");
    printf("| %-20s | %-12s | %-20s |\n", "Name", "Mobile", "Email");
    printf("------------------------------------------------------------------------\n");
    
    for (int i = 0; i < a->contact_count; ++i) 
    {
       printf("| %-20s | %-12s | %-20s |\n",a->arr[i].name,a->arr[i].mobile,a->arr[i].mail); 
    }
    printf("------------------------------------------------------------------------\n");
    printf("Total Contacts: %d\n", a->contact_count);
}

int search(struct address *a)
{
    int choice;
        printf("Search By : \n");
        printf("1.Name\n");
        printf("2.Mobile\n");
        printf("3.Mail\n");
        printf("Enter a choice: ");
        scanf("%d",&choice);

        struct contact temp;
       
        switch(choice)
        {
            case 1:                        // Search by name
              
                    printf("Enter the name: ");
                    scanf(" %[^\n]",temp.name);
                    strcpy(temp.mobile,"0000000000");//dummy
                    strcpy(temp.mail,"a@.com");//dummy

                    if(!valid(&temp,1))//call validation
                    return -1;
               
                for(int i=0;i < a->contact_count;i++)
                {
                    if(strcasecmp(a->arr[i].name,temp.name)==0)
                    {
                        printf("Contact found...\n");
                        printf("Name : %s\n", a->arr[i].name);
                        printf("Mobile : %s\n", a->arr[i].mobile);
                        printf("Email : %s\n", a->arr[i].mail);
                        
                        return i;
                    }
                }
            break;
            case 2:                      // Search by mobile
               
                    printf("Enter the Mobile number : ");
                    scanf(" %[^\n]",temp.mobile);
                    strcpy(temp.name,"A");//dummy
                    strcpy(temp.mail,"a@.com");//dummy

                    if(!valid(&temp,2))//call validation
                    
                    return -1;
               
                for(int i=0;i < a->contact_count;i++)
                {
                    if(strcasecmp(a->arr[i].mobile,temp.mobile)==0)
                    {
                        printf("Contact found...\n");
                        printf("Name : %s\n", a->arr[i].name);
                        printf("Mobile : %s\n", a->arr[i].mobile);
                        printf("Email : %s\n", a->arr[i].mail);
                        
                        return i;
                       
                    }
                }
            break;
            case 3:                   // Search by email
               
                    printf("Enter the Email : ");
                    scanf(" %[^\n]",temp.mail);
                    strcpy(temp.name,"A");//dummy
                    strcpy(temp.mobile,"0000000000");//dummy

                    if(!valid(&temp,3))
                    
                    return -1;
                
                for(int i=0;i < a->contact_count;i++)
                {
                    if(strcasecmp(a->arr[i].mail,temp.mail)==0)
                    {   
                        printf("Contact found...\n");
                        printf("Name : %s", a->arr[i].name);
                        printf("Mobile : %s", a->arr[i].mobile);
                        printf("Email : %s", a->arr[i].mail);
                       
                        return i;
                    }
                }
                break;
            default:
                printf("Invalid choice\n");
                return -1;
        }
      
        
            printf("Contact not found\n");
            return -1;
           // If no match found, return -1
}
void delete(struct address *a)
{
    int index=search(a);  // Search contact first

    if(index == -1)
    {
        printf("Delete failed.\n");
        return;
    }
    char confirm;
    printf("Are you sure you want to delete this contact?(Y/N): ");
    scanf(" %c",&confirm);
    if(confirm =='Y' || confirm == 'y')
    {
        for(int i=index;i<a->contact_count-1;i++)  // Shift contacts to remove the deleted one
        {
            a->arr[i]=a->arr[i+1];
        }
        a->contact_count--;
        printf("Contact Deleted Successfully..!\n");
       // save(a); // Save updated contact list after deletion
    }
    else
    {
        printf("Deletion cancelled.\n");
    }
}

void edit(struct address *a)
{
    struct contact temp;
    int found = -1;
    int choice;
        //  Step 1: Ask user how they want to search the contact
        printf("\n---- Edit Contact ----\n");
        printf("Search By : \n");
        printf("1.Name\n");
        printf("2.Mobile\n");
        printf("3.Mail\n");
        printf("Enter a choice: ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                while(1)
                {
                    // Ask for name and validate input
                    printf("Enter the name: ");
                    scanf(" %[^\n]",temp.name);
                    strcpy(temp.mobile,"0000000000");//dummy
                    strcpy(temp.mail,"a@.com");//dummy

                    if(valid(&temp,1))//call validation
                    break;
                }
                //  Search for the contact with matching name
                for(int i=0;i < a->contact_count;i++)
                {
                    if(strcmp(a->arr[i].name,temp.name)==0)
                    {
                        found =i;
                        break;
                    }
                }
            break;
            case 2:
                while(1)
                {
                     //  Ask for mobile number and validate input
                    printf("Enter the Mobile number : ");
                    scanf(" %[^\n]",temp.mobile);
                    strcpy(temp.name,"A");//dummy
                    strcpy(temp.mail,"a@.com");//dummy

                    if(valid(&temp,2))//call validation
                    
                    break;
                }
                //  Search for contact by mobile number
                for(int i=0;i < a->contact_count;i++)
                {
                    if(strcmp(a->arr[i].mobile,temp.mobile)==0)
                    {
                        found =i;
                        break;
                    }
                }
            break;
            case 3:
                while(1)
                {
                    // Ask for email and validate input
                    printf("Enter the Email : ");
                    scanf(" %[^\n]",temp.mail);
                    strcpy(temp.name,"A");//dummy
                    strcpy(temp.mobile,"0000000000");//dummy

                    if(valid(&temp,3))
                    
                    break;
                }
                //  Search for contact by email
                for(int i=0;i < a->contact_count;i++)
                {
                    if(strcmp(a->arr[i].mail,temp.mail)==0)
                    {   
                        found =i;
                        break;
                    }
                }
                break;
            default:
                printf("Invalid choice\n");
                return;
        }
         //  If no matching contact found
        if(found == -1)
        {
            printf("Contact not found\n");
            return;
        }
        //  Display found contact details
        printf("Contacat found: \n");
        printf("Name: %s Mobile : %s mail: %s",a->arr[found].name,a->arr[found].mobile,a->arr[found].mail);
        int editchoice;    
        printf("\nWhat do you want to edit?\n");
        printf("1. Name\n");
        printf("2. Mobile\n");
        printf("3. Email\n");
        printf("Enter choice: ");
        scanf("%d", &editchoice);

        switch(editchoice)
        {
            case 1:
            //  Edit name and validate + ensure uniqueness
                printf("Enter new name: ");
                scanf(" %[^\n]",temp.name);
                strcpy(temp.mobile,a->arr[found].mobile);
                strcpy(temp.mail,a->arr[found].mail);

                if(!valid(&temp,1)|| !unique(a,&temp,1,found))
                return;
                strcpy(a->arr[found].name, temp.name); 
                break;
            case 2:
            //  Edit mobile number and validate + ensure uniqueness
                printf("Enter new mobile: ");
                scanf(" %[^\n]",temp.mobile);
                strcpy(temp.name,a->arr[found].name);
                strcpy(temp.mail,a->arr[found].mail);

                if(!valid(&temp,2)|| !unique(a,&temp,2,found))
                    return;
                strcpy(a->arr[found].mobile, temp.mobile);
                break;
            case 3:
            //  Edit email and validate + ensure uniqueness
                printf("Enter new Email: ");
                scanf(" %[^\n]",temp.mail);
                strcpy(temp.name,a->arr[found].name);
                strcpy(temp.mobile,a->arr[found].mobile);

                if(!valid(&temp,3)|| !unique(a,&temp,3,found))
                    return;
                strcpy(a->arr[found].mail, temp.mail);
                break;
            default:
                printf("\n Invalid Choice!\n");
                return;
        }
        //  Save updated contact list
        printf("Contact updated successfully...!\n");
      //  save(a);
}
int unique (struct address *a,struct contact*c,int mode,int skip_index)
{
    //mode:1-name,2-mobile,3-mail
    // Checks if name, mobile, or mail already exists (skips current contact if editing)
    for(int i=0;i < a->contact_count;i++)
    {
        if(i == skip_index)  // skip the same record during edit
        continue;
        if(mode == 1 && strcmp(a->arr[i].name,c->name)==0)
        {
            printf("This contact name already exist..!\n");
            return 0;
        }

        if(mode == 2 && strcmp(a->arr[i].mobile,c->mobile)==0)
        {
            printf("This contact Number already exist..!\n");
            return 0;
        }
        if(mode == 3 && strcmp(a->arr[i].mail,c->mail)==0)
        {
            printf("This Email already exist..!\n");
            return 0;
        }
    }
    return 1;
}
void save(struct address*a)
{
    FILE *fp = fopen("addressbook.csv","w"); // Save all contacts into a CSV file
    if(fp == NULL)
    {
        perror("ERROR : ");
        return;
    }
    fprintf(fp,"#%d\n",a->contact_count);
    
     
    for(int i=0;i < a->contact_count;i++)
    {
        fprintf(fp,"%s,%s,%s\n",a->arr[i].name,a->arr[i].mobile,a->arr[i].mail);
    }
    

    fclose(fp);
    printf("Contact Saved Successfully....!\n");
}
void load(struct address*a,int *contact_count)
{
    FILE *fp = fopen("addressbook.csv", "r");
    if (fp == NULL)
    {
        printf("No contacts to display.\n");
        a->contact_count = 0;
        return;
    }
    fscanf(fp,"#%d\n",contact_count);
    a->contact_count = *contact_count;
    for(int i=0;i<a->contact_count;i++)
    {
        fscanf(fp,"%[^,],%[^,],%[^\n]\n",a->arr[i].name,a->arr[i].mobile,a->arr[i].mail);
    }
    fclose(fp);
    printf("contacts loaded successfully(%dfound).\n",a->contact_count);

}
