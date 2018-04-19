# Discussion of Compound Random Variable

<!-- TOC -->

- [Discussion of Compound Random Variable](#discussion-of-compound-random-variable)
    - [Example 3.8 (conditional density)](#example-38-conditional-density)
        - [Solution](#solution)
    - [Example 3.10 (Expectation)](#example-310-expectation)

<!-- /TOC -->

## Example 3.8 (conditional density)

This exercise is using two independent exponential random variables, to illustrate the conditional density function.

Here we have $X_1$, $X_2$, as our independent exponential random variables, which have $\mu_1, \mu_2$ as mean respectively:

$$\begin{array}{lcl}
X_1 &\sim& exp(\mu_1)\\
    &\sim& f_{x_1}(x) = \mu_1e^{-\mu_1x} \\
    \\
X_2 &\sim& exp(\mu_2)\\
    &\sim& f_{x_2}(y) = \mu_2e^{-\mu_2y}
\end{array}$$

And now we need to find the **conditional density** of $X_1$ and $X_1+X_2=t$ , which $0\le x\le t$.

### Solution

We can set the *joint density* $f(x,y)$ of $X,Y$ first, and then we can have the *joint density* $f_{X,X+Y}(x,t)$ of  $X,X+Y$, which $f_{X,X+Y}(x,t)=f(x,t-x)=f_{X_1|X_1+X_2}(x|t)$ 

In this step, we need to confirm that $X_1$ must be independent.

So we can derive the formula:

$$\begin{array}{lcl}
f_{X_1|X_1+X_2}(x|t) &=& \frac{f_{X_1}\cdot f_{X_2}(t-x)}{f_{X_1+X_2}(t)} \\
\\
&=& \frac{\mu_1 e^{-\mu_1x}\cdot\mu_2 e^{-\mu_2x}}{f_{X_1+X_2}(t)} , 0\le x\le t \\
\\
&=& C \cdot e^{-(\mu_1-\mu_2)x} , 0\le x\le t
\end{array}
$$

After the derivation, we can pack some variables into $C = \frac{\mu_1 \mu_2 \cdot e^{-\mu_2 t}}{f_{X_1+X_2}(t)}$

And then we can discuss the following two scenarios: 

* Case 1:


$$\begin{array}{lcl}
\mu_1=\mu_2, \\
&f_{X_1 | X_1+X_2}(x|t) = C, 0\le x\le t
\end{array}
$$

And we will get: 
$C=\frac{1}{t}, X_1 \ given \ X_1+X_2=t \ (uniformly \  distribution\ (0,t))$

* Case 2:

$$\begin{array}{lcl}
\mu_1\ne\mu_2, \\
&1=\int_0^tf_{X_1 | X_1+X_2}(x|t) dx \\
\\
&1=\frac{C}{\mu_1 - \mu_2} (1-e^{-(\mu_1-\mu_2)t}) \\
\\
&C=\frac{\mu_1-\mu_2}{1-e^{-(\mu_1-\mu_2)t}}
\end{array}
$$

And we can get:
$$C=\frac{\mu_1-\mu_2}{1-e^{-(\mu_1-\mu_2)t}}$$

Also we can have the byproduct of $f_{X_1+X_2}(t)$:

$$\begin{array}{lcl}
f_{X_1+X_2}(t)&=&\frac{\mu_1\mu_2e^{-\mu_2 t}}{C}\\
\\ 
if\ \mu_1 = \mu_2 = \mu&,&= \mu^2te^{-\mu t} \\
\\
if\ \mu_1 \ne \mu_2 &,&= \frac{\mu_1\mu_2(e^{-\mu_2t}-e^{-\mu_1t})}{\mu_1-\mu_2}
\end{array}
$$

## Example 3.10 (Expectation)

> The Expectation of the sum of a Random Number of Random Variables

Now we calculate the *expectation* of compound random variables. Consider the case: we have a random number of accidents in each day, and each accident will cost some money which also use a random variable to represent.

So here we can have: 

$$\begin{array}{lcl}
E[\ \sum_{i=1}^N X_i \ ] &=& E[ E[\ \sum_{i=1}^N X_i | N \ ] ] \\
\\
E[\ \sum_{i=1}^N X_i | N \ ] &=& E[\ \sum_{i=1}^n X_i | N=n \ ], n=constant \\
\\
&=&E[\sum_{i=1}^n X_i] \\
\\
&=&n\cdot E[X]
\end{array}
$$

We can derive the equation: 

$$
E[\ \sum_{i=1}^N X_i | N \ ] = N \cdot E[X] , N \sim Random\ Number
$$

Need to consider $N$, the expectation of this random number, and we can get the final state:

$$
E[\ \sum_{i=1}^N X_i \ ] = E[N \cdot E[X]] = E[N] \cdot E[X]
$$

which

$$\begin{array}{lcl}
E[N] : Average\ Expectation\ of\ N \\
E[X] : Average\ Expectation\ of\ X 
\end{array}
$$