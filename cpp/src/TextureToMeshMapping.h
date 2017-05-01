#ifndef TEXTURETOMESHMAPPING_H_
#define TEXTURETOMESHMAPPING_H_

#include <iostream>
#include <CGAL/Parameterization_polyhedron_adaptor_3.h>
#include <CGAL/parameterize.h>
#include <CGAL/LSCM_parameterizer_3.h>
#include "TexturedPolyhedron/Textured_polyhedron.h"
#include "PolyhedronBuilder/Textured_polyhedron_builder.h"
#include "PolyhedronBuilder/Polyhedron_builder.h"
#include "IO/Reader.h"
#include "IO/Writer.h"
#include "Free_matrix_loader.h"
#include "Pinned_matrix_loader.h"
#include "Matrix_solver.h"
/*#include "CPPUnitTests/SeamPinnedTestSuite.h"
#include "CPPUnitTests/CalculationsTestSuite.h"
#include "CPPUnitTests/LoadingTestSuite.h"
#include "CPPUnitTests/Runner.h"*/

using namespace std;

class Texture_To_Mesh_Mapping {
private:
    typedef CGAL::Simple_cartesian<double> K;
	typedef CGAL::Polyhedron_3<K> Polyhedron;
	typedef Textured_polyhedron<K, Textured_items> TexturedPolyhedron;
    typedef TexturedPolyhedron::Halfedge_handle Halfedge_handle;
	typedef TexturedPolyhedron::HalfedgeDS HalfedgeDS;
	typedef Textured_Polyhedron_builder<HalfedgeDS, Polyhedron, TexturedPolyhedron, K> Textured_builder;
public:
	Texture_To_Mesh_Mapping();
	virtual ~Texture_To_Mesh_Mapping();
	/** previous main file, builds the mesh and sets the pinned vertices and the seam, preforms the 
	*conformal mapping and stores the result in output.obj
	* @param pinned the IDs of the pinned vertices directly followed by their texture coordinates
	* @param seam IDs of the vertices that lie on the seam
	* @param coords 3D coordinates for each vertex
	* @param tris IDs for each vertex at each triangle
	* @param sizes the length of the rpevious inputs in the same order */
	void textureToMeshMapping(double *pinned, double *seam, double* coords, double* tris, double* sizes);
};
#endif
