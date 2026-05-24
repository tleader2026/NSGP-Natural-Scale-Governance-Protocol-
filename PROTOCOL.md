# Natural Governance Protocol v0

This document defines the prototype operational contract for Natural Governance Protocol implementations.

## Objective

The protocol evaluates a governance action across scale. It does not automate moral judgment. It produces a structured conflict map that makes scale-contingent disagreement visible.

## Canonical Scale Axis

| Index | Symbol | Name |
| --- | --- | --- |
| 0 | s1 | person |
| 1 | s2 | individuals |
| 2 | s3 | family |
| 3 | s4 | community |
| 4 | s5 | neighborhood |
| 5 | s6 | institution |
| 6 | s7 | city |
| 7 | s8 | county |
| 8 | s9 | region |
| 9 | s10 | state |
| 10 | s11 | country |
| 11 | s12 | continent |
| 12 | s13 | planet |

The C implementation is the reference for enum order and default scoring semantics.

## Input Contract

Each scale receives:

```text
stakes_density: float
harmony: float
admissible: boolean
weight: float
```

Recommended prototype ranges:

```text
stakes_density: 0.0 to 1.0
harmony: -1.0 to 1.0
admissible: true or false
weight: 0.0 or greater
```

The prototype does not clamp values. Implementations should surface validation separately so research users can test alternative ranges.

## Scoring

For a selected interval `[s_a, s_b]`, each scale contribution is:

```text
contribution_i = stakes_density_i * harmony_i * admissible_i * weight_i
```

Where:

```text
admissible_i = 1.0 if true
admissible_i = 0.0 if false
```

The aggregate score is:

```text
score = sum contribution_i
```

## Output Contract

Every implementation should return:

```text
score: float
conflict_count: integer
constraint_failures: integer
outputs: per-scale contribution records
```

A scale is counted as a conflict when its contribution is less than zero.

A scale is counted as a constraint failure when `admissible` is false.

## Implementation Layers

### C Core

The C core is the reference implementation intended for infrastructure, operating-system, embedded, and high-trust environments.

The current C API is intentionally allocation-free for evaluation:

```c
NgpEvaluation ngp_evaluate(
    const NgpScaleInput inputs[NGP_SCALE_COUNT],
    NgpScale start,
    NgpScale end
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

