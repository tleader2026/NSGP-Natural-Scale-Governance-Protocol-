# Natural Scale Governance Protocol Prototype

This repository is an initial operational prototype for the Natural Scale Governance Protocol (NSGP).

NSGP evaluates a governance action across a fixed scale ladder and produces a structured conflict map — making scale-contingent disagreement visible without automating moral judgment. See [PROTOCOL.md](PROTOCOL.md) for the full operational contract.

## Scale Ladder

```
s1  = person
s2  = peers
s3  = family
s4  = community
s5  = neighborhood
s6  = institution
s7  = city
s8  = county
s9  = region
s10 = state
s11 = country
s12 = continent
s13 = planet
```

> `s1` is a single person. `s2` (peers) covers 2–3 people in a loose, non-familial relationship — distinct from `s3` (family), which implies a deeper relational bond.

## Model

The continuous model is:

$$f(g;\, y, x) = \int_{y}^{x} \rho(s)\,\kappa(g, s)\,\mathbf{1}_Z(g, s)\, ds$$

This prototype uses the discrete operational approximation:

$$F(g;\, s_a, s_b) = \sum_{i=a}^{b} \rho(s_i)\,\kappa(g, s_i)\,\mathbf{1}_Z(g, s_i)\,w_i$$

Where:

- `ρ(sᵢ)` — **stakes density** (`stakes_density`): how much is at stake at scale `sᵢ`. Recommended range: `0.0–1.0`.
- `κ(g, sᵢ)` — **harmony**: how well action `g` fits at scale `sᵢ`. Recommended range: `-1.0` (direct conflict) to `1.0` (full alignment).
- `𝟙_Z(g, sᵢ)` — **admissibility**: `1` when the action is feasible at that scale, `0` otherwise. A `0` zeroes the contribution at that scale and counts as a constraint failure.
- `wᵢ` — **scale weight**: defaults to `1.0`. Increase to give a scale more influence on the aggregate score; useful when certain scales are disproportionately affected by an action.

## Output

Every implementation returns:

- **score** — aggregate weighted sum across the evaluated range
- **conflict_count** — number of scales where `contribution < 0` (harmony is negative at that scale)
- **constraint_failures** — number of scales where `admissible = false`
- **per-scale contributions** — full breakdown by scale

## Repository Layout

```
c/        C reference core and CLI (infrastructure primitive)
python/   Python SDK prototype
go/       Go SDK prototype
rust/     Rust SDK prototype
examples/ Shared example data
```

## C Reference CLI

Build with a C99 compiler:

```sh
cc -std=c99 -Wall -Wextra -pedantic c/ngp.c c/ngp_cli.c -o ngp
```

On Windows with the installed portable GCC toolchain:

```sh
gcc -std=c99 -Wall -Wextra -pedantic c/ngp.c c/ngp_cli.c -o ngp.exe
```

Run:

```sh
./ngp
```

## Python

```sh
python python/example.py
```

## Go

```sh
cd go
go test ./...
go run ./cmd/ngp-example
```

## Rust

```sh
cd rust
cargo test
cargo run --example factory
```

## Status

This is a prototype contract, not a final standard. The useful invariant is that each implementation returns the four outputs above. See [PROTOCOL.md](PROTOCOL.md) for the full specification and planned extensions.

## Toolchain Notes

The prototype has been verified with:

- Go `1.26.3`
- Rust/Cargo `1.95.0`
- LLVM/Clang `22.1.6`
- Portable w64devkit GCC `16.1.0`
- Python `3.9.1`

Rust can be built with either the MSVC or GNU Windows toolchain, depending on the local environment.
