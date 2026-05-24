from ngp import Scale, ScaleInput, empty_inputs, evaluate, scale_name


def main() -> None:
    inputs = empty_inputs()
    values = {
        Scale.PERSON:       ScaleInput(0.95, -0.60),
        Scale.PEERS:        ScaleInput(0.80, -0.30),
        Scale.FAMILY:       ScaleInput(0.70, -0.20),
        Scale.COMMUNITY:    ScaleInput(0.90, -0.55),
        Scale.NEIGHBORHOOD: ScaleInput(0.85, -0.65),
        Scale.INSTITUTION:  ScaleInput(0.75,  0.80),
        Scale.CITY:         ScaleInput(0.70,  0.35),
        Scale.COUNTY:       ScaleInput(0.55,  0.25),
        Scale.REGION:       ScaleInput(0.60,  0.20),
        Scale.STATE:        ScaleInput(0.65,  0.25),
        Scale.COUNTRY:      ScaleInput(0.50,  0.10),
        Scale.CONTINENT:    ScaleInput(0.30, -0.05),
        Scale.PLANET:       ScaleInput(0.90, -0.70),
    }

    for scale, value in values.items():
        inputs[int(scale)] = value

    result = evaluate(inputs)
    print("Natural Scale Governance Protocol evaluation")
    print(f"score:               {result.score:.4f}")
    print(f"conflicts:           {result.conflict_count}")
    print(f"constraint failures: {result.constraint_failures}")
    print()

    for output in result.outputs:
        print(
            f"{scale_name(output.scale):13s} "
            f"contribution={output.contribution: .4f} "
            f"constraint_failed={output.constraint_failed}"
        )


if __name__ == "__main__":
    main()
