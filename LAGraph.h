
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

info = LAGraph_whatever (&level, NULL, G, Src, 5) ;
if info is 'error' then level is returned as level == NULL.

// expert function:
GrB_Info LAGraph_BreadthFirstSearch_Frontier
(
    // input/output:
    GrB_Vector level,
    GrB_Vector parent,
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

// this: easy mode
GrB_Vector centrality ; // uninit
LAGraph_something (&centrality, ...)
// then for 'expert' mode
GrB_Vector x ; // 
LAGraph_something_init (&x, ...)     or GrB_Vector_new (&x, n, 1, INT32)
    for a billion times:
        LAGraph_something_tiny (x, ...)        // reuse it, might be faster

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
// or:
LAGraph_Degree_in (&degree, G)
LAGraph_Degree_out (&degree, G) // ... etc
LAGraph_Degree_etc (&degree, G) // ... etc

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
    // output:
    LAGraph_info *LGInfo,

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
    LAGraph_Graph G 
) ;

    // negative-weight-cycle: result is not defined, must stop!
    // report info = GrB_NO_VALUE. or something else

// there is no:
GrB_set_error (C, string)
char *GrB_Matrix_error (GrB_Matrix C) ;
char *GrB_error (object) ; // polymorphic

// one solution:  but what if 2 LAGraph calls want to use G at the same time?
// G is input, and GrB_Matrix_wait(G->A) has been done so it is read-only.
// ... except for the error string here...
    char *LAGraph_report (G) ;

// another solution:
typedef struct
{
    GrB_Info info ;
    char message [128] ;
}
LAGraph_Info ;

typedef enum    // we need an LAGraph_Info
{
    // success, but ...:
    GrB_SUCCESS = 0,            // all is well
    GrB_NO_VALUE = 1,           // A(i,j) requested but not there

    // API errors:
    GrB_UNINITIALIZED_OBJECT = 2,   // object has not been initialized
    GrB_INVALID_OBJECT = 3,         // object is corrupted
    GrB_NULL_POINTER = 4,           // input pointer is NULL
    GrB_INVALID_VALUE = 5,          // generic error code; some value is bad
    GrB_INVALID_INDEX = 6,          // a row or column index is out of bounds;
                                    // used for indices passed as scalars, not
                                    // in a list.
    GrB_DOMAIN_MISMATCH = 7,        // object domains are not compatible
    GrB_DIMENSION_MISMATCH = 8,     // matrix dimensions do not match
    GrB_OUTPUT_NOT_EMPTY = 9,       // output matrix already has values in it

    // execution errors:
    GrB_OUT_OF_MEMORY = 10,         // out of memory
    GrB_INSUFFICIENT_SPACE = 11,    // output array not large enough
    GrB_INDEX_OUT_OF_BOUNDS = 12,   // a row or column index is out of bounds;
                                    // used for indices in a list of indices.
    GrB_PANIC = 13                  // unknown error, or GrB_init not called.
}
GrB_Info ;

GrB_Matrix_error (&s, A) ;

            // later: or not at all:
            // GrB_Info LAGraph_ShortestPath_SingleSourceSingleDestination
            // GrB_Info LAGraph_ShortestPath_MultiSource ??

GrB_Info LAGraph_ShortestPath_AllPairs
(
    // input/output:
    LAGraph_Info *info,
    // output:
    GrB_Matrix *Distance,
    GrB_Matrix *Parent,
    GrB_Matrix *Hops,
    // input:
    LAGraph_Graph G,
) ;

// Dist, Parent undefined on input, created on output, just like GrB_Matrix_new
info = LAGraph_something (&Dist, &Parent, NULL, G) ;

//------------------------------------------------------------------------------

    LAGraph_Info lginfo ;   // fixed size, no malloc

    typedef struct
    {
        int64_t info ;     // algorithm specific, warning > 0, ok 0, err<0
        char message [120] ;
    }
    LAGraph_Info ;

    LAGraph_ShortestPath_AllPairs (Dis, Pa, Hop, G, NULL) ;
    i = LAGraph_utility (stuff, G, NULL) ;    // no LAGraph_Info needed

    GrB_Info info = LAGraph_ShortestPath_AllPairs (Dis, Pa, Hop, G, &lginfo) ;
    if (info != GrB_SUCCESS) 
    {
        printf ("oops %d:%s\n", lginfo.info, lginfo.message) ;
    }

    GrB_Info info = LAGraph_BFS (&level, source, G) ;


    
//------------------------------------------------------------------------------
// what's next?
//------------------------------------------------------------------------------

GAP: BFS, SSSP, TriangleCount, Conn.Components, PageRank, BetweennessCentrality

LDBC: Local Clustering Coef, CDLP, different PageRank

