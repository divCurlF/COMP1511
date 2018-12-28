#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SPECIES_NAME_LENGTH 4096

// a struct to represent the date
// a whale pod sighting was made

struct date {
    int year;
    int month;
    int day;
};

// a struct to represent a sighting
// of a pod (group) of whales

struct pod {
    struct pod  *next;
    struct date *when;
    int         how_many;
    char        *species;
};


struct pod *read_sightings_file(char filename[]);
struct pod *read_sighting(FILE *f);
struct date *read_date(FILE *f);
void write_sightings_file(char filename[], struct pod *first_pod);
void write_sighting(FILE *f, struct pod *p);
void write_date(FILE *f, struct date *d);
void free_sightings(struct pod *p);

void merge_day_whales(struct pod *first_pod);
void removeNode(struct pod *curr);
int compareDate(struct date *d1, struct date *d2);


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <old_file> <new_file>\n", argv[0]);
        return 1;
    }

    struct pod *first_pod = read_sightings_file(argv[1]);

    merge_day_whales(first_pod);

    write_sightings_file(argv[2], first_pod);

    free_sightings(first_pod);

    return 0;
}


// merge sightings of the same species on the same day
// into the first sighting of the  species on that day
// The number of whales seen in subsequent sightings is added
// to the number of whales seen in the first sighting.
// The subsequent sightings are deleted from the list
// and all associated memory freed.

//IDEA: at each node, go forward through the list to see if any sighitng on the same day has the same species. If a node exists, we add its how many field to the original search node (so keep this in a pointer called search). Then we detach it:
//
// [x] -> [y] -> [curr] -> [curr->next] -> [curr->next->next] -> ...
// If we are at curr, and curr->next is the node we want: temp = curr->next->next; free(curr->next); curr->next = temp;
void merge_day_whales(struct pod *first_pod) {
	struct pod *search = first_pod;
	int inner = 0;
	int outer = 0;
	//Have to nest these loops as we are searching through the list for each node in front of the search node.
	while (search->next != NULL) {
		outer++;
		struct pod *curr = search;
		while (curr->next != NULL) {
			inner++;

			while (curr->next != NULL &&
			(compareDate(curr->next->when, search->when) == 0) &&
			(strcmp(curr->next->species, search->species) == 0)
			) {
				search->how_many += curr->next->how_many;
				removeNode(curr);
			}
			// If we had to replace the last node in the list, exit this loop.
			if (curr->next == NULL) {
				break;
			}


			curr = curr->next;
		}
		inner = 0;
		search = search->next;
	}
}

void removeNode(struct pod *curr) {
	if (curr->next->next != NULL) {
		struct pod *temp = curr->next;
		curr->next = temp->next;
		free(temp->species);
		free(temp->when);
		free(temp);
	} else {
		free(curr->next->species);
		free(curr->next->when);
		free(curr->next);
		curr->next = NULL;
	}
}

int compareDate(struct date *d1, struct date *d2) {
	if (d1->year < d2->year) {
		return 1;
	} else if (d1->year > d2->year){
		return -1;
	} else {
		if (d1->month < d2->month) {
			return 1;
		} else if (d1->month > d2->month) {
			return -1;
		} else {
			if (d1->day < d2->day) {
				return 1;
			} else if (d1->day > d2->day) {
				return -1;
			} else {
				return 0;
			}
		}
	}
}


//
// DO NOT CHANGE THE FUNCTIONS BELOW HERE
//

// return linked list of sightings read from filename
// exit called if there is an error

struct pod *read_sightings_file(char filename[]) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr,"error: file '%s' can not open\n", filename);
        exit(1);
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


// read a whale sighting (date, number of whales, whale species)
// return a pointer to a malloced struct containing these details
// return NULL if a sighting can not be read

struct pod *read_sighting(FILE *f) {
    struct pod *p = malloc(sizeof (struct pod));
    if (p == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }

    p->next = NULL;

    p->when = read_date(f);
    if (p->when == NULL) {
        free(p);
        return NULL;
    }

    int n_scanned = fscanf(f, "%d", &(p->how_many));
    if (n_scanned != 1) {
        free(p);
        return NULL;
    }

    fgetc(f);
    char species_buffer[MAX_SPECIES_NAME_LENGTH];
    if (fgets(species_buffer, MAX_SPECIES_NAME_LENGTH, f) == NULL) {
        free(p);
        return NULL;
    }
   // finish string at '\n' if there is one
    char *newline_ptr = strchr(species_buffer, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    // also finish string at '\r' if there is one - files from Windows  will
    newline_ptr = strchr(species_buffer, '\r');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    // malloc a char array long enough to hold species name
    // and copy species to it
    p->species = malloc(strlen(species_buffer) + 1);
    if (p->species == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    strcpy(p->species, species_buffer);

    return p;
}


// read a date in day/month/year format from stream f
// return a pointer to a malloced date struct containing them
//  return NULL if a date can not be read

struct date *read_date(FILE *f) {
    struct date *d = malloc(sizeof (struct date));
    if (d == NULL) {
        fprintf(stderr, "out of memory\n");
        exit(1);
    }
    int n_scanned = fscanf(f, "%d/%d/%d", &(d->day), &(d->month), &(d->year));
    if (n_scanned != 3) {
        free(d);
        return NULL;
    }
    return d;
}


// print linked list of sightings to  filename

void write_sightings_file(char filename[], struct pod *first_pod) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr,"error: file '%s' can not open\n", filename);
        exit(1);
    }

    struct pod *p = first_pod;
    while (p != NULL) {
        write_sighting(f, p);
        p = p->next;
    }
    fclose(f);
}


// print pod details to stream f

void write_sighting(FILE *f, struct pod *p) {
    write_date(f, p->when);
    fprintf(f, " %2d %s\n", p->how_many, p->species);
}


// print date to  stream f

void write_date(FILE *f, struct date *d) {
    fprintf(f, "%02d/%02d/%02d", d->day, d->month, d->year);
}

// free the list of sightings

void free_sightings(struct pod *p) {
    struct pod *curr = p;
    while (curr != NULL) {
        struct pod *next = curr->next;
        free(curr->species);
        free(curr->when);
        free(curr);
        curr = next;
    }
}
