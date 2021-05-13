/*
  waveTableOsc - compact library for wavetable synthesis.
  Created by Vinícius Fernandes, May 11, 2021.
  Released into the public domain.
*/
#include "waveTableOsc.h"

waveTableOsc::waveTableOsc(int WaveSize, int tempSampRate, const char *functionSelect, float tempAmp)
{
  String functionReceive = functionSelect;
  this->sampleRate = tempSampRate;
  this->amp = tempAmp;
  this->WaveSizeGlobal = WaveSize;
  if (functionReceive.equals("square"))
  {
    this->waveLow = new int[WaveSize];
    this->waveMid = new int[WaveSize];
    this->waveHigh = new int[WaveSize];
    this->waveSuperHigh = new int[WaveSize];
    this->generateSquare(100, this->waveLow);
    this->generateSquare(35, this->waveMid);
    this->generateSquare(15, this->waveHigh);
    this->generateSquare(7, this->waveSuperHigh);
  }
  else if (functionReceive.equals("saw"))
  {
    this->waveLow = new int[WaveSize];
    this->waveMid = new int[WaveSize];
    this->waveHigh = new int[WaveSize];
    this->waveSuperHigh = new int[WaveSize];
    this->generateSaw(100, this->waveLow);
    this->generateSaw(35, this->waveMid);
    this->generateSaw(15, this->waveHigh);
    this->generateSaw(7, this->waveSuperHigh);
  }
  else if (functionReceive.equals("sine"))
  {
    this->waveLow = new int[WaveSize];
    this->waveMid = new int[WaveSize];
    this->waveHigh = new int[WaveSize];
    this->waveSuperHigh = new int[WaveSize];
    this->generateSine();
  }
}

void waveTableOsc::generateSine()
{
  for (int i = 0; i < this->WaveSizeGlobal; i++)
  {
    float factor = TWO_PI / this->WaveSizeGlobal;
    float sampValue = (this->amp * sin(factor * i) + this->amp) / 2;
    this->waveLow[i] = sampValue;
    this->waveMid[i] = sampValue;
    this->waveHigh[i] = sampValue;
    this->waveSuperHigh[i] = sampValue;
    
  }
}
void waveTableOsc::generateSaw(int harmonics, int *table)
{
  for (int i = 0; i < this->WaveSizeGlobal; i++)
  {
    float factor = TWO_PI / this->WaveSizeGlobal;
    for (int j = 1; j <= harmonics; j++)
    {
      float prevValue = ((this->amp * sin(i * factor * j) / j * PI)) / 2;
      value = value + prevValue;
    }
    table[i] = (value + (this->amp * 3)) / 6;
    value = 0;
  }
}

void waveTableOsc::generateSquare(int harmonics, int *table)
{
  for (int i = 0; i < this->WaveSizeGlobal; i++)
  {
    float factor = TWO_PI / this->WaveSizeGlobal;
    for (int j = 1; j <= harmonics; j++)
    {
      if (j % 2 != 0)
      {
        float prevValue = ((this->amp * sin(i * factor * j) / j * PI)) / 2;
        value = value + prevValue;
      }
    }
    table[i] = ((value + (this->amp + this->amp / 4)) / 2) * 0.75;
    value = 0;
  }
}

int waveTableOsc::phasor(double freq)
{
  double inc = freq / this->sampleRate;
  this->phaseInc = inc;
  this->phasorAcu += this->phaseInc;
  if (this->phasorAcu >= 1.0)
  {
    this->phasorAcu -= 1.0;
  }
  if (freq > 0 && freq < 700)
  {
    return this->tabRead(this->waveLow);
  }
  else if (freq > 700 && freq < 1200)
  {
    return this->tabRead(this->waveMid);
  }
  else if (freq > 1200 && freq < 2000)
  {
    return this->tabRead(this->waveHigh);
  }
  else
  {
    return this->tabRead(this->waveSuperHigh);
  }
}

int waveTableOsc::tabRead(int *bufferWav)
{
  double temp = this->phasorAcu * this->WaveSizeGlobal;
  int sample = bufferWav[int(temp)];
  return sample;
}
