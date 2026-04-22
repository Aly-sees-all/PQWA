/* io.h - file I/O function declarations */

#ifndef IO_H
#define IO_H

#include "WaveformSample.h"

[[maybe_unused]] WaveformSample *load_csv(const char *filename, [[maybe_unused]] const int *count);
void write_results(PhaseResult results[3]);

#endif