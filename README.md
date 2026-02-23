# TTbar Black Hole Analysis

High-energy physics analysis framework for studying top-antitop quark pair production with black hole contributions at 100 TeV center-of-mass energy.

## Overview

This project implements a complete analysis pipeline for ttbar production events with potential black hole signals. It processes Large Hadron Collider (LHC) simulation data from LHE (Les Houches Event) format to ROOT format and performs physics analysis.

**Key Features:**
- Automated LHE to ROOT event conversion
- Physics-based event selection and analysis
- Support for multiple theoretical predictions (PQCD LO, PQCD NLO, Black Hole models)
- CMake-based build system for cross-platform compatibility
- Configurable analysis parameters and cross-section weights

## Requirements

### System Dependencies
- **C++ Compiler:** GCC 11+ or Clang 12+ (C++17 support required)
- **CMake:** Version 3.10 or higher
- **ROOT Framework:** Version 6.30+ (built with C++17)
  - Download from: https://root.cern/
  - Ensure `root-config` is in your PATH

### Optional
- **Make:** For building with CMake
- **Python 3.7+:** For LHE conversion utilities

## Installation

### 1. Install ROOT Framework

```bash
# Download and install ROOT (example with v6.36)
wget https://root.cern/download/root_v6.36.02.Linux-ubuntu22.04-x86_64-gcc11.4.tar.gz
tar xzf root_v6.36.02.Linux-ubuntu22.04-x86_64-gcc11.4.tar.gz
source root/bin/thisroot.sh
```

Alternatively, use your system's package manager:
```bash
# Ubuntu/Debian
sudo apt-get install root-system-dev root-ttree-dev

# Fedora
sudo dnf install root root-devel
```

### 2. Clone the Repository

```bash
git clone https://github.com/danernani2-spec/ttbar_BH_analysis.git
cd ttbar_BH_analysis
```

## Building

The project uses CMake for configuration and compilation.

### Standard Build

```bash
# Create and enter build directory
mkdir -p build && cd build

# Configure with CMake
cmake ..

# Compile (using 4 parallel jobs)
make -j4
```

### Clean Build

```bash
cd build
rm -rf *
cmake ..
make
```

### Build Options

```bash
# Verbose compilation output
cmake -DCMAKE_VERBOSE_MAKEFILE=ON ..

# Release build with optimization
cmake -DCMAKE_BUILD_TYPE=Release ..

# Debug build with symbols
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

## Running the Analysis

### Single Event Processing

```bash
# From the source directory
cd source/
./top_inclusive_withBH_overlay <input.root> <output.root> <cross_section>
```

**Parameters:**
- `<input.root>`: Input ROOT file with LHE events (converted)
- `<output.root>`: Output analysis ROOT file
- `<cross_section>`: Cross-section weight (in picobarns)

**Example:**
```bash
./top_inclusive_withBH_overlay data.root analysis.root 1.88467E+04
```

### Automated Analysis Suite

Run all standard analyses:

```bash
cd run/
./run_all.sh
```

This script processes:
- **PQCD LO** (100 TeV): 5M events, σ = 1.88467E+04 pb
- **PQCD NLO** (100 TeV): 5M events, σ = 2.81E+04 pb  
- **Black Hole** (n=6, M_D=4 TeV, M_BH=8 TeV): σ = 6.7979721E+02 pb

All output files are saved to the `output/` directory.

## Project Structure

```
ttbar_BH_analysis/
├── CMakeLists.txt              # CMake build configuration
├── README.md                   # This file
├── .gitignore                  # Git ignore rules
│
├── source/
│   └── top_inclusive_withBH_overlay.cpp    # Main analysis code
│
├── run/
│   └── run_all.sh             # Automated analysis script
│
├── build/                      # Build directory (generated)
│   ├── CMakeCache.txt
│   ├── CMakeFiles/
│   └── Makefile
│
├── input_root/                # Input ROOT files
│   ├── pqcd_LO_100tev_5M_converted.root
│   ├── pqcd_NLO_100tev_5M_converted.root
│   └── 100tev_n6_md4_mbh8_converted.root
│
├── input_lhe/                 # Input LHE files
│   └── *.lhe
│
├── output/                    # Analysis output
│   └── analysis_*.root
│
└── lhe-to-root-master/        # LHE conversion utilities
    ├── LHEConverter.py
    ├── Event.py
    └── read_lhe_tree.cpp
```

## Data Format

### Input: LHE (Les Houches Event)
Standard event format for particle physics simulations. Each event contains:
- Particle four-momenta
- Particle species and status codes
- Interaction weights and scales

### Output: ROOT TTree
ROOT binary format containing:
- Event selection flags
- Kinematic variables (pT, η, φ)
- Invariant masses
- Cross-section weights

## Compilation Details

The build system:
1. **Detects ROOT installation** via `root-config`
2. **Enforces C++17 standard** for compatibility
3. **Links ROOT libraries** (Core, Tree, Hist, Physics)
4. **Generates optimized executable** with `-O2` flag

Build artifacts:
- **Object files:** `build/CMakeFiles/top_inclusive_withBH_overlay.dir/`
- **Executable:** `source/top_inclusive_withBH_overlay`
- **Symbolic information:** Used for debugging with `-g` flag

## Physics Analysis

### Event Selection
- Top quark pair reconstruction
- Lepton isolation and identification
- Jet clustering and b-tagging
- Missing energy requirements

### Theoretical Predictions
- **PQCD LO/NLO:** Standard Model ttbar production
- **Black Hole Models:** Extra-dimensional scenarios (Randall-Sundrum, ADD)
- **Cross-section Weights:** Automatic normalization per dataset

### Output Variables
- Reconstructed top mass (M_tt)
- Top quark transverse momentum
- Angular distributions
- Missing transverse energy

## Troubleshooting

### CMake Configuration Fails
```bash
# Verify ROOT installation
root-config --version
root-config --cflags
root-config --libs

# If root-config not found, set paths:
export PATH=/path/to/root/bin:$PATH
```

### C++ Standard Mismatch
```
Warning: The C++ standard in this build does not match ROOT configuration
```
**Solution:** Ensure ROOT was built with C++17:
```bash
root-config --cflags | grep -o '\-std=.*'
```

### Compilation Errors
```bash
# Clean build
cd build && rm -rf * && cmake .. && make

# Verbose output
make VERBOSE=1
```

### Runtime Issues
```bash
# Verify ROOT libraries
ldd ./source/top_inclusive_withBH_overlay

# Run in debug mode
./source/top_inclusive_withBH_overlay --help
```

## Performance

**Typical Performance:**
- **Analysis Speed:** ~100k events/minute (single core)
- **Memory Usage:** ~500 MB per analysis process
- **5M Event Dataset:** ~50 minutes per dataset

**Optimization Tips:**
- Use parallel make: `make -j4`
- Enable optimizations: `-DCMAKE_BUILD_TYPE=Release`
- Process datasets sequentially or on computing cluster

## Contributing

Found issues or have suggestions?
1. Fork the repository
2. Create a feature branch
3. Make your improvements
4. Submit a pull request

## References

### Physics Papers
- CMS Collaboration: Top Pair Production Studies
- ATLAS Collaboration: Black Hole Production at LHC
- Extra Dimensions in High-Energy Physics

### Tools & Libraries
- **ROOT:** https://root.cern/
- **CMake:** https://cmake.org/
- **LHE Format:** https://lhapdf.hepforge.org/

## License

This project is released under the MIT License. See LICENSE file for details.

## Author

**Dan Ernani** - High Energy Physics Analysis
- GitHub: [@danernani2-spec](https://github.com/danernani2-spec)
- Project: [ttbar_BH_analysis](https://github.com/danernani2-spec/ttbar_BH_analysis)

## Acknowledgments

- ROOT Team for the excellent data analysis framework
- CMS and ATLAS collaborations for event simulation standards
- High energy physics community for theoretical predictions
