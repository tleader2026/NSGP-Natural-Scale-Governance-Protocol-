use ngp::{empty_inputs, evaluate, scale_name, Scale, ScaleInput};

fn main() {
    let mut inputs = empty_inputs();

    inputs[Scale::Person as usize] = ScaleInput { stakes_density: 0.95, harmony: -0.60, admissible: true, weight: 1.0 };
    inputs[Scale::Peers as usize] = ScaleInput { stakes_density: 0.80, harmony: -0.30, admissible: true, weight: 1.0 };
    inputs[Scale::Family as usize] = ScaleInput { stakes_density: 0.70, harmony: -0.20, admissible: true, weight: 1.0 };
    inputs[Scale::Community as usize] = ScaleInput { stakes_density: 0.90, harmony: -0.55, admissible: true, weight: 1.0 };
    inputs[Scale::Neighborhood as usize] = ScaleInput { stakes_density: 0.85, harmony: -0.65, admissible: true, weight: 1.0 };
    inputs[Scale::Institution as usize] = ScaleInput { stakes_density: 0.75, harmony: 0.80, admissible: true, weight: 1.0 };
    inputs[Scale::City as usize] = ScaleInput { stakes_density: 0.70, harmony: 0.35, admissible: true, weight: 1.0 };
    inputs[Scale::County as usize] = ScaleInput { stakes_density: 0.55, harmony: 0.25, admissible: true, weight: 1.0 };
    inputs[Scale::Region as usize] = ScaleInput { stakes_density: 0.60, harmony: 0.20, admissible: true, weight: 1.0 };
    inputs[Scale::State as usize] = ScaleInput { stakes_density: 0.65, harmony: 0.25, admissible: true, weight: 1.0 };
    inputs[Scale::Country as usize] = ScaleInput { stakes_density: 0.50, harmony: 0.10, admissible: true, weight: 1.0 };
    inputs[Scale::Continent as usize] = ScaleInput { stakes_density: 0.30, harmony: -0.05, admissible: true, weight: 1.0 };
    inputs[Scale::Planet as usize] = ScaleInput { stakes_density: 0.90, harmony: -0.70, admissible: true, weight: 1.0 };

    let result = evaluate(&inputs, Scale::Person, Scale::Planet);

    println!("Natural Governance Protocol evaluation");
    println!("score: {:.4}", result.score);
    println!("conflicts: {}", result.conflict_count);
    println!("constraint failures: {}", result.constraint_failures);
    println!();

    for output in result.outputs {
        println!(
            "{:<13} contribution={:+.4} constraint_failed={}",
            scale_name(output.scale),
            output.contribution,
            output.constraint_failed
        );
    }
}
