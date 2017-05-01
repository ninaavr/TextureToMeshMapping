% determines which vertices to fix to texture coordinates
% INPUT: "seam", "neighbours"
%
% "seam" - 2 texture ends (0.2, 0.2) and (0.2, 0.8) to seam vertex
% "neighbours" - 2 texture points (0.2, 0.2) and (0.2, 0.222) are connected to
% vertices close to each other on the mesh (numerically instable, 
% better fix vertices further from each other)
function pinnedV = select_pinned(pinned_type, mesh)
global seam;
if(pinned_type == "seam")
    i = round(size(seam, 2)/5);
    while(sum(seam(:) == seam(1,i)) ~= 1)
        i = i+1;
    end
    pinnedV = [seam(1,i), 0.2, 0.2, seam(1,i), 0.2, 0.8];
else if(pinned_type == "neighbours")
        i = 1;
        %select vertices not in seam
    while ((sum(seam(:) == mesh.f.v(i,1)) ~= 0) && (sum(seam(:) == mesh.f.v(i,2)) ~= 0))
        i = i +1;
    end
        pinnedV = [mesh.f.v(i,1), 0.2, 0.2, mesh.f.v(i,2), 0.2, 0.222];
    else
        DISP("Error! Inalid input at select_pinned!")
    end
end

