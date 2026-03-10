# Hack Assembler

A C++ implementation of an assembler for the 16-bit Hack computer architecture, based on the specifications from "The Elements of Computing Systems" (Nand2Tetris).

## Overview

This program translates assembly code written in the Hack language into binary machine code that can be executed by the Hack computer. It processes both A-instructions (addressing) and C-instructions (computation), handling symbolic labels and variables according to the Hack specification.

## Features

- **Two-pass assembly**: First pass builds symbol table, second pass generates machine code
- **Symbol resolution**: Handles predefined symbols, labels, and variables
- **Comprehensive error handling**: Detects syntax errors and invalid instructions
- **Binary output**: Generates 16-bit machine code in text format (one instruction per line)
- **Configurable**: Supports custom symbol tables and output formats

## Input/Output

- **Input**: `.asm` file containing Hack assembly code
- **Output**: `.hack` file containing 16-bit binary machine code

## Usage

```bash
./hack_assembler path/to/program.asm
```

## Implementation Details

- Written in modern C++ (C++17)
- Object-oriented design with classes for symbol table, parser, and code generator
- Efficient string handling and memory management
- Modular architecture for easy testing and extension

Perfect for anyone working through the Nand2Tetris course or building their own Hack computer implementation!