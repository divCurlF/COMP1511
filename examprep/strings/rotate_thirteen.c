// Perform the ROT13 algorithm on a string
// Completed by
//  ... (z0000000)
//  ... (z0000000)
// Commpleted on 2017-08-??
// Tutor's name (day_hH-lab)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 256

// Add your own #defines here

void rotate_thirteen(char *string);
char rotate_one(char c);
void rotate_thirteen(char *string);
int strings_equal(char *string1, char *string2);

// Add your own function porototypes here

int main(int argc, char *argv[]) {
    // Example tests
    char test_a[MAX_LENGTH] = "Hello, world!";
    rotate_thirteen(test_a);
    assert(strings_equal("Uryyb, jbeyq!", test_a));

    char test_b[MAX_LENGTH] = "abcdefghijklmnopqrstuvwxyz";
    rotate_thirteen(test_b);
    assert(strings_equal("nopqrstuvwxyzabcdefghijklm", test_b));

    char test_c[MAX_LENGTH] = "The quick brown fox jumped over the lazy dog.";
    rotate_thirteen(test_c);
    assert(strings_equal("Gur dhvpx oebja sbk whzcrq bire gur ynml qbt.", test_c));

    // Add your own tests here

    printf("All tests passed. You are awesome!\n");

    return 0;
}

void rotate_thirteen(char *string) {
    int i = 0;
    while (string[i] != '\0') {
    	if (isupper(string[i])) {
    		string[i] = (string[i] - 'A' + 13) % 26 + 'A';
    	} else if (islower(string[i])) {
    		string[i] = (string[i] - 'a' + 13) % 26 + 'a';
    	}
    	
    	i++;
    }
}

int strings_equal(char *string1, char *string2) {
    return (strcmp(string1, string2) == 0);
}
