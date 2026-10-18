# Small Language Model (SLM)

## Overview

This project implements a Small Language Model (SLM) in C++17 using *k-grams* to learn character-level patterns from a training text.

The program analyzes a training text to calculate:
- The frequency of each k-gram.
- The conditional probability of each character occurring after a given k-gram.

Using these probabilities, the program generates new text by selecting a starting k-gram and repeatedly sampling the next character from the learned probability distribution.

## Requirements

- A C++ compiler that supports C++17.
- GNU Make to build the project using the provided Makefile.

## Compilation

Compile the program using GNU Make:

```bash
make
```

To remove the generated executable, run:

```bash
make clean
```

## Usage

The program accepts the following command-line arguments:

```text
slm [-a alpha] k training_file output_length
```

| Argument | Description |
|---|---|
| `-a alpha` | Optional non-negative pseudocount for additive smoothing. Defaults to `0`. |
| `k` | Integer specifying the length of each k-gram. |
| `training_file` | Path to the text file used to train the model. |
| `output_length` | Number of characters to generate. |

### Examples

Generate 100 characters using k-grams of length 3, without smoothing:

```bash
./slm 3 src/input_texts/moby_dick.txt 100
```

Use a pseudocount of `0.5`:

```bash
./slm -a 0.5 3 src/input_texts/moby_dick.txt 100
```

## How It Works

### 1. Training the Model

`GramFrequency` reads the training file and records the frequency of each k-gram, along with the characters that follow each k-gram.

### 2. Calculating Probabilities

For a k-gram \(g\) and a character \(c\), the conditional probability is estimated from the observed transition counts.

When additive smoothing is enabled, the probability is calculated as

\[
P(c \mid g) = \frac{N(g,c)+\alpha}{N(g)+\alpha |A|}
\]

where:
- \(N(g,c)\) is the number of times character \(c\) follows k-gram \(g\).
- \(N(g)\) is the total number of observed transitions following \(g\).
- \(\alpha\) is the pseudocount.
- \(|A|\) is the size of the alphabet observed in the training text.

When \(\alpha = 0\), the model uses the observed transition frequencies without smoothing.

### 3. Generating Text

`TextGenerator` selects an initial k-gram according to its frequency, then repeatedly samples the next character using the conditional probability distribution. The generated text grows one character at a time until the requested length is reached or no valid next transition is available.