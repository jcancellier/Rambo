//Finally a simple OpenAL example program.
//Author: Gordon Griesel
//Edited By: Rafael Noriega
//2015 - 2018

#define USE_OPEN_SOUND true
#include <X11/keysym.h>
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
#include "rafaelN.h"
#include <fcntl.h>
#include <sys/stat.h>
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

extern Timers timers;
extern Global g;
void sound()
{
    //Get started right here.
#ifdef USE_OPENAL_SOUND
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
        printf("ERROR: alutInit()\n");
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
    }
        alSourcePlay(alSource);
        usleep(290000);
    //Cleanup.
    //First delete the source.
    alDeleteSources(1, &alSource);
    //Delete the buffer.
    alDeleteBuffers(1, &alBuffer);
    //Close out OpenAL itself.
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
#endif //USE_OPENAL_SOUND
}





double test_funct() {
   
    static double td = 0.0; 
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    Rect r;
    r.center = 0;
    r.bot = g.yres - 500;
    r.left = g.xres/3;

    for(int i = 0; i < 100000; i++) {

    r.center = 0;
    }
    ggprint8b(&r, 16, 0xffff47, "Rafael");

    clock_gettime(CLOCK_REALTIME, &end);
    td += timers.timeDiff(&start, &end);

    return td;

}

double test_funct2(){

    static double td = 0.0;
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    Rect r;
    r.bot = g.yres << 3;
    r.bot = r.bot >> 3;
    r.left = g.xres >> 3;
    r.center = 0;
    ggprint8b(&r, 16, 0xffff47, "Rafael :) ");

    clock_gettime(CLOCK_REALTIME, &end);
    td += timers.timeDiff(&start, &end);

    return td;
}

