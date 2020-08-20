
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

// Policy: in general, if an input *x is NULL, do not compute

// TODO: hops for all methods?

GrB_Info LAGraph_BreadthFirstSearch     // no _Variant suffix
(
    // outputs:
    GrB_Vector *level,              // if NULL do not compute
    GrB_Vector *parent,             // if NULL do not compute
    // inputs:
    LAGraph_Graph G,
    GrB_Index source
) ;

GrB_Info LAGraph_BreadthFirstSearch_MultiSource
(
    // outputs:
    GrB_Matrix *level,              // if NULL do not compute
    GrB_Matrix *parent,             // if NULL do not compute
    // inputs:
    LAGraph_Graph G,
    GrB_Index *sources, size_t nsources     // or LAGraph_array?  GrB_array?
) ;

GrB_Info LAGraph_BreadthFirstSearch_Frontier
(
    // outputs:
    GrB_Vector *level,              // should this be input/output?
    GrB_Vector *parent,
    // input/output:
    GrB_Vector frontier,
    // inputs:
    LAGraph_Graph G,
    GrB_Vector vertex_mask,         // filter the vertices
    bool vertex_mask_complement,
    bool vertex_mask_structural,
//  or:
//  GrB_Descriptor desc,    // mask complement, mask structural:
//                          // NULL, GrB_DESC_C, GrB_DESC_S, or GrB_DESC_SC
    uint64_t hops           // if hops=0, no limit (or INT64_MAX), or "NONE"
) ;

//------------------------------------------------------------------------------
// connected components:
//------------------------------------------------------------------------------

// TODO: utility to do SCC = Comm * G * Comm'
// TODO: utility to do Gnew = Perm * G * Perm' ; or Gnew = G (P,P)
// TODO: utility to convert Perm matrix <==> perm "vector" (array?) GrB_Index*

// SCC graph = Community * G * Community', a contracted graph

GrB_Info LAGraph_Community_Map
(
    // output:
    uint64_t *ncomponents,
    GrB_Vector *component,  // vertex i is in component(i), a dense vector.
    // input:
    GrB_Matrix Community    // Community(c,i)=1 becomes c=component(i)
) ;

// Gnew = Perm * G *Perm', then Gnew is block diagonal
GrB_Info LAGraph_Community_Permutation
(
    // output:
    GrB_Matrix *Perm,        // Perm(...), n-by-n
    // input:
    GrB_Matrix Community    // Community(c,i)=1 becomes c=component(i)
) ;

GrB_Info LAGraph_ConnectedComponents
(
    // output:
    GrB_Matrix *Community,  // k-by-n if there are k components.  GrB_BOOL.
                            // Community(c,i)=1 if c=component(i)
                            // TODO: or n-by-k?
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
// centrality:
//------------------------------------------------------------------------------

// TODO: utility to remove self loops, or add all self-loops (G=G+I), ...
// TODO: utility like trace(G), trace-like methods
// TODO: G =G+G', G = spones(G)

// random number generator?  vertex sampler?
// exact vs approx

// TODO make 2 different typedef enums, for VertexC. and EdgeC.

typedef enum
{
    LAGR_BETWEENNESS_FP32 = 4,
    LAGR_BETWEENNESS_FP64 = 5, 
    ...
}
LAGraph_VertexCentrality_Type ;

GrB_Info LAGraph_VertexCentrality
(
    // output:
    GrB_Vector *centrality,

    // input:
    LAGraph_Graph G,
    LAGraph_VertexCentrality_Type kind
                            // betweenness, eigenvector, degree, pagerank, ...
                            // which pagerank? parameters to pagerank?
                            // LAGR_BETWEENNESS_FP32,
                            // LAGR_BETWEENNESS_FP64
) ;

LAGraph_VertexCentrality (&degree, G, LAGR_OUTDEGREE) ;

// utility function:
LAGraph_Degree (&degree, G, kind)


GrB_Info LAGraph_EdgeCentrality
(
    // output:
    GrB_Matrix *Centrality,

    // input:
    LAGraph_Graph G,
    LAGraph_EdgeCentrality_Type kind
                            // betweeness, eigenvector, degree, pagerank, ...
                            // LAGR_BETWEENNESS_FP32,
                            // LAGR_BETWEENNESS_FP64
) ;


//------------------------------------------------------------------------------
// shortest paths:
//------------------------------------------------------------------------------

GrB_Info LAGraph_ShortestPath_[...]

GrB_Info LAGraph_ShortestPath_SingleSource
(
    // output: if NULL do not compute
    GrB_Vector *distance,       // type: INT64, FP32, or FP64
                                // INT64: if G is int*
                                // UINT64: if G is bool, uint*
                                // FP32: if G is FP32
                                // FP64: if G is FP64
    GrB_Vector *parent,         // tree
    GrB_Vector *hops,           // # of hops, level from source

    // input:
    GrB_Index source,
    LAGraph_Graph G,
) ;

GrB_Info LAGraph_ShortestPath_SingleSourceSingleDestination

GrB_Info LAGraph_ShortestPath_MultiSource ??

GrB_Info LAGraph_ShortestPath_AllPairs

//------------------------------------------------------------------------------
// what's next?
//------------------------------------------------------------------------------

GAP: BFS, SSSP, TriangleCount, Conn.Components, PageRank, BetweennessCentrality

LDBC: Local Clustering Coef, CDLP, different PageRank

