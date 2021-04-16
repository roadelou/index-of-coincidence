/* Include once header guard */
#ifndef INDEX_OF_COINCIDENCE_INCLUDED
#define INDEX_OF_COINCIDENCE_INCLUDED

/********************************** METADATA **********************************/

/*
 * Contributors: roadelou
 * Contacts:
 * Creation Date: 2021-04-16
 * Language: C Header
 */

/********************************** INCLUDES **********************************/

/* Used for the definition of size_t. */
#include <stddef.h>

/*********************************** MACROS ***********************************/

/* The macros definitions for your header go here */

/********************************** STRUCTS ***********************************/

/* An enum used to represent various languages, returned by the
 * "likely_language" function. Random refers to a random string of characters.
 * */
enum Language {
    ENGLISH,
    FRENCH,
    GERMAN,
    ITALIAN,
    RANDOM,
};

/* The structs of your header go here */

/* The unions of your header go here */

/* The typedefs of your header go here */

/********************************* PROTOTYPES *********************************/

/* Returns the index of coincidence for the provided text.
 *
 * The alphabet used is the 26 letters (lowercase) latin alphabet. ASCII
 * encoding only. Any other non-recognized ASCII character will simply be
 * discarded and won't contribute to the total count of letters.
 *
 * Arguments
 * =========
 *  - text: The text to compute the index of coincidence on.
 *  - size: The number of characters in the text, assuming ASCII encoding.
 *
 * Returns
 * =======
 * A float holding the index of coincidence for the provided text. The value
 * reported is normalized over the number of letters in te alphabet. In other
 * words, we are return the "IC" value and not the "kappa_plaintext". The
 * relation between the two is: IC = 26 * kappa_plaintext.
 * */
float index_of_coincidence(const char *text, size_t size);

/* Returns the kappa plaintext associated with the provided text.
 *
 * For more information, see "index_of_coincidence".
 * */
float kappa_plaintext(const char *text, size_t size);

/* Returns the guessed language of the provided text based on its index of
 * coincidence. The non-latin characters (accents in french and the Eszett in
 * german) have to be removed before analysis because they aren't valid ASCII.
 *
 * Arguments
 * =========
 *  - text: The provided ASCII text to analyze.
 *  - size: The number of characters in the text, assuming ASCII encoding.
 *
 * Returns
 * =======
 * The likely language as "Language" enum.
 *
 * Note
 * ====
 * Given the IC of the language, the rules for the guess are:
 *  - IC < 1.6: Random,
 *  - 1.6 <= IC < 1.8: English,
 *  - 1.8 <= IC < 1.98: Italian,
 *  - 1.98 <= IC < 2.03: French,
 *  - 2.03 <= IC: German,
 * */
enum Language likely_language(const char *text, size_t size);

/* Returns a string representation of the provided Language value. The string is
 * statically alocated (i.e. the caller shouldn't attempt to free it) but
 * constant.
 * */
const char *language_string(enum Language language);

/* End of include once header guard */
#endif

/************************************ EOF *************************************/
