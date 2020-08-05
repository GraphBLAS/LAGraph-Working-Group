// June 17, 2020, LAGraph discussion

LAGraph_Info LAGraph_vertex_bc
(
    GrB_Vector *c,
    const LAGraph_Graph A
)

LAGraph_Info LAGraph_edge_bc
(
    LAGraph_Graph *E,
    const LAGraph_Graph A
)

LAGraph_Info LAGraph_top_k
(
    list *x,
    const LAGraph_Graph E
)

E = f (A)
x = g (E)
x = g (f (A))

desc->query true/false
desc->algorithm char *
    ""  (auto)
    "priority queue:other stuff:more stuff:"
    "batch"
    "stuff"
    "..."

LAGraph_Info LAGraph_bc
(
    LAGraph_descriptor desc,
    GrB_Vector *c,
    const LAGraph_Graph A,
    GrB_Vector sources,
)

LAGraph_Info LAGraph_bc_Y
(
    LAGraph_descriptor desc,
    GrB_Vector *c,
    const LAGraph_Graph A,
    GrB_Vector sources,
    LAGraph_Random rand
)

LAGraph_Info LAGraph_bc_Z
(
    LAGraph_descriptor desc,
    GrB_Vector *c,
    const LAGraph_Graph A,
    LAGraph_Random rand
)

LAGraph_descriptor :  
    ignore edge weights
    treat graph as undirected, even though A.stuff says otherwise


#define LAGraph_bc(arg1,...)
    _Generic ((arg1),
        LAGraph_descriptor:  LAGraph_bc_X,
        default: LAGraph_bc_easy )
        (arg1, __VA_ARGS__)


