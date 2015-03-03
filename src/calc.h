#ifndef _CALCH_
#define _CALCH_

#include <jack/jack.h>
#include "data.h"
typedef jack_default_audio_sample_t sample_t;

void calculate(jack_nframes_t nframes, jack_port_t* output_port, void* arg);
sample_t* freqToAmp();

#endif
