## Student Record Keeping System (Modernized)

A modular C application for managing simple student records using a binary file.
This refactor modernizes the original single-file program into clear modules with
headers, adds a portable Make-based build, and documents usage and development.

### Features
- **Add records**: single or bulk input
- **List students**: tabular summary of roll and name
- **Search by roll**: then edit, delete, or view a marksheet
- **Binary storage**: fast, simple file-backed store (`rex.txt`)

### Project structure
- `include/` — public headers
  - `record.h` — data model and file operations API
  - `ui.h` — CLI helpers and prompts
- `src/` — implementation
  - `record.c` — binary file read/write/update/delete
  - `ui.c` — interactive prompts, input parsing, printing
  - `main.c` — program entry and menu loop
- `Makefile` — portable build, run, and clean targets
- `bin/` — compiled binary output (created by the build)

### Build
Requires `gcc` (or a compatible C compiler) and `make`.

```bash
make
```

This produces the binary at `bin/student_records`.

### Run
```bash
make run
```

Or run directly:

```bash
./bin/student_records
```

### Data file
- Records are stored in a binary file named `rex.txt` (kept for backward compatibility).
- You can safely move or back up this file; the app will recreate it if missing when adding records.

### Usage (CLI)
Main menu options:
1. Add a record
2. Add Bulk Records
3. List Students
4. Search Student (then: Edit, Delete, or View Marksheet)
5. Quit

Input is validated for numbers; names can contain spaces.

### Development notes
- C standard: C11 (`-std=c11`), with warnings enabled (`-Wall -Wextra -Wpedantic`).
- Code is split into `record` (storage) and `ui` (interaction) modules for clarity.
- Functions and data types are documented in headers; implementation favors readable, straightforward control flow.

### License
No license specified by the original project. Add one if you plan to distribute.
