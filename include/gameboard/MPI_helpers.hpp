#ifndef PARALLEL_MPI_HELPERS_HPP
#define PARALLEL_MPI_HELPERS_HPP

#include <mpi.h>
#include "State.hpp"

#define MASTER_RANK 0

void bcast_state_out(State state, int root, MPI_Comm communicator);

State bcast_state_in(int n, int d, int root, MPI_Comm communicator);

#endif //PARALLEL_MPI_HELPERS_HPP
