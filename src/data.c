#include "data.h"

// Getters
double* getFrequencies() { return frequencies; }
jack_nframes_t getSr() { return sr; }
sample_t* getInputBuffer() { return inputBuffer; }
sample_t* getTransBuffer() { return transBuffer; }
sample_t** getWaveForms() { return waveForms; }

// Setters
void setFrequencies( double newFrequencies[] ) {
	for(int i = 0; i<RES_FRE; i++) {
		frequencies[i] = newFrequencies[i];
	}
}

void setSr( jack_nframes_t newSr ) {
	sr = newSr;
}

void setInputBuffer( sample_t* newInputBuffer ) {
	inputBuffer = newInputBuffer;
}

void setTransBuffer( sample_t* newTransBuffer ) {
	transBuffer = newTransBuffer;
}

void setWaveForms( sample_t** newWaveForms ) {
	waveForms = newWaveForms;
}

void setFrequency( double frequency, int index ) {
	frequencies[index] = frequency;
}

void increaseFrequency( double amount, int index ) {
	frequencies[index] += amount;
}

void storeWaves(int num){
	sample_t* wave = malloc(SAMINCY * sizeof(sample_t));
	for(int i=0; i<SAMINCY; i++) {
		wave[i] = sin(i * 2*PI/SAMINCY);
		
	}
	waveForms[num] = wave;
}

void freeWaveforms(){
	free(waveForms[0]);
	free(inputBuffer);
	free(transBuffer);
}
