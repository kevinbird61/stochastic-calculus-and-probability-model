# Stochastic Calculus
Record the learning materials of the course - "stochastic calculus" in National Cheng Kung University.

![](res/ncku.jpg)

> **Before starting to read this article, please install chrome extension: [`Github with MathJax`](https://chrome.google.com/webstore/detail/github-with-mathjax/ioemnmodlmafdkllaclgeombjnmnbima/related), to ensure the correctness of formula format.**

- [Stochastic Calculus](#stochastic-calculus)
    - [Practice Cases](#practice-cases)
        - [Example 2.5 (See more)](#example-25-see-more)
        - [Example 3.31 (See more)](#example-331-see-more)
        - [Poisson Distribution (See more)](#poisson-distribution-see-more)
        - [Random Access Problem in Machine-to-Machine (See more)](#random-access-problem-in-machine-to-machine-see-more)
        - [Compound Random Variables](#compound-random-variables)
    - [Some useful self-defined libraries](#some-useful-self-defined-libraries)
- [Author](#author)

Mostly use **`C++`** to do both simulation/mathematic work and validation.

> Develop environment requirement:
> 
> - Operating System : `ubuntu 16.04`
> 
> |  | version |
> | ------ | ------ |
> | gnuplot | version 5.0 patchlevel 3 |
> | g++ | gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9) | 
> | make | GNU Make 4.1 |
> | astyle | Artistic Style Version 2.05.1 | 

## Practice Cases

### [Example 2.5 (See more)](example2.5/)

| Normal case | Increased simulation times |
| ------ | ------ |
| ![](example2.5/simulation.png) | ![](example2.5/simulation_large.png) |

---

### [Example 3.31 (See more)](example3.31/)

![](example3.31/example3_31.png)

---

### [Poisson Distribution (See more)](poisson_distribution/)

| | Merge Poisson Process | Split Poisson Process | 
| ------ | ------ | ------ |
| Mathematic | ![](poisson_distribution/image/part_a.png) | ![](poisson_distribution/image/part_b.png) |
| Simulation | ![](poisson_distribution/image/part_a_sim.png) | ![](poisson_distribution/image/part_b_sim_X_10000_3.000000_0.500000.png) ![](poisson_distribution/image/part_b_sim_Y_10000_3.000000_0.500000.png) |

---

### [Random Access Problem in Machine-to-Machine (See more)](m2m/)

| Access Class Barring | Random Access |
| ------ | ------ |
| ![](m2m/image/part_a_100_30_0.100000.png) | ![](m2m/image/part_b_10000_20_1_20_1.png) | 

---

### [Compound Random Variables](compound_random_variable/)

---

## Some useful self-defined libraries

| Name | Description |
| ------ | ------ |
| [parse_arg](utils/) | parsing the argument from `argc`/`argv` |
| [poisson](utils/) | generating poisson distribution. |
| [rand_gen](utils/) | additional wrapper of different kinds of random number generator. |
| [event_list](utils/) | scheduling、storing event list, use for discrete event simulation process. | 

# Author 

* Kevin Cyu(瞿旭民), kevinbird61@gmail.com