#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void display_loading_bar(int percentage) {
    int bar_width = 50;
    int pos = (percentage * bar_width) / 100;
    
    printf("\r[");
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos)
            printf("=");
        else
            printf(" ");
    }
    printf("] %d%%", percentage);
    fflush(stdout);
}

void timer() {
    printf("Loading...\n");
    for (int i = 0; i <= 100; i++) {
        display_loading_bar(i);
        #ifdef _WIN32
            Sleep(10);
        #else
            usleep(10000);
        #endif
    }
    printf("\nLoading Completed!\n");
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int STARTING_SCREEN() {
    int choice;
    printf("\n=============================\n");
    printf("       Welcome\n");
    printf("=============================\n");
    printf("[1] Sign Up\n");
    printf("[2] Sign In\n");
    printf("[0] Exit\n");
    printf("=============================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clear input buffer
    return choice;
}

int email_exists(const char *email) {
    FILE *file = fopen("credentials.csv", "r");
    if (!file) return 0;

    char storedEmail[200], storedPassword[200], storedName[200];
    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", storedEmail, storedPassword, storedName) != EOF) {
        if (strcmp(email, storedEmail) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

void signup() {
    char email[200], password[200], confirm_password[200], name[200];
    
    printf("\n=============================\n");
    printf(" =    Enter your Name:     =\n");
    printf("=============================\n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    printf("\n=============================\n");
    printf(" =    Enter your Email:     =\n");
    printf("=============================\n");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    if (email_exists(email)) {
        printf("This email is already registered. Please use another email.\n");
        return;
    }

    printf("\n=============================\n");
    printf(" =    Enter your Password:   =\n");
    printf("=============================\n");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    printf("\n=============================\n");
    printf(" =    Re-enter your Password: =\n");
    printf("=============================\n");
    fgets(confirm_password, sizeof(confirm_password), stdin);
    confirm_password[strcspn(confirm_password, "\n")] = 0;

    if (strcmp(password, confirm_password) == 0) {
        printf("ID Successfully created\n");
        FILE *file = fopen("credentials.csv", "a+");
        if (!file) {
            perror("Error creating file");
            return;
        }
        fprintf(file, "%s,%s,%s\n", email, password, name);
        fclose(file);
    } else {
        printf("Passwords do not match. Returning to main menu...\n");
    }
}

int signin() {
    char email[200], password[200];
    char storedEmail[200], storedPassword[200], storedName[200];
    int found = 0;

    printf("\n=============================\n");
    printf(" =    Enter your Email:     =\n");
    printf("=============================\n");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;

    printf("\n=============================\n");
    printf(" =    Enter your Password:   =\n");
    printf("=============================\n");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    FILE *file = fopen("credentials.csv", "r");
    if (!file) {
        perror("Error opening file");
        return 0;
    }

    while (fscanf(file, "%[^,],%[^,],%[^\n]\n", storedEmail, storedPassword, storedName) != EOF) {
        if (strcmp(email, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
            printf("Login successful! Welcome, %s.\n", storedName);
            fclose(file);
            dashboard(storedName);
            return 1;
        }
    }

    fclose(file);
    printf("Invalid email or password. Try again.\n");
    return 0;
}

typedef struct {
    int index;
    char round[MAX_LINE_LENGTH];
    char college[MAX_LINE_LENGTH];
    char branch[MAX_LINE_LENGTH];
    char stream[MAX_LINE_LENGTH];
    char quota[MAX_LINE_LENGTH];
    char category[MAX_LINE_LENGTH];
    char seatGender[MAX_LINE_LENGTH];
    int openingRank;
    int closingRank;
} CollegeData;

// void dashboard(const char *name) {
//     int rank;
//     printf("=============================================================================\n");
//     printf("=                                                        Hi, %s!       \n", name);
//     printf("=============================================================================\n");
//     printf("=                    RANK:                                             \n");
//     printf("=============================================================================\n");
//     printf("Enter your rank: ");
//     scanf("%d", &rank);
//     printf("=============================================================================\n");

//     printCSVRowsForUserRank("corrected_admissions1.csv", rank);
// }

void printCSVRowsForUserRank(const char * filename, int userRank) {
    FILE *file = fopen("/path/to/corrected_admissions1.csv", "r");
    if (!file) {
        printf("File not found. Sorry.\n");
        file = fopen("corrected_admissions1.csv", "r");
        fprintf(file, "Index,Round,College,Branch,Stream,Quota,Category,SeatGender,OpeningRank,ClosingRank\n");
        fclose(file);
        printf("No data available\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    int foundEligible = 0;

    fgets(line, sizeof(line), file); // Skip header

    printf("\nColleges matching your rank or above:\n");
    printf("===============================================================================================\n");
    printf("Index, Round, College, Branch, Stream, Quota, Category, Seat Gender, Opening Rank, Closing Rank\n");
    printf("===============================================================================================\n");

    while (fgets(line, sizeof(line), file)) {
        CollegeData data;
        sscanf(line, "%d,%[^,],\"%[^\"]\",\"%[^\"]\",%[^,],%[^,],%[^,],%[^,],%d,%d",
               &data.index,
               data.round,
               data.college,
               data.branch,
               data.stream,
               data.quota,
               data.category,
               data.seatGender,
               &data.openingRank,
               &data.closingRank);

        if (userRank >= data.openingRank && userRank <= data.closingRank) {
            printf("%d, %s, %s, %s, %s, %s, %s, %s, %d, %d\n",
                   data.index,
                   data.round,
                   data.college,
                   data.branch,
                   data.stream,
                   data.quota,
                   data.category,
                   data.seatGender,
                   data.openingRank,
                   data.closingRank);
            foundEligible = 1;
        }
    }

    if (!foundEligible) {
        printf("No colleges found with a closing rank that matches or exceeds your rank.\n");
    }

    fclose(file);
}

void dashboard(const char *name) {
    int rank;
    printf("=============================================================================\n");
    printf("=                                                        Hi, %s!       \n", name);
    printf("=============================================================================\n");
    printf("=                    RANK:                                             \n");
    printf("=============================================================================\n");
    printf("Enter your rank: ");
    scanf("%d", &rank);
    printf("=============================================================================\n");

    printCSVRowsForUserRank("corrected_admissions1.csv", rank);
}

int main() {
    timer();
    int choice;

    while ((choice = STARTING_SCREEN()) != 0) {
        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                signin();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    printf("Thank you for using the system. Goodbye!\n");
    return 0;
}
