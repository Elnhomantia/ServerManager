## Overview
Server-Manager is a light client side application which only use SSH to send commands to a server.
This is only to provide a GUI to people that don't like to use a terminal (which is faster).
I've also already learned lots of things programming this.

## How it works
By using QProcess, we can simulate an ssh terminal. However we are forced to allocate a pseudo-terminal (`ssh -tt ...`) else commands like `sudo`, asking for a password, will immediately fail.
SSH connection are async and uses signals to exchange data between threads. (This also makes the GUI fluid).

## Build
This uses Qt with Cmake to build. Get Qt creator, load the cmake file, and build the app.
It should be possible to build on both Linux and Windows.

## NOTICE
This project is still WIP.
