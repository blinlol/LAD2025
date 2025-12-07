#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <libintl.h>
#include <locale.h>

/* _(STR) is a shorthand used by gettext-aware projects for translated literals. */
#define _(STR) gettext(STR)

/* Lookup table that maps every integer in [1,100] to its Roman numeral spelling. */
char *const roman_table[101] = {
    "",
    "I",
    "II",
    "III",
    "IV",
    "V",
    "VI",
    "VII",
    "VIII",
    "IX",
    "X",
    "XI",
    "XII",
    "XIII",
    "XIV",
    "XV",
    "XVI",
    "XVII",
    "XVIII",
    "XIX",
    "XX",
    "XXI",
    "XXII",
    "XXIII",
    "XXIV",
    "XXV",
    "XXVI",
    "XXVII",
    "XXVIII",
    "XXIX",
    "XXX",
    "XXXI",
    "XXXII",
    "XXXIII",
    "XXXIV",
    "XXXV",
    "XXXVI",
    "XXXVII",
    "XXXVIII",
    "XXXIX",
    "XL",
    "XLI",
    "XLII",
    "XLIII",
    "XLIV",
    "XLV",
    "XLVI",
    "XLVII",
    "XLVIII",
    "XLIX",
    "L",
    "LI",
    "LII",
    "LIII",
    "LIV",
    "LV",
    "LVI",
    "LVII",
    "LVIII",
    "LIX",
    "LX",
    "LXI",
    "LXII",
    "LXIII",
    "LXIV",
    "LXV",
    "LXVI",
    "LXVII",
    "LXVIII",
    "LXIX",
    "LXX",
    "LXXI",
    "LXXII",
    "LXXIII",
    "LXXIV",
    "LXXV",
    "LXXVI",
    "LXXVII",
    "LXXVIII",
    "LXXIX",
    "LXXX",
    "LXXXI",
    "LXXXII",
    "LXXXIII",
    "LXXXIV",
    "LXXXV",
    "LXXXVI",
    "LXXXVII",
    "LXXXVIII",
    "LXXXIX",
    "XC",
    "XCI",
    "XCII",
    "XCIII",
    "XCIV",
    "XCV",
    "XCVI",
    "XCVII",
    "XCVIII",
    "XCIX",
    "C"
};

/* Returns a pointer to the Roman spelling for value or NULL when out of range. */
char *decimal_to_roman(int value) {
    if (value < 1 || value > 100) {
        return NULL;
    }
    return roman_table[value];
}

/* Converts a Roman numeral string in [I,C] to its integer value or -1 on errors. */
int roman_to_decimal(const char *roman) {
    if (roman == NULL || *roman == '\0') {
        return -1;
    }

    char normalized[16];
    size_t len = strlen(roman);
    if (len >= sizeof(normalized)) {
        return -1;
    }

    for (size_t i = 0; i < len; ++i) {
        normalized[i] = (char)toupper((unsigned char)roman[i]);
    }
    normalized[len] = '\0';

    for (int i = 1; i <= 100; ++i) {
        if (strcmp(normalized, roman_table[i]) == 0) {
            return i;
        }
    }
    return -1;
}

/* Prints English + Russian help text then exits. */
static void print_help(const char *prog_name) {
    printf("Usage (EN): %s [-r] [--help]\n", prog_name);
    printf("  -r       %s\n", _("Play entirely with Roman numerals."));
    printf("  --help   %s\n", _("Show this help message and exit."));
    printf("\n");
}

/* Binary-search guessing game that optionally works entirely in Roman mode via -r. */
int main(int argc, char **argv) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALE_PATH);
    textdomain(PACKAGE);

    bool roman_mode = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-r") == 0) {
            roman_mode = true;
        } else if (strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        } else {
            fprintf(stderr, _("Unknown option: %s\n"), argv[i]);
            print_help(argv[0]);
            return 1;
        }
    }

    int low = 1, high = 100;
    char answer[4];
    
    if (roman_mode) {
        printf(_("Guess a number from %s to %s.\n"),
               decimal_to_roman(low), decimal_to_roman(high));
    } else {
        printf(_("Guess a number from %d to %d.\n"), low, high);
    }
    
    while (low < high) {
        int mid = (low + high) / 2;
        if (roman_mode) {
            const char *roman_mid = decimal_to_roman(mid);
            printf(_("Higher than %s?\n"), roman_mid ? roman_mid : "?");
        } else {
            printf(_("Higher than %d?\n"), mid);
        }
        
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
    
    if (roman_mode) {
        const char *roman_answer = decimal_to_roman(low);
        printf(_("Answer: %s\n"), roman_answer ? roman_answer : "?");
    } else {
        printf(_("Answer: %d\n"), low);
    }
    return 0;
}