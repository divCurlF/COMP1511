//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)

#define MAX_SPECIES_NAME_LENGTH 128
#define MAX_SIGHTINGS 10000

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
	struct date when;
	int 		how_many;
	char		species[MAX_SPECIES_NAME_LENGTH];
};


int read_sightings_file(char filename[], int len, struct pod sightings[len]);
int read_sighting(FILE *f, struct pod *w);
int read_date(FILE *f, struct date *d);

int count_orca_sightings(int n_sightings, struct pod sightings[n_sightings]);

int isOrca(char *species);
void sanitize_whale(char species_names_file[], int n_sightings, struct pod sightings[n_sightings]);

void print_data(int n_sightings, struct pod sightings[n_sightings]);


int main(int argc, char *argv[]) {
	if (argc != 2) {
			fprintf(stderr, "Usage %s <file>\n", argv[0]);
			exit(1);
	}

	//Initialise array of sightings.
	struct pod whale_sightings[MAX_SIGHTINGS];

	// Read in the data to memory from the files.
	// Return the number of reads.
	int n_sightings = read_sightings_file(argv[1], MAX_SIGHTINGS, whale_sightings);

	// print_data(n_sightings, whale_sightings);
	if (n_sightings > 0) {
			int n_orca_pods = count_orca_sightings(n_sightings, whale_sightings);
			printf("%d Orca sightings in %s\n", n_orca_pods, argv[1]);
	}
	return EXIT_SUCCESS;
}

// IDEA: For each line of input from the struct, strip all non alphanumeric
// characters and turn everything to lower case. Compare this the same
// thing in the species file, if it is the same then return the string
// written in the file.

void sanitize_whale(char species_names_file[], int n_sightings, struct pod sightings[n_sightings]) {

}
void print_data(int n_sightings, struct pod whale_sightings[n_sightings]) {

	printf("There are %d data entries\n", n_sightings);

	int i = 0;
	while (i < n_sightings) {
		printf("%s\n", whale_sightings[i].species);
		i++;
	}
}

int count_orca_sightings(int n_sightings, struct pod sightings[n_sightings]) {

	int sum = 0;
	int i = 0;
	while ( i < n_sightings) {
		if (isOrca(sightings[i].species)) {
				sum++;
		}
		i++;
	}
	return sum;
}

int isOrca(char *species) {
	if (strcmp(species, "Orca") == 0) {
			return TRUE;
	}
	return FALSE;
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
