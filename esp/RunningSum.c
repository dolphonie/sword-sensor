int WINDOW_SIZE = 25

struct RunningAvg{
	float signal[WINDOW_SIZE];
	int current_index;
	
	void RunningAvg() {
		current_index = 0;
	}

	float Average(){ # Use to get current value of smoothed signal
		float sum = 0;
		for(int i = 0;  i < WINDOW_SIZE; i++) {
			sum += vals[i];
		}
		return sum / WINDOW_SIZE;
	}

	void input_sample(float sample) { #Call this function on samples as you get them
		current_index = (current_index + 1) % WINDOW_SIZE;
		samples[current_index] = sample;
	}
}
