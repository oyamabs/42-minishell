# minishell

As simple as a shell

## Goal

Recreate a simple shell, that can do commands, redirections, pipes, handle signals.

## Grade

![Grade](https://img.shields.io/badge/Grade-101-darkgreen)

## Bonus part

We only did one bonus but it's more due to how our parser works.

## Special thanks

- bfiquet - my peer
- jguelen - for helping me debugging and testing
- cguilber - for teaching me how to write a good parser

## My thoughts on the project

I both love and hate this project. On one hand, it’s really interesting—implementing a shell is fun. On the other hand, it’s also a huge hassle. The shell MUST have perfect parsing; otherwise, everything breaks, and debugging becomes a nightmare.
I learned how to write a parser with cguilber using an [RDP](https://en.wikipedia.org/wiki/Recursive_descent_parser) algorithm, which was really interesting. I also learned how to execute commands properly using child processes. That’s also when I started hating the project—debugging child processes is incredibly frustrating. GDB doesn’t handle it well, memory leaks are manageable but still a pain, and the worst are file descriptor leaks. They can be hard to trace and sometimes come from unexpected places, like the pipe itself.

Despite all that, it’s still a good project—just occasionally annoying when it comes to debugging.

To any 42 students reading this:
First, hi! Feel free to ping me on Slack.
Second, it’s okay to fail. My peer and I had to retry this project four times, and it ended up taking us nearly five months. Keep pushing forward. Use RDP for parsing—it handles a lot of the "special cases" and is required for the bonus anyway.

## How to launch the project

> Requires `cc`, `make` and `readline`

First clone the project:
`git clone https://github.com/oyamabs/42-minishell`

Go into the directory and compile with `make`.

Enjoy your minishell!
