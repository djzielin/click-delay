#define NUM_BUFFERS 3

class canon_delay
{
public: 
	canon_delay(unsigned int _b_length)
    {
       b_length=_b_length;  
       b_length2=b_length*2;
       b_length3=b_length*3;
       
       for(int i=0;i<3;i++)
          buffer[i]=new float[b_length3]; //for 1 octave down
       
       for(unsigned int i=0;i<b_length2;i++) //clear everything
       {
       	  for(int e=0;e<3;e++)
             buffer[e][i]=0.0f;
       }
       
       read_index[0]=b_length2;
       read_index[1]=b_length;
       read_index[2]=0;
       
       write_to_which=2; //so we start with buffer 0
    }	

    float process(int index, float input)
    {
    	if(index==0) //on zero switch to next buffer
    	   write_to_which=(write_to_which+1) % NUM_BUFFERS;
    	
    	buffer[write_to_which][index*2]=input;
    	buffer[write_to_which][index*2]=input;

    	
    	float retval=0.0f;
    	
    	for(int i=0;i<3;i++)
    	{
           retval+=buffer[i][read_index[i]];
           read_index[i]=(read_index[i]+1) % b_length3;
    	}

	    return retval;
    }
    
    int write_to_which;
    
	unsigned int b_length;
	unsigned int b_length2;
	unsigned int b_length3;
	
	float *buffer[NUM_BUFFERS];

	unsigned read_index[NUM_BUFFERS];

};
