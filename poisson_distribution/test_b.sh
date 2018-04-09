#!/bin/bash
# This script use to generating the different testcase of part-a and part-b
# Copyright (C) 2018 Kevin Cyu - All Rights Reserved

# define variable
B=part_b.out

# Step 1 - using make command to compile and generate part-a and part-b executable file
make

# Step 2 - run multi-case and plot it immediately
# =============================== Part B ===============================
# for adjust P (Probability of X)
./$B -k 20 -s 10000 -l 6 && make plot_b_sim
./$B -k 20 -s 10000 -l 6 -p 0.3 && make plot_b_sim
./$B -k 20 -s 10000 -l 6 -p 0.7 && make plot_b_sim
./$B -k 20 -s 100000 -l 6 && make plot_b_sim
./$B -k 20 -s 100000 -l 6 -p 0.3 && make plot_b_sim
./$B -k 20 -s 100000 -l 6 -p 0.7 && make plot_b_sim
./$B -k 20 -s 100000 -l 30 && make plot_b_sim
./$B -k 20 -s 100000 -l 30 -p 0.3 && make plot_b_sim
./$B -k 20 -s 100000 -l 30 -p 0.7 && make plot_b_sim