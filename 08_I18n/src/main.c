#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libintl.h>
#include <locale.h>

#define _(STR) gettext(STR)

int main() {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALE_PATH);
    textdomain(PACKAGE);

    int low = 1, high = 100;
    char answer[4];
    
    printf(_("Guess a number from 1 to 100.\n"));
    
    while (low < high) {
        int mid = (low + high) / 2;
        printf(_("Higher than %d?\n"), mid);
        
        if (fgets(answer, sizeof(answer), stdin) == NULL) {
            printf("Input error\n");
            return 1;
        }
        
        answer[strcspn(answer, "\n")] = '\0';
        if (strcmp(answer, _("Yes")) == 0) {
            low = mid + 1;
        } else if (strcmp(answer, _("No")) == 0) {
            high = mid;
        } else {
            printf(_("Yes or No?\n"));
        }
    }
    
    printf(_("Answer: %d\n"), low);
    return 0;
}