//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

#define MAX_SPECIES_NAME_LENGTH 128
#define MAX_WHALE_SPECIES    	256
#define MAX_SIGHTINGS 		10000

// Create a struct of date: day, month, year whale sighting was made
// Create a struct to represent a sighting of a group of whales - how many, date, string for species name.
//
//

struct date {
	int year;
	int month;
	int day;
};

struct pod {
	struct date 	when;
	int 		how_many;
	char		species[MAX_SPECIES_NAME_LENGTH];
};


int read_sightings_file(char filename[], int len, struct pod sightings[len]);
int read_sighting(FILE *f, struct pod *w);
int read_date(FILE *f, struct date *d);

void write_sightings_file(char filename[], int n_sightings, struct pod sightings[n_sightings]);
void write_sighting(FILE *f, struct pod *p);
void write_date(FILE *f, struct date *d);

void sanitize_whales(char species_names_file[], int n_sightings, struct pod sightings[n_sightings]);

void readValid(char species_names_file[], char valid_species[MAX_WHALE_SPECIES][MAX_SPECIES_NAME_LENGTH], int *n_species);
char* actualString(char valid_species[MAX_WHALE_SPECIES][MAX_SPECIES_NAME_LENGTH], char* clean_string, int n_species);
void convertValid(char arr[MAX_SPECIES_NAME_LENGTH]);

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "Usage: %s <species_names_file> <old_file> <new_file>\n", argv[0]);
		return 1;
	}

    	char *species_names_file = argv[1];
    	char *old_file = argv[2];
    	char *new_file = argv[3];

	//Initialise array of sightings.
	struct pod whale_sightings[MAX_SIGHTINGS];

	// Read in the data to memory from the files.
	// Return the number of reads.


	int n_sightings = read_sightings_file(old_file, MAX_SIGHTINGS, whale_sightings);

	if (n_sightings < 1) {
		return 1;
	}

	sanitize_whales(species_names_file, n_sightings, whale_sightings);
	write_sightings_file(new_file, n_sightings, whale_sightings);

	return EXIT_SUCCESS;
}

// IDEA: For each line of input from the struct, strip all non alphanumeric
// characters and turn everything to lower case. Compare this the same
// thing in the species file, if it is the same then return the string
// written in the file.

void sanitize_whales(char species_names_file[], int n_sightings, struct pod sightings[n_sightings]) {

	char valid_species_unstripped[MAX_WHALE_SPECIES][MAX_SPECIES_NAME_LENGTH];
	char valid_species[MAX_WHALE_SPECIES][MAX_SPECIES_NAME_LENGTH];

	int n_species;
	readValid(species_names_file, valid_species_unstripped, &n_species);
	readValid(species_names_file, valid_species, &n_species);

	int i = 0;
	while ( i < n_species) {
		convertValid(valid_species[i]);
		i++;
	}

	// take sightings[i].species and convert it to lower case no whitespace. (cleanstring)
	// take valid string array, convert it to lower case no whitespace.

	i = 0;
	while (i < n_sightings) {
		convertValid(sightings[i].species);
		int j = 0;
		while (j < n_species) {
			if (strcmp(sightings[i].species, valid_species[j]) == 0) {
				strcpy(sightings[i].species, valid_species_unstripped[j]);
				break;
			}
			j++;
		}
		i++;
	}
	return;
}

//Removes non-alphanumeric characters from a string.

void convertValid(char arr[MAX_SPECIES_NAME_LENGTH]) {

	char clean_string[MAX_SPECIES_NAME_LENGTH];
	int clean_len = 0;

	int i = 0;
	while (i < strlen(arr)) {
		if (isalpha(arr[i])) {
			clean_string[clean_len] = tolower(arr[i]);
			clean_len++;
		}
		i++;
	}
	clean_string[clean_len] = '\0';
	strcpy(arr, clean_string);
}



// Return number of sightings read from filename. or -1 if error or none read.
int read_sightings_file(char filename[], int len, struct pod sightings[len]) {
	FILE *input = fopen(filename, "r");

	if (input == NULL) {
		fprintf(stderr, "File could not be read.");
		return -1;
	}

	// Read_sightings for the length of the data file.
	// Stop reading when we fail to read a sighting.

	int i = 0;
	while (read_sighting(input, &sightings[i]) == 1 && i < len ) {
			i++;
	}

	fclose(input);
	return i;
}

// Return 1 if a sighting can be read, 0 otherwise.

int read_sighting(FILE *f, struct pod *s) {
	// read in the date.
	if (read_date(f, &s->when) != 1) {
		return 0;
	}
	if (fscanf(f, "%d", &s->how_many) != 1) {
		return 0;
	}

	//Get the whitespace character.

	fgetc(f);
	if (fgets(s->species, MAX_SPECIES_NAME_LENGTH, f) == NULL) {
		return 0;
	}

	//Linux newline
	char *newline_ptr = strchr(s->species, '\n');
	if (newline_ptr != NULL) {
		*newline_ptr = '\0';
	}

	//Windows carriage return.
	newline_ptr = strchr(s->species, '\r');
	if (newline_ptr != NULL) {
		*newline_ptr = '\0';
	}

	return 1;
}

//Return 1 if a date can be read, 0 otherwise.
int read_date(FILE *f, struct date *d) {
	if (fscanf(f, "%d/%d/%d", &d->day, &d->month, &d->year) != 3) {
			return 0;
	}
	return 1;
}

void write_sightings_file(char filename[], int n_sightings, struct pod sightings[n_sightings]) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr,"error: file '%s' can not open\n", filename);
        exit(1);
    }

    int i = 0;
    while (i < n_sightings) {
        write_sighting(f, &sightings[i]);
        i = i + 1;
    }
    fclose(f);
}
// print pod details to stream f

void write_sighting(FILE *f, struct pod *s) {
    write_date(f, &(s->when));
    fprintf(f, " %2d %s\n", s->how_many, s->species);
}



// print date to  stream f

void write_date(FILE *f, struct date *d) {
    fprintf(f, "%02d/%02d/%02d", d->year, d->month, d->day);
}


// Reads in the valid species names into an array from given file.
void readValid(char species_names_file[], char valid_species[MAX_WHALE_SPECIES][MAX_SPECIES_NAME_LENGTH], int *n_species) {
	FILE *f = fopen(species_names_file, "r");
	if (f == NULL) {
		printf("File read error");
		exit(1);
	}

	int i = 0;
	int n_reads = 0;

	while (i < MAX_SPECIES_NAME_LENGTH) {
		if (fgets(valid_species[i], MAX_SPECIES_NAME_LENGTH, f) != NULL) {
			//Linux newline
			char *newline_ptr = strchr(valid_species[i], '\n');
			if (newline_ptr != NULL) {
				*newline_ptr = '\0';
			}

			//Windows carriage return.
			newline_ptr = strchr(valid_species[i], '\r');
			if (newline_ptr != NULL) {
				*newline_ptr = '\0';
			}
			n_reads++;

		} else {
			// reached the end of the file.
			break;
		}
		i++;
	}
	*n_species = n_reads;
	fclose(f);
}
