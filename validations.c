#include "validations.h"
#include <regex.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function to check if the date pattern is correct using regex
bool isValidDate(const char *date) {
    regex_t regex;
    int ret;
    const char *pattern = "^\\d{4}-\\d{2}-\\d{2}$";

    // Compile the regular expression
    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return false;
    }

    // Execute the regular expression
    ret = regexec(&regex, date, 0, NULL, 0);
    regfree(&regex);

    return !ret;
}