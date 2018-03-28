# Example 2.5

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

- [Example 2.5](#example-25)
    - [How to use?](#how-to-use)
    - [Run the program](#run-the-program)
    - [Result](#result)
    - [Author](#author)

<!-- /code_chunk_output -->

## How to use?

* Requirement
    * Linux - `ubuntu 16.04`
    * gnuplot
    ```bash
    sudo apt install gnuplot build-essential
    ```

* Compile and run the default testcase: 
    * range: `1~5`
    * testcase: **`100`**
    ```bash
    make
    ```

## Run the program

* Let's see the content in `Makefile`:
    * First, compile and generate `sim.out` for simulation program, and `math.out` for mathematic model program.
    ```Makefile
    # compile the simulation
    g++ simulation.cc -o sim.out -I../utils -std=c++11
    # compile the mathematic proof
    g++ mathematic.cc -o math.out -std=c++11 
    ```
    * Second, run the program of `sim.out` and `math.out` to generate the simulation result and mathematic result.
        * In this step, specify the range upperbound (e.g. `-m`) and X (e.g. P{`X`>N}) in `sim.out`, with default testcase = `100`
        * If you want to generate the result with large testcase, you can specify the number with argument `-n [large_testcase]`, for example : "`./sim.out -m 5 -x 10 -n 1000000`"
        * And run the `math.out`, only using argument without specify parameter flag, and parse out the first line of the result `simulation.output` which generated from `sim.out`, to get the **MAXIMUM** value to set the upperbound, and then `math.out` will generate the output file `mathematic.output`
    ```Makefile
    # Feed the testdata
    # Run the simulation first: 
    ./sim.out -m 5 -x 10 
    # generate with large testcase
    #./sim.out -m 5 -x 10 -n 10^6
    # And then get the maximum, to generate the mathematic result
    ./math.out 10 $$(head -1 simulation.output | awk '{print $$4}')
    ```
    * Last step, after generating all the results (e.g. `simulation.output`, `mathematic.output`), we can use `gnuplot` to generate the line chart from these 2 files.
    ```Makefile   
    # Using gnuplot the plot
    gnuplot simulation.gp
    ```
    * After gnuplot plotting process, we now can open the line chart image `simulation.png`
    ```bash
    > eog simulation.png
    ```


## Result 

* As you can see the figure down below, the `simulation(red line)` and the `mathematic(green line)` have the similar curve.
    ![](simulation.png)

* And then we increase the testcase to **`10^6`** (run with `./sim.out -m 5 -x 10 -n 1000000`):
    ![](simulation_large.png)
    * You can see it's more fit with the curve from mathematic model!

## Difference (TODO)

* Measure the difference between simulation and mathematic result!

```
Difference = 100%×(Simulation - Math) / Math
```

## Author

* Kevin Cyu, kevinbird61@gmail.com