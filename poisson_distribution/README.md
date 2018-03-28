# Poisson Probability Discussion

After `example 2.5`, `3.31`, the program has been refactor a lot, make code reusable.

<!-- TOC -->

- [Poisson Probability Discussion](#poisson-probability-discussion)
    - [Discuss two *network model*](#discuss-two-network-model)
        - [Example 2.37 (Merge)](#example-237-merge)
            - [Difference (TODO)](#difference-todo)
        - [Example 3.23 (Split)](#example-323-split)
            - [Difference (TODO)](#difference-todo-1)
    - [Author](#author)

<!-- /TOC -->

## Discuss two *network model*

### Example 2.37 (Merge)
* It will be implemented in `part_a.cc`
![](../res/example2_37.png)

Consider the formula: $$P\{X+Y=n\}=\sum_{k=0}^nP\{X=k, Y=n-k\}   $$

$$ = \sum_{k=0}^nP\{X=k\} \cdot P\{Y=n-k\}$$

So that we can :

* **Directly** calculate the *S=X+Y* with: $$\frac{e^{-(\lambda_1+\lambda_2)}}{n!} \cdot (\lambda_1 + \lambda_2)^n$$

* **Separately** calculate *X* and *Y* with: $$P\{X=k\} =\frac{e^{-(\lambda_1)}}{n!} \cdot (\lambda_1)^n, P\{Y=n-k\} =\frac{e^{-(\lambda_2)}}{(n-k)!} \cdot (\lambda_2)^{n-k}$$, and need to consider the summation, from **k=0~n**: $$\sum_{k=0}^n ...$$

* So we need to compare these two part:
    * run with command `make run && make plot` to run the program and plot: $$k=40,\ \lambda_1=1,\ \lambda_2=2$$
    ![](part_a.png)
    * As the `part_a.png` shown, two line match perfectly. It means that the results generate `directly` or `separately` are the same.

#### Difference (TODO)


### Example 3.23 (Split)
* It will be implemented in `part_b.cc`
![](../res/example3_23.png)

#### Difference (TODO)

## Author 

* Kevin Cyu, kevinbird61@gmail.com