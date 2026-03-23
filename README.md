## Tic Tac Toe

A tictactoe which has a bot opponent which uses minimax algorithm to choose a move which has gauranteed success.

## Opponent AI

The opponent ai uses minimax algorithm to explore all possible moves recursively and when it finds a move with
guaranteed success, it chooses that move.
Thus it can never loose and can only win or lead to tie.

## How minimax works

1. When minimax is called it checks for all possible moves that can be made. And then recursively calls itself thus
   exploring all possible moves till the game terminates.
2. While exploring the tree formed by all the moves, it plays as the opponent as well as the player(assuming how the
   player would react when opponent move is played) to reach a terminal state.
3. It forms a recursion tree containing all states of the game. Once the game reaches terminal state, it propagates the
   score up the tree and chooses the best move.
4. It assumes the player will play in their best interests and hence the opponent AI tries to minimize the player AI and
   maximize the opponent AI.

## How to play

1. Clone the repository:
   ```bash 
   gh repo clone pinkteddybearfluff/minimax_tictactoe
2. Compile the board.cpp file.

   ```bash
   g++ board.cpp -o tictactoe
3. Run the tictactoe file.