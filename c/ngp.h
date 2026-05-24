#ifndef NGP_H
#define NGP_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NGP_SCALE_COUNT 13

typedef enum NgpScale {
    NGP_SCALE_PERSON = 0,
    NGP_SCALE_INDIVIDUALS,
    NGP_SCALE_FAMILY,
    NGP_SCALE_COMMUNITY,
    NGP_SCALE_NEIGHBORHOOD,
    NGP_SCALE_INSTITUTION,
    NGP_SCALE_CITY,
    NGP_SCALE_COUNTY,
    NGP_SCALE_REGION,
    NGP_SCALE_STATE,
    NGP_SCALE_COUNTRY,
    NGP_SCALE_CONTINENT,
    NGP_SCALE_PLANET
} NgpScale;

typedef struct NgpScaleInput {
    double stakes_density;
    double harmony;
    int admissible;
    double weight;
} NgpScaleInput;

typedef struct NgpScaleOutput {
    NgpScale scale;
    double contribution;
    int constraint_failed;
} NgpScaleOutput;

typedef struct NgpEvaluation {
    double score;
    size_t conflict_count;
    size_t constraint_failures;
    NgpScaleOutput outputs[NGP_SCALE_COUNT];
} NgpEvaluation;

const char *ngp_scale_name(NgpScale scale);
NgpScaleInput ngp_default_input(void);
NgpEvaluation ngp_evaluate(
    const NgpScaleInput inputs[NGP_SCALE_COUNT],
    NgpScale start,
    NgpScale end
);

#ifdef __cplusplus
}
#endif

#endif

