function plot_mesh(N)
    trisurf(N.f.v,N.v(:,1),N.v(:,2),N.v(:,3),zeros(size(N.v,1),1));
    axis equal
	xlabel('X')
	ylabel('Y')
	zlabel('Z')
    rotate3d on
end
