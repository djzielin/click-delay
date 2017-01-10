/***** metronome.h *****/

float impulse[2][32]={{1,0,0,0,0,1,0,0,1,0,1,0,1,1,0,0,0,1,0,0,0,1,0,1,0,0,1,0,1,0,1,0},
                      {1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0}};

class single_metronome
{
public: 
	single_metronome(unsigned int _b_length)
    {
       b_length=_b_length;  	
       
       buffer=new float[b_length];
       
       for(unsigned int i=0;i<b_length;i++) //clear everything
       {
          buffer[i]=0.0f;
       }
    }	

    void add_click(unsigned int how_many_clicks, int which_impulse)
    {
       for(unsigned int i=0;i<how_many_clicks;i++) 
       {
          buffer[i*(b_length/how_many_clicks)]=which_impulse;	
       }	
    }
    
    float process(int index)
    {
    	float retval=0.0f;
    	
     	if(buffer[index]!=0)
		{
		    impulse_index=0;
		    which_impulse=buffer[index]-1;
		    is_playing=true;
		}
		
	    if(is_playing)
		{
		   retval=impulse[which_impulse][impulse_index];
		   impulse_index++;
		   if(impulse_index>=32)
		     is_playing=false;
		}
	
	    return retval;
    }
    
	unsigned int b_length;
	float *buffer;
	bool is_playing;
	unsigned int impulse_index;
	unsigned int which_impulse;
};

single_metronome *metronomes[2];


 
