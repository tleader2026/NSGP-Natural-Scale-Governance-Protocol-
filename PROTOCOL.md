# Natural Scale Governance Protocol v0

This document defines the prototype operational contract for Natural Scale Governance Protocol implementations.

## Objective

The protocol evaluates a governance action across scale. It does not automate moral judgment. It produces a structured conflict map that makes scale-contingent disagreement visible.

## Canonical Scale Axis

| Index | Symbol | Name         |
|-------|--------|--------------|
| 0     | s1     | person       |
| 1     | s2     | peers        |
| 2     | s3     | family       |
| 3     | s4     | community    |
| 4     | s5     | neighborhood |
| 5     | s6     | institution  |
| 6     | s7     | city         |
| 7     | s8     | county       |
| 8     | s9     | region       |
| 9     | s10    | state        |
| 10    | s11    | country      |
| 11    | s12    | continent    |
| 12    | s13    | planet       |

> `s1` (person) is a single individual. `s2` (peers) covers 2–3 people in a loose, non-familial relationship — distinct from `s3` (family), which implies a deeper relational bond.

The C implementation is the reference for enum order and default scoring semantics.

## Input Contract

Each scale receives:

- `stakes_density`: float
- `harmony`: float
- `admissible`: boolean
- `weight`: float

Recommended prototype ranges:

- `stakes_density`: `0.0` to `1.0`
- `harmony`: `-1.0` to `1.0`
- `admissible`: `true` or `false`
- `weight`: `0.0` or greater

The prototype does not clamp values. Implementations should surface validation separately so research users can test alternative ranges.

## Scoring

For a selected interval `[s_a, s_b]`, each scale contribution is:

```
contribution_i = stakes_density_i * harmony_i * admissible_i * weight_i
```

Where:

- `admissible_i = 1.0` if true
- `admissible_i = 0.0` if false

The aggregate score is:

```
score = sum contribution_i
```

## Output Contract

Every implementation must return:

- `score`: float — aggregate weighted sum across the evaluated range
- `conflict_count`: integer — number of scales where `contribution < 0`
- `constraint_failures`: integer — number of scales where `admissible = false`
- `outputs`: per-scale contribution records

A scale is counted as a **conflict** when its contribution is less than zero (harmony is negative at that scale).

A scale is counted as a **constraint failure** when `admissible` is false.

## Implementation Layers

### C Core

The C core is the reference implementation intended for infrastructure, operating-system, embedded, and high-trust environments. It is an infrastructure primitive: allocation-free, dependency-free, and stable.

The current C API is intentionally allocation-free for evaluation:

```c
NsgpEvaluation nsgp_evaluate(
    const NsgpScaleInput inputs[NSGP_SCALE_COUNT],
    NsgpScale start,
    NsgpScale end
);
```

### Python SDK

The Python implementation is intended for policy analysis, notebooks, internal tooling, AI orchestration, and data workflows.

### Go SDK

The Go implementation is intended for services, infrastructure APIs, policy engines, and distributed systems.

### Rust SDK

The Rust implementation is intended for high-assurance applications, local agents, browser/edge runtimes, and future FFI-safe cores.

## Future Extensions

- JSON input and output parsers for the C CLI.
- Validation profiles for public policy, AI governance, corporate review, and safety-critical systems.
- FFI bindings from the C core into Python, Go, and Rust.
- Constraint classes instead of a single boolean.
- Uncertainty intervals for `stakes_density` and `harmony`.
- Explainable provenance fields for every score.
- Deliberation triggers when high-stakes scales diverge sharply.
