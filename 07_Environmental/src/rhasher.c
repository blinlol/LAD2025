#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <rhash.h>

// #define HAVE_READLINE 1

#ifdef HAVE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#define MAX_DIGEST_SIZE 128
#define MAX_RESULT_SIZE 256

void initialize_readline(void) {
#ifdef HAVE_READLINE
    rl_bind_key('\t', rl_complete);
#endif
}

char *read_input(const char *prompt) {
    char *line = NULL;
    
#ifdef HAVE_READLINE
    line = readline(prompt);
    if (line && *line) {
        add_history(line);
    }
#else
    size_t buffer_size = 0;
    printf("%s", prompt);
    fflush(stdout);
    
    size_t len = getline(&line, &buffer_size, stdin);
    if (len > 0) {
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
    } else {
        free(line);
        line = NULL;
    }
#endif
    
    return line;
}

void free_input(char *line) {
    free(line);
}

void add_to_history(const char *line) {
#ifdef HAVE_READLINE
    if (line && *line) {
        add_history(line);
    }
#endif
}

int compute_hash(const char *algorithm, const char *target, char *result, size_t result_size) {
    int hash_id;
    if (strcasecmp(algorithm, "MD5") == 0) hash_id = RHASH_MD5;
    else if (strcasecmp(algorithm, "SHA1") == 0) hash_id = RHASH_SHA1;
    else if (strcasecmp(algorithm, "TTH") == 0) hash_id = RHASH_TTH;
    else {
        fprintf(stderr, "Error: unknown algorithm '%s'\n", algorithm);
        return -1;
    }

    int output_mode = isupper((unsigned char)algorithm[0]) ? RHPR_HEX : RHPR_BASE64;

    unsigned char digest[MAX_DIGEST_SIZE];
    int res;

    if (target[0] == '"') {    
        res = rhash_msg(hash_id, target+1, strlen(target)-1, digest);
    } else {
        res = rhash_file(hash_id, target, digest);
    }

    if (res < 0) {
        fprintf(stderr, "Error computing hash for '%s'\n", target);
        return -1;
    }

    rhash_print_bytes(result, digest, rhash_get_digest_size(hash_id), output_mode);
    return 0;
}

int main(void) {
    rhash_library_init();
    
    initialize_readline();

    while (1) {
        char *line = read_input("> ");
        if (!line) {
            break;
        }

        if (strlen(line) == 0) {
            free_input(line);
            continue;
        }

        char *line_copy = strdup(line);
        char *algorithm = strtok(line_copy, " \t");
        char *target = strtok(NULL, " \t");

        if (!algorithm || !target) {
            fprintf(stderr, "Error: invalid command format\n");
            free(line_copy);
            free_input(line);
            continue;
        }

        char result[MAX_RESULT_SIZE];
        if (compute_hash(algorithm, target, result, sizeof(result)) == 0) {
            printf("%s\n", result);
        }

        free(line_copy);
        free_input(line);
    }

    return 0;
}