#include "TextureToMeshMapping.h"

Texture_To_Mesh_Mapping::Texture_To_Mesh_Mapping(){
	};
Texture_To_Mesh_Mapping::~Texture_To_Mesh_Mapping(){
	};

void Texture_To_Mesh_Mapping::textureToMeshMapping(double *pinned, double *seam, double* coords, double* tris, double* sizes) {
    int numPinned = (int)sizes[0];
    int numSeam = (int) sizes[1];
    std::vector<double> coords2;
	std::vector<int> tris2;
    
    //copy input arrays in std vectors
    for(int i = 0; i < (int)sizes[2]; ++i)
        coords2.push_back(coords[i]);
    for(int i = 0; i < (int)sizes[3]; ++i)
        tris2.push_back((int)tris[i]-1);
    
	//builds textured polyhedron builder and from it also textured polyhedron
	Textured_builder tb(coords2, tris2);
	TexturedPolyhedron tp;
	
    tp.delegate(tb);
	//sets vertices IDs
    tp.set_ids();
 


	//run(TestSeamAndPinn::suite());
	//run(CalculationsTest::suite());
	//run(LoadingTest::suite());
  
	std::list<TexturedPolyhedron::Halfedge_iterator> bord;
	TexturedPolyhedron::Halfedge_iterator hi, start;
    typename std::list<Halfedge_handle>::iterator it;
    it = bord.begin();
    //get begin of the seam
	hi = tp.halfedges_begin();
    while (hi->vertex()->id() != (int) seam[0]-1)
        ++hi;
    
    for(int i = 1; i < numSeam; ++i){
        start = hi; //if hi gets back to start and next seam is not found, then the seam is broken
        while ((hi->opposite()->vertex()->id() != (int) seam[i]-1) && (start!=hi->next_on_vertex())){
            hi = hi->next_on_vertex();  
        } 
        if(start==hi->next_on_vertex()){
            hi = tp.halfedges_begin();
            while((hi->opposite()->vertex()->id() != (int) seam[i]-1)&&
                    (hi->vertex()->id() != (int) seam[i+1]-1))
                ++hi;
            ++i;
        }else{
            hi = hi->opposite();
            bord.push_back(hi);
        }
    }
    
    
    
    
    
    
    //sets pinned vertices
    int idx = 0;
    for(int i = 0; i != (int) sizes[0]; i+=3){
        hi = tp.halfedges_begin();
        while (hi->vertex()->id() != (int) pinned[i]-1)
            ++hi;
        //this is a seam vertex and the first side is already set
        if(hi->vertex()->u()[0]!=-1)
            ++idx;
        hi->vertex()->u()[idx] = pinned[i+1];
        hi->vertex()->v()[idx] = pinned[i+2];
        idx = 0;
    }
	tp.set_seam(bord);
	//cout<<tp.seam->size()<<endl;


	tp.compute_normals_per_facet();

	Eigen::SparseMatrix<double> Mf;
	Free_matrix_loader fml;
	fml.load_M(tp, Mf);

	Eigen::SparseMatrix<double> Mp;
	Eigen::SparseMatrix<double> U;
	Pinned_matrix_loader pml;
	pml.load_M(tp, Mp);
	pml.load_U(tp, U);
	Matrix_solver ms;
	Eigen::VectorXd x;
	ms.solve_system(Mf, Mp, U, x);
	fml.store_result(x, tp);
	//writes textured polyhedron in  an .obj file
	Writer w;
	w("output.obj", tp);
	cout << "Conformal mapping performed!" << endl; 
};
