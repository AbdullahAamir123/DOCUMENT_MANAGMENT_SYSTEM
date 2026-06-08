# 📁 Document Management System (DMS)

A console-based **Document Management System** written in C++ that lets you receive, send, search, view, and delete documents — with automatic persistence between sessions via file storage.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compile & Run](#compile--run)
- [Usage](#usage)
- [OOP Concepts Demonstrated](#oop-concepts-demonstrated)
- [Known Challenges](#known-challenges)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

DMS is a C++ terminal application built around a clean object-oriented design. Documents are typed (PDF, JPG, PNG, TXT), assigned a serial number automatically, and saved to `docs.txt` on exit so data is retained across sessions.

---

## Features

| # | Feature |
|---|---------|
| 1 | **Receive** a document — auto-assigns a serial number and sets status to `received` |
| 2 | **Send** an existing document — updates its status to `sent` |
| 3 | **Search by serial number** (integer overload) |
| 4 | **Search by title** (string overload) |
| 5 | **View all documents** with type, serial, and status |
| 6 | **Statistics** — total received and sent counts |
| 7 | **Delete** a document by serial number |
| 8 | **Persistent storage** — loaded on startup, saved on exit via `docs.txt` |

Supported file types: `.pdf` `.jpg` `.png` `.txt`

---

## Project Structure

```
DMS_Final1/
├── main.cpp       # Entry point — menu loop only
├── library.h      # All classes and business logic
├── docs.txt       # Auto-generated at runtime for persistence
└── README.md      # This file
```

### Class Hierarchy

```
Document  (abstract base)
├── PDFDoc
├── JPGDoc
├── PNGDoc
└── TXTDoc

Manager   (owns Document* docs[100], handles all operations)
```

---




- A C++ compiler supporting **C++11** or later (e.g. `g++`, `clang++`)
- A terminal / command prompt

### Compile & Run

```bash
# Compile
g++ main.cpp -o dms

# Run
./dms
```

On Windows (MinGW / MSVC):

```bash
g++ main.cpp -o dms.exe
dms.exe
```

---

## Usage

Once running, the program presents an interactive menu:

```
  === DOCUMENT MANAGEMENT SYSTEM ===
  Supported: .pdf  .jpg  .png  .txt

  1. Receive Document
  2. Send Document
  3. Search by Serial Number
  4. Search by Title
  5. View All Documents
  6. View Statistics
  7. Delete Document
  8. Exit
  Choice:
```

**Example session:**

```
Choice: 1
Enter filename (e.g. report.pdf): thesis.pdf
  Document received. Serial #1

Choice: 5
  [PDF]   #1  |  thesis.pdf  |  received

Choice: 2
Enter filename to send (e.g. photo.jpg): thesis.pdf
  Document sent. Serial #1

Choice: 6
  Total Received : 1
  Total Sent     : 1
```

> `docs.txt` is created automatically in the working directory and stores all document records between sessions.

---

## OOP Concepts Demonstrated

| Concept | Where Applied |
|---|---|
| **Encapsulation** | Private data members (`serial`, `title`, `type`, `status`) in `Document` with public getters |
| **Abstraction** | Pure virtual `show()` in the `Document` base class |
| **Inheritance** | `PDFDoc`, `JPGDoc`, `PNGDoc`, `TXTDoc` all extend `Document` |
| **Dynamic Polymorphism** | Each subclass overrides `show()` differently; called through a `Document*` base pointer |
| **Static Polymorphism** | `Manager::search()` is overloaded — one version takes `int` (serial), another takes `string` (title) |
| **Static Members** | `totalReceived` and `totalSent` are class-level counters shared across all instances |
| **File Handling** | Documents are saved to `docs.txt` on exit and restored on startup via a factory helper (`makeDoc()`) |

---

## Known Challenges

### Memory management 
Using a raw array of base-class pointers (`Document* docs[100]`) required manual `new`/`delete` and careful shifting logic on deletion to avoid dangling pointers or memory leaks.



### Static member initialization
Static members (`totalReceived`, `totalSent`) must be defined outside the class body in C++. Forgetting this causes linker errors.

### Input handling
Mixing `cin >>` with `getline()` requires careful use of `cin.ignore()` to discard the leftover newline, otherwise subsequent `getline()` calls read an empty string.

---



