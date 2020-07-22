
// LAGraph graph

typedef struct
{
    GrB_Matrix A ;

    // may be NULL:
    GrB_Matrix AT ;

    // graph properties
    undirected, directed
    bipartite, etc
    weighted, unweighted? ... constant value?
    ...
}
LAGraph_Graph ;

// or a different return value for error status?

LAGraph_Algorithm_Variant ?
GrB_Info LAGraph_BreadthFirstSearch_variant
or

// rule: NULL vs GrB_NULL:  use NULL (discuss this later)

// rule: if any output (*arg) is NULL, do not compute

// rule: if any input arg is NULL: use default, don't use it, etc

// rule:  output vectors and matrices are "new'd" by the LAGraph function:
    // usage:
    GrB_Vector level ;
    LAGraph_BreadthFirstSearch (&level, NULL, ...)


GrB_Info LAGraph_BreadthFirstSearch     // no _Variant suffix
(
    // outputs:
    GrB_Vector *level,
    GrB_Vector *parent,
    // inputs:
    LAGraph_Graph G,
    GrB_Index source
        // or GrB_Scalar source
) ;

GrB_Info LAGraph_BreadthFirstSearch_MultiSource
(
    // outputs:
    GrB_Matrix *level,
    GrB_Matrix *parent,
    // inputs:
    LAGraph_Graph G,
    GrB_Index *sources, size_t nsources
        // alternatives:
        // (1)     GrB_Vector Source of size 1-by-nsources
        //          can have different types
        // (2) should [Source, nsources] be an LAGraph_array?
) ;

GrB_Info LAGraph_BreadthFirstSearch_Frontier
(
    // outputs:
    GrB_Vector *level,
    GrB_Vector *parent,
    GrB_Vector *next_frontier,
    // inputs:
    LAGraph_Graph G,
    GrB_Vector frontier,
    uint64_t hops           // if hops=0, no limit (or INT64_MAX), or "NONE"
) ;

// connected components:

// random number generator?  node sampler?

