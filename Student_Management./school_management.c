#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define FILE_NAME "students.txt"

typedef struct {
    int id;
    char name[50];
    int age;
    char grade[10];
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

// Function prototypes
void loadStudents();
void saveStudents();
void addStudent(int id, char* name, int age, char* grade);
void displayStudents();
void searchStudent(int id);

int main(int argc, char *argv[]) {
    // Load students from file when the program starts
    loadStudents();

    if (argc < 2) {
        printf("Invalid arguments!\n");
        return 1;
    }

    // Command line argument 1: operation
    char* operation = argv[1];

    if (strcmp(operation, "addStudent") == 0 && argc == 6) {
        int id = atoi(argv[2]);
        char* name = argv[3];
        int age = atoi(argv[4]);
        char* grade = argv[5];

        addStudent(id, name, age, grade);
        printf("Student added successfully!\n");

        // Save students to file after adding
        saveStudents();
    } 
    else if (strcmp(operation, "displayStudents") == 0) {
        displayStudents();
    } 
    else if (strcmp(operation, "searchStudent") == 0 && argc == 3) {
        int id = atoi(argv[2]);
        searchStudent(id);
    } 
    else {
        printf("Invalid arguments or operation.\n");
        return 1;
    }

    return 0;
}

void loadStudents() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        return; // No file found, so no students to load
    }

    while (fscanf(file, "%d\n%49[^\n]\n%d\n%9[^\n]\n", &students[studentCount].id, students[studentCount].name,
                   &students[studentCount].age, students[studentCount].grade) == 4) {
        studentCount++;
    }
    fclose(file);
}

void saveStudents() {
    FILE *file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error saving students to file.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%d\n%s\n%d\n%s\n", students[i].id, students[i].name, students[i].age, students[i].grade);
    }
    fclose(file);
}

void addStudent(int id, char* name, int age, char* grade) {
    if (studentCount >= MAX_STUDENTS) {
        printf("Maximum student limit reached!\n");
        return;
    }

    Student s;
    s.id = id;
    strcpy(s.name, name);
    s.age = age;
    strcpy(s.grade, grade);

    students[studentCount++] = s;
}

void displayStudents() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n", students[i].age);
        printf("Grade: %s\n", students[i].grade);
        printf("--------------------------\n");
    }
}

void searchStudent(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Student Found!\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Age: %d\n", students[i].age);
            printf("Grade: %s\n", students[i].grade);
            return;
        }
    }
    printf("Student with ID %d not found.\n", id);
}
