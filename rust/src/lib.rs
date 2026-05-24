#[derive(Clone, Copy, Debug, Eq, PartialEq)]
#[repr(usize)]
pub enum Scale {
    Person = 0,
    Peers = 1,
    Family = 2,
    Community = 3,
    Neighborhood = 4,
    Institution = 5,
    City = 6,
    County = 7,
    Region = 8,
    State = 9,
    Country = 10,
    Continent = 11,
    Planet = 12,
}

pub const SCALE_COUNT: usize = 13;

pub const SCALE_NAMES: [&str; SCALE_COUNT] = [
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
];

#[derive(Clone, Copy, Debug)]
pub struct ScaleInput {
    pub stakes_density: f64,
    pub harmony: f64,
    pub admissible: bool,
    pub weight: f64,
}

impl Default for ScaleInput {
    fn default() -> Self {
        Self {
            stakes_density: 0.0,
            harmony: 0.0,
            admissible: true,
            weight: 1.0,
        }
    }
}

#[derive(Clone, Copy, Debug)]
pub struct ScaleOutput {
    pub scale: Scale,
    pub contribution: f64,
    pub constraint_failed: bool,
}

#[derive(Clone, Debug)]
pub struct Evaluation {
    pub score: f64,
    pub conflict_count: usize,
    pub constraint_failures: usize,
    pub outputs: Vec<ScaleOutput>,
}

pub fn empty_inputs() -> [ScaleInput; SCALE_COUNT] {
    [ScaleInput::default(); SCALE_COUNT]
}

pub fn scale_name(scale: Scale) -> &'static str {
    SCALE_NAMES[scale as usize]
}

pub fn evaluate(inputs: &[ScaleInput; SCALE_COUNT], start: Scale, end: Scale) -> Evaluation {
    let mut start_index = start as usize;
    let mut end_index = end as usize;

    if start_index > end_index {
        std::mem::swap(&mut start_index, &mut end_index);
    }

    let mut evaluation = Evaluation {
        score: 0.0,
        conflict_count: 0,
        constraint_failures: 0,
        outputs: Vec::with_capacity(SCALE_COUNT),
    };

    for (index, input) in inputs.iter().enumerate() {
        let scale = scale_from_index(index);

        if index < start_index || index > end_index {
            evaluation.outputs.push(ScaleOutput {
                scale,
                contribution: 0.0,
                constraint_failed: false,
            });
            continue;
        }

        let admissible = if input.admissible { 1.0 } else { 0.0 };
        let contribution = input.stakes_density * input.harmony * admissible * input.weight;

        evaluation.score += contribution;

        if contribution < 0.0 {
            evaluation.conflict_count += 1;
        }

        if !input.admissible {
            evaluation.constraint_failures += 1;
        }

        evaluation.outputs.push(ScaleOutput {
            scale,
            contribution,
            constraint_failed: !input.admissible,
        });
    }

    evaluation
}

fn scale_from_index(index: usize) -> Scale {
    match index {
        0 => Scale::Person,
        1 => Scale::Peers,
        2 => Scale::Family,
        3 => Scale::Community,
        4 => Scale::Neighborhood,
        5 => Scale::Institution,
        6 => Scale::City,
        7 => Scale::County,
        8 => Scale::Region,
        9 => Scale::State,
        10 => Scale::Country,
        11 => Scale::Continent,
        _ => Scale::Planet,
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn evaluates_scale_fit() {
        let mut inputs = empty_inputs();
        inputs[Scale::Person as usize] = ScaleInput {
            stakes_density: 1.0,
            harmony: -0.5,
            admissible: true,
            weight: 1.0,
        };
        inputs[Scale::Institution as usize] = ScaleInput {
            stakes_density: 1.0,
            harmony: 0.75,
            admissible: true,
            weight: 1.0,
        };

        let result = evaluate(&inputs, Scale::Person, Scale::Planet);

        assert_eq!(result.score, 0.25);
        assert_eq!(result.conflict_count, 1);
        assert_eq!(result.constraint_failures, 0);
    }
}
