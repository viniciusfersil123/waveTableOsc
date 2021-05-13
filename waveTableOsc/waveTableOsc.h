/*
  waveTableOsc - compact library for wavetable synthesis.
  Created by Vinícius Fernandes, May 11, 2021.
  Released into the public domain.
*/
#ifndef waveTableOsc_h
#define waveTableOsc_h
#include <Arduino.h>

class waveTableOsc
{
  public:
    waveTableOsc(int WaveSize, int tempSampRate, const char* functionSelect, float tempAmp);
    int phasor(double freq);

 private:
    int *waveMid,*waveHigh,*waveSuperHigh,*waveLow;
    int amp,sampleRate, WaveSizeGlobal;
    float phaseInc;
    float phasorAcu = 0;
    float value = 0;
    
    void generateSine();
    void generateSaw(int harmonics, int* table);
    void generateSquare(int harmonics, int *table);
    int tabRead(int *bufferWav);
};

#endif
