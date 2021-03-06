#ifndef _DATAH_
#define _DATAH_

#include <math.h>
#include <jack/jack.h>
#include <stdlib.h>
#include <stdio.h>

// Definitions

typedef jack_default_audio_sample_t sample_t;

#define PI 3.14

// Number of samples passed to the output buffer per second
#define SAMPERSEC 100

// Number of different shapes of default waveforms stored
// TODO: change to a config option
#define WAVE_TYPE_COUNT 1

// Number of different frequencies in the frequency array
// TODO: change to a config option
#define RES_FRE 30

// Number of samples in a cycle.
#define SAMINCY 200

// The frequency of the highest frequency in the array, in terms of number of
// selections taken from the waveform.
// Note that the frequency of the lowest frequency in the array just includes all
// entries in the waveform, so it is equal to SAMPERSEC
#define HIGH_FRE 4


// sample rate
static jack_nframes_t sr;

// Number of samples in one cycle
// jack_nframes_t samincy;

// The input buffer
static sample_t* inputBuffer;

// The buffer in transition between the input and output buffer
static sample_t* transBuffer;

// An array of waveforms
static sample_t** waveForms;

// The frequency array
static double frequencies[RES_FRE];

// Getters
double* getFrequencies();
jack_nframes_t getSr();
jack_nframes_t getSamincy();
sample_t* getInputBuffer();
sample_t* getTransBuffer();
sample_t** getWaveForms();
//int getOffset() { return offset; }

// Setters
void setFrequencies( double newFrequencies[] );
void setFrequency( double frequency, int index );
void increaseFrequency( double amount, int index );
void setSr( jack_nframes_t newSr );
void setInputBuffer( sample_t* newInputBuffer );
void setTransBuffer( sample_t* newTransBuffer ) ;
void setWaveForms( sample_t** newWaveForms );

void storeWaves(int num);

void freeWaveforms();

#endif
