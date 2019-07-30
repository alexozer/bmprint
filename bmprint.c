#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char bm_path[512] = {};
    snprintf(bm_path, sizeof(bm_path), "%s%s", getenv("HOME"), "/doc/personal/bookmarks");

    FILE *bm_file = fopen(bm_path, "r");
    if (!bm_file) {
        fprintf(stderr, "Failed to open %s\n", bm_path);
        return 1;
    }

    char line[512] = {};
    while (fgets(line, sizeof(line), bm_file)) {
        if (line[0] == '\n' || line[0] == '#') continue;

        char *tab_ptr = strchr(line, '\t');
        if (!tab_ptr) {
            fprintf(stderr, "Invalid entry, no TAB found\n");
            return 1;
        }
        if (tab_ptr == line || tab_ptr == line + sizeof(line) - 1) {
            fprintf(stderr, "Invalid entry, empty title or URL\n");
            return 1;
        }

        *tab_ptr = '\0'; // Split string in two
        char *title = line;
        size_t title_len = tab_ptr - line;
        char *url = tab_ptr + 1;

        char padded_title[31] = {};
        memset(padded_title, ' ', sizeof(padded_title));
        memcpy(padded_title, title, title_len);
        padded_title[sizeof(padded_title) - 1] = '\0';

        printf("%s\t\x1b[36m%s\x1b[m", padded_title, url);
    }

    fclose(bm_file);
}