#include "ngp.h"

static const char *NGP_SCALE_NAMES[NGP_SCALE_COUNT] = {
    "person",
    "individuals",
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

const char *ngp_scale_name(NgpScale scale)
{
    if (scale < 0 || scale >= NGP_SCALE_COUNT) {
        return "unknown";
    }

    return NGP_SCALE_NAMES[scale];
}

NgpScaleInput ngp_default_input(void)
{
    NgpScaleInput input;
    input.stakes_density = 0.0;
    input.harmony = 0.0;
    input.admissible = 1;
    input.weight = 1.0;
    return input;
}

NgpEvaluation ngp_evaluate(
    const NgpScaleInput inputs[NGP_SCALE_COUNT],
    NgpScale start,
    NgpScale end
)
{
    NgpEvaluation evaluation;
    size_t i;

    evaluation.score = 0.0;
    evaluation.conflict_count = 0;
    evaluation.constraint_failures = 0;

    for (i = 0; i < NGP_SCALE_COUNT; i++) {
        evaluation.outputs[i].scale = (NgpScale)i;
        evaluation.outputs[i].contribution = 0.0;
        evaluation.outputs[i].constraint_failed = 0;
    }

    if (start > end) {
        NgpScale tmp = start;
        start = end;
        end = tmp;
    }

    for (i = (size_t)start; i <= (size_t)end && i < NGP_SCALE_COUNT; i++) {
        const NgpScaleInput input = inputs[i];
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

