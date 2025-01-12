# Homework 3

> Due: 11-24-2024 11:59:59 PM

**Topics**: Quick Sort

## Table of Contents

- [Homework 3](#homework-3)
  - [Table of Contents](#table-of-contents)
  - [Homework Spec](#homework-spec)
    - [Grading](#grading)
    - [Submission](#submission)
  - [Setup](#setup)
    - [Option 1: VS Code with Local Dev Container](#option-1-vs-code-with-local-dev-container)
    - [Option 2: VS Code with Remote Dev](#option-2-vs-code-with-remote-dev)
    - [Option 3: Terminal](#option-3-terminal)
  - [Run/Debug](#rundebug)
    - [Run tests using VS Code](#run-tests-using-vs-code)
    - [Run tests using Terminal](#run-tests-using-terminal)

> ⚠️ DO NOT change files marked with
>
> ```cpp
> // DO NOT CHANGE THIS FILE
> ```

## Homework Spec

In this homework, you will write a template function that implements Quick Sort
with randomized pivot selection.

### Grading

You will be graded only on the same (hidden) test cases your TAs created. The
test includes correctness and performance tests. The performance tests will be
graded based on the running time of your implementation.

We provided some tests cases in [./tests](./tests). Feel free to modify and add
more test cases, but the [./tests](./tests) in your submission will not be
graded. However, you will be able to see the results for your submitted test
cases on Gradescope.

### Submission

Use `./generate_submission.sh` and submit `hw3-submission.zip` on Gradescope.

## Setup

Use one of the following options to set up your environment.

> ⚠️ If you're a student, **DO NOT FORK** this repository because you cannot
> change the visibility of a forked repo to private. If you plan to use Git for
> version control (which is encouraged), run `rm -rf .git && git init` after
> setting up using one of the options below and push to your **private**
> repository. Any public repository containing part of this homework solution
> will be reported to SJA.

### Option 1: VS Code with Local Dev Container

- If Docker is not running, start Docker.

- Click the following button to set up the environment.

  [![Setup Local Dev Container](https://img.shields.io/static/v1?label=Local%20Dev%20Container&message=Setup&color=blue&logo=visualstudiocode)](https://vscode.dev/redirect?url=vscode://ms-vscode-remote.remote-containers/cloneInVolume?url=https://github.com/ecs36c-fq2024/hw3)

- When asked for selecting a Kit to configure CMake, choose **GCC**.

### Option 2: VS Code with Remote Dev

- Connect VS Code to the remote host.

- Install **C/C++ Extension Pack** on Remote Server (if not already).

- Run the following command inside the integrated terminal.

  `git clone https://github.com/ecs36c-fq2024/hw3 ecs36c-hw3`

- Run `code ./ecs36c-hw3` to open the folder.

- When prompted to configure CMake, confirm and choose **GCC** when prompted for
  kit selection.

### Option 3: Terminal

- Run the following commands

  ```bash
  git clone https://github.com/ecs36c-fq2024/hw3 ecs36c-hw3
  cd ./ecs36c-hw3
  mkdir build
  cd build
  cmake ..
  ```

## Run/Debug

### Run tests using VS Code

Run -> Start Debugging

### Run tests using Terminal

```bash
cd build
make
./run_tests
```
