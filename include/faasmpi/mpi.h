#ifndef FAASM_MPI_H
#define FAASM_MPI_H

#ifdef __cplusplus
extern "C" {
#endif

#define MPI_SUCCESS 0
#define MPI_ERR_OTHER 1

/**
 * Custom Faasm MPI implementation
 * Official MPI spec: https://www.mpi-forum.org/docs/
 * Open MPI repo: https://github.com/open-mpi/ompi
 * You can probably find a version of mpi.h somewhere on your system, e.g. /usr/local/include/mpi.h
 */

#define MPI_MAX_OBJECT_NAME 128

/*
 * Behind the scenes structs (some parts of which are defined in the MPI specification)
 * Each can be extended with private fields as necessary
 */
struct faasmpi_status_public_t {
    // These MPI_XXX fields are defined in the spec
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;

    // These are internal
    int bytesSize;
};

// Open MPI version: https://github.com/open-mpi/ompi/blob/master/ompi/datatype/ompi_datatype.h
struct faasmpi_datatype_t {
    int id;
};

// Open MPI version: https://github.com/open-mpi/ompi/blob/master/ompi/communicator/communicator.h
struct faasmpi_communicator_t {
    int id;
};

// Open MPI version: https://github.com/open-mpi/ompi/blob/master/ompi/message/message.h
struct faasmpi_message_t {
    int id;
};

struct faasmpi_op_t {
    int id;
};

/**
 * User-facing constants
 */
// MPI_Comms
#define FAASMPI_COMM_WORLD 1
extern struct faasmpi_communicator_t faasmpi_comm_world;
#define MPI_COMM_WORLD (&faasmpi_comm_world)

// MPI_Datatypes
#define FAASMPI_INT 1
extern struct faasmpi_datatype_t faasmpi_type_int;
#define MPI_INT &faasmpi_type_int

// MPI_Ops
#define FAASMPI_OP_MAX    1
#define FAASMPI_OP_MIN    2
#define FAASMPI_OP_SUM    3
#define FAASMPI_OP_PROD   4
#define FAASMPI_OP_LAND   5
#define FAASMPI_OP_LOR    6
#define FAASMPI_OP_BAND   7
#define FAASMPI_OP_BOR    8
#define FAASMPI_OP_MAXLOC 9
#define FAASMPI_OP_MINLOC 10

extern struct faasmpi_op_t faasmpi_op_max;
extern struct faasmpi_op_t faasmpi_op_min;
extern struct faasmpi_op_t faasmpi_op_sum;
extern struct faasmpi_op_t faasmpi_op_prod;
extern struct faasmpi_op_t faasmpi_op_land;
extern struct faasmpi_op_t faasmpi_op_lor;
extern struct faasmpi_op_t faasmpi_op_band;
extern struct faasmpi_op_t faasmpi_op_bor;
extern struct faasmpi_op_t faasmpi_op_maxloc;
extern struct faasmpi_op_t faasmpi_op_minloc;

#define MPI_MAX &faasmpi_op_max
#define MPI_MIN &faasmpi_op_min
#define MPI_SUM &faasmpi_op_sum
#define MPI_PROD &faasmpi_op_prod
#define MPI_LAND &faasmpi_op_land
#define MPI_LOR &faasmpi_op_lor
#define MPI_BAND &faasmpi_op_band
#define MPI_BOR &faasmpi_op_bor
#define MPI_MAXLOC &faasmpi_op_maxloc
#define MPI_MINLOC &faasmpi_op_minloc


// MPI_Statuses
#define MPI_STATUS_IGNORE (static_cast<MPI_Status *> (0))

/*
 * User-facing types
 */
typedef struct faasmpi_op_t *MPI_Op;
typedef struct faasmpi_communicator_t *MPI_Comm;
typedef struct faasmpi_datatype_t *MPI_Datatype;
typedef struct faasmpi_status_public_t MPI_Status;
typedef struct faasmpi_message_t *MPI_Message;

/*
 * User-facing functions
 */
int MPI_Init(int *argc, char ***argv);

int MPI_Finalize(void);

int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);

int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);

int MPI_Comm_rank(MPI_Comm comm, int *rank);

int MPI_Comm_size(MPI_Comm comm, int *size);

int MPI_Abort(MPI_Comm comm, int errorcode);

int MPI_Get_count(const MPI_Status *status, MPI_Datatype datatype, int *count);

int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status *status);

int MPI_Barrier(MPI_Comm comm);

int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm);

int MPI_Scatter(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                void *recvbuf, int recvcount, MPI_Datatype recvtype,
                int root, MPI_Comm comm);

int MPI_Gather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
               void *recvbuf, int recvcount, MPI_Datatype recvtype,
               int root, MPI_Comm comm);

int MPI_Allgather(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                  void *recvbuf, int recvcount, MPI_Datatype recvtype,
                  MPI_Comm comm);

int MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype,
               MPI_Op op, int root, MPI_Comm comm);

int MPI_Allreduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype,
               MPI_Op op, MPI_Comm comm);

int MPI_Alltoall(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                 void *recvbuf, int recvcount, MPI_Datatype recvtype,
                 MPI_Comm comm);

#ifdef __cplusplus
}
#endif

#endif
