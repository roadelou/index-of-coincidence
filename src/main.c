/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-04-16
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

/* Header for the functions we have built. */
#include <ioc.h>

/* Used for io manipulations. */
#include <stdio.h>

/* Used for the command line arguments. */
#include <getopt.h>

/* Used for malloc and realloc. */
#include <stdlib.h>

/* Used for the ERRNO enums values. */
#include <errno.h>

/* An enum used to represent the mode in which the tool is running. */
enum Mode {
    IC,              /* We print the index of occurences. */
    KAPPA_PLAINTEXT, /* We print the kappa plaintext value. */
    LANGUAGE,        /* We print the guessed language as a string. */
    HELP,            /* We print the help. */
};

/* A compile time overridable cllocation length used when consuming the input.
 */
#ifndef BLOCK_CONSUME_INPUT
#define BLOCK_CONSUME_INPUT 1024
#endif

/********************************* SINGLETONS *********************************/

/* The static global variables for your code goe here. */

/********************************* PROTOYPES **********************************/

/* Prints the help message for the tool on stdout. */
int print_help(void);

/************************************ MAIN ************************************/

int main(int argc, char *const *argv) {
    /* Used to hold the value returned by getopt. */
    int opt;

    /* Used to determine what the tool will run. Default is index of occurences.
     */
    enum Mode mode = IC;

    /* We let getopt do the error handling. */
    while ((opt = getopt(argc, argv, "iklh")) != -1) {
        switch (opt) {
        case 'i':
            /* Index of coincidence mode. */
            mode = IC;
            break;
        case 'k':
            /* kappa plaintext mode. */
            mode = KAPPA_PLAINTEXT;
            break;
        case 'l':
            /* Language guess mode. */
            mode = LANGUAGE;
            break;
        case 'h':
            /* Help mode. */
            mode = HELP;
            break;
        default:
            /* Error handling. An error message has already been printed by
             * getopt, we just have to exit. */
            return EINVAL;
        }
    }

    /* Edge case, if the mode requested is to print the help, we shortcut the
     * rest of the program. */
    if (mode == HELP) {
        print_help();
        /* The execution was a success, we simply exit. */
        return EXIT_SUCCESS;
    }

    /* We now consume the entire stdin and put it into a dynamically allocated
     * array. */
    char *stdin_array = malloc(BLOCK_CONSUME_INPUT * sizeof(char));
    /* The real length of the stdin_array. */
    size_t stdin_size = 0;
    /* The number of characters read in one chunk of the following loop. */
    size_t chunk_size;

    /* We now consume the entire input using fread for performance. */
    while ((chunk_size = fread(stdin_array, sizeof(char), BLOCK_CONSUME_INPUT,
                               stdin)) == BLOCK_CONSUME_INPUT) {
        /* We have successfully read an entire chunk of the input, we move on to
         * the next one. */
        /* We update the length of our stdin buffer. */
        stdin_size += chunk_size;
        /* We have to resize our buffer. */
        char *temporary_pointer = realloc(
            stdin_array, (stdin_size + BLOCK_CONSUME_INPUT) * sizeof(char));
        /* We check if the realloc was successfull. */
        if (temporary_pointer == NULL) {
            /* We are out of memory. We free the stdin buffer as we won't use
             * it. */
            free(stdin_array);
            /* We print a small error message. */
            fprintf(stderr,
                    "Out of memory encountered after character %lu of stdin.\n",
                    stdin_size);
            /* We exit with an error code. */
            return ENOMEM;
        } else {
            /* We found some memory, we swap our old pointer for the new one. */
            stdin_array = temporary_pointer;
        }
    }

    /* We check if we failed because of an error. */
    if (ferror(stdin)) {
        /* We free the allocated memory. */
        free(stdin_array);
        /* We print an error message. */
        fprintf(stderr, "IO error encountered after character %lu of stdin.\n",
                stdin_size);
        /* We return an error code. */
        return EIO;
    }
    /* else it means that we have reached EOF, which is the expected behavior.
     * We still have to account for the last call to fread in our stdin_size. */
    stdin_size += chunk_size;

    /* Depending the chosen mode, we print the appropriate result. */
    switch (mode) {
    case IC: {
        /* We compute and print the index of coincidence. */
        float ic = index_of_coincidence(stdin_array, stdin_size);
        printf("Index of Coincidence: %f\n", ic);
        break;
    }
    case KAPPA_PLAINTEXT: {
        /* We compute and print the kappa_plaintext. */
        float kp = kappa_plaintext(stdin_array, stdin_size);
        printf("Kappa Plaintext: %f\n", kp);
        break;
    }
    case LANGUAGE: {
        /* We compute and print the guessed language. */
        enum Language language = likely_language(stdin_array, stdin_size);
        printf("Likely Language: %s\n", language_string(language));
        break;
    }
    default: {
        /* Inconsistent value, should never happen. */
        fprintf(stderr, "Inconsistent Mode: %d\n", mode);
        /* We free the memory currently reserved. */
        free(stdin_array);
        /* We return an error code. */
        return EINVAL;
    }
    }

    /* If we reached this line, the execution was a success. We free the
     * allocated memory and exit the process. */
    free(stdin_array);
    return EXIT_SUCCESS;
}

/********************************* FUNCTIONS **********************************/

int print_help(void) {
    return puts(
        "Usage: index-of-coincidence [options]\n"
        "\n"
        "Description\n"
        "===========\n"
        "Computes the Index of Coincidence of the lowercase ASCII text from "
        "stdin.\n"
        "\n"
        "Options\n"
        "=======\n"
        " -i\n"
        "   Output the Index of Coincidence of the input (the default).\n"
        "\n"
        " -k\n"
        "   Output the kappa plaintext of the input.\n"
        "\n"
        " -l\n"
        "   Tries to guess the input language of the input from the index of "
        "coincidence.\n"
        "\n"
        " -h\n"
        "   Prints this help message and exits\n"
        "\n"
        "Note\n"
        "====\n"
        "Only the last specified option will be considered.");
}

/************************************ EOF *************************************/
