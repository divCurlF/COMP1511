//COMP1511 Zac Sanchez z5194994
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0

#define FALSE 0
#define TRUE (!FALSE)
#define MA_STUDENTS 100

struct student {
	char id[10];
	double labs[5];
	double assigns[2];
	double final_exam;
	char name[50];
};

int read_record(FILE *f, struct student *sp);
int read_data_file(char filename[], struct student sa[], int len);
void print_names(struct student sa[], int no_students);

//INPUT FORMAT:
//	zID [string], lab0 [double] , lab1, lab2, lab3, lab4, ass0 [double], ass1, ass2, final_exam [double], name [string]
int main(int argc, char *argv[]) {
		if (argc != 2) {
				fprintf(stderr, "Usage %s <file>\n", argv[0]);
				return 1;
		}

		struct student student_array[MA_STUDENTS];
		int no_students = read_data_file(argv[1], student_array, MA_STUDENTS);
		print_names(student_array, no_students);

		printf("no_students = %d\n", no_students);
		return EXIT_SUCCESS;
}

// Read in one data line from a file.
// THIS HAS to take a struct student pointer so that we can input data line by line. the function will be called per array index - this is a pointer!

int read_record(FILE *f, struct student *sp) {
		//Read a string, go into sp pointer, replace id.
		if (fscanf(f, "%s,", sp->id) != 1) {
			return 0;
		}
		int i = 0;
		while ( i < 5) {
			if (fscanf(f, "%lf,", &sp->labs[i]) != 1) {
					return 0;
			}
			i++;
		}
		i = 0;
		while ( i < 2) {
			if (fscanf(f, "%lf,", &sp->assigns[i]) != 1) {
				return 0;
			}
			i++;
		}
		if (fscanf(f, "%lf,", &sp->final_exam) != 1) {
			return 0;
		}

		//Read one space
		fgetc(f);
		if (fgets(sp->name, 49, f) == NULL) {
			return 0;
		}
		// looks for char '\n' in the string, returns pointer to char.
		char *newline_ptr = strchr(sp->name, '\n');

		if (newline_ptr != NULL) {
				*newline_ptr = '\0';
		}

		// windows carriage return.
		newline_ptr = strchr(sp->name, '\r');
		if (newline_ptr != NULL) {
			*newline_ptr = '\0';
		}
		return 1;
}

// Read in the data to our student array

int read_data_file(char filename[], struct student sa[], int len) {

	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		fprintf(stderr, "Read Error %s \n", filename);
		exit(1);
	}

	int i = 0;

	// Always have to put a pointer to the struct because we want to actually edit the data inside the structure.
	while ( (read_record(f, &sa[i]) == 1) && (i < len)) {
		i++;
	}

	fclose(f);
	return i;
}

void print_names(struct student sa[], int no_students) {
	int i = 0;
	while (i < no_students) {
		printf("%s\n", sa[i].name);
		i++;
	}
}
