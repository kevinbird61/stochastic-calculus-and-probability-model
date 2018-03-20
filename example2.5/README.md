# Example 2.5

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

* [Example 2.5](#example-25)
	* [How to use?](#how-to-use)
	* [Result](#result)
	* [Author](#author)

<!-- /code_chunk_output -->

## How to use?

* Requirement
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

## Result 

* As you can see the figure down below, the `simulation(red line)` and the `mathematic(green line)` have the similar curve.
    ![](simulation.png)

* And then we increase the testcase to **`10^6`**:
    ![](simulation_large.png)
    * You can see it's more fit with the curve from mathematic model!

## Author

* Kevin Cyu, kevinbird61@gmail.com