#include <Bela.h>
#include <cmath>

#define BUFFER_LENGTH 88200

unsigned int index=0;
float metronome[BUFFER_LENGTH];

float content[BUFFER_LENGTH];
unsigned int taps[2]={0,BUFFER_LENGTH/2};

bool i1_playing=false;
unsigned int i1_index=0;
float impulse1[32]={1,0,0,0,0,1,0,0,
                    1,0,1,0,1,1,0,0,
                    0,1,0,0,0,1,0,1,
                    0,0,1,0,1,0,1,0};

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
       metronome[i]=0.0f;
       content[i]=0.0f; 
    }
    
    for(unsigned int i=0;i<8;i++) //setup 8 16th notes
    {
       metronome[i*(BUFFER_LENGTH/8)]=1;	
    }
    
	return true;
}

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) 
	{
		if(metronome[index]==1)
		{
			i1_index=0;
			i1_playing=true;
		}
		
	    if(i1_playing)
		{
		   analogWrite(context,n,0,impulse1[i1_index]);
		   i1_index++;
		   if(i1_index>=32)
		     i1_playing=false;
		}
		
		
		analogWrite(context,n,2,content[(index+BUFFER_LENGTH-taps[0])%BUFFER_LENGTH]);
		analogWrite(context,n,3,content[(index+BUFFER_LENGTH-taps[1])%BUFFER_LENGTH]);
		
		content[index] = analogRead(context, n, 0);
		
		index=(index+1)%BUFFER_LENGTH;
    }
}  

void cleanup(BelaContext *context, void *userData)
{

}