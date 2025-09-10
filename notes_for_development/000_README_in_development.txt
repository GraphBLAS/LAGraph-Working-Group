Sept 10, 2025:

    consider these methods for src.  Minor revisions needed in some of them,
    including API revisions:

        LAGr_BreadthFirstSearch_Extended.c: uses LG_:
            LG_BreadthFirstSearch_SSGrB_Extended.c
            LG_BreadthFirstSearch_vanilla_Extended.c
        LAGr_PeerPressureClustering.c
        LAGraph_AllKCore.c: need both basic & adv methods; this is mixed
        LAGraph_AllKTruss.c
        LAGraph_HITS.c
        LAGraph_Hdip_Fiedler.c: needs lots of polish
        LAGraph_KCore.c: need both basic & adv
        LAGraph_KTruss.c
        LAGraph_MaximalIndependentSet.c: rename LAGr_, need a basic method
        LAGraph_SquareClustering.c
        LAGraph_VertexCentrality_Triangle.c
        LAGraph_coloring_MIS.c
        LAGraph_coloring_independent_set.c
        LAGraph_lcc.c
        LAGraph_cdlp.c: use Container methods

    these need "vanilla" methods, or do we abandon the need for vanilla
    methods and just require SuiteSparse:GraphBLAS?

        LAGr_EdgeBetweennessCentrality.c
        LAGr_MarkovClustering.c (but see latest issue posted)
        LAGr_Modularity.c
        LAGr_PartitionQuality.c
        LAGr_SwapEdges.c
        LAGraph_SwapEdges.c
        LAGraph_CFL_reachability.c
        LAGraph_EstimateDiameter.c
        LAGraph_ExactDiameter.c
        LAGraph_FastGraphletTransform.c
        LAGraph_KCoreDecompose.c
        LAGraph_MultiSourceBFS.c
        LAGraph_RegularPathQuery.c
        LAGraph_RichClubCoefficient.c
        LAGraph_scc.c
        LG_CC_FastSV5.c
        LG_CC_FastSV7_FA.c

    Algorithms need work:

        LAGr_MaxFlow.c (need to provide output R matrix?  And flow_matrix is
                expensive to compute; revise)
        LAGraph_argminmax.c
        LAGraph_msf.c
        LAGraph_BF_*.c: need just one variant

    need new LAGraph_Graph enums:

        LAGraph_MaximalMatching.c: need LAGraph_Graph incidence matrix
        LAGraph_Coarsen_Matching.c: need LAGraph_Graph incidence matrix,
            and vanilla method
        LAGr_MaximumMatching.c:  need to switch to Container methods;
            need LAGraph_Graph bipartite graph, and vanilla method
        LAGraph_cc_lacc.c: unsure

    do not consider:

        LAGr_PageRankGX.c: for LDBC benchmarks only
        LAGr_TriangleCount_GPU.c: for testing draft GPU kernels only
        LAGraph_dnn.c: for an IEEE HPEC Graph Challenge only
        LAGraph_HelloWorld.c: will always be experimental
        LAGraph_cdlp_withsort.c: OK, but slow, see LAGraph_cdlp instead

