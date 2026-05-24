from dataclasses import dataclass
from enum import IntEnum
from typing import Iterable


class Scale(IntEnum):
    PERSON = 0
    INDIVIDUALS = 1
    FAMILY = 2
    COMMUNITY = 3
    NEIGHBORHOOD = 4
    INSTITUTION = 5
    CITY = 6
    COUNTY = 7
    REGION = 8
    STATE = 9
    COUNTRY = 10
    CONTINENT = 11
    PLANET = 12


SCALE_NAMES = [
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
    "planet",
]


@dataclass(frozen=True)
class ScaleInput:
    stakes_density: float = 0.0
    harmony: float = 0.0
    admissible: bool = True
    weight: float = 1.0


@dataclass(frozen=True)
class ScaleOutput:
    scale: Scale
    contribution: float
    constraint_failed: bool


@dataclass(frozen=True)
class Evaluation:
    score: float
    conflict_count: int
    constraint_failures: int
    outputs: tuple[ScaleOutput, ...]


def empty_inputs() -> list[ScaleInput]:
    return [ScaleInput() for _ in SCALE_NAMES]


def scale_name(scale: Scale) -> str:
    return SCALE_NAMES[int(scale)]


def evaluate(
    inputs: Iterable[ScaleInput],
    start: Scale = Scale.PERSON,
    end: Scale = Scale.PLANET,
) -> Evaluation:
    values = list(inputs)
    if len(values) != len(SCALE_NAMES):
        raise ValueError(f"expected {len(SCALE_NAMES)} scale inputs")

    start_index = int(start)
    end_index = int(end)
    if start_index > end_index:
        start_index, end_index = end_index, start_index

    score = 0.0
    conflict_count = 0
    constraint_failures = 0
    outputs: list[ScaleOutput] = []

    for index, value in enumerate(values):
        if index < start_index or index > end_index:
            outputs.append(ScaleOutput(Scale(index), 0.0, False))
            continue

        admissible = 1.0 if value.admissible else 0.0
        contribution = (
            value.stakes_density * value.harmony * admissible * value.weight
        )
        score += contribution

        if contribution < 0.0:
            conflict_count += 1
        if not value.admissible:
            constraint_failures += 1

        outputs.append(ScaleOutput(Scale(index), contribution, not value.admissible))

    return Evaluation(
        score=score,
        conflict_count=conflict_count,
        constraint_failures=constraint_failures,
        outputs=tuple(outputs),
    )

