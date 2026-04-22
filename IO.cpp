/* io.c - loading CSV and writing results */
/* ERRORS TO FIND: 3 */

#include "IO.h"
#include <cstdio>
#include <cstdlib>

static double
strtod(char string[256], const char string1[32], double *pDouble, double *pDouble1, double *pDouble2, double *pDouble3,
       double *pDouble4, double *pDouble5, double *pDouble6, double *pDouble7);

[[maybe_unused]] WaveformSample *load_csv(const char *filename, [[maybe_unused]] const int *count) {
    FILE *f = fopen(filename, "r");
    if (f == nullptr) {
        printf("Error: could not open file %s\n", filename);
        return nullptr;
    }

    /* Skip header line */
    char line[256];
    fgets(line, sizeof(line), f);

    /* Count rows */
    int rows = 0;
    while (fgets(line, sizeof(line), f) != nullptr) {
        rows++;
    }

    /* Allocate memory */
    auto *samples = static_cast<WaveformSample *>(malloc(rows * sizeof(WaveformSample)));
    if (samples == nullptr) {
        printf("Error: memory allocation failed\n");
        fclose(f);
        return nullptr;
    }

    /* Go back to start and skip header again */
    rewind(f);
    fgets(line, sizeof(line), f);

    /* Read data */
    int i = 0;
    while (fgets(line, sizeof(line), f) != nullptr) {
        strtod(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &samples[i].timestamp,
               &samples[i].phase_A_voltage,
               &samples[i].phase_B_voltage,
               &samples[i].phase_C_voltage,
               &samples[i].line_current,
               &samples[i].frequency,
               &samples[i].power_factor,
               &samples[i].thd_percent
        );
        i++;
    }

    fclose(f);
    return samples;
}

static double
strtod(char string[256], const char string1[32], double *pDouble, double *pDouble1, double *pDouble2, double *pDouble3,
       double *pDouble4, double *pDouble5, double *pDouble6, double *pDouble7) {
    return 0;
}

void write_results(PhaseResult results[3]) {
    FILE *f = nullptr;

    const char *phase_names[] = {"A", "B", "C"};

    fprintf(f, "=== Power Quality Analysis Report ===\n\n");

    for (int i = 0; i < 3; i++) {
        fprintf(f, "Phase %s:\n", phase_names[i]);
        fprintf(f, "  RMS Voltage    : %.2f V\n", results[i].rms);
        fprintf(f, "  Peak-to-Peak   : %.2f V\n", results[i].peak_to_peak);
        fprintf(f, "  DC Offset      : %.4f V\n", results[i].dc_offset);
        fprintf(f, "  Clipping events: %d\n",     results[i].clipping_count);
        fprintf(f, "  Compliant      : %s\n",     results[i].compliant ? "YES" : "NO");
        fprintf(f, "\n");
    }

    fclose(f);
}