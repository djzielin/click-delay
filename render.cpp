#include <Bela.h>
#include <cmath>
#include "metronome.h"
#include "canon_delay.h"

//#define BUFFER_LENGTH 132300
#define BUFFER_LENGTH 88200

unsigned int index=0;

float content[BUFFER_LENGTH];
unsigned int taps[4]={44100,88200,33075,66150};

canon_delay *cd;

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
    
    //metronomes[1]->add_click(15,1);
    //metronomes[1]->add_click(5,2);
    
    metronomes[0]->add_click(4,2);
    //metronomes[0]->add_click(1,1);
    
    //metronomes[1]->add_click(4,1);
    metronomes[1]->add_click(4,2);
     
    
    //cd=new canon_delay(BUFFER_LENGTH);

	return true;
}

int counter=0;

void render(BelaContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) 
	{
	   analogWrite(context,n,0,metronomes[0]->process(index));
	   analogWrite(context,n,1,metronomes[1]->process(index));
	   
	   //for canon delay
	   //analogWrite(context,n,2,cd->process(index,analogRead(context, n, 0)));

       float vol1=analogRead(context, n, 2);
       float vol2=analogRead(context, n, 3);
       
       float tap0=content[(index+BUFFER_LENGTH-taps[0])%BUFFER_LENGTH]*vol1;
       float tap1=content[(index+BUFFER_LENGTH-taps[1])%BUFFER_LENGTH]*vol1;
       float tap2=content[(index+BUFFER_LENGTH-taps[2])%BUFFER_LENGTH]*vol2;
       float tap3=content[(index+BUFFER_LENGTH-taps[3])%BUFFER_LENGTH]*vol2;

	   analogWrite(context,n,2,tap0+tap2);
	   analogWrite(context,n,3,tap1+tap3);
		
	   content[(index+BUFFER_LENGTH-6)%BUFFER_LENGTH] = analogRead(context, n, 0); //store incoming audio (accounting for latency)
		
	   index=(index+1)%BUFFER_LENGTH;
    }
}  

void cleanup(BelaContext *context, void *userData)
{

}