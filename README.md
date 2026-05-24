# Natural Governance Protocol Prototype

This repository is an initial operational prototype for the Natural Governance Protocol (NGP).

NGP evaluates a governance action across a fixed scale ladder:

```text
s1  = person
s2  = individuals
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

The continuous model is:

```text
f(g; y, x) = integral_y^x o(s) * kappa(g, s) * I_Z(g, s) ds
```

This prototype uses the discrete operational approximation:

```text
F(g; s_a, s_b) = sum_i=a..b o(s_i) * kappa(g, s_i) * I_Z(g, s_i) * w_i
```

Where:

- `o(s_i)` is the stakes or sustainability density at scale `s_i`.
- `kappa(g, s_i)` is the harmony score for action `g` at scale `s_i`.
- `I_Z(g, s_i)` is `1` when the action is admissible at that scale, otherwise `0`.
- `w_i` is the scale weight. It defaults to `1.0`.

## Repository Layout

```text
c/        C reference core and CLI example
python/   Python SDK prototype
go/       Go SDK prototype
rust/     Rust SDK prototype
examples/ Shared example data
```

## C Reference CLI

Build with a C99 compiler:

```text
cc -std=c99 -Wall -Wextra -pedantic c/ngp.c c/ngp_cli.c -o ngp
```

On Windows with the installed portable GCC toolchain:

```text
gcc -std=c99 -Wall -Wextra -pedantic c/ngp.c c/ngp_cli.c -o ngp.exe
```

Run:

```text
./ngp
```

## Python

```text
python python/example.py
```

## Go

```text
cd go
go test ./...
go run ./cmd/ngp-example
```

## Rust

```text
cd rust
cargo test
cargo run --example factory
```

## Status

This is a prototype contract, not a final standard. The useful invariant is that each implementation returns:

- aggregate score
- per-scale contributions
- conflict count
- hard constraint failures

## Toolchain Notes

The prototype has been verified with:

- Go `1.26.3`
- Rust/Cargo `1.95.0`
- LLVM/Clang `22.1.6`
- Portable w64devkit GCC `16.1.0`
- Python `3.9.1`

Rust can be built with either the MSVC or GNU Windows toolchain, depending on the local environment.
