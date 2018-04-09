#!/bin/bash
# This script use to generating the different testcase of part-a and part-b
# Copyright (C) 2018 Kevin Cyu - All Rights Reserved

# define variable
A=part_a.out

# Step 1 - using make command to compile and generate part-a and part-b executable file
make

# Step 2 - run multi-case and plot it immediately
# =============================== Part A ===============================
# plot it immediately, or it will overwrite the output
./$A -k 20 -s 10000 -1 1 -2 5 && make plot_a_sim
./$A -k 20 -s 10000 -1 1 -2 10 && make plot_a_sim 
./$A -k 20 -s 10000 -1 10 -2 20 && make plot_a_sim 
./$A -k 20 -s 100000 -1 10 -2 20 && make plot_a_sim 