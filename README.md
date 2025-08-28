# Peregrinations

**A hybrid C++ / ML project comparing classical and machine learning approaches for the Traveling Salesman Problem (TSP).**

## Project Overview

This repository is designed to explore and compare different methods for solving the TSP:

- **Classical solvers** (exact algorithms, heuristics) implemented in **C++** for performance.  
- **Machine learning models** (GNN, Pointer Networks, Transformers) trained in **Python** and exported to **TorchScript** for inference in C++.  

The primary goals are:

1. Benchmark classical vs. ML-based solvers in terms of **solution quality** and **execution time**.  
2. Maintain a clean separation between **high-performance C++ code** and **flexible Python ML training**.  
3. Provide a reproducible pipeline for generating **synthetic TSP instances**.

---

## Build Instructions (C++)

**Prerequisites**: Linux, C++17 compiler (g++ >= 9 or clang >= 10), CMake >= 3.16, cuda-toolkit >= 12.6, LibTorch >= 12.6.
  

Because this project uses CUDA to improve computational time, you will need to install cuda-toolkit and LibTorch **(make sure they are the same version, e.g 12.6)**. You may unzip the LibTorch folder in the root directory.


Once everything is installed, you can run these commands:
```bash
mkdir -p build && cd build
cmake -DCMAKE_CUDA_COMPILER=/usr/local/cuda-12.6/bin/nvcc -DCMAKE_PREFIX_PATH=../libtorch ..
make
```

This will generate the executable tsp_gen in /build/.


## Usage

Generate synthetic TSP instances:

```.tsp_gen --n 50 --seed 42 --out data/synthetic_points.csv ```

Options:
- `--n <int>`: number of cities (default: 50)
- `--seed <int>`: random seed (default: 0)
- `--out <dir>`: output directory (default: `data/synthetic_points.csv`)

## Next steps

1. Implement **classical heuristics** (Nearest Neighbor, 2-opt)
2. Implement a **benchmark framework** to compare classical vs ML solutions
3. Integrate **TorchScript ML inference** into C++ core
4. Add GNN-based or RL solvers for TSP