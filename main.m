% lambda:
% determines how much to take into account the curvature by shortest 
% path calculations:  from 0 - used only Euclidean distance to 1 - only curvature 

% pinnedType:
% determines which vertices to fix to texture coordinates
% "seam" - 2 texture ends to seam vertex
% "neighbours" - close texture points to close vertices on the mesh
% instead of calling select_pinned, pinnedV could be determined manually
% pinnedV = [v1_ID, u_1, v_1, v2_ID, u_2, v_2, ...];
% for pin seam, repeat the ID of the vertex in v2_ID
% Warning: do not pin only one texture point at seam vertex
% to determine neighbour points manually call: 
% m = load_obj("*.obj") and pick_points(m)

%PARAMETERS TO BE SET
filename = 'centaur2.obj';
lambda = 0;
pinnedType = "neighbours";


mesh = load_obj(filename);
G = load_G(mesh,lambda);
select_seam(mesh, G);
global seam;
%call after seam is selected
pinnedV = select_pinned(pinnedType, mesh);
coords = reshape(mesh.v',1, []);
tris = reshape(mesh.f.v',1, []);
sizes = [size(pinnedV, 2), size(seam, 2), size(coords, 2), size(tris, 2)];
CXX_caller(pinnedV, seam, coords, tris, sizes);