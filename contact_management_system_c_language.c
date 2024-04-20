#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void Menu() {
printf("\n\t **** My-Contact Management System ****\n");
printf("\n\n\n\t\t\tMAIN MENU\n");
printf("\t\t=====================\n");
printf("\t\t[1] Add a new Contact\n");
printf("\t\t[2] List all Contacts\n");
printf("\t\t[3] Search for contact\n");
printf("\t\t[4] Edit a Contact\n");
printf("\t\t[5] Delete a Contact\n");
printf("\t\t[6] Delete All Contact\n");
printf("\t\t[0] Exit\n\t\t=================\n\t\t");
printf("Enter the choice:");
}
void AddNewContact() {
char Name[20];
char Phone[20];
char Email[30];
char NewContact[100];
NewContact[0] = 0;
printf("Enter The Name: ");
scanf(" %[^\n]s", Name);
printf("Enter The Phone Number: ");
scanf("%s", Phone);
printf("Enter The Email: ");
scanf("%s", Email);
// creating a new contact
strcat(NewContact, Name);
strcat(NewContact, "\n");
strcat(NewContact, Phone);
strcat(NewContact, "\n");
strcat(NewContact, Email);
strcat(NewContact, "\n");
FILE *allContactTxtFile = fopen("All-Contact.txt", "a"); // open file
fprintf(allContactTxtFile, "%s", NewContact); // store contact in text file
fclose(allContactTxtFile);
printf("\nContact Added Successfully!\n");
}
void ShowAllContacts() {
FILE *allContactTextFile = fopen("All-Contact.txt", "r");
if (allContactTextFile == NULL) {
printf("No contacts found!\n");

return;
}
int lineLength = 100;
char line[lineLength];
// table header: name = 20, phone = 20, and email = 30 characters
printf("|====================|====================|==============================|\
n");
printf("| Name | Phone Number | Email
|\n");
printf("|====================|====================|==============================|\
n");
int totalContacts = 0;
while (fgets(line, lineLength, allContactTextFile)) {
printf("|");
printf("%-20s", strtok(line, "\n"));
printf("|");
printf("%-20s", strtok(NULL, "\n"));
printf("|");
printf("%-30s", strtok(NULL, "\n"));
printf("|\n");
totalContacts++;
}
printf("|====================|====================|==============================|\
n");
printf("Total Contacts: %d\n", totalContacts);
fclose(allContactTextFile);
}
void SearchContact() {
int FoundContact = 0;
char Name[100];
printf("Enter The Name: ");
scanf(" %[^\n]s", Name);
strcat(Name, "\n"); // adding new line char with name
FILE* AllContactFile;
int LineLength = 255;
char Line[LineLength];
AllContactFile = fopen("All-Contact.txt", "r"); // open file in read mood
int LineCount = 0;
while (fgets(Line, LineLength, AllContactFile)) {
LineCount++;

if (LineCount == 1 && strcmp(Name, Line) ==0)
{
FoundContact = 1;
}
if (FoundContact > 0) {
if (LineCount == 1) {
printf("\nContact information of %s", Name);
printf("\nName: %s", Line);
}
else if (LineCount == 2) {
printf("Phone: %s", Line);
}
else if (LineCount == 3) {
printf("Email: %s\n", Line);
}
}
if (LineCount == 3) {
LineCount = 0;
}
}
fclose(AllContactFile);
if (FoundContact == 0) {
printf("\nSorry, no contact found for %s\n", Name);
}
}
void EditContact() {
int LineCount = 0;
int FoundContact = 0;
int SkipLines = 0;
char GivenName[100];
char NewName[100];
char NewPhone[20];
char NewEmail[100];
char NewFullContact[300];
NewFullContact[0] = 0;
printf("Enter The Name which one you want to edit: ");
scanf(" %[^\n]s", GivenName);
strcat(GivenName, "\n");
FILE* OurExistingFile;
FILE* NewTempFile;
int LineLength = 255;
char Line[LineLength];
OurExistingFile = fopen("All-Contact.txt", "r"); // open in read mode
NewTempFile = fopen("temp-file.txt", "w"); // open in write mode + create the
temp file
while (fgets(Line, LineLength, OurExistingFile)) {
LineCount++;

if (LineCount == 1 && strcmp(GivenName, Line) == 0) {
// we found the contact
FoundContact = 1;
SkipLines = 3;
}
if (SkipLines > 0) {
if (LineCount == 1) {
printf("Old Name is: %s", Line);
printf("New Name (0 to skip): ");
scanf(" %[^\n]s", NewName);
if (strcmp(NewName, "0") == 0) {
strcat(NewFullContact, Line);
}
else {
strcat(NewFullContact, NewName);
strcat(NewFullContact, "\n");
}
SkipLines = 2;
}
else if (LineCount == 2) {
printf("Old Phone is: %s", Line);
printf("New Phone (0 to skip): ");
scanf("%s", NewPhone);
if (strcmp(NewPhone, "0") == 0) {
strcat(NewFullContact, Line);
}
else {
strcat(NewFullContact, NewPhone);
strcat(NewFullContact, "\n");
}
SkipLines = 1;
}
else if (LineCount == 3) {
printf("Old Email is: %s", Line);
printf("New Email (0 to skip): ");
scanf("%s", NewEmail);
if (strcmp(NewEmail, "0") == 0) {
strcat(NewFullContact, Line);
}
else {
strcat(NewFullContact, NewEmail);
strcat(NewFullContact, "\n");
}
SkipLines = 0;
fprintf(NewTempFile, "%s", NewFullContact);
}
}

else {
fprintf(NewTempFile, "%s", Line);
}
if (LineCount == 3) {
LineCount = 0;
}
}
fclose(NewTempFile);
fclose(OurExistingFile);
if (FoundContact == 0) {
printf("Contact Not Found!\n");
remove("temp-file.txt");
}
else {
printf("\nContact Updated Successfully!\n\n");
remove("All-Contact.txt"); // delete existing file
rename("temp-file.txt", "All-Contact.txt"); // rename temp file to the name
of existing file
}
}
void DeleteContact() {
int LineCount = 0;
int FoundTheContact = 0;
int SkipLines = 0;
char GivenName[100];
printf("Enter The Name which one you want to delete: ");
scanf(" %[^\n]s", GivenName);
strcat(GivenName, "\n");
FILE* OurExistingFile;
FILE* NewTempFile;
int LineLength = 300;
char Line[LineLength];
OurExistingFile = fopen("All-Contact.txt", "r"); // open in read mode
NewTempFile = fopen("temp-file.txt", "w"); // open in write mode + create the
file
while (fgets(Line, LineLength, OurExistingFile)) {
LineCount++;
if (LineCount == 1 && strcmp(GivenName, Line) == 0) {
// we found the contact
FoundTheContact = 1;
SkipLines = 3;
}
if (SkipLines > 0) {

SkipLines--;
}
else {
fprintf(NewTempFile, "%s", Line);
}
if (LineCount == 3) {
LineCount = 0;
}
}
fclose(NewTempFile);
fclose(OurExistingFile);
if (FoundTheContact == 0) {
printf("\nContact Not Found!\n\n");
remove("temp-file.txt");
}
else {
printf("\nContact Deleted Successfully!\n\n");
remove("All-Contact.txt"); // delete the existing file
rename("temp-file.txt", "All-Contact.txt"); // rename the temp-file to the
existing file name
}
}
void DeleteAllContacts() {
printf("\n\t\t **** Delete All The Contacts ****\n\n");
char Option;
getchar();
printf("Are you sure want to delete all the contacts? (Y/N): ");
scanf("%c", &Option);
if (Option == 'Y' || Option == 'y') {
remove("All-Contact.txt"); // delete the file
FILE* AllContactTxtFile = fopen("All-Contact.txt", "w"); // create the file
again
fclose(AllContactTxtFile);
printf("\nSuccessfully Deleted all Contacts!\n\n");
}
}
int main() {
int option;
Menu();
scanf("%d", &option);
switch (option) {
case 0:
exit(0);
break;
case 1:
AddNewContact();

break;
case 2:
ShowAllContacts();
break;
case 3:
SearchContact();
break;
case 4:
EditContact();
break;
case 5:
DeleteContact();
break;
case 6:
DeleteAllContacts();
break;
default:
printf("Invalid option. Please restart the program.\n");
break;
}
return 0;
}
