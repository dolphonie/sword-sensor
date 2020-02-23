#include <stdio.h>

#define WINDOW_SIZE 25

static float samples[WINDOW_SIZE];

int running_avg_current_index = 0;

float Average(){ // Use to get current value of smoothed signal
	float sum = 0;
	for(int i = 0;  i < WINDOW_SIZE; i++) {
		sum += samples[i];
	}
	return sum / WINDOW_SIZE;
}

void push_sample(float sample) { // Call this function on samples as you get them
	running_avg_current_index = (running_avg_current_index + 1) % WINDOW_SIZE;
	samples[running_avg_current_index] = sample;
}
