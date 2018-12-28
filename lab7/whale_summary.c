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
#define MAX_SIGHTINGS			10000
#define MAX_WHALE_SPECIES		256

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

struct tally {
	int 	n_pods;
	int 	n_whales;
	char 	species[MAX_SPECIES_NAME_LENGTH];
};


int read_sightings_file(char filename[], int len, struct pod sightings[len]);
int read_sighting(FILE *f, struct pod *w);
int read_date(FILE *f, struct date *d);
void whale_summary(int n_sightings, struct pod sightings[n_sightings]);

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

	if (n_sightings < 1) {
		return 1;
	}

	whale_summary(n_sightings, whale_sightings);


	return EXIT_SUCCESS;
}

// Construct an array that stores all the species.
// Keep a counter of how many species we have seen n.
// For each sighting, check if the species is in the summary array
// If it is, adjust the entry, break the inner loop.
// If it isn't, create an index at entry n.
void whale_summary(int n_sightings, struct pod sightings[n_sightings]) {
	struct tally summary[MAX_WHALE_SPECIES];
	int n_summaries = 0;
	int i = 0;
	while (i < n_sightings) {
		int j = 0;

		// it is a new_summary until proven otherwise by strcmp.
		int new_summary = TRUE;
		while (j < n_summaries) {
			if (strcmp(sightings[i].species, summary[j].species) == 0) {
				summary[j].n_pods++;
				summary[j].n_whales += sightings[i].how_many;
				new_summary = FALSE;
			}
			j++;
		}
		if (new_summary) {
			summary[n_summaries].n_pods = 1;
			summary[n_summaries].n_whales = sightings[i].how_many;
			strcpy(summary[n_summaries].species,sightings[i].species);
			n_summaries++;
		}
		i++;
	}

	i = 0;
	while (i < n_summaries) {
		printf("%d %s pods containing %d whales\n", summary[i].n_pods, summary[i].species, summary[i].n_whales);
		i++;
	}

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
