//Finally a simple OpenAL example program.
//Gordon Griesel
//2015 - 2018

#include "Global.h"
#include "Timers.h"
#include "SpriteSheet.h"
#include "Character.h"
#include <GL/glx.h>
#include <sstream>
#include "fonts.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "rafaelN.h"

#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#include <pthread.h>
#endif //USE_OPENAL_SOUND

bool inUse[8] = {0,0,0,0,0,0,0,0};

void* migos(void* arg)
{
    if (arg){

    }
    //int* threadNumber = (int*)arg;
    //int i = *threadNumber;

    //printf("Thread number: %i\n",i);	

    //Get started right here.
#ifdef USE_OPENAL_SOUND
//	alutInit(0, NULL);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: alutInit()\n");
		//return 0;
	}
	//Clear error state.
	alGetError();
	//
	//Setup the listener.
	//Forward and up vectors are used.
	float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alListenerfv(AL_ORIENTATION, vec);
	alListenerf(AL_GAIN, 1.0f);
	//
	//Buffer holds the sound information.
	ALuint alBuffer;
	alBuffer = alutCreateBufferFromFile("./Migos_gun.wav");
	//
	//Source refers to the sound.
	ALuint alSource;
	//Generate a source, and store it in a buffer.
	alGenSources(1, &alSource);
	alSourcei(alSource, AL_BUFFER, alBuffer);
	//Set volume and pitch to normal, no looping of sound.
	alSourcef(alSource, AL_GAIN, 1.0f);
	alSourcef(alSource, AL_PITCH, 1.0f);
	alSourcei(alSource, AL_LOOPING, AL_FALSE);
	if (alGetError() != AL_NO_ERROR) {
		printf("ERROR: setting source\n");
        alutExit();
     //   inUse[i] = 0;
        pthread_exit(NULL);
		//return 0;
	}
	ALint state;
		alSourcePlay(alSource);
		do {
			alGetSourcei(alSource, AL_SOURCE_STATE, &state);
		} while (state == AL_PLAYING);
		//alSourceStop(alSource); 
      //  usleep(250000);
	//Cleanup.
	//First delete the source.
	alDeleteSources(1, &alSource);
	//Delete the buffer.
	alDeleteBuffers(1, &alBuffer);
	//Close out OpenAL itself.
//	alutExit();
    //inUse[i]=0;
    pthread_exit(NULL);
    /*
//Get active context.
	ALCcontext *Context = alcGetCurrentContext();
	//Get device for active context.
	ALCdevice *Device = alcGetContextsDevice(Context);
	//Disable context.
	alcMakeContextCurrent(NULL);
	//Release context(s).
	alcDestroyContext(Context);
	//Close device.
	alcCloseDevice(Device);
*/
#endif //USE_OPENAL_SOUND
	//return 0;
}

void sound() {
    pthread_t thread;
    //for(int i=1; i< 8; i++) {
        //if (!inUse[i]) {
           // inUse[i] = 1;
            if (pthread_create(&thread, NULL, migos, (void*)NULL)) {
                printf("Error: unable to create thread\n");
            } else {
                printf("Thread created\n");
                return;
            }   
        //}
    //}
}


