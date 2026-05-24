#ifndef NSGP_H
#define NSGP_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NSGP_SCALE_COUNT 13

typedef enum NsgpScale {
    NSGP_SCALE_PERSON = 0,
    NSGP_SCALE_PEERS,
    NSGP_SCALE_FAMILY,
    NSGP_SCALE_COMMUNITY,
    NSGP_SCALE_NEIGHBORHOOD,
    NSGP_SCALE_INSTITUTION,
    NSGP_SCALE_CITY,
    NSGP_SCALE_COUNTY,
    NSGP_SCALE_REGION,
    NSGP_SCALE_STATE,
    NSGP_SCALE_COUNTRY,
    NSGP_SCALE_CONTINENT,
    NSGP_SCALE_PLANET
} NsgpScale;

typedef struct NsgpScaleInput {
    double stakes_density;
    double harmony;
    int admissible;
    double weight;
} NsgpScaleInput;

typedef struct NsgpScaleOutput {
    NsgpScale scale;
    double contribution;
    int constraint_failed;
} NsgpScaleOutput;

typedef struct NsgpEvaluation {
    double score;
    size_t conflict_count;
    size_t constraint_failures;
    NsgpScaleOutput outputs[NSGP_SCALE_COUNT];
} NsgpEvaluation;

const char *nsgp_scale_name(NsgpScale scale);
NsgpScaleInput nsgp_default_input(void);
NsgpEvaluation nsgp_evaluate(
    const NsgpScaleInput inputs[NSGP_SCALE_COUNT],
    NsgpScale start,
    NsgpScale end
);

#ifdef __cplusplus
}
#endif

#endif
