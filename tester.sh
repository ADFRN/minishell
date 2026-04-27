#!/bin/sh

echo "ls" | ./minishell

echo "exit 126" | ./minishell | echo exitcode = $?