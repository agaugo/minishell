lezer -> parser -> expander -> executor

Naming conventions:

Variables start with '_', e.g. _index, _userInput, _commandTable.
Functions declared and implemented outside of the src files bave prefix 'ft_' or nothing, for std library functions like malloc(), printf() or free()
Functions Declared inside src files will have prefix 'ms' (minishell) and then a descriptive name like, 'ms_processInput' or 'ms_executeBuiltin'.

