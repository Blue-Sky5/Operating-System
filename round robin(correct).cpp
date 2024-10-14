#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <queue>

using namespace std;
struct process {
	char pid[5];
	int arrival;
	int duration;
	int start_time;
	int end_time;
};

int main() {
	int temp;
	int temp1;
	int index = 0;
	int process_count = 0;
	int quantum = 2;
	int time = 0;
	int index_fin = 0;
	//struct process arr[process_count];
	struct process swapp;
	FILE* d;
	queue<process> process_queue;
	//------------------------------

	d = fopen("input.txt", "r");
	while (EOF != (temp = getc(d)))
		if ('\n' == temp)
			process_count += 1;
	process_count += 1;
	fclose(d);


	process* arr = (struct process*)malloc(sizeof(struct process) * process_count);
	d = fopen("input2.txt", "r");
	for (int i = 0; i < process_count; i++) {
		fscanf(d, "%s %d %d", arr[i].pid, &arr[i].duration, &arr[i].arrival);
		arr[i].start_time = -1;
	}

	//sorting the proc array with selection sort <of course there were better options but this is os class not ds>
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

	index = 0;
	time = 0;
	index_fin = 0;

	bool hold = false;
	while (index < process_count || !process_queue.empty()) {
		if (!process_queue.empty()) {
			if (process_queue.front().start_time == -1) {
				process_queue.front().start_time = time;
			}
			if (process_queue.front().duration < quantum) {
				time += process_queue.front().duration;
				process_queue.front().duration = 0;
				process_queue.front().end_time = time;
				arr[index_fin] = process_queue.front();
				index_fin += 1;
				process_queue.pop();
			}
			else if (process_queue.front().duration == quantum) {
				time += quantum;
				process_queue.front().duration -= quantum;
				process_queue.front().end_time = time;
				arr[index_fin] = process_queue.front();
				index_fin += 1;
				process_queue.pop();
			}
			else {
				hold = true;
				time += quantum;
				process_queue.front().duration -= quantum;
			}
		}
		if (index < process_count) {
			while (index < process_count && arr[index].arrival <= time) {
				process_queue.push(arr[index]);
				index += 1;
			}
		}
		if (hold) {
			process_queue.push(process_queue.front());
			process_queue.pop();
			hold = false;
		}
	}

	temp = 0;
	temp1 = 0;
	for (int i = 0; i < process_count; i++) {
		temp += arr[i].start_time - arr[i].arrival;
		temp1 += arr[i].end_time - arr[i].arrival;
	}
	/*
	for (int i = 0; i < process_count; i++) {
		printf("process name %s         arrival %d        start time%d     end time %d\n", arr[i].pid, arr[i].arrival, arr[i].start_time, arr[i].end_time);
	}
	*/
	free(arr);
	printf("%.2f, %.2f", (float)temp / process_count, (float)temp1 / process_count);

	return 0;
}

