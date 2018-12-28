#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define MAX_SPECIES_NAME_LENGTH  128
#define MAX_SIGHTINGS           10000
#define MAX_WHALE_SPECIES         256

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
    struct date when;
    int         how_many;
    char        species[MAX_SPECIES_NAME_LENGTH];
};


int read_sightings_file(char filename[], int len, struct pod sightings[len]);
int read_sighting(FILE *f, struct pod *p);
int read_date(FILE *f, struct date *d);

void write_sightings_file(char filename[], int n_sightings, struct pod sightings[n_sightings]);
void write_sighting(FILE *f, struct pod *p);
void write_date(FILE *f, struct date *d);

void sanitize_whales(char species_names_file[], int n_sightings, struct pod sightings[n_sightings]);
int match_sighting(char sighting_name[MAX_SPECIES_NAME_LENGTH], int n,
	char correct_names[MAX_WHALE_SPECIES][MAX_SPECIES_NAME_LENGTH]);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <species_names_file> <old_file> <new_file>\n", argv[0]);
        return 1;
    }

    char *species_names_file = argv[1];
    char *old_file = argv[2];
    char *new_file = argv[3];

    struct pod whale_sightings[MAX_SIGHTINGS];
    int n_sightings = read_sightings_file(old_file, MAX_SIGHTINGS, whale_sightings);

    if (n_sightings < 1) {
        return 1;
    }

    sanitize_whales(species_names_file, n_sightings, whale_sightings);

    write_sightings_file(new_file, n_sightings, whale_sightings);

    return 0;
}


//
// correct whales names removing extra characters and correcting case
//

void sanitize_whales(char species_names_file[], int n_sightings, struct pod sightings[n_sightings]) {
    char correct_names[MAX_WHALE_SPECIES][MAX_SPECIES_NAME_LENGTH];
    
    FILE *f = fopen(species_names_file, "r");
    
    if (f == NULL) {
    	fprintf(stderr, "Error reading file %s.", species_names_file);
    }
    
    int num_species = 0;
    
    while (fgets(correct_names[num_species], MAX_SPECIES_NAME_LENGTH, f) != NULL) {
    	num_species++;
    }
    
    char *c;
    for (int i = 0; i < num_species; i++) {
    	c = strchr(correct_names[i], '\n');
    	c[0] = '\0';
    	printf("%s\n", correct_names[i]);
    }
    
    fclose(f);
    
    char sighting_name[MAX_SPECIES_NAME_LENGTH];
    
	
    int i = 0;
    while (i < n_sightings) {
    	
    	int sight_curr = 0;
    	int c = 0;
    	
    	while (sightings[i].species[c] != '\0') {
    		if (isalpha(sightings[i].species[c])) {
    		
    			sighting_name[sight_curr] = tolower(sightings[i].species[c]);
    			sight_curr++;
    		}
    		c++;
    	}
    	sighting_name[sight_curr] = '\0';

    	int index = match_sighting(sighting_name, num_species, correct_names);
    	
    	if (index == -1) {
    		fprintf(stderr, "Error matching sighting");
    	}
    	strcpy(sightings[i].species, correct_names[index]);
    	
    	i++;
    }
}

int match_sighting(char sighting_name[MAX_SPECIES_NAME_LENGTH], int n,
	char correct_names[MAX_WHALE_SPECIES][MAX_SPECIES_NAME_LENGTH]) 
{
	int i = 0;
	
	char clean_name[MAX_SPECIES_NAME_LENGTH];
	int clean_curr = 0;
	
	while (i < n) {
		int c = 0;
		clean_curr = 0;
		
		while (correct_names[i][c] != '\0') {
			if (isalpha(correct_names[i][c])) {
				clean_name[clean_curr] = tolower(correct_names[i][c]);
				clean_curr++;
			}
			c++;
		}
		
		clean_name[clean_curr] = '\0';
		
		if (strcmp(clean_name, sighting_name) == 0) {
			return i;
		}
		
		i++;
	}
	
	return -1;
}


//
// DO NOT CHANGE THE FUNCTION BELOW HERE
//

// return number of sightings read from filename
// -1 is returned if there is an error

int read_sightings_file(char filename[], int len, struct pod sightings[len]) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr,"error: file '%s' can not open\n", filename);
        return -1;
    }

    int n_sightings = 0;
    while (read_sighting(f, &sightings[n_sightings]) == 1 && n_sightings < len) {
        n_sightings = n_sightings + 1;
    }
    fclose(f);

    return n_sightings;
}


// return 1 if a sighting can be read, 0 otherwise

int read_sighting(FILE *f, struct pod *s) {
    if (read_date(f, &(s->when)) != 1) {
        return 0;
    }
    if (fscanf(f, "%d", &(s->how_many)) != 1) {
        return 0;
    }
    fgetc(f);
    if (fgets(s->species, MAX_SPECIES_NAME_LENGTH, f) == NULL) {
        return 0;
    }

    // finish string at '\n' if there is one
    char *newline_ptr = strchr(s->species, '\n');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }

    // also finish string at '\r' if there is one - files from Windows  will
    newline_ptr = strchr(s->species, '\r');
    if (newline_ptr != NULL) {
        *newline_ptr = '\0';
    }
    return 1;
}

// return 1 if a date can be read, 0 otherwise

int read_date(FILE *f, struct date *d) {
    int n_scanned = fscanf(f, "%d/%d/%d", &(d->year), &(d->month), &(d->day));
    return n_scanned == 3;
}


// print array of sightings to filename

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
