# Deterministic vs. Randomized Hash Tables: Security & Performance Analysis

This project explores the vulnerability of deterministic hash tables to "Algorithmic Complexity Attacks" (Denial of Service) and demonstrates how Universal Hashing fully mitigates this vulnerability while maintaining $O(1)$ performance. 

By running this project, you will compile and benchmark two distinct Hash Table implementations (V1 and V2) against Benign, Adversarial, and Avalanche datasets. You can then generate high-quality data visualizations comparing their performance up to 100,000 data elements.

## Prerequisites
- **C++ Compiler**: Clang, GCC, or MSVC (with C++17 support)
- **CMake**: Version 3.10 or higher
- **Python**: Python 3.8+ (for data visualization)

---

## 1. Building the Project
The core benchmarking logic is written in C++ and managed via CMake. 

1. Create a build directory and configure the project:
   ```powershell
   cmake -B build
   ```
2. Compile the executable:
   ```powershell
   cmake --build build --config Release
   ```

---

## 2. Running the Benchmarks
Once compiled, you can run the benchmarking suite. The program will:
- Generate a Benign payload (random alphanumeric strings).
- Generate an Adversarial payload (mathematically calculated hash collisions).
- Generate an Avalanche payload (mutated seed strings).
- Benchmark both insertions, lookups, and deletions across data sizes from 10,000 to 100,000.

Run the executable:
```powershell
.\build\experiment.exe
```

*Note: Because the adversarial dataset forces an $O(n)$ degradation on the deterministic hash table (V1), the final tests evaluating 100,000 elements will take a few moments to complete.*

The application will output all metric data to a new file named `benchmark_results.csv` in your root directory.

---

## 3. Generating the Visualizations
You can visualize the benchmarking results using the included Python script, which leverages the standard `csv` and `matplotlib` libraries to prevent OS-level DLL blocking issues.

1. Create a Python Virtual Environment:
   ```powershell
   python -m venv venv
   ```
2. Activate the Virtual Environment:
   - On **Windows**:
     ```powershell
     .\venv\Scripts\Activate.ps1
     ```
   - On **Mac/Linux**:
     ```bash
     source venv/bin/activate
     ```
3. Install the required visualization dependencies:
   ```powershell
   pip install matplotlib
   ```
4. Run the plotting script:
   ```powershell
   python plot_results.py
   ```

### Output
The Python script will parse the `benchmark_results.csv` and generate four high-resolution charts in the `plots/` directory:
- `max_chain_lengths.png`: A logarithmic bar chart comparing maximum collision counts.
- `lookup_time_degradation.png`: An $O(1)$ vs $O(n)$ search time comparison curve.
- `delete_time_degradation.png`: An $O(1)$ vs $O(n)$ deletion time comparison curve.
- `insert_time_degradation.png`: Total insertion overhead comparison.
