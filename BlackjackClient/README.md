# TCP Game Client

This is the **client** for the multiplayer TCP game. It connects to the server, sends player actions, and listens for updates.

## How It Works
- The client connects its socket to the server once via TCP to join the game.
- The user interacts with the GUI to player the game once it starts.
- The client continuously listens for server updates over the same socket in a background thread. These updates will trigger visual changes in the GUI.
