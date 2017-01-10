#include <Bela.h>
#include <cmath>
#include "metronome.h"
#define BUFFER_LENGTH 88200

unsigned int index=0;

float content[BUFFER_LENGTH];
unsigned int taps[2]={0,BUFFER_LENGTH/2};

bool setup(BelaContext *context, void *userData)
{
	printf("setting things up!\n");
	float sample_rate=context->analogSampleRate;
    if(sample_rate!=44100.0f)
    {
       printf("  error: we are expecting sample rate of 44100, check settings in Bela IDE!\n");
       return false;  
    }

	for(unsigned int i=0;i<BUFFER_LENGTH;i++) //clear everything
    {
       content[i]=0.0f; 
    }
    
    metronomes[0]=new single_metronome(BUFFER_LENGTH);
    metronomes[1]=new single_metronome(BUFFER_LENGTH);
    
    metronomes[0]->add_click(8,1);
    metronomes[0]->add_click(2,2);

	return true;
}

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) 
	{
	    
       analogWrite(context,n,0,metronomes[0]->process(index));
	   analogWrite(context,n,1,metronomes[1]->process(index));

	   analogWrite(context,n,2,content[(index+BUFFER_LENGTH-taps[0])%BUFFER_LENGTH]);
	   analogWrite(context,n,3,content[(index+BUFFER_LENGTH-taps[1])%BUFFER_LENGTH]);
		
	   content[(index+BUFFER_LENGTH-6)%BUFFER_LENGTH] = analogRead(context, n, 0); //store incoming audio (accounting for latency)
		
	   index=(index+1)%BUFFER_LENGTH;
    }
}  

void cleanup(BelaContext *context, void *userData)
{

}