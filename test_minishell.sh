#! /usr/bin/bash

view_diff()
{
	echo $1 | bash > expected
	echo $1 | ./minishell > actual
	diff expected actual
}

view_diff "echo hello"
