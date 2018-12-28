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
void species_count(char species[], int n_sightings, struct pod sightings[n_sightings], int *n_pods, int *n_whales);

int main(int argc, char *argv[]) {
	if (argc != 3) {
			fprintf(stderr, "Usage %s <file>\n", argv[0]);
			exit(1);
	}

	char *filename = argv[1];
	char *species = argv[2];

	//Initialise array of sightings.
	struct pod whale_sightings[MAX_SIGHTINGS];

	// Read in the data to memory from the files.
	// Return the number of reads.


	int n_sightings = read_sightings_file(argv[1], MAX_SIGHTINGS, whale_sightings);

	if (n_sightings < 1) {
			return 1;
	}

	int pod_count;
	int whale_count;

	species_count(species, n_sightings, whale_sightings, &pod_count, &whale_count);
	printf("%d %s pods containing %d whales in %s\n", pod_count, species, whale_count, filename);



	return EXIT_SUCCESS;
}

// IDEA: For each line of input from the struct, strip all non alphanumeric
// characters and turn everything to lower case. Compare this the same
// thing in the species file, if it is the same then return the string
// written in the file.

void species_count(char species[], int n_sightings, struct pod sightings[n_sightings], int *n_pods, int *n_whales) {
	int i = 0;
	int pods = 0;
	int whales = 0;
	while (i < n_sightings) {
		if (strcmp(species, sightings[i].species) == 0) {
			pods += 1;
			whales += sightings[i].how_many;
		}
		i++;
	}
	*n_pods = pods;
	*n_whales = whales;
	return;
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
