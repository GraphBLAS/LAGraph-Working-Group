
// LAGr_Matrix: A matrix, not a graph.
// not opaque

typedef struct
{
    GrB_Matrix A
    kind                // adjacency, incidence, bipartite?, hypergraph?, ...
                        // none of the above
    symmetry            // yes, no, unknown
    diagonal            // yes, no, unknown ...

    // discuss more:
    typeid              // enum?
    tril or triu or neither?
    row vs col vs both (agnostic)?
    char name [64] ?

    // probably not:
    cycle
    scc
    # of conn. components?

}
LAGr_Matrix

