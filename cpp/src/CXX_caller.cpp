/*==========================================================
 * arrayProduct.c - example in MATLAB External Interfaces
 *
 * Multiplies an input scalar (multiplier) 
 * times a 1xN matrix (inMatrix)
 * and outputs a 1xN matrix (outMatrix)
 *
 * The calling syntax is:
 *
 *		outMatrix = arrayProduct(multiplier, inMatrix)
 *
 * This is a MEX-file for MATLAB.
 * Copyright 2007-2012 The MathWorks, Inc.
 *
 *========================================================*/

#include "extern/include/mex.h"
#include "TextureToMeshMapping.h"

/* The computational routine */
void CXX_caller(double *pinned, double *seam, double* coords, double* tris, double* sizes)
{
    Texture_To_Mesh_Mapping tp;
    tp.textureToMeshMapping(pinned, seam, coords, tris, sizes);
}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    double *pinned;
    double *seam;
    double *coords;
    double *tris;
    double *sizes;

    /* check for proper number of arguments */
    if(nrhs!=5) {
        mexErrMsgIdAndTxt("CXX_caller:nrhs","Two inputs required.");
    }
    if(nlhs!= 0) {
        mexErrMsgIdAndTxt("CXX_caller:nlhs","None output required.");
    }
    /* check that number of rows in input arguments is 1 */
    for(int i= 0; i < 4; ++i){
        if(mxGetM(prhs[i])!=1) {
            mexErrMsgIdAndTxt("CXX_caller:notRowVector","Input must be a row vector.");
        }
    }
    /* check that sizes has 4 values*/
    if(mxGetN(prhs[4])!=4) {
        cout << mxGetN(prhs[4]) << endl;
        mexErrMsgIdAndTxt("CXX_caller:incorrectSize","Sizes has to conatin 4x1 values - size for each argument.");
    }
    
    pinned = mxGetPr(prhs[0]);
    seam = mxGetPr(prhs[1]);
    coords = mxGetPr(prhs[2]);
    tris = mxGetPr(prhs[3]);
    sizes = mxGetPr(prhs[4]);
    
    /* call the computational routine */
    CXX_caller(pinned, seam, coords, tris, sizes);
}