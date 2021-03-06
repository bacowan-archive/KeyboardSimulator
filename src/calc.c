#include "calc.h"

// offset from the start of the buffer
static int offset = 0;

/* Does calculations to convert the frequency array to an array of
 * amplites, which is then sent to the output buffer.
 * @param nframes the number of frames available in all input ports
 * @param output_port the port to send the sound to
 * @param arg arbitrary input from the jack function "process"
 */
void calculate(jack_nframes_t nframes, jack_port_t* output_port, void* arg) {
	
	//sample_t* transBuffer = getTransBuffer();
	sample_t* out = (sample_t*) jack_port_get_buffer(output_port, nframes);
	sample_t* waves = freqToAmp();
	
	for(jack_nframes_t i=0; i<nframes; i++) {
		out[i] = waves[offset];
		offset++;
		if(offset == SAMINCY)
			offset = 0;
	}
	
}

/* Convert the frequency array to an waveform
 * @return the waveform
 */
sample_t* freqToAmp() {
	sample_t** waveForms = getWaveForms();
	sample_t* selectedWaveForm = waveForms[0];
	sample_t combinedWaves[SAMINCY];
	double* freqMultiply = getFrequencies();
	for(int i=0; i<SAMINCY; i++) {
		combinedWaves[i] = 0;
	}
	for(int i=0; i<RES_FRE; i++) {
		// The math to obtain the number of samples taken from the
		// waveforms for each element in the frequency array.
		// y = ax+b
		// HIGH_FRE = a*(RES_FRE-1) + SAMINCY
		// a = (HIGH_FRE-SAMINCY)/(RES_FRE-1)
		int waveSamples = ((HIGH_FRE-SAMINCY)/(RES_FRE-1))*i + SAMINCY;
		int waveDifference = SAMINCY/waveSamples;
		sample_t newWave[waveSamples];
		
		for(int j=0; j < SAMINCY/(waveDifference+1); j++) {
			newWave[j] = selectedWaveForm[j*(waveDifference+1)] * freqMultiply[i];
		}
		
		int disp = 0;
		for(int j=0; j<SAMINCY; j++) {
			combinedWaves[j] += newWave[disp];
			disp++;
			if(disp >= waveSamples)
				disp = 0;
		}
		
	}
	return combinedWaves;
}
