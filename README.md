# coreutils
Unix core utilities implemented from scratch. The goal is to create a the full set of coreutils in modern C99 based on the UNIX v1 spec.
A simple shell as well as basic file manipulation tools are already done, not sure if they are up to spec because I do not have access to documentation (yet).

To compile simple run `make` and everything will compile to `./bin`. Before running `sh`, append `./bin` to you `PATH` with `PATH="${PATH}:${HOME}/.local/bin"`.
