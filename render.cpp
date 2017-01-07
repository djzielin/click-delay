#include <Bela.h>
#include <cmath>

float gFrequency = 440.0;
float gPhase;
float gInverseSampleRate;

bool setup(BelaContext *context, void *userData)
{
	printf("setup happening");
	
	gInverseSampleRate = 1.0 / context->audioSampleRate;
	gPhase = 0.0;

	return true;
}

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) 
	{
		//for(unsigned int channel = 0; channel < context->audioOutChannels; channel++) 
		for(unsigned int channel = 0; channel < 1; channel++) 
		{
			// Read the audio input and half the amplitude
			float input = analogRead(context, n, channel);
			//if(input>0.4) printf("data");
			analogWrite(context, n, channel, input);
		}
    }
}  

void cleanup(BelaContext *context, void *userData)
{

}