#include "ngp.h"

static const char *NSGP_SCALE_NAMES[NSGP_SCALE_COUNT] = {
    "person",
    "peers",
    "family",
    "community",
    "neighborhood",
    "institution",
    "city",
    "county",
    "region",
    "state",
    "country",
    "continent",
    "planet"
};

const char *nsgp_scale_name(NsgpScale scale)
{
    if (scale < 0 || scale >= NSGP_SCALE_COUNT) {
        return "unknown";
    }

    return NSGP_SCALE_NAMES[scale];
}

NsgpScaleInput nsgp_default_input(void)
{
    NsgpScaleInput input;
    input.stakes_density = 0.0;
    input.harmony = 0.0;
    input.admissible = 1;
    input.weight = 1.0;
    return input;
}

NsgpEvaluation nsgp_evaluate(
    const NsgpScaleInput inputs[NSGP_SCALE_COUNT],
    NsgpScale start,
    NsgpScale end
)
{
    NsgpEvaluation evaluation;
    size_t i;

    evaluation.score = 0.0;
    evaluation.conflict_count = 0;
    evaluation.constraint_failures = 0;

    for (i = 0; i < NSGP_SCALE_COUNT; i++) {
        evaluation.outputs[i].scale = (NsgpScale)i;
        evaluation.outputs[i].contribution = 0.0;
        evaluation.outputs[i].constraint_failed = 0;
    }

    if (start > end) {
        NsgpScale tmp = start;
        start = end;
        end = tmp;
    }

    for (i = (size_t)start; i <= (size_t)end && i < NSGP_SCALE_COUNT; i++) {
        const NsgpScaleInput input = inputs[i];
        const int admissible = input.admissible ? 1 : 0;
        const double contribution =
            input.stakes_density * input.harmony * (double)admissible * input.weight;

        evaluation.outputs[i].contribution = contribution;
        evaluation.outputs[i].constraint_failed = admissible ? 0 : 1;
        evaluation.score += contribution;

        if (!admissible) {
            evaluation.constraint_failures++;
        }

        if (contribution < 0.0) {
            evaluation.conflict_count++;
        }
    }

    return evaluation;
}
