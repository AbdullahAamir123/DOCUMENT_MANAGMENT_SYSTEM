# Document Management System (DMS)
A console-based Document Management System written in C++ that allows users to receive, send, search, view, and delete documents. All data is persisted between sessions using file storage.

## Features
- Receive and send documents (.pdf, .jpg, .png, .txt)
- Search documents by serial number or title
- View all documents with type and status
- View statistics (total received/sent)
- Delete documents by serial number

## How to Compile & Run
```bash
g++ main.cpp -o dms
./dms
```

## Project Structure
```
DMS_Final/
├── main.cpp      # Entry point — menu loop only
├── library.h     # All classes and logic
└── docs.txt      # Auto-generated at runtime for persistence
```

## OOP Concepts Used
| Concept | Where Used |
|---|---|
| Encapsulation | Private data members in `Document` class with public getters |
| Abstraction | Pure virtual `show()` in `Document` base class |
| Inheritance | `PDFDoc`, `JPGDoc`, `PNGDoc`, `TXTDoc` all extend `Document` |
| Dynamic Polymorphism | Each subclass overrides `show()` differently; called via base pointer |
| Static Polymorphism | `search()` is overloaded for `int` (serial) and `string` (title) |
| Static Members | `totalReceived` and `totalSent` are shared across all instances |
| File Handling | Documents saved on exit and loaded on startup via `docs.txt` |

## Difficulties
- **Memory management without STL containers** — Using a raw array of base-class pointers (`Document* docs[100]`) required manual `new`/`delete` and careful shifting logic when deleting elements to avoid dangling pointers or memory leaks.
- **File persistence with polymorphism** — Saving and reloading polymorphic objects meant storing the type string explicitly so the correct subclass could be reconstructed on startup via the `makeDoc()` factory helper.
- **Static member initialization** — Static members (`totalReceived`, `totalSent`) must be defined outside the class body in C++, which is easy to forget and causes linker errors.
- **Input handling** — Mixing `cin >>` and `getline()` requires careful use of `cin.ignore()` to discard the leftover newline, otherwise subsequent `getline()` calls read an empty string.
