#!/bin/bash

#gcc -g -Wall -Wextra -Werror ./sources/main1.c ./sources/parser.c ./sources/lexxer.c ./sources/tokens.c ./sources/parse.c ./libft/libft.a

gcc -g ./sources/main.c ./sources/parser.c ./sources/lexxer.c ./sources/tokens.c ./sources/parse.c ./sources/before_lexxer.c ./libft/libft.a
