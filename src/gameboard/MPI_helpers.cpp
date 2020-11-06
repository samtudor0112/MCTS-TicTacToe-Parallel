#include "../../include/gameboard/MPI_helpers.hpp"

void bcast_state_out(State state, int root, MPI_Comm communicator) {
    if (state.getGameStatus() != inProgress) {
        std::cout <<"Uh oh!" << std::flush;
    }
    PlayerColour turn = state.getTurn();
    MPI_Bcast(&turn, 1, MPI_INT, root, communicator);
    MPI_Bcast(&(state.getBoard().getWhiteBoard()[0]), state.getBoard().getSize(), MPI_INT, root, communicator);
    MPI_Bcast(&(state.getBoard().getBlackBoard()[0]), state.getBoard().getSize(), MPI_INT, root, communicator);
    int numMoves = state.getBoard().getNumMoves();
    MPI_Bcast(&numMoves, 1, MPI_INT, root, communicator);
}

State bcast_state_in(int n, int d, int root, MPI_Comm communicator) {
    int size = pow(n, d);
    int* buffer = new int[size];
    // The turn
    MPI_Bcast(buffer, 1, MPI_INT, root, communicator);
    auto turn = (PlayerColour)buffer[0];

    // The white board
    MPI_Bcast(buffer, size, MPI_INT, root, communicator);
    std::vector<int> whiteBoard(buffer, buffer + size);

    // The black board
    MPI_Bcast(buffer, size, MPI_INT, root, communicator);
    std::vector<int> blackBoard(buffer, buffer + size);

    // the numMoves
    MPI_Bcast(buffer, 1, MPI_INT, root, communicator);
    int numMoves = buffer[0];

    // Reconstruct the TicTacToe and State object
    // Note this won't update the gameStatus. So if the gameStatus was not inProgress this won't be an exact duplicate. Hence we should only send / receive states that are still inProgress.
    TicTacToe board = TicTacToe(n, d, whiteBoard, blackBoard, numMoves);

    State state = State(turn, board);

    delete[] buffer;
    
    return state;
}
