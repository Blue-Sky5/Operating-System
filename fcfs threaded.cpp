#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <queue>
#include <thread>


using namespace std;

int Mytime = 0;
bool has_finished = false;
int waiting = 0;
int all_durations = 0;
int process_count = 0;

struct process {
	int arrival;
	int duration;
	int start_time;
};

queue<process> holder;

void user_input() {
	process temp;
	int temp1;
	int temp2;
	while (true) {
		scanf("%d %d", &temp1 , &temp2);
		if (temp1 == -1) {
			has_finished = true;
			break;
		}
		else{
			process_count += 1;
			temp.arrival = temp2;
			temp.duration = temp1;
			all_durations += temp1;
			holder.push(temp);
		}
	}
	//return NULL;
}

void execution_method() {
	while (!has_finished) {
		while (!holder.empty()) {
			holder.front().start_time = Mytime;
			Mytime = Mytime + holder.front().duration;
			//printf("%d --- %d \n", holder.front().start_time, holder.front().arrival);
			waiting += (holder.front().start_time - holder.front().arrival);
			holder.pop();
		}
	}
	//return NULL;
}

int main() {
	thread input(user_input);
	thread exec(execution_method);
	input.join();
	exec.join();
	//printf("%d\n", waiting);
	printf("%.2f, %.2f", (float)waiting / process_count, (float)(waiting+all_durations) / process_count);
	return 0;
}