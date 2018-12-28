//COMP1511 Zac Sanchez z5194994
//
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPECIES_NAME_LENGTH 4096
#define EXIT_SUCCESS 0
#define FALSE 0
#define TRUE (!FALSE)

struct date {
	int year;
	int month;
	int day;
};

struct pod {
	struct pod  *next;
	struct date *when;
	int         how_many;
	char        *species;
};

//Print details of sightings by p to stream f
void write_sighting(FILE *f, struct pod *p);

//Opens file give as argument and calls write_sighting to print details
// of all the pod struct in the linked list it is given.
void write_sightings_file(char filename[], struct pod *first_pod);

//prints details of a date struct to stream f.
void write_date(FILE *f, struct date *d);
//-----------------------------------------------------------------------

//mallocs pod struct and asigns values to fields, read from a line of stream given as argument.
struct pod *read_sighting(FILE *stream);

//opens file and calls read)sighting to create pod structs.
struct pod *read_sightings_file(char filename[]);

//Mallocs date struct, assigns values to fields from stream f.
struct date *read_date(FILE *f);

//-----------------------------------------------------------------------

void print_sightings(struct pod *p);

int main(int argc, char *argv[]) {

	if (argc != 2) {
		fprintf(stderr, "Usage <./linked_sightings> <input_file>");
		return 1;
	}

	struct pod *list = read_sightings_file(argv[1]);
	print_sightings(list);

	return EXIT_SUCCESS;
}

void print_sightings(struct pod *list) {
	if (list == NULL) {
		return;
	}

	struct pod *curr = list;
	while (curr->next != NULL) {
		printf("%d/%d/%d %d %s\n", curr->next->when->day,
				curr->next->when->month,
				curr->next->when->year,
				curr->next->how_many,
				curr->next->species
		);
		curr = curr->next;
	}
}

struct pod *read_sightings_file(char filename[]) {
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		fprintf(stderr, "Error reading file %s\n", filename);
		return NULL;
	}

        struct pod *first_sighting = NULL;
        struct pod *last_sighting = NULL;
        struct pod *sighting = read_sighting(f);

        while (sighting != NULL) {
            if (first_sighting == NULL) {
                first_sighting = sighting;
                first_sighting->next = NULL;
            } else {
                last_sighting->next = sighting;
            }
            last_sighting = sighting;
            sighting = read_sighting(f);
        }
	fclose(f);
        return first_sighting;
}
struct pod *read_sighting(FILE *stream) {

	struct pod *p = malloc(sizeof(struct pod));
	if (p == NULL) {
		fprintf(stderr, "Memory error.\n");
		exit(1);
	}

	p->when = read_date(stream);

	if (p->when == NULL) {
		free(p);
		return NULL;
	}

	if (fscanf(stream, "%d", &p->how_many) != 1) {
		fprintf(stderr, "Error reading number of whales.");
		free(p);
		return NULL;
	}

	fgetc(stream);

	// This does not work... why?
	char species_buffer[MAX_SPECIES_NAME_LENGTH];
       	if (fgets(species_buffer, MAX_SPECIES_NAME_LENGTH, stream) == NULL) {
		fprintf(stderr, "Error reading species name");
		free(p);
		return NULL;
	}
	char *newline_ptr = strchr(species_buffer, '\n');
	if (newline_ptr != NULL) {
		*newline_ptr = '\0';
	}

	newline_ptr = strchr(species_buffer, '\r');
	if (newline_ptr != NULL) {
		*newline_ptr = '\0';
	}

	p->species = malloc(strlen(species_buffer) + 1);

	if (p->species == NULL) {
		fprintf(stderr, "Memory Error.\n");
		free(p);
		exit(1);
	}
	strcpy(p->species, species_buffer);
	return p;
}

struct date *read_date(FILE *f) {
	struct date *d = malloc(sizeof(struct date));

	if (d == NULL) {
		fprintf(stderr, "Memory error.\n");
		exit(1);
	}
	if (fscanf(f, "%d/%d/%d", &d->day, &d->month, &d->year) != 3) {
		free(d);
		return NULL;
	}
	return d;

}

void write_sightings_file(char filename[], struct pod *first_pod) {
	FILE *f = fopen(filename, "w");

	if (f == NULL) {
		fprintf(stderr, "Could not open %s for writing.\n", filename);
		return;
	}
	if (first_pod == NULL) {
		fprintf(stderr, "bad reference to head of list.");
		return;
	}
	struct pod *pod_curr = first_pod;
	write_sighting(f, pod_curr);

	while (pod_curr->next != NULL) {
		write_sighting(f, pod_curr->next);
		pod_curr = pod_curr->next;
	}
}

void write_sighting(FILE *f, struct pod *p) {
	assert(f != NULL && p != NULL);
	write_date(f, p->when);
	fprintf(f, " %d ", p->how_many);
	fprintf(f, "%s\n", p->species);
}

void write_date(FILE *f, struct date *d) {
	assert(f != NULL && d != NULL);
	fprintf(f, "%d/%d/%d", d->day, d->month, d->year);
}



