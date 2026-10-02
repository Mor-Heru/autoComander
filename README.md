# AutoCommander

AutoCommander is a simple command manager for Linux. It lets you store shell commands in one place and run, edit, or delete them. The terminal user interface is built with ncurses.

## Requirements

- Linux
- A C++ compiler such as `g++`
- The ncurses development library

Install the required packages on Ubuntu/Debian:

```sh
sudo apt update
sudo apt install g++ libncurses-dev
```

## Build and run

Run these commands from the repository root:

```sh
g++ source/main.cpp source/terminal.cpp source/comand.cpp source/line.cpp -lncurses -o main
./main
```

Run the application from the repository root so it can find `data/comands.csv`.

## Controls

- Up/Down arrows — select a command or the add-command option.
- Left/Right arrows — select RUN, EDIT, or DELETE.
- Enter — activate the selected action.
- A — go to the add-command option.
- Q — quit the application.

## Command data

Commands are stored in `data/comands.csv`. Each record contains a name, description, and shell command.

> **Security warning:** RUN executes the stored command on your system. Only run commands you trust; commands may modify or delete files or otherwise affect your system.