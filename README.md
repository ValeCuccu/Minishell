hh# 🐚 minishell — Recreating a Unix Shell

## 🧭 Project Description

**minishell** is one of the most complex and important projects at 42 School.

The goal is to recreate a simplified version of **bash**, implementing:

- Prompt and interactive loop
- Lexer and parser
- Environment variable expansion
- Redirections and pipes
- Built-in commands
- Process creation and management
- Signal handling
- Exit status management

This project is where everything learned in previous projects (libft, ft_printf, get_next_line, minitalk, push_swap, so_long) comes together into a real system-level program.

---

## 🎯 Learning Objectives

With minishell, you learn to:

- Parse complex user input
- Manage processes with `fork`, `execve`, `wait`
- Handle pipes and file descriptor redirections
- Implement heredoc behavior
- Correctly manage signals (Ctrl+C, Ctrl+D, Ctrl+\)
- Reproduce bash behavior in edge cases
- Build a modular and scalable architecture
- Prevent memory leaks in a long-running program
