#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void subs(const char* string, const regmatch_t* matches, const char* substitution, char** result) {
    size_t result_size = 0;
    size_t result_len = 0;
    *result = NULL;
    
    for (size_t i = 0; substitution[i] != '\0'; ) {
        if (substitution[i] != '\\') {
            if (result_len + 1 >= result_size) {
                result_size = result_size ? result_size * 2 : 64;
                *result = realloc(*result, result_size);
                if (!*result) {
                    perror("realloc");
                    exit(1);
                }
            }
            (*result)[result_len++] = substitution[i++];
            (*result)[result_len] = '\0';
            continue;
        }
        
        i++;
        
        if (substitution[i] == '\\') {
            if (result_len + 1 >= result_size) {
                result_size = result_size ? result_size * 2 : 64;
                *result = realloc(*result, result_size);
                if (!*result) {
                    perror("realloc");
                    exit(1);
                }
            }
            (*result)[result_len++] = '\\';
            (*result)[result_len] = '\0';
            i++;
            continue;
        }
        
        if (substitution[i] >= '0' && substitution[i] <= '9') {
            int pocket = substitution[i] - '0';
            i++;
            
            if (matches[pocket].rm_so == -1) {
                fprintf(stderr, "Error: reference to non-existent pocket \\%d\n", pocket);
                exit(1);
            }
            
            int start = matches[pocket].rm_so;
            int end = matches[pocket].rm_eo;
            int pocket_len = end - start;
            
            if (result_len + pocket_len >= result_size) {
                result_size = result_len + pocket_len + 1;
                *result = realloc(*result, result_size);
                if (!*result) {
                    perror("realloc");
                    exit(1);
                }
            }
            
            memcpy(*result + result_len, string + start, pocket_len);
            result_len += pocket_len;
            (*result)[result_len] = '\0';
            continue;
        }
        
        fprintf(stderr, "invalid escape sequence '\\%c'\n", substitution[i]);
        exit(1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s regexp substitution string\n", argv[0]);
        return 1;
    }
    
    char* regexp_str = argv[1];
    char* substitution = argv[2];
    char* string = argv[3];
    char error_buf[100];
    
    regex_t regex;
    int ret = regcomp(&regex, regexp_str, REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, error_buf, sizeof(error_buf));
        fprintf(stderr, "regcomp error: %s\n", error_buf);
        return 1;
    }
    
    regmatch_t matches[10];
    ret = regexec(&regex, string, 10, matches, 0);
    
    if (ret == REG_NOMATCH) {
        printf("%s\n", string);
        regfree(&regex);
        return 0;
    } else if (ret != 0) {
        regerror(ret, &regex, error_buf, sizeof(error_buf));
        fprintf(stderr, "regexec error: %s\n", error_buf);
        regfree(&regex);
        return 1;
    }
    
    char* replacement = NULL;
    subs(string, matches, substitution, &replacement);
    
    if (!replacement) {
        replacement = strdup("");
    }
    
    int start = matches[0].rm_so;
    int end = matches[0].rm_eo;
    if (start > 0) {
        fwrite(string, 1, start, stdout);
    }
    
    printf("%s", replacement);
    
    if (string[end] != '\0') {
        printf("%s", string + end);
    }
    
    printf("\n");
    
    free(replacement);
    regfree(&regex);
    
    return 0;
}