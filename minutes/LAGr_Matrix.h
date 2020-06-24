
// Every LAGraph function has a descriptor input (opaque?)
// modes:
//      debug: check all properties
//      etc: ...
//      raw:

// LAGr_Matrix: A matrix, not a graph:  [ opaque ]

// blocking and non-blocking?

    G->stuff = x
    LAGr_set_stuff (G, x)

typedef struct
{
    GrB_Matrix A    // one matrix
    symmetry        // yes, no, unknown
    typeid          // enum for now int8, int16, .... user
    typestring      // name of user defined type, or "GrB_INT8"

    diagonal        // yes (any neg? all pos? all >=0), no, unknown ...
    cc              
    kind  ?         // adjacency, incidence, bipartite?, hypergraph?, ...
                    // none of the above

    char name [64] ;

    // ... hidden:  implementation defined
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

