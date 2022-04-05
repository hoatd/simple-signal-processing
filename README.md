# simple-signal-processing

Two real valued signals are given as:

- A sine wave with a frequency of 10 Hz, an amplitude of 3 and a phase offset of 90°.
- A symmetrical square wave with a frequency of 40 Hz, an amplitude of 1 and a phase offset of 0°.
 

- Both signals shall be sampled with a sampling frequency of 200 Hz (for a duration of 1 second) into a data buffer and printed to the screen.
- Create a third mixed signal by multiplying both, print it as well.
- Compute the mean of the mixed signals first quarter (the first 0.25 seconds) and the integral of the second quarter. Print the results as well.

NOTES: Code for adding noise provided, output signal data to file as well

# build

`clang++ sinusoid.cpp -o sinusoid -std=c++14`

