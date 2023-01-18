# Panacea

<!-- badges: start -->


<!-- badges: end -->

**Package name:** Portable ANalytical data Aggregation and Coordination
for database Entry and Access (panacea)

This package is currently a concept. See also the ISC proposal [1].

Panacea is aimed at making data streams in e.g. analytical laboratory 
settings more transparent and easily accessible. This is needed as 
closed sourced vendor-supplied software for analytical instruments often 
act as black boxes, thereby inhibiting access to raw data and 
full-disclosure of critical processing and transformations. 

Panacea would constitute at it most fundamental level a parser for text based
data in poorly structured formats (e.g. non-tabular). It detects variable, 
value, and, optionally, units triplets.

Ultimately, panacea could help establish fully integrated laboratories with 
centralised data management. Hence this solution contributes to the FAIR [2] 
guiding principles for data, thereby stimulating innovation, and inclusiveness 
through open science.

## Configure and build panacea

After copying the source files, start the build process of panacea as follows:

```
./configure
```
JSON for Modern C++ is needed to enable parsing of results into the JSON format. 
This can be achieved by cloning the nlohmann/json repository and performing a 
complete build. Alternatively one can just copy the header file json.hpp to your 
desired location and do the following during the build process:

```
./configure CXXFLAGS="-I/path/to/nlohmann/json.hpp"
```
Note, that the nlohmann/json.hpp is not a breaking build requirement for 
panacea. Results can alternatively be streamed to the terminal.

## Installation

To install panacea use the `install` target of the makefile, like so:

```
make install
```

To customise the installation query the GNU make manual [3].

## Basic usage

Currenlty, panacea only has four control options, wich can be modified with the
following flags:

- `--data`:  for the input text file (e.g. `test.txt`).
- `--output`:  for the output JSON file (e.g. `test.json`)
- `--white`:  the relative white level (a value in between 0 to 1) to detect 
tables (defaults to 0.7)
- `--verbose`: whether input filename and output results should be streamed to 
the terminal (defaults to 1)	

## Example

The source files contain an example text file (`extdata/test.txt`) to 
demonstrate the core functionality of panacea.

```
panacea --data "extdata/test.txt" --output. "extdata/test.json"
```

## References

[1]: https://github.com/FAIReLABS/isc-proposal-panacea    
[2]: Findable, Accessible, Interoperable, and Reusable    
[3]: https://www.gnu.org/software/make/manual