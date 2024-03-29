#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>

using namespace std;
struct process{
	char pid[5];
	int arrival;
	int duration;
	int start_time;
};

int main() {
	int temp;
	int index = 0;
	int process_count = 0;
	//struct process arr[process_count];
	struct process swapp;
	FILE* d;
	int time = 0;
	//------------------------------

	d = fopen("C:\\Users\\amn_n\\Documents\\refrence folders\\processes.txt", "r");
	while (EOF != (temp = getc(d)))
		if ('\n' == temp)
			process_count+=1;
	process_count += 1;
	fclose(d);


	process* arr = (struct process*)malloc(sizeof(struct process) * process_count);
	d = fopen("C:\\Users\\amn_n\\Documents\\refrence folders\\processes.txt", "r");
	for (int i = 0; i < process_count; i++) {
		fscanf(d, "%s %d %d", arr[i].pid, &arr[i].duration, &arr[i].arrival);
	}

	//sorting the proc array with selection sort <of course there were better options but this is os course not ds>
	for (int i = 0; i < process_count; i++) {
		int temp = arr[i].arrival;
		index = i;
		for (int j = i; j < process_count; j++) {
			if (temp > arr[j].arrival) {
				index = j;
				temp = arr[j].arrival;
			}
		}
		swapp = arr[i];
		arr[i] = arr[index];
		arr[index] = swapp;
	}
	for (int i = 0; i < process_count; i++) {
		arr[i].start_time = time;
		time += arr[i].duration;
	}
	temp = 0;
	time = 0;
	for (int i = 0; i < process_count; i++) {
		time += (arr[i].start_time - arr[i].arrival);
		temp += arr[i].duration;
	}
	temp += time;
	free(arr);
	printf("%.2f, %.2f", (float)time / process_count, (float)temp / process_count);


	return 0;
}

