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

```bash
./configure
```
JSON for Modern C++ is needed to enable parsing of results into the JSON format. 
This can be achieved by cloning the nlohmann/json repository and performing a 
complete build. Alternatively one can just copy the header file json.hpp to your 
desired location and do the following during the build process:

```bash
./configure CXXFLAGS="-I/path/to/nlohmann/json.hpp"
```
Note, that the nlohmann/json.hpp is not a breaking build requirement for 
panacea. Results can alternatively be streamed to the terminal.

## Installation

To install panacea use the `install` target of the makefile, like so:

```bash
make install
```

To customise the installation query the GNU make manual [3].

## Basic usage

Currenlty, panacea only has four control options, wich can be modified with the
following flags:

- `--data`:  for the input text file (e.g. `test.txt`).
- `--output`:  for the output JSON file (e.g. `test.json`)
- `--white`:  the relative white level (a value in between 0 and 1) to detect 
tables (defaults to 0.7)
- `--verbose`: whether input filename and output results should be streamed to 
the terminal (defaults to 1)	

## Example

The source files contain an example text file (`extdata/test.txt`) to 
demonstrate the core functionality of panacea.

```bash
panacea --data "extdata/test.txt" --output. "extdata/test.json"
```
<!-- convert -size 570x690 xc:white -font "FreeMono" -pointsize 12 -fill black -annotate +15+15 "@extdata/test.txt" extdata/test.png -->

**Input text file:**

<img src="extdata/test.png" width="1000" />

**Output json file:**   
*Parsed as a table for convenience*

| **Variable** | **Value**       | **Unit** | **Textfield** | **Linenumber** | **Characternumber** |
|--------------|-----------------|----------|---------------|----------------|---------------------|
| foo          | a,b,c,d         |          | 2             | 5,6,7,8,9      | 1,1,1,1             |
| bar          | 5,6,7,8         |          | 2             | 5,6,7,8,9      | 7,7,7,7             |
| baz          | x,y,z,z         |          | 2             | 5,6,7,8,9      | 13,13,13,13         |
| qux          | 1,2,3,4         | s        | 2             | 5,6,7,8,9      | 19,19,19,19         |
| quz          | x,z,,           |          | 2             | 5,6,7,8,9      | 29,29,32,32         |
| x            | 42e-3,42e-3     |          | 3             | 12,13,14       | 1,1                 |
| y            | 4.3e-02,4.3e-02 |          | 3             | 12,13,14       | 9,9                 |
| z            | 4.4e-01,4.4e-01 |          | 3             | 12,13,14       | 19,19               |
| numeric      | 42              |          | 4             | 24             | 1                   |
| numeric      | 42              | um       | 5             | 25             | 1                   |
| foo          | 42              |          | 6             | 26             | 1                   |
| bar          | -41             |          | 7             | 26             | 11                  |
| baz          | 40              |          | 8             | 26             | 23                  |
| foo          | 42              |          | 9             | 27             | 1                   |
| bar          | -41             |          | 10            | 27             | 11                  |
| baz          | 40              |          | 11            | 27             | 22                  |
| foo          | 42              |          | 12            | 28             | 1                   |
| bar          | -41             |          | 13            | 28             | 11                  |
| baz          | 40              |          | 14            | 28             | 23                  |
| x            | -12761          | um       | 15            | 29             | 23                  |
| y            | -13469          | um       | 16            | 29             | 59                  |
| z            | 3709            | um       | 17            | 29             | 73                  |
| x            | 1               | um       | 18            | 30             | 21                  |
| y            | 2               | um       | 19            | 30             | 50                  |
| z            | 3               | um       | 20            | 30             | 59                  |
| x            | 4               | um       | 21            | 30             | 89                  |
| x            | -12761          | um       | 22            | 31             | 42                  |
| y            | -13469          | um       | 23            | 31             | 97                  |
| z            | 3709            | um       | 24            | 31             | 111                 |
| numeric      | 42              |          | 25            | 32             | 14                  |
| LoremIpsum   | 42              | numeric  | 26            | 33             | 1                   |
| LoremIpsum   | 42              | numeric  | 27            | 34             | 1                   |
| LoremIpsum   | 42              | numeric  | 28            | 35             | 1                   |

## References

[1]: https://github.com/FAIReLABS/isc-proposal-panacea    
[2]: Findable, Accessible, Interoperable, and Reusable    
[3]: https://www.gnu.org/software/make/manual