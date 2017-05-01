function G = load_G(mesh, weight)
%LOAD_G calculates distances between the vertices and loads them in
%adjacency matrix,which is used in dijkstra, weight determines how much we
%take into account the shape of the the object 1 - 100%, 0 - only distance
%is taken into account
if(weight<0 || weight>1)
    display('Error! weight must be between 0 and 1');
end
size_v = size(mesh.v,1);
edges = compute_edges(mesh.f.v);
[~, fn] = compute_normal(mesh.v, mesh.f.v);
A = compute_edge_face_ring(mesh.f.v);
G = sparse(size_v,size_v, inf);
dist = abs(mesh.v(edges(1,:),:) - mesh.v(edges(2,:),:));
dist = (sum(dist,2));
for i = 1:size(edges,2)
    angle = 10;
    if(A(edges(1,i),edges(2,i))>0 && A(edges(2,i),edges(1,i))>0) %if some faces are missing
        n1 = fn(:,A(edges(1,i),edges(2,i)));
        n2 = fn(:,A(edges(2,i),edges(1,i)));
        angle3D = n1 .*n2;
        angle= sum(angle3D) + 1;
    end
        G(edges(1,i),edges(2,i)) = (1-weight)*dist(i) + weight*angle;
        G(edges(2,i),edges(1,i)) =  G(edges(1,i),edges(2,i));
end
end