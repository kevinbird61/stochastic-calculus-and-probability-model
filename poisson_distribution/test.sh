#!/bin/bash
# This script use to generating the different testcase of part-a and part-b
# Copyright (C) 2018 Kevin Cyu - All Rights Reserved

# define variable
A=part_a.out
B=part_b.out

# Step 1 - using make command to compile and generate part-a and part-b executable file
make

# Step 2 - run multi-case and plot it immediately
# =============================== Part A ===============================
# plot it immediately, or it will overwrite the output
./$A -k 20 -s 10000 -1 1 -2 5 && make plot_a_sim
./$A -k 20 -s 10000 -1 1 -2 10 && make plot_a_sim 
./$A -k 20 -s 10000 -1 10 -2 20 && make plot_a_sim 
./$A -k 20 -s 100000 -1 10 -2 20 && make plot_a_sim 

# =============================== Part B ===============================
# for adjust P (Probability of X)
./$B -k 20 -s 10000 -l 6 && make plot_b_sim
./$B -k 20 -s 10000 -l 6 -p 0.3 && make plot_b_sim
./$B -k 20 -s 10000 -l 6 -p 0.7 && make plot_b_sim
./$B -k 20 -s 10000 -l 11 && make plot_b_sim
./$B -k 20 -s 10000 -l 11 -p 0.3 && make plot_b_sim
./$B -k 20 -s 10000 -l 11 -p 0.7 && make plot_b_sim
./$B -k 20 -s 10000 -l 30 && make plot_b_sim
./$B -k 20 -s 10000 -l 30 -p 0.3 && make plot_b_sim
./$B -k 20 -s 10000 -l 30 -p 0.7 && make plot_b_sim
./$B -k 20 -s 100000 -l 30 && make plot_b_sim
./$B -k 20 -s 100000 -l 30 -p 0.3 && make plot_b_sim
./$B -k 20 -s 100000 -l 30 -p 0.7 && make plot_b_sim
./$B -k 20 -s 1000000 -l 30 && make plot_b_sim