# Batched Post Analyser

A coursework-based C++ application for storing posts in batches,
removing posts by like count, and finding the post with the smallest
like count strictly above a given threshold.

The project combines generic merge sort, a linked list of batches,
and AVL trees.

## Features

- Add fixed-size batches of posts
- Sort each incoming batch by like count
- Build a balanced tree from each sorted batch
- Remove one matching post by like count
- Find the smallest like count strictly greater than a threshold
- Rebalance trees after deletion

## How It Works

1. Copy and sort an incoming batch using merge sort.
2. Build an AVL tree from the sorted records.
3. Store the batch tree in a linked list.
4. Search each tree for its smallest value above the threshold.
5. Return the smallest candidate across all batches.

## Tech Stack

- C++11 or later
- Standard C++ library
- Template-based data structures and algorithms
- No third-party libraries required

## Project Structure

```text
.
├── code.cpp             # Post model, batch analyser, and CLI
├── algorithms.h         # Generic merge sort
├── data_structures.h    # Linked list and AVL tree
├── .gitignore
└── README.md
```

## Build and Run

From the repository root:

```bash
mkdir -p build
c++ -std=c++17 -Wall -Wextra code.cpp -o build/post-analyser
./build/post-analyser demo
```

The original coursework entry point requires a command-line argument
to start the interactive menu. Here, `demo` is a placeholder argument;
its value is not inspected.

Running the executable without an argument exits without showing
the menu.

## Example Session

1. Enter a batch size of `3`.
2. Select `1` to add a batch.
3. Enter these like counts and names:
   - `10`, `Alpha`
   - `30`, `Beta`
   - `20`, `Gamma`
4. Select `3` and enter a threshold of `15`.
   Expected result: `Post found with 20 likes`.
5. Select `2` and remove a post with `20` likes.
6. Query threshold `15` again.
   Expected result: `Post found with 30 likes`.
7. Query threshold `30`.
   Expected result: `No such post exists`.
8. Select `5` to quit.

## Complexity

Let n be the fixed batch size and b the number of stored batches.

| Operation | Time complexity |
| --- | --- |
| Sort an incoming batch | O(n log n) |
| Build a balanced tree from a sorted batch | O(n) |
| Add a batch overall | O(n log n) |
| Threshold query across all batches | O(b log(n + 1)) |
| Remove a post across batches, worst case | O(b log(n + 1)) |

The bounds rely on maintaining balanced trees.

## Validation

Compiled locally with Clang using C++17.

A scripted smoke check verified:

- Adding one batch containing three posts
- Finding the smallest like count above a threshold
- Deleting a post and querying again
- Returning no match when no post exceeds the threshold

This is a limited smoke check, not a comprehensive test suite.
Compilation reports an unused `argv` parameter warning.

## Current Limitations

- Batch size must be a positive integer; validation needs improvement.
- Post names entered through the CLI cannot contain spaces.
- Posts are compared by like count, not by name or unique ID.
- When like counts are duplicated, deletion removes one matching post.
- Records are stored in memory and are not saved after exit.
- Owning data structures use raw pointers and should not be copied.
- Broader tests are needed for duplicate values and repeated deletions.

## Project Background

Developed as part of FIT1008 C2: Batched Queries.

This repository presents a coursework implementation for learning
data structures, algorithm design, and complexity analysis.
