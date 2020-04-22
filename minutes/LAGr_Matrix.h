
// LAGr_Matrix: A matrix, not a graph.
// not opaque or NOT

    G->stuff = x
    LAGr_set_stuff (G, x)

typedef struct
{
    GrB_Matrix A
    kind                // adjacency, incidence, bipartite?, hypergraph?, ...
                        // none of the above
    symmetry            // yes, no, unknown
    diagonal            // yes, no, unknown ...
    typeid              // enum? for now

    char name [64] ;

    // ...

    MPI_comm_world stuff
    FPGA stuff
    GPU stuff ...
    special GxB stuff

    // ... other

    uint8_t other [64]  // user definable space

} LAGr_Matrix_struct


typedef LAGr_Matrix *LAGr_Matrix_struct ;

    // discuss more:
    tril or triu or neither?
    row vs col vs both (agnostic)?
    char name [64] ?
    posweights

    // probably not:
    cycle
    scc
    # of conn. components?

}
LAGr_Matrix

