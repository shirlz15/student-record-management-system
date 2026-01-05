// Student Record Management System
// Author: Shirley.S
// Description: Menu-driven C program with basic record management
//              and some added novel features.

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* ---------------- Structure ---------------- */
struct StudentData {
    int rollNo;
    char studentName[50];
    float totalMarks;
};

/* ------------ Function Declarations ----------- */
void addRecord();
void displayRecords();
void smartSearchRecord();
char getAcademicStatus(float marks);
void writeLog(char action[], int roll);

/* ---------------- Main Function ---------------- */
int main() {
    int userChoice;

    do {
        printf("\n===== Student Record Management System =====\n");
        printf("1. Add Student Record\n");
        printf("2. View All Records\n");
        printf("3. Smart Search\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                addRecord();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                smartSearchRecord();
                break;
            case 4:
                printf("Program exited.\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (userChoice != 4);

    return 0;
}
// Adding Records
void addRecord() {
    struct StudentData stu;
    FILE *filePtr;

    filePtr = fopen("records.txt", "a");

    // Taking input from user
    printf("Enter Roll Number: ");
    scanf("%d", &stu.rollNo);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", stu.studentName);

    printf("Enter Total Marks: ");
    scanf("%f", &stu.totalMarks);

    // Writing data to file
    fprintf(filePtr, "%d %s %.2f\n",
            stu.rollNo, stu.studentName, stu.totalMarks);

    fclose(filePtr);

    // Logging the action
    writeLog("Added record for", stu.rollNo);

    printf("Record added successfully.\n");
}
// Display Records + Academic Status Analyzer
void displayRecords() {
    struct StudentData stu;
    FILE *filePtr;

    filePtr = fopen("records.txt", "r");

    if (filePtr == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\nRoll\tName\t\tMarks\tStatus\n");
    printf("-------------------------------------------\n");

    // Reading data from file
    while (fscanf(filePtr, "%d %s %f",
                  &stu.rollNo, stu.studentName, &stu.totalMarks) != EOF) {

        printf("%d\t%s\t\t%.2f\t%c\n",
               stu.rollNo,
               stu.studentName,
               stu.totalMarks,
               getAcademicStatus(stu.totalMarks));
    }

    fclose(filePtr);
}
// Academic Status Analyzer
char getAcademicStatus(float marks) {
    // Checking performance based on marks
    if (marks < 40)
        return 'R';   // At Risk
    else if (marks >= 75)
        return 'D';   // Distinction
    else
        return 'P';   // Pass
}
// Smart Search (Partial + Case-Insensitive)
void smartSearchRecord() {
    struct StudentData stu;
    FILE *filePtr;
    char searchKey[30];
    char nameLower[50], keyLower[30];
    int found = 0;

    printf("Enter name keyword to search: ");
    scanf(" %[^\n]", searchKey);

    // Convert search key to lowercase
    for (int i = 0; searchKey[i]; i++)
        keyLower[i] = tolower(searchKey[i]);
    keyLower[strlen(searchKey)] = '\0';

    filePtr = fopen("records.txt", "r");

    if (filePtr == NULL) {
        printf("No records available.\n");
        return;
    }

    while (fscanf(filePtr, "%d %s %f",
                  &stu.rollNo, stu.studentName, &stu.totalMarks) != EOF) {

        // Convert name to lowercase
        for (int i = 0; stu.studentName[i]; i++)
            nameLower[i] = tolower(stu.studentName[i]);
        nameLower[strlen(stu.studentName)] = '\0';

        // Checking partial match
        if (strstr(nameLower, keyLower)) {
            printf("Found: %d %s %.2f\n",
                   stu.rollNo, stu.studentName, stu.totalMarks);
            found = 1;
        }
    }

    if (!found)
        printf("No matching record found.\n");

    fclose(filePtr);
}
// Change Log (Audit Trail)
void writeLog(char action[], int roll) {
    FILE *logPtr;
    time_t currentTime;

    time(&currentTime);

    logPtr = fopen("log.txt", "a");

    // Writing log with time
    fprintf(logPtr, "%s Roll No %d at %s",
            action, roll, ctime(&currentTime));

    fclose(logPtr);
}
