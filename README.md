# Cultural Agenda Manager (Teatro de Bragança)

A modular, robust Command-Line Interface (CLI) application written in **C** to manage the cultural schedule, event scheduling, and ticket sales for the **Teatro de Bragança**.

This project was developed as a key practical assessment during the **1st Year, 1st Semester** of the **Informatics Engineering (Engenharia Informática)** program at the **Instituto Politécnico de Bragança (IPB)**.

---

## 🎯 Project Overview

The objective was to build a structured, error-resilient system capable of handling theater event registrations, managing seat capacities, preventing schedule overlapping, registering ticket transactions, and persisting agenda data locally across sessions using binary files.

### Key Features

* **Interactive CLI Menu**: An intuitive text-based control panel to guide users.
* **Smart Input Validation**: Rigorous runtime checks including leap year calculations, calendar date logic, and valid operational hours.
* **Conflict Prevention**: Time-collision logic that checks if a newly proposed event overlaps with an existing scheduled event on the same day.
* **Persistent Binary Storage**: Auto-saves state and loads records directly to and from a local binary file (`events.dat`) using serialization.
* **Event Filtering**: Instantly filters upcoming events by age rating (B6, B12, B16) that still have available seats.

---

## 🛠️ System Architecture & Modularity

The application is engineered using clean **modular programming principles**, breaking down concerns into distinct header and implementation files:

```
├── main.c              # Application entry point and menu router loop
├── eventlibrary.h      # Prototypes for core event & catalog management
├── eventlibrary.c      # Implementations of insertion, loading, saving, and booking
├── validation.h        # Data types (Structs/Enums) and validation signatures
└── validation.c        # Time arithmetic, calendar checks, and UI utility helpers

```

### Data Structures Built

* `Classification`: An `enum` representation for age restrictions (`B6 = 1`, `B12`, `B16`).
* `Date` & `Time`: Custom structures nested inside each other to handle chronological calculations with minute-level precision.
* `EventRegister`: The primary composite database record containing metadata like unique keys, names, date/time, duration, capacity limit, and active ticket balances.

---

## 💾 Technical Highlights (C Concepts Demonstrated)

1. **Structured Data Modeling**: Nested custom structures and type definitions (`typedef`).
2. **Binary File I/O**: Direct memory blocks saved to disk using standard binary stream manipulations (`fopen`, `fwrite`, `fread`, `fclose`).
3. **Pointers & Pass-by-Reference**: Memory addresses passed efficiently to update global program states (e.g., tracking tracking-pointer array updates via pointers like `int *num`).
4. **Custom Time Arithmetic**: Includes an implementation to normalize overflows (e.g., automatically converting `1h 90m` to `2h 30m` using modulo and integer division).
5. **Array Compaction**: Handled cancellation of records by shifting subsequent elements leftward and re-indexing keys gracefully.

---

## 🚀 How to Run the Project

### Prerequisites

A C compiler such as `gcc` or `clang` installed on your system.

### Compilation

Compile all modules together from your terminal:

```bash
gcc main.c eventlibrary.c validation.c -o CulturalAgenda

```

### Running the App

Execute the compiled binary:

```bash
./CulturalAgenda

```

Upon exiting the program through the menu option `0`, the application automatically updates or creates `events.dat` so that your database state is perfectly preserved for the next session.