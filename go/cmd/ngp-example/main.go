package main

import (
	"fmt"

	"natural-governance-protocol/ngp"
)

func main() {
	inputs := ngp.EmptyInputs()
	inputs[ngp.Person] = ngp.ScaleInput{StakesDensity: 0.95, Harmony: -0.60, Admissible: true, Weight: 1.0}
	inputs[ngp.Peers] = ngp.ScaleInput{StakesDensity: 0.80, Harmony: -0.30, Admissible: true, Weight: 1.0}
	inputs[ngp.Family] = ngp.ScaleInput{StakesDensity: 0.70, Harmony: -0.20, Admissible: true, Weight: 1.0}
	inputs[ngp.Community] = ngp.ScaleInput{StakesDensity: 0.90, Harmony: -0.55, Admissible: true, Weight: 1.0}
	inputs[ngp.Neighborhood] = ngp.ScaleInput{StakesDensity: 0.85, Harmony: -0.65, Admissible: true, Weight: 1.0}
	inputs[ngp.Institution] = ngp.ScaleInput{StakesDensity: 0.75, Harmony: 0.80, Admissible: true, Weight: 1.0}
	inputs[ngp.City] = ngp.ScaleInput{StakesDensity: 0.70, Harmony: 0.35, Admissible: true, Weight: 1.0}
	inputs[ngp.County] = ngp.ScaleInput{StakesDensity: 0.55, Harmony: 0.25, Admissible: true, Weight: 1.0}
	inputs[ngp.Region] = ngp.ScaleInput{StakesDensity: 0.60, Harmony: 0.20, Admissible: true, Weight: 1.0}
	inputs[ngp.State] = ngp.ScaleInput{StakesDensity: 0.65, Harmony: 0.25, Admissible: true, Weight: 1.0}
	inputs[ngp.Country] = ngp.ScaleInput{StakesDensity: 0.50, Harmony: 0.10, Admissible: true, Weight: 1.0}
	inputs[ngp.Continent] = ngp.ScaleInput{StakesDensity: 0.30, Harmony: -0.05, Admissible: true, Weight: 1.0}
	inputs[ngp.Planet] = ngp.ScaleInput{StakesDensity: 0.90, Harmony: -0.70, Admissible: true, Weight: 1.0}

	result, err := ngp.Evaluate(inputs, ngp.Person, ngp.Planet)
	if err != nil {
		panic(err)
	}

	fmt.Println("Natural Governance Protocol evaluation")
	fmt.Printf("score: %.4f\n", result.Score)
	fmt.Printf("conflicts: %d\n", result.ConflictCount)
	fmt.Printf("constraint failures: %d\n\n", result.ConstraintFailures)

	for _, output := range result.Outputs {
		fmt.Printf(
			"%-13s contribution=% .4f constraint_failed=%t\n",
			ngp.ScaleName(output.Scale),
			output.Contribution,
			output.ConstraintFailed,
		)
	}
}
