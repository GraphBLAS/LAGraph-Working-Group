# GraphBLAS notation

This is a working document to come up with a notation for typesetting the pseudocode of LAGraph algorithms.

## Requirements

We would like to come up with a consistent notation in LaTeX that also has an ASCII counterpart (and it should also work in WYSIWYG presentation software).

It would be nice if the LaTeX one could be mapped to PowerPoint's equation editor (Gabor).

## Existing notations

- There are multiple notations in the 2011 GALLA book.
- The specification's notation in <https://people.eecs.berkeley.edu/~aydin/GraphBLAS_API_C_v13.pdf#page=84>.
- Tim Davis's notation in <https://people.engr.tamu.edu/davis/GraphBLAS_files/toms_graphblas.pdf#page=8> and in the SuiteSparse User Guide.
- Scott McMillan's notation in <https://resources.sei.cmu.edu/asset_files/Presentation/2016_017_001_474272.pdf#page=15>
- Manoj Kumar et al.'s notation in the CF'18 paper, <https://dl.acm.org/doi/10.1145/3203217.3205342>, Table 2.

## Questions regarding the notation

### Matrices, vectors, arrays

* How to differentiate matrices/vectors from each other? (bold/regular, lowercase/uppercase, ...)
  * There seems to be a consensus to use bold for both **A** and **w**.
  * Uppercase for matrices, lowercase for vectors?

* How to denote the transpose operation (superscript `T` or `'`)?
  * `T` seems more popular in LaTeX-based notations.
  * `'` is used in MATLAB.

* Do we differentiate row vectors from column vectors, i.e., do we use `q'A` or just `qA`?
  * I think there's no need to differentiate between them. (Gabor)

* How to typeset arrays (italic, bold, uppercase, lowercase, ...)?
  * Italic, i.e., _J_?
  * Italic bold, i.e., _**J**_?

### Masks

* How to denote masks with the 'replace' flag?
  * The spec has a separate parameter, `z`.
  * Kumar et al.'s notation uses a symbol, the double dagger `‡` to denote the 'replace' flag.
  * We could use `<<M>>` for replace. (Gabor)

* How to denote masks with the 'structure' flag?
  * `<M>` (value) and `<M.S>` (structure)

### Operations

* For matrix multiplication of `A` and `B`, do we write `AB` or spell out `A  ⊕.⊗ B`?
  * ?

* Is it allowed to use a `+=`-style notation for the accumulator, e.g., express `C = C MIN A` as `C MIN= A`?
  * ?

* How to denote common mathematical operations such 'logical and' and 'logical or'?
  * By spelling our the operator's name, i.e., `LAND`/`LOR`, or with wedge/vee symbols.
  * Same for their binary counterparts `BAND`/`BOR`, or `&`/`|`.

* How to denote the `extractElement` and `setElement` operations?
  * Seems fairly simple to have `s = C(i,j)` and `C(i,j) = s`.

* How to denote common operations such as `nvals`/`nrows`/`ncols`, `clear`, `size`?
  * It is probably simplest to just spell them out.

* How to denote the Kronecker operation?
  * I've seen the double circled times symbol and the 'kron' string used for this.

### Operators

* How to spell the `FIRST` and `SECOND` operators? `1ST`/`FIRST`, `2ND`/`SECOND`)?
  * For me, `FIRST` / `SECOND` seem better due to less havig less numbers. (Gabor)

* How to denote element-wise operations such as element-wise division?
  * Division: `DIV`, `/` or circled `/`. (See also `MINV`.)
  * Minus: `MINUS`, `-` or circled `-`.

* How to handle corner cases where an operator needs unusual element-wise semantics? E.g., sometimes it is desirable to evaluate `GrB_PLUS` with element-wise multiplication semantics.
  * Kumar et al.'s notation handles this by passing the separate operator.
  * Put the intersection/union symbol there?

### Matrix initialization

* What syntax (if any) should be used for initializing matrices/vectors? While the memory allocation itself isn't very important in a pseudocode, the dimensions of the matrix and the precise types (`UINTxx` instead of `N`) would be useful to display.
  * Do we use the mathematical symbols for number sets (`Q`/`R` vs. `FPxx`, `N` vs. `UINTxx`, `Z` vs. `INTxx`)?

* How to state the domain(s) of the semiring that an operation is evaluated on? 
  * Kumar et al.'s notation handles this by defining the semirings `S1`, `S2`, ... used in each algorithm.

### Types

* How to typeset the logical variables
  * `true`/`True`/`TRUE` or `1` or the 'top' symbol?

* How to handle conversions (both implicit and explicit) such as `float` to `boolean`?
  * ?

### Indexing

* Does the indexing start from 0 or 1?
  * I'm strongly inclined towards 0-based indexing as the API is defined in C. It's also orthogonal to the rest of the notation. (Gabor)
