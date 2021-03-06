#include "instrument.h"

/* What happens in every frame. Amplitude is sent to the output buffer.
 * Input parameter are taken care of by Jack.
 * @param nframes the number of frames available in all input ports
 * @param arg arbitrary input from the jack function "process"
 */
int process(jack_nframes_t nframes, void* arg){
	calculate(nframes, output_port, arg);
	return 0;
}

/* Called whenever the sample rate changes. Updates the sample rate here and
 * sends a notification to the console.
 * @param nframes the number of frames available in all input ports
 * @param arg arbitrary input from the jack function "process"
 */
int srate(jack_nframes_t nframes, void* arg){
	printw("the sample rate is now %lu/sec\n", nframes);
	sr = nframes;
	return 0;
}

/* Called when a Jack error occurs. Prints an error to the console.
 * @param desc a description of the error
 */
void error(const char* desc){
	fprintf(stderr, "JACK error: %s\n", desc);
}

/* Called when jack shuts down. Frees memory allocation, and exits program.
 * @param arg arbitrary input from the jack function "process"
 */
void jack_shutdown(void* arg){
	freeWaveforms();
	exit(1);
}

/*
 * Main function. Sets up ports etc. Contains main loop to look for input.
 * @param argc number of input args given
 * @param argv an array of the input args
 *	0 - an identifying name for the process that jack will create
 */
int main(int argc, char* argv[]){
	
	// Setup user input
	set_curses();

	// Setup
	jack_client_t* client;
	const char** ports;
	
	// bad input args
	if(argc < 2){
		fprintf(stderr, "usage: jack_simple_client <name>\n");
		unset_curses();
		return 1;
	}
	
	jack_set_error_function(error);
	
	if ((client = jack_client_new(argv[1])) == 0){
		unset_curses();
		fprintf(stderr, "jack server not running?\n");
		return 1;
	}
	
	jack_set_process_callback(client, process, 0);
	
	jack_set_sample_rate_callback(client, srate, 0);
	
	jack_on_shutdown(client, jack_shutdown, 0);
	
	printw("engine sample rate: %lu\n", jack_get_sample_rate(client));

	setSr( jack_get_sample_rate(client) );
	
	output_port = jack_port_register(client, "output", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
	
	// Create the input buffer
	setInputBuffer( malloc(SAMINCY * sizeof(sample_t)) );
	
	// Create the transition buffer
	setTransBuffer( malloc(SAMINCY * sizeof(sample_t)) );

	// Put the waveforms in memory
	setWaveForms( malloc(WAVE_TYPE_COUNT * SAMINCY * sizeof(sample_t)) );
	for(int i = 0; i < WAVE_TYPE_COUNT; i++)
		storeWaves(i);

	// Activate the Jack client	
	if(jack_activate (client)){
		fprintf(stderr, "cannot activate client\n");
		return 1;
	}

	/* connect the ports*/
	if ((ports = jack_get_ports (client, NULL, NULL, JackPortIsPhysical|JackPortIsInput)) == NULL) {
		fprintf(stderr, "Cannot find any physical playback ports\n");
		exit(1);
	}

	int i=0;
	while(ports[i]!=NULL){
		if (jack_connect (client, jack_port_name (output_port), ports[i])) {
			fprintf(stderr, "cannot connect output ports\n");
		}
		i++;
	}

	// Cleanup
	free (ports);            
//	sleep(1);
	int c = -1;
	while(c != ESC)
	{
		c = getch();
		double* fre = getFrequencies();
		key_hit(c, RES_FRE);
		for(int i=0; i < RES_FRE; i++)
		{
			char buff[5];
			sprintf(buff, "%f    ", fre[i]);
			print_string(i+10, 2, buff);
		}
		
	}
	printf("\n");
	unset_curses();
	jack_client_close(client);
//	free(waveForms[0]);
	
	exit(0);
}
