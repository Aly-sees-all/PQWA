#include <cstdio>
#include "io.h"
#include "WaveformSample.h"
#include "WaveformSample.h"

WaveformSample *load_csv(char *string, int *pInt);

void write_results(PhaseResult results[3]);

void free([[maybe_unused]] WaveformSample *samples);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: analyser <filename.csv>\n");
        return 1;
    }

    int count = 0;
    WaveformSample *samples = load_csv(argv[1], &count);

    if (samples == nullptr) {
        return 1;
    }

    /* Analyse each phase */
    PhaseResult results[3];
    results[0] = analyse_phase(samples, count, 0);
    results[1] = analyse_phase(samples, count, 1);
    results[2] = analyse_phase(samples, count, 2);

    /* Write report */
    write_results(results);
    printf("Analysis complete. Results written to results.txt\n");

    /* Clean up */
    free(samples);
    return;
}

void free([[maybe_unused]] WaveformSample *samples) {

}

void write_results(PhaseResult results[3]) {

}

WaveformSample *load_csv(char *string, int *pInt) {
    return nullptr;
}
