# TCP Game Server

This is the **server** for the multiplayer TCP game. It listens for client connections, handles up to **5 players**, and starts the game once all players are connected or once the host (first player) starts it.

## How It Works
- The server listens on a port.
- It waits for 5 players to join or for the host to request before starting the game.
- Players send actions and the server processes them.
- The server periodically sends game state updates.
