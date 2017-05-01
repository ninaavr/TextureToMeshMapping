function idx = pick_points(M)

function [txt] = myupdatefcn(~,event_obj)
        pos = get(event_obj,'Position');
        [~,idx] = ismember(pos,M.v,'rows');
        txt = {['idx: ',num2str(idx)]}; 
end

    figure, plot_mesh2(M)
    %figure, scatter3(M.VERT(:,1), M.VERT(:,2), M.VERT(:,3), 20, 1:M.n, 'filled'),
    
    h = datacursormode;
    set(h,'SnapToDataVertex','on');
    set(h,'UpdateFcn',@myupdatefcn);
        
    % Use ALT to select multiple points, and the code below to have the
    % points saved into an array.
    
%     f = getCursorInfo(h);
%     
%     a = struct2cell(f);
%     n = size(a,3);
%     
%     idx = zeros(n,3);
%     
%     for i=1:n
%         p = a(2,:,i);
%         idx(i,:) = p{1};
%     end
    
end
