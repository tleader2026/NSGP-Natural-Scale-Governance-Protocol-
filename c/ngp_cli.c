#include "ngp.h"

#include <stdio.h>

static void set_input(
    NsgpScaleInput inputs[NSGP_SCALE_COUNT],
    NsgpScale scale,
    double stakes_density,
    double harmony,
    int admissible
)
{
    inputs[scale].stakes_density = stakes_density;
    inputs[scale].harmony = harmony;
    inputs[scale].admissible = admissible;
    inputs[scale].weight = 1.0;
}

int main(void)
{
    NsgpScaleInput inputs[NSGP_SCALE_COUNT];
    NsgpEvaluation evaluation;
    size_t i;

    for (i = 0; i < NSGP_SCALE_COUNT; i++) {
        inputs[i] = nsgp_default_input();
    }

    set_input(inputs, NSGP_SCALE_PERSON, 0.95, -0.60, 1);
    set_input(inputs, NSGP_SCALE_PEERS, 0.80, -0.30, 1);
    set_input(inputs, NSGP_SCALE_FAMILY, 0.70, -0.20, 1);
    set_input(inputs, NSGP_SCALE_COMMUNITY, 0.90, -0.55, 1);
    set_input(inputs, NSGP_SCALE_NEIGHBORHOOD, 0.85, -0.65, 1);
    set_input(inputs, NSGP_SCALE_INSTITUTION, 0.75, 0.80, 1);
    set_input(inputs, NSGP_SCALE_CITY, 0.70, 0.35, 1);
    set_input(inputs, NSGP_SCALE_COUNTY, 0.55, 0.25, 1);
    set_input(inputs, NSGP_SCALE_REGION, 0.60, 0.20, 1);
    set_input(inputs, NSGP_SCALE_STATE, 0.65, 0.25, 1);
    set_input(inputs, NSGP_SCALE_COUNTRY, 0.50, 0.10, 1);
    set_input(inputs, NSGP_SCALE_CONTINENT, 0.30, -0.05, 1);
    set_input(inputs, NSGP_SCALE_PLANET, 0.90, -0.70, 1);

    evaluation = nsgp_evaluate(inputs, NSGP_SCALE_PERSON, NSGP_SCALE_PLANET);

    printf("Natural Scale Governance Protocol evaluation\n");
    printf("score: %.4f\n", evaluation.score);
    printf("conflicts: %zu\n", evaluation.conflict_count);
    printf("constraint failures: %zu\n\n", evaluation.constraint_failures);

    for (i = 0; i < NSGP_SCALE_COUNT; i++) {
        printf(
            "%-13s contribution=% .4f constraint_failed=%d\n",
            nsgp_scale_name(evaluation.outputs[i].scale),
            evaluation.outputs[i].contribution,
            evaluation.outputs[i].constraint_failed
        );
    }

    return 0;
}
