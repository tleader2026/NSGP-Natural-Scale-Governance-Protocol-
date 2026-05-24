package ngp

import "testing"

func TestEvaluate(t *testing.T) {
	inputs := EmptyInputs()
	inputs[Person] = ScaleInput{StakesDensity: 1.0, Harmony: -0.5, Admissible: true, Weight: 1.0}
	inputs[Peers] = ScaleInput{StakesDensity: 0.0, Harmony: 0.0, Admissible: true, Weight: 1.0}
	inputs[Institution] = ScaleInput{StakesDensity: 1.0, Harmony: 0.75, Admissible: true, Weight: 1.0}

	result, err := Evaluate(inputs, Person, Planet)
	if err != nil {
		t.Fatal(err)
	}

	if result.Score != 0.25 {
		t.Fatalf("score = %f, want 0.25", result.Score)
	}

	if result.ConflictCount != 1 {
		t.Fatalf("conflict count = %d, want 1", result.ConflictCount)
	}
}
