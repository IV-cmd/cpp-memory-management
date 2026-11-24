# cpp-memory-management

Phase 2 of my systems engineering notes: stack, heap, RAII, smart pointers, ownership, copy/move semantics and the Rule of Zero/Five in modern C++. Phase 1 is [cpp-language-foundations](https://github.com/IV-cmd/cpp-language-foundations).

## Curriculum

| Phase | Topic | Covers |
|---|---|---|
| 1 | [C++ Language Foundations](https://github.com/IV-cmd/cpp-language-foundations) | Compilation, types, pointers, references, functions, classes, object lifetimes, constructors, destructors, inheritance, polymorphism |
| **2** | **Memory Management and Modern C++** (this repo) | Stack, heap, RAII, smart pointers, ownership, move/copy semantics, Rule of Zero/Five |
| 3 | Concurrency and Multithreading | Threads, mutexes, locks, condition variables, atomics, memory ordering, race conditions, deadlocks, thread pools |
| 4 | Linux and Operating Systems | Processes, virtual memory, syscalls, file descriptors, filesystems, scheduling, signals, debugging |
| 5 | Storage Systems and Linux I/O | Block devices, page cache, buffered/direct I/O, `pread`/`pwrite`, `io_uring`, `fsync`, RAID, performance |
| 6 | Distributed Systems | Replication, consistency, quorum, consensus, failure detection, recovery, erasure coding, distributed metadata |

## Phase 2 modules

| # | Module |
|---|---|
| 1 | [Memory architecture](01-memory-architecture/) |
| 2 | [Object lifetime and storage duration](02-object-lifetime-storage-duration/) |
| 3 | [Dynamic memory allocation](03-dynamic-memory-allocation/) |
| 4 | [RAII](04-raii/) |
| 5 | [Ownership and resource management](05-ownership-resource-management/) |
| 6 | [`std::unique_ptr` and exclusive ownership](06-unique-ptr/) |

## Diagrams

Every diagram is a small HTML file in a module's `images/src/` folder. `python3 tools/diagrams/render.py` turns them into the PNGs in `images/` (it needs `pip install playwright`).
