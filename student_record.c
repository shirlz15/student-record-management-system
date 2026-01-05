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

/* -------- Function Declarations -------- */
void addRecord();
void displayRecords();
void SearchRecord();
char AcademicStatus(float marks);
void writeLog(char action[], int roll);

/* ---------------- Main ---------------- */
int main() {
    int userChoice;

    // Force file creation (important for online compilers)
    FILE *initFile = fopen("records.txt", "w+");
    if (initFile != NULL) {
        fclose(initFile);
    }

    do {
        printf("\n===== Student Record Management System =====\n");
        printf("1. Add Student Record\n");
        printf("2. View All Records\n");
        printf("3. Smart Search\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1: addRecord(); break;
            case 2: displayRecords(); break;
            case 3: SearchRecord(); break;
            case 4: printf("Program exited.\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (userChoice != 4);

    return 0;
}
// Adding Records
void addRecord() {
    struct StudentData stu;
    FILE *filePtr;

    filePtr = fopen("records.txt", "a+");

    if (filePtr == NULL) {
        printf("Error opening records file.\n");
        return;
    }

    printf("Enter Roll Number: ");
    scanf("%d", &stu.rollNo);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", stu.studentName);

    printf("Enter Total Marks (0 - 100): ");
    scanf("%f", &stu.totalMarks);

    fprintf(filePtr, "%d %s %.2f\n",
            stu.rollNo, stu.studentName, stu.totalMarks);

    fclose(filePtr);

    writeLog("Added record for", stu.rollNo);

    printf("Record added successfully.\n");
}
// Display Records + Academic Status Analyzer
void displayRecords() {
    struct StudentData stu;
    FILE *filePtr;

    filePtr = fopen("records.txt", "a+");

    if (filePtr == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\nRoll\tName\t\tMarks\tStatus\n");
    printf("-------------------------------------------\n");

    while (fscanf(filePtr, "%d %s %f",
                  &stu.rollNo, stu.studentName, &stu.totalMarks) != EOF) {

        printf("%d\t%s\t\t%.2f\t%c\n",
               stu.rollNo,
               stu.studentName,
               stu.totalMarks,
               AcademicStatus(stu.totalMarks));
    }

    fclose(filePtr);
}
// Academic Status Analyzer
char AcademicStatus(float marks) {
    if (marks < 40)
        return 'R';   // At Risk
    else if (marks >= 75)
        return 'D';   // Distinction
    else
        return 'P';   // Pass
}
// Smart Search (Partial + Case-Insensitive)
void SearchRecord() {
    struct StudentData stu;
    FILE *filePtr;
    char searchKey[30];
    char nameLower[50], keyLower[30];
    int found = 0;

    printf("Enter name keyword to search: ");
    scanf(" %[^\n]", searchKey);

    for (int i = 0; searchKey[i]; i++)
        keyLower[i] = tolower(searchKey[i]);
    keyLower[strlen(searchKey)] = '\0';

    filePtr = fopen("records.txt", "a+");

    if (filePtr == NULL) {
        printf("No records available.\n");
        return;
    }

    while (fscanf(filePtr, "%d %s %f",
                  &stu.rollNo, stu.studentName, &stu.totalMarks) != EOF) {

        for (int i = 0; stu.studentName[i]; i++)
            nameLower[i] = tolower(stu.studentName[i]);
        nameLower[strlen(stu.studentName)] = '\0';

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

    if (logPtr == NULL) {
        printf("Log file error.\n");
        return;
    }

    fprintf(logPtr, "%s Roll No %d at %s",
            action, roll, ctime(&currentTime));

    fclose(logPtr);
}
