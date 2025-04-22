 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
            Sleep(10);  // Windows Sleep (50 milliseconds)
        //#else
          //  usleep(50000);  // Unix usleep (50 milliseconds)
        #endif
    }
    printf("\nLoading Completed!\n");
    