#ifndef _INSTRUMENTH_
#define _INSTRUMENTH_

// Includes
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include <jack/jack.h>

#include "input.h"
#include "calc.h"
//#include "utility_functions.h"
#include "data.h"

// Structures


// Prototypes
int process(jack_nframes_t nframes, void *arg);
int srate(jack_nframes_t nframes, void *arg);
void error(const char *desc);
void jack_shutdown(void *arg);

// Static Variables
static jack_port_t *output_port;

#endif
