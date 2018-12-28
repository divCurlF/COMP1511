// Find the average of the values in a given array.
// By ... (z0000000)
// Written on 2018-0?-??
// Tutor (dayHH-lab)

// You need to implement this function

// Calculates the average of all the values in a given array,
// and returns the average value.
double arrayAverage(int a[], int size) {
    int i = 0;
    double sum = 0;
    while (i < size) {
	sum += a[i];
	i++;
    }
    return sum/size;
}
