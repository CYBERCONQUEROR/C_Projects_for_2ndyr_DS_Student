#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1024

#ifdef _WIN32
    #include <windows.h>  // For Windows Sleep() and system("cls")
#else
    #include <unistd.h>   // For Unix usleep()
#endif

void display_loading_bar(int percentage) {
    int bar_width = 50; // Width of the loading bar
    int pos = (percentage * bar_width) / 100; // Calculate the position based on percentage
    
    printf("\r["); // Carriage return to stay on the same line
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos)
            printf("."); // Filled part of the bar
        else
            printf(" "); // Empty part of the bar
    }
    printf("] %d%%", percentage); // Print percentage
    fflush(stdout); // Ensure the output is displayed immediately
}

void timer() {
    printf("Loading...\n");
    for (int i = 0; i <= 100; i++) {
        display_loading_bar(i); // Display loading bar
        #ifdef _WIN32
            Sleep(10);  // Windows Sleep (10 milliseconds)
        #else
            usleep(10000);  // Unix usleep (10 milliseconds)
        #endif
    }
    printf("\nLoading Completed!\n");
    
    // Clear the screen after loading is complete
    #ifdef _WIN32
        system("cls");  // Clear screen for Windows
    #else
        system("clear");  // Clear screen for Unix-like systems
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
    while (getchar() != '\n');  // Clear input buffer
    return choice;
}

void signup() {
    char email[200], password[200], confirm_password[200], name[200];
    
    printf("\nEnter your Name: ");
    fgets(name, sizeof(name), stdin);

    printf("Enter your Email: ");
    fgets(email, sizeof(email), stdin);

    printf("Enter your Password: ");
    fgets(password, sizeof(password), stdin);

    printf("Re-enter your Password: ");
    fgets(confirm_password, sizeof(confirm_password), stdin);
    
    // Remove newline characters from inputs
    name[strcspn(name, "\n")] = 0;
    email[strcspn(email, "\n")] = 0;
    password[strcspn(password, "\n")] = 0;
    confirm_password[strcspn(confirm_password, "\n")] = 0;

    if (strcmp(password, confirm_password) == 0) {
        printf("ID Successfully created\n");
        FILE *file = fopen("credentials.csv", "a+");
        if (file == NULL) {
            perror("Error opening file");
            return;
        }
        fprintf(file, "%s,%s,%s\n", email, password, name);
        fclose(file);
    } else {
        printf("Passwords do not match. Returning to main menu...\n");
    }
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

void create_admission_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "Index,Round,College,Branch,Stream,Quota,Category,SeatGender,OpeningRank,ClosingRank\n");
        printf("No data available. A template admission.csv file has been created for future use.\n");
    } else {
        perror("Error creating the admission.csv file");
    }
    fclose(file);
}

void printCSVRowsForUserRank(const char *filename, int userRank) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("File not found. Creating a new admission.csv file.\n");
        create_admission_file(filename);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int foundEligible = 0; // Flag to track if any eligible colleges are found

    // Skip the header line
    fgets(line, sizeof(line), file);

    // Read each line from the CSV file
    while (fgets(line, sizeof(line), file)) {
        CollegeData data;

        // Parse the line
        sscanf(line, "%d,%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d",
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

        // Check eligibility
        if (userRank >= data.openingRank && userRank <= data.closingRank) {
            printf("Eligible College: %s, Branch: %s, Rank Range: %d-%d\n",
                   data.college, data.branch, data.openingRank, data.closingRank);
            foundEligible = 1;
        }
    }

    if (!foundEligible) {
        printf("No eligible colleges found for your rank.\n");
    }

    fclose(file);
}

void dashboard(const char *name) {
    int rank;
    printf("=============================================================================\n");
    printf("Hi, %s! Please enter your rank to view eligible colleges.\n", name);
    printf("=============================================================================\n");
    printf("Enter your rank: ");
    scanf("%d", &rank);
    while (getchar() != '\n');  // Clear input buffer
    printf("=============================================================================\n");

    printCSVRowsForUserRank("admission.csv", rank);
}

void signin() {
    char email[200], password[200];

    printf("Enter your Email: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0; // Remove newline

    printf("Enter your Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline

    FILE *file = fopen("credentials.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char id[200], pass[200], name[200];
    int found = 0; // Flag to check if credentials are found
    char line[256]; // Buffer to read lines from the file

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%199[^,],%199[^,],%199[^\n]", id, pass, name);
        if (strcmp(email, id) == 0 && strcmp(password, pass) == 0) {
            printf("Successfully logged in as %s!\n", name);
            found = 1;
            dashboard(name);
            break;
        }
    }

    if (!found) {
        printf("Invalid email or password.\n");
    }

    fclose(file);
}

int main() {
    timer();  // Show loading screen
    int choice;

    do {
        choice = STARTING_SCREEN();

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                signin();
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
