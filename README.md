# Introduction
Simple library for audio wavetable synthesis programming in Arduino IDE.
waveTableOsc is based on the wonderful articles by Nigel Redmon about the subject. You can read it in https://www.earlevel.com/main/2012/05/03/a-wavetable-oscillator%e2%80%94introduction/

Currently there are only one class, waveTableOsc, with two public member functions, including the constructor: waveTableOsc(int,int,cons char*,float) and phasor(double);

This library is still under development, feel free to point out issues and suggestions.

# Class waveTableOsc

## Member Functions

### waveTableOsc (CONSTRUCTOR)
Create and initializes a waveTableOsc instance

* Syntax <br>
waveTableOsc(int table_size, int sample_rate, const char* function_select, float amplitude);

* Parameters
0. **int** table_size                The length of the array storing the Wave Function.
1. **int** sample_rate               The Sample Rate of the context the function will be used.
2. **const char*** function_select   String to define the Wave Function. Valid values are: "sine","saw","square".
3. **float** amplitude               The amplitude of the Wave Function stored in the array.

* Returns

  **void**

### Phasosr
* Synthax <br>
phasor(double frequency);

* Parameters
0. **double** frequency     The wave frequency that the wavetableOsc object will output. This method returns an **int** sample value corresponding to the current phase of the phasor object.             


* Returns

  **int**

