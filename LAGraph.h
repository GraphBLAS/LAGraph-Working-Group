
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

// TODO: discuss sanity checking.
// what if A is unsymmetric, but the graph is labeled "undirected"?
// error?  use A+A' ?

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

//------------------------------------------------------------------------------
// breadth first search
//------------------------------------------------------------------------------

// TODO: hops for all methods?

GrB_Info LAGraph_BreadthFirstSearch     // no _Variant suffix
(
    // outputs:
    GrB_Vector *level,
    GrB_Vector *parent,
    // inputs:
    LAGraph_Graph G,
    GrB_Index source
) ;

GrB_Info LAGraph_BreadthFirstSearch_MultiSource
(
    // outputs:
    GrB_Matrix *level,
    GrB_Matrix *parent,
    // inputs:
    LAGraph_Graph G,
    GrB_Index *sources, size_t nsources     // or LAGraph_array?  GrB_array?
) ;

GrB_Info LAGraph_BreadthFirstSearch_Frontier
(
    // outputs:
    GrB_Vector *level,
    GrB_Vector *parent,
    // input/output:
    GrB_Vector frontier,
    // inputs:
    GrB_Vector vertex_mask,         // filter the vertices
    bool vertex_mask_complement,
    bool vertex_mask_structural,
//  or:
//  GrB_Descriptor desc,    // mask complement, mask structural:
//                          // NULL, GrB_DESC_C, GrB_DESC_S, or GrB_DESC_SC
    LAGraph_Graph G,
    uint64_t hops           // if hops=0, no limit (or INT64_MAX), or "NONE"
) ;

//------------------------------------------------------------------------------
// connected components:
//------------------------------------------------------------------------------

// SCC graph = Community * G * Community', a contracted graph

GrB_Info LAGraph_Community_Map
(
    // output:
    uint64_t &ncomponents,
    GrB_Vector *component,  // vertex i is in component(i), a dense vector.
    // input:
    GrB_Matrix Community    // Community(c,i)=1 becomes c=component(i)
) ;

// Gnew = Perm * G *Perm', then Gnew is block diagonal
GrB_Info LAGraph_Community_Permutation
(
    // output:
    GrB_Matrix Perm,        // Perm(...), n-by-n
    // input:
    GrB_Matrix Community    // Community(c,i)=1 becomes c=component(i)
) ;

GrB_Info LAGraph_ConnectedComponents
(
    // output:
    GrB_Matrix *Community,  // k-by-n if there are k components.  GrB_BOOL.
                            // Community(c,i)=1 if c=component(i)
    // input:
    LAGraph_Graph G         // if directed: strongly cc
) ;

GrB_Info LAGraph_ConnectedComponents_Weakly
(
    // output:
    GrB_Matrix *Community,  // k-by-n if there are k components.  GrB_BOOL.
                            // Community(c,i)=1 if c=component(i)
    // input:
    LAGraph_Graph G
) ;

//------------------------------------------------------------------------------
// centrality: up next
//------------------------------------------------------------------------------

// random number generator?  node sampler?

