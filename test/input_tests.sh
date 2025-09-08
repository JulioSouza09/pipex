#!/bin/bash

valgrind ./pipex infile "cat -e" "wc -l" outfile
valgrind ./pipex src/main.c "cat -e" "wc -l" outfile
valgrind ./pipex src/main.c "cat -e" "wc -l" include/pipex.h
valgrind ./pipex src/main.c "wc -l" "lskdjf" include/pipex.h
valgrind ./pipex src/main.c "lssdfs -a " "wc -l" include/pipex.h
