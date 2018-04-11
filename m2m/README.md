# Random Access Problem in Machine-to-Machine

<!-- TOC -->

- [Random Access Problem in Machine-to-Machine](#random-access-problem-in-machine-to-machine)
    - [Talking About Network Modeling](#talking-about-network-modeling)
    - [Our Environment: `LTE-A cellular network`](#our-environment-lte-a-cellular-network)
    - [Part A: Access Class Barring](#part-a-access-class-barring)
        - [Technique Background](#technique-background)
        - [System Model](#system-model)
            - [Mathematic Model](#mathematic-model)
        - [Simulation](#simulation)
            - [Simulation Model](#simulation-model)
        - [Analysis](#analysis)
    - [Part B: Random Access](#part-b-random-access)
        - [Technique Background](#technique-background)
        - [System Model](#system-model)
        - [Simulation](#simulation)
        - [Analysis](#analysis)
    - [Reference](#reference)

<!-- /TOC -->
## Talking About Network Modeling

A basic way to build network model:
1. Technique background (From `paper` ,technical essay, magazine ... etc)
2. System model (Mathematic & Question-Defined)
3. Simulation (Base on Step 1,2 to construct `program`)
4. Analysis (Measure the result from program)

Base on this four method, we can easily define our question and find an efficient way to locate and find the answer.

## Our Environment: `LTE-A cellular network`

* LTE-A cellular network [ [1] ](#reference)

![](../res/demo/LTE-A.png)

* Access class barring procedure for an MTC device or UE [ [1] ](#reference)

![](../res/demo/access-class-barring.png)

---
## Part A: Access Class Barring

### Technique Background

* Here we can refer the **Fig 2.** to see the `Access Class Barring` part.
* We need to create a `simulation` and `mathematic` model to represent this part.
* Assumption was made:
    * Draw a random number q~uniform(0, 1) before performing the random access procedure.
    * Assume that devices are blocked for 1 ms. 
    * Calculate the `access delay` by simulation and mathematical analysis.

### System Model 

#### Mathematic Model

### Simulation 

#### Simulation Model

### Analysis 

---
## Part B: Random Access

### Technique Background

* Here we can refer the **Fig 2.** to see the `Random Access` part.
* We need to create a `simulation` and `mathematic` model to represent this part.
* Assumption was made:
    * Simulate a contention-based random access procedure. 
    * Collision occurs when devices are trying to transmit the same preamble.
    * There is no retransmission in your simulation.
    * Compute the success probability after the random access procedure by simulation and mathematical analysis.

### System Model 

Assume there have `M` devices (e.g. `UE` / `MTC device`), and `N` preamble.

### Simulation 

### Analysis 

---
## Reference

[[1] Efficient cooperative access class barring with load balancing and traffic adaptive radio resource management for M2M communications over LTE-A](). **Yi-Huai Hsu, Kuochen Wang, Yu-Chee Tseng**. *Department of Computer Science, National Chiao Tung University, Hsinchu 300, Taiwan*