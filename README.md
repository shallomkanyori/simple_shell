## C - Simple Shell
#### Write a simple UNIX command interpreter.

**Task 0: Betty would be proud.**
Write beautiful code that passes the Betty checks.

**Task 1: Simple shell 0.1.**
Write a UNIX command line interpreter.
- Usage: `simple_shell`
Your Shell should:
- Display a prompt and wait for the user to type a command.
- The prompt is displayed again each time a command has been executed.
- The commands are simple: no semicolons, pipes, redirections or any other advanced features.
- The commands are made only of one word. No arguments will be passed.
- If an executable cannot be found, print an error message and display the promt again.
- Handle errors.
- Handle the "end of file" condition (`Ctrl-D`)
You don't have to:
- use the `PATH`
- implement built-ins
- handle special characters: `"`, `'`, `\`, `*`, `&`, `#`, backtick
- be able to move the cursor

**Task 2: Simple shell 0.2.**
Simple shell 0.1 +
- Handle commands with arguments
