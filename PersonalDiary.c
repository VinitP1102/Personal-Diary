/* Program to design a password protected personal diary
 * All the records are stored in text files so they are available even if program rerun
 * Designed By : Vinit Patel
 */
#include <stdio.h>  // Header file for standard input output and file management
#include <string.h> // Header file for string functions like strcpy()
#include <stdlib.h> // Header file for exit()
// Function to display available options to user and takes the choice
int menu()
{
    int c=5;
    printf("\n<----- Welcome to My Diary ----->\n\n");
    printf("1.View Records\n");
    printf("2.Add Record\n");
    printf("3.Edit Record\n");
    printf("4.Delete Record\n");
    printf("5.Close the diary\n");
    printf("Enter your choice : ");
    scanf("%d",&c);
    return c;
}
// Function to check the entered password is correct or not
void checkPass(char* password)
{
    char p[20];
    for(int i=0;i<3;i++)   // Max 3 try for correct password
    {
        printf("Enter password : ");
        scanf(" %[^\n]",p);
        if(!strcmp(password,p))
            return;
        printf("Incorrect Password!!\n");
    }
    printf("You entered incorrect password 3 times!!\n");
    printf("Try again later\n");
    printf("xxxxxx Diary is locked for security reasons xxxxx\n");// Diary gets locked if password is incorrect
    exit(1);
}
// Function to count the number of records stored in the text file
int countRecord()
{
    FILE *fp=fopen("diary.txt","r");  // Opening text file in read mode
    if(fp==NULL)
        return 0;
    int c=0;
    char ch1=fgetc(fp);
    char ch2=fgetc(fp);
    while(ch2!=EOF)
    {
        if(ch1=='\n' && ch2=='\n')
            c++;
        ch1=ch2;
        ch2=fgetc(fp);
    }
    fclose(fp);  // closing text file
    return c;  // returning number of records to caller function
}
// Function to display the records stored in text file
void viewRecord()
{
    FILE *fp=fopen("diary.txt","r");
    if(fp==NULL)  // Checking if file is present or not
    {
        printf("Failed to open diary.\n");
        return;
    }
    int c=1;
    char ch1=fgetc(fp),ch2=fgetc(fp);
    if(ch2==EOF)  // Checking if file is empty
    {
        printf("No record to display\n");
        return;
    }
    printf("\nRecords : \n");  // Displaying records
    printf("1.");
    while(ch2!=EOF)
    {
        printf("%c",ch1);
        if(ch1=='\n' && ch2=='\n')
        {
            ch2=fgetc(fp);
            if(ch2==EOF)
            {
                printf("\n");
                break;
            }
            c++;
            printf("\n%d.",c);
        }
        ch1=ch2;
        ch2=fgetc(fp);
    }
    fclose(fp);
}
// Function to add new record in the text file
void addRecord(int* record_count)
{
    FILE *fp=fopen("diary.txt","a");  // Opening file in append mode
    if(fp==NULL)
    {
        printf("Failed to open diary.\n");
        return;
    }
    char ch;
    (*record_count)++;  // Incrementing Number of Records
    fprintf(fp,"%s","Task = ");
    printf("\nEnter details of record\n");  // Taking record details from user
    printf("Enter Task name : ");
    scanf(" %c",&ch);
    while(ch!='\n')
    {
        fprintf(fp,"%c",ch);
        scanf("%c",&ch);
    }
    fprintf(fp,"%c",'\n');

    fprintf(fp,"%s","Status = ");
    printf("Enter Status : ");
    scanf(" %c",&ch);
    while(ch!='\n')
    {
        fprintf(fp,"%c",ch);
        scanf("%c",&ch);
    }
    fprintf(fp,"%c",'\n');

    fprintf(fp,"%s","Time [hh:mm:ss] = ");
    printf("Enter Time [hh:mm:ss] : ");
    scanf(" %c",&ch);
    while(ch!='\n')
    {
        fprintf(fp,"%c",ch);
        scanf("%c",&ch);
    }
    fprintf(fp,"%c",'\n');

    fprintf(fp,"%s","Date [dd/mm/yyyy] = ");
    printf("Enter Date [dd/mm/yyyy] : ");
    scanf(" %c",&ch);
    while(ch!='\n')
    {
        fprintf(fp,"%c",ch);
        scanf("%c",&ch);
    }
    fprintf(fp,"%c",'\n');

    fprintf(fp,"%s","Note = ");
    printf("Enter Note : ");
    scanf(" %c",&ch);
    while(ch!='\n')
    {
        fprintf(fp,"%c",ch);
        scanf("%c",&ch);
    }
    fprintf(fp,"%s","\n\n");
    fclose(fp);
    printf("Record successfully created.\n");  // Record is added successfully if its reach at this point
}
// Function to delete a record from the text file
void deleteRecord(int* record_count)
{
    if(*record_count==0)  // Checking if file is empty
    {
        printf("No record to delete\n");
        return;
    }
    int record_no=0;
    do{
        printf("Enter record number to be deleted : ");
        scanf("%d",&record_no);
        if(record_no<1 || record_no>*record_count)      // Checking if record number given by user is correct
            printf("Invalid record number\nPlease enter valid record number\n");
        else
            break;
    }while(1);

    FILE *fp1=fopen("diary.txt","r");  // Opening diary text file in read mode
    if(fp1==NULL)
    {
        printf("Failed to open diary.\n");
        return;
    }
    FILE *fp2=fopen("newdiary.txt","w");  // Writing in new file
    char ch1=fgetc(fp1),ch2=fgetc(fp1);
    int i=1;
    while(ch2!=EOF)  // Reading from one file and writing to other file
    {
        if(i==record_no)  // Skiping the record to be deleted
        {
            if(ch1=='\n')
                fputc(ch1,fp2);
            while(!(ch1=='\n' && ch2=='\n'))
            {
                ch1=ch2;
                ch2=fgetc(fp1);
            }
            ch1=fgetc(fp1);
            ch2=fgetc(fp1);
            i++;
            if(ch1==EOF)
                break;
        }
        fputc(ch1,fp2);
        if(ch1=='\n' && ch2=='\n')
            i++;
        ch1=ch2;
        ch2=fgetc(fp1);
    }
    fputc(ch1,fp2);
    fclose(fp1);
    fclose(fp2);
    remove("diary.txt");  // Deleting the old text file
    rename("newdiary.txt","diary.txt");  // Renaming new file as old file name
    (*record_count)--;
    printf("Record has been deleted successfully.\n");
}
// Function to edit an existing record in text file
void editRecord(const int record_count)
{
    if(record_count==0)
    {
        printf("No record to edit\n");
        return;
    }
    int record_no=0;
    do{
        printf("Enter record number to be edited : ");
        scanf("%d",&record_no);
        if(record_no<1 || record_no>record_count)
            printf("Invalid record number\nPlease enter valid record number\n");
        else
            break;
    }while(1);

    FILE *fp1=fopen("diary.txt","r");
    if(fp1==NULL)
    {
        printf("Failed to open diary.\n");
        return;
    }
    FILE *fp2=fopen("newdiary.txt","w");
    char ch1=fgetc(fp1),ch2=fgetc(fp1);
    int i=1;
    while(ch2!=EOF)  // Reading from one file and writing to other file
    {
        if(i==record_no)  // Skipping old record and writing new one
        {
            if(ch1=='\n')
                fputc(ch1,fp2);
            while(!(ch1=='\n' && ch2=='\n'))
            {
                ch1=ch2;
                ch2=fgetc(fp1);
            }
            ch1=fgetc(fp1);
            ch2=fgetc(fp1);
            i++;

            char ch;
            fprintf(fp2,"%s","Task = ");
            printf("\nEnter new details\n");
            printf("Enter Task name : ");
            scanf(" %c",&ch);
            while(ch!='\n')
            {
                fprintf(fp2,"%c",ch);
                scanf("%c",&ch);
            }
            fprintf(fp2,"%c",'\n');

            fprintf(fp2,"%s","Status = ");
            printf("Enter Status : ");
            scanf(" %c",&ch);
            while(ch!='\n')
            {
                fprintf(fp2,"%c",ch);
                scanf("%c",&ch);
            }
            fprintf(fp2,"%c",'\n');

            fprintf(fp2,"%s","Time [hh:mm:ss] = ");
            printf("Enter Time [hh:mm:ss] : ");
            scanf(" %c",&ch);
            while(ch!='\n')
            {
                fprintf(fp2,"%c",ch);
                scanf("%c",&ch);
            }
            fprintf(fp2,"%c",'\n');

            fprintf(fp2,"%s","Date [dd/mm/yyyy] = ");
            printf("Enter Date [dd/mm/yyyy] : ");
            scanf(" %c",&ch);
            while(ch!='\n')
            {
                fprintf(fp2,"%c",ch);
                scanf("%c",&ch);
            }
            fprintf(fp2,"%c",'\n');

            fprintf(fp2,"%s","Note = ");
            printf("Enter Note : ");
            scanf(" %c",&ch);
            while(ch!='\n')
            {
                fprintf(fp2,"%c",ch);
                scanf("%c",&ch);
            }
            fprintf(fp2,"%s","\n\n");

            if(ch1==EOF)
                break;
        }
        fputc(ch1,fp2);
        if(ch1=='\n' && ch2=='\n')
            i++;
        ch1=ch2;
        ch2=fgetc(fp1);
    }
    if(ch1!=EOF)
        fputc(ch1,fp2);
    fclose(fp1);
    fclose(fp2);
    remove("diary.txt");  // Deleting old file
    rename("newdiary.txt","diary.txt");  // Renaming new file
    printf("Record has been edited successfully.\n");
}
// Main Function to drive the working of whole program
int main()
{
    printf("\n<===== Vinit's Personal Diary =====>\n");
    char password[]="vinit123";  // Setting passwords for diary
    char tpass[]="vinit12345";
    checkPass(password);  // checking if password is correct
    int record_count=countRecord();
    int choice;
    while(1)
    {
        choice=menu();
        switch(choice)  // Menu driving the program according to user choice
        {
            case 1:viewRecord();
                break;
            case 2:checkPass(tpass);
                addRecord(&record_count);
                break;
            case 3:checkPass(tpass);
                editRecord(record_count);
                break;
            case 4:checkPass(tpass);
                deleteRecord(&record_count);
                break;
            case 5:
                printf("Closing diary.\n");
                exit(2);  // Exiting the program
            default:
                printf("Invalid Choice\n");
        }
    }
}