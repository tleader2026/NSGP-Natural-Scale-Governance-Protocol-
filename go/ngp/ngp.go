package ngp

import "fmt"

type Scale int

const (
	Person Scale = iota
	Peers
	Family
	Community
	Neighborhood
	Institution
	City
	County
	Region
	State
	Country
	Continent
	Planet
	ScaleCount
)

var scaleNames = [...]string{
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
	"planet",
}

type ScaleInput struct {
	StakesDensity float64
	Harmony       float64
	Admissible    bool
	Weight        float64
}

type ScaleOutput struct {
	Scale            Scale
	Contribution     float64
	ConstraintFailed bool
}

type Evaluation struct {
	Score              float64
	ConflictCount      int
	ConstraintFailures int
	Outputs            []ScaleOutput
}

func ScaleName(scale Scale) string {
	if scale < 0 || scale >= ScaleCount {
		return "unknown"
	}
	return scaleNames[scale]
}

func EmptyInputs() []ScaleInput {
	inputs := make([]ScaleInput, ScaleCount)
	for i := range inputs {
		inputs[i] = ScaleInput{Admissible: true, Weight: 1.0}
	}
	return inputs
}

func Evaluate(inputs []ScaleInput, start Scale, end Scale) (Evaluation, error) {
	if len(inputs) != int(ScaleCount) {
		return Evaluation{}, fmt.Errorf("expected %d scale inputs", ScaleCount)
	}

	if start > end {
		start, end = end, start
	}

	evaluation := Evaluation{
		Outputs: make([]ScaleOutput, ScaleCount),
	}

	for i, input := range inputs {
		scale := Scale(i)
		evaluation.Outputs[i] = ScaleOutput{Scale: scale}

		if scale < start || scale > end {
			continue
		}

		admissible := 0.0
		if input.Admissible {
			admissible = 1.0
		}

		contribution := input.StakesDensity * input.Harmony * admissible * input.Weight
		evaluation.Outputs[i].Contribution = contribution
		evaluation.Outputs[i].ConstraintFailed = !input.Admissible
		evaluation.Score += contribution

		if contribution < 0.0 {
			evaluation.ConflictCount++
		}

		if !input.Admissible {
			evaluation.ConstraintFailures++
		}
	}

	return evaluation, nil
}
