# 🚇 Delhi Metro Path Finder & Route Optimizer

A C++ console-based project that finds the **shortest path and travel time** between metro stations in a city's metro system (e.g., Delhi Metro). It supports **dynamic station additions**, **interchange handling**, and **interactive route discovery** using graph algorithms.

---

## 🧠 Features

- ✅ **Shortest Path by Distance** using Dijkstra's algorithm  
- ✅ **Fastest Path by Time** with weighted graphs  
- ✅ **Input Validation** for non-existent stations or disconnected routes  
- ✅ **Interchange Station Detection** (e.g., Rajiv Chowk, Central Secretariat)  
- ✅ **Dynamic Graph Editing** – add new stations or edges at runtime  
- ✅ **Interactive CLI Menu** for user-friendly input/output  
- ✅ **Highlights Line Transfers** on route  
- ✅ **Handles Realistic Metro Network** like Delhi Metro

---

## 📌 Sample Input / Output


---

## 🛠 Technologies Used

- Language: **C++**
- STL Containers: `map`, `vector`, `set`, `priority_queue`
- Algorithms: **Dijkstra’s shortest path**
- Platform: CLI (Console-Based)

---

## ⚙️ How to Run

### Prerequisites
- C++ Compiler (e.g., g++)
- VS Code / Code::Blocks / Terminal

### Compile & Run

```bash
g++ metro.cpp -o metro
./metro

metro_project/
│
├── metro.cpp           # Main C++ file
├── README.md           # Project description
└── sample_input.txt    # Sample test cases (optional)
