# Example 3.31

<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.9.0/katex.min.css" integrity="sha384-TEMocfGvRuD1rIAacqrknm5BQZ7W7uWitoih+jMNFXQIbNl16bO8OZmylH/Vi/Ei" crossorigin="anonymous">
<script src="https://cdnjs.cloudflare.com/ajax/libs/KaTeX/0.9.0/katex.min.js" integrity="sha384-jmxIlussZWB7qCuB+PgKG1uLjjxbVVIayPJwi6cG6Zb4YKq0JIw+OMnkkEC7kYCq" crossorigin="anonymous"></script>

This part will provide an `alternative mathematic model` for calculate the probability of each outcome occurs at least one time.

Instead of using venn diagram to solve this problem, example 3.31 using `conditional probability` to calculate P(n,k), which `n` means the execution time, and `k` means the categories of outcome.

<!-- TOC -->

- [Example 3.31](#example-331)
    - [How to use](#how-to-use)
    - [Run the program](#run-the-program)
    - [Result](#result)
    - [Comparison/Time Complexity](#comparisontime-complexity)
    - [Author](#author)

<!-- /TOC -->

## How to use 

* Requirement
    * Linux - `ubuntu 16.04`
    * gnuplot 

* Testbed
    * categories of outcome: `5` (e.g. `range` in *example 2.5*)
    * testcase( for *example 2.5* simulation ): `10^6`
    * execution times( for *example 3.31* mathematic model ): `30`
        * When execution times increase, the more time will spend on this program.

* The testbed is built with Makefile, so just need to run `make` and all the program will be compile and run automatically.
    ```bash
    make
    ```

## Run the program

* Let's see the content in `Makefile`:
    * **First**:
        * Compile mathematic model program ( under `example 3.31` ) and the simulation program ( under `example 2.5` )
    * **Second**:
        * Similar to the demo in `example 2.5`, we run the simulation program first, and store the result into `simulation.output`.
        * And then run the mathematic model program, and directly pipe its output content into `mathematic.output`.
    * **Last**:
        * After generating all the result into output file with specified format, then we can using the gnuplot script - `result.gp` to plot the result into `PNG` format.

## Result

* As you can see the figure down below, the `simulation(red line)` and the `mathematic(green line)` have the similar curve.
    * Run with testcase `10^6`:
    ![](example3_31.png)

* That we can say this mathematic model has the correct answer!

## Comparison/Time Complexity

* We can now see the mathematic model between 2 example (e.g. `2.5` & `3.31`)

* *Mathematic model in `Example 2.5`:*

$$P\{X=N\} = \sum_{i=1}^m P_i (1-P_i)^{n-1} - \sum_{i<j} (P_i+P_j)(1-Pi-Pj)^{n-1} + \sum_{i<j<k} (P_i+P_j+P_k)(1-P_i-P_j-P_k)^{n-1} - \dots $$

* *Mathematic model in `Example 3.31`:*

$$P(m,r) = \sum_{j=1}^{m-r+1} P(m-j,r-1) \cdot C_j^m \cdot ( \frac{P_r}{\sum_{j=1}^{r} P_j})^j \cdot (1 - \frac{P_r}{\sum_{j=1}^{r} P_j})^{m-j}$$

$$Starting \ from: P(m,1) = 1, if \ m>=1 ; P(m,1) = 0, if \ m==0$$

## Author

* Kevin Cyu, kevinbird61@gmail.com