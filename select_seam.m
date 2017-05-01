%calls plot_mesh, reads points selected by user and calls dijkstra to
%determine shortest path between them
function idx = select_seam(M, G)
    function [txt] = myupdatefcn(~,event_obj)
        pos = get(event_obj,'Position');
        [~,idx] = ismember(pos,M.v,'rows');
        txt = {}; %{['idx: ',num2str(idx)]}; 
    end

    function text_to_display = datatiptxt(~, ~, ~)
        text_to_display = {};
    end

%initialize
global seam;
seam = [];
global ready;
ready = 0;
global is_set;
is_set = 0;
global reset;
reset = 0;
pl = [];
G2=0;

% Use ALT/Shift to select multiple points, and the code below to have
% the points saved into an array.

fig = figure; plotM = plot_mesh(M);
h = datacursormode();
set(h,'SnapToDataVertex','on');
set(h,'UpdateFcn',@myupdatefcn);

while(~ready)
    while(~is_set && ~ready && ~reset && ishandle(fig))
        pause(0.1);
    end
    if(~ishandle(fig))
        ready = 1;
    end
    if(is_set)
        is_set = 0;
        
        %loads selected by user points to idx
        f = getCursorInfo(h);
        a = struct2cell(f);
        n = size(a,3);
        pos = zeros(n,3);
        for i=1:n
            p = a(2,:,i);
            pos(i,:) = p{1};
            [~,idx] = ismember(pos,M.v,'rows');
        end
        
        %case for the first two connected points
        if(size(idx,1)==2)
            [~, L, ~] = graphshortestpath(G,idx(1),idx(2),'Directed', false,'Method','Dijkstra');
     
            hold on;
            pl = [pl,plot3(M.v(L(1,:),1),M.v(L(1,:),2),M.v(L(1,:),3), 'color', 'r', 'LineWidth', 3)];
            seam = L(1,:);
        else
            %case for selected points after first found path
            %applies Dijkstra on multiple start points, if user
            %selected 3 or more points at the beginning nothing happens
            if(size(idx,1)>2 && size(seam,1)>0)
                if(G2==0)
                    sPoints = zeros(size(M.v,1),1);
                    sPoints(seam)=1;
                    sPoints(seam(size(seam,1))) = 0;
                    G2 = [[G;sPoints'],[0;sPoints]];
                end
                [~, L, ~] = graphshortestpath(G2,(size(G2,1)),idx(1),'Directed', false,'Method','Dijkstra');
                
                %c++ supports only 2 branches for a vertex
                %so we do not connect a third branch the vertex that
                %already has one
                G2 (size(G2,1), L(1,1)) = 0;
                G2 (L(1,1), size(G2,1)) = 0;
                
                seam = [seam, L];
                n = size(L,2)-1;
                hold on;
                pl = [pl,plot3(M.v(L(1,2:n),1),M.v(L(1,2:n),2),M.v(L(1,2:n),3), 'color', 'r', 'LineWidth', 3)];
            end
        end
    end
    if(reset)
        h.removeAllDataCursors
        delete(pl);
        seam = [];
        reset = 0;
    end
end
close all;
end
