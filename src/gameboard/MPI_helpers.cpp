#include "../../include/gameboard/MPI_helpers.hpp"

// Broadcasts a State object to the root process. It does this by broadcasting all relevant members variables of the
// State.
// This is probably very slow. It could be improved by using a custom MPI datatype, but this seemed difficult.
void bcast_state_out(State state, int root, MPI_Comm communicator) {
    PlayerColour turn = state.getTurn();
    MPI_Bcast(&turn, 1, MPI_INT, root, communicator);

    // The rest is sending the TicTacToe data
    MPI_Bcast(&(state.getBoard().getWhiteBoard()[0]), state.getBoard().getSize(), MPI_INT, root, communicator);

    MPI_Bcast(&(state.getBoard().getBlackBoard()[0]), state.getBoard().getSize(), MPI_INT, root, communicator);

    int numMoves = state.getBoard().getNumMoves();
    MPI_Bcast(&numMoves, 1, MPI_INT, root, communicator);

    GameStatus status = state.getBoard().getGameStatus();
    MPI_Bcast(&status, 1, MPI_INT, root, communicator);
}

// The corresponding function to receive a broadcasted State object.
State bcast_state_in(int n, int d, int root, MPI_Comm communicator) {
    int size = pow(n, d);
    int* buffer = new int[size];
    // The turn
    MPI_Bcast(buffer, 1, MPI_INT, root, communicator);
    auto turn = static_cast<PlayerColour>(buffer[0]);

    // The white board
    MPI_Bcast(buffer, size, MPI_INT, root, communicator);
    std::vector<int> whiteBoard(buffer, buffer + size);

    // The black board
    MPI_Bcast(buffer, size, MPI_INT, root, communicator);
    std::vector<int> blackBoard(buffer, buffer + size);

    // the numMoves
    MPI_Bcast(buffer, 1, MPI_INT, root, communicator);
    int numMoves = buffer[0];

    // the status
    MPI_Bcast(buffer, 1, MPI_INT, root, communicator);
    auto status = static_cast<GameStatus>(buffer[0]);

    // Reconstruct the TicTacToe and State object
    TicTacToe board = TicTacToe(n, d, whiteBoard, blackBoard, numMoves);

    board.setGameStatus(status);

    State state = State(turn, board);

    delete[] buffer;
    
    return state;
}
