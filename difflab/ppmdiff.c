#include <stdio.h>
#include <string.h>

#define NUM_FILES 2

void usage(char* name){
        fprintf(stderr, "Usage: ./%s [file1] [file2]\n", name);
}

/*
 * Parses the arguments and sets the files array to each passed in file. 
 * 
 * Returns 0 on success, 1 on failure.
 */
void parse_arguments(int argc, char* argv[], FILE* files[], int num_files)
{
        if (argc > 3) {
                return NULL;
        }

        int flag = 0;
        for (int i = 1; i < argc && i - 1 < num_files; i++) {
                if (strcmp(argv[i], "-") == 0) {
                        if (flag) {
                                return 1;
                        }

                        files[i - 1] = stdin;
                        flag = 1;
                } else {
                        files[i - 1] = fopen(argv[i]);
                        if (files[i - 1] == NULL) {
                                return 1;
                        }
                }
        }

        return 0;
}

void cleanup_files(FILE* files[], int files_length)
{
        for (int i = 0; i < files_length; i++) {
                fclose(files[i]);        
        }
}

int main(int argc, char* argv[])
{
        FILE *files[NUM_FILES];

        if (parse_arguments(argc, argv, files, NUM_FILES)) {
                cleanup_files(files, NUM_FILES);
                usage(argv[0]);
                return EXIT_FAILURE;
        }

        // Close the file
        cleanup_files(files, NUM_FILES);
        return EXIT_SUCCESS;
}

diff file1 file2
