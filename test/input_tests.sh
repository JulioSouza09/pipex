#!/bin/bash

./pipex infile "cat -e" "wc -l" outfile
./pipex src/main.c "cat -e" "wc -l" include/pipex.h
