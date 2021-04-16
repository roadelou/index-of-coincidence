/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-04-16
 * Language: C Source
 */

/********************************** INCLUDES **********************************/

/* The library we are implementing */
#include <ioc.h>

/* Used for memset. */
#include <string.h>

/********************************* SINGLETONS *********************************/

/* For the sake of having some more readable code, we define a constant for the
 * number of letters in the alphabet. The compiler can optimize it out since it
 * is static. */
const static int ALPHABET_SIZE = 26;

/* The globally allocated constant strings for the languages representations. */
const char *RANDOM_REPRESENTATION = "RANDOM";
const char *ENGLISH_REPRESENTATION = "ENGLISH";
const char *ITALIAN_REPRESENTATION = "ITALIAN";
const char *FRENCH_REPRESENTATION = "FRENCH";
const char *GERMAN_REPRESENTATION = "GERMAN";
/* The value returned for a garbage input. */
const char *GARBAGE_REPRESENTATION = "GARBAGE";

/********************************* PROTOYPES **********************************/

/* The prototypes of your functions go here. */

/************************************ MAIN ************************************/

/* The main function of your code goes here. */

/********************************* FUNCTIONS **********************************/

/* The public functions we are implementing. */

float index_of_coincidence(const char *text, size_t size) {
    /* We normalize the kappa_plaintext with the number of letters in the
     * alphabet. Doing it that way means we just have to do a multiplication
     * instead of division. Not that it matters... */
    return kappa_plaintext(text, size) * ALPHABET_SIZE;
}

float kappa_plaintext(const char *text, size_t size) {
    /* We create a table to hold the number of occurence of each letters. */
    size_t occurences[ALPHABET_SIZE];

    /* Setting all the occurences to 0 initialy. */
    memset((size_t *)occurences, 0, ALPHABET_SIZE * sizeof(size_t));

    /* We iterate over the characters of the input text. */
    for (size_t i = 0; i < size; i++) {
        /* The character we are currently inspecting. */
        char letter = *(text + i);
        /* If the character is a valid ASCII lowercase letter, we count it. We
         * are relying on the fact that the lowercase letters are contiguously
         * ordered in the ASCII encoding.
         * */
        if ((letter >= 'a') && (letter <= 'z')) {
            /* We can compute the index of the character to increment by
             * computing the offset of the found letter from 'a'. */
            occurences[letter - 'a']++;
        }
        /* We just ignore any other characters. */
    }

    /* Some variables used in the formula of the index of coincidence. */
    size_t numerator = 0;
    size_t total = 0;

    /* We iterate over the letters of the lowercase alphabet to compute the
     * index of coincidence. */
    for (size_t i = 0; i < ALPHABET_SIZE; i++) {
        /* We grab the number of occurences of the letter for more concise code.
         */
        size_t occurences_letter = *(occurences + i);
        numerator += occurences_letter * (occurences_letter - 1);
        /* This letter contributes to the total number of letters counted in the
         * text. */
        total += occurences_letter;
    }

    /* We return the final value. */
    return ((float)numerator) / (total * (total - 1));
}

enum Language likely_language(const char *text, size_t size) {
    /* We use a simple if chain with float comparison to guess the language.
     * "ic" stands for "index of coincidence". */
    float ic = index_of_coincidence(text, size);

    /* We rely on the sequential evaluation of tests to avoid some comparisons.
     */
    if (ic < 1.6) {
        return RANDOM;
    } else if (ic < 1.8) {
        return ENGLISH;
    } else if (ic < 1.98) {
        return ITALIAN;
    } else if (ic < 2.03) {
        return FRENCH;
    } else {
        return GERMAN;
    }
}

const char *language_string(enum Language language) {
    /* We use a simple string and return the globally allocated values for the
     * language. */
    switch (language) {
    case RANDOM:
        return RANDOM_REPRESENTATION;
    case ENGLISH:
        return ENGLISH_REPRESENTATION;
    case ITALIAN:
        return ITALIAN_REPRESENTATION;
    case FRENCH:
        return FRENCH_REPRESENTATION;
    case GERMAN:
        return GERMAN_REPRESENTATION;
    default:
        /* This should never happen, but still... */
        return GARBAGE_REPRESENTATION;
    }
}

/************************************ EOF *************************************/
