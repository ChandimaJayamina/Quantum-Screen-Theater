#include <stdio.h>
#include "welcomescreen.h"
#include <time.h>

void someFunction() {
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    if (local != NULL) {
        printf("Current local time: %s", asctime(local));
    } else {
        printf("Failed to get local time.\n");
    }

    // Code that uses the 'local' variable or other logic
}

int main(void)
{
  welcome();
  return 0;
}
