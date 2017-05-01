function plotM = plot_mesh(N)
%draws the mesh and the three buttons
    plotM = trisurf(N.f.v,N.v(:,1),N.v(:,2),N.v(:,3),zeros(size(N.v,1),1));
    axis equal
	xlabel('X')
	ylabel('Y')
	zlabel('Z')
    rotate3d on
    set_button();  
    reset_button();
    ready_button();
end

function set_button(idx)
btn = uicontrol('Style', 'pushbutton', 'String', 'Set',...
        'Position', [20 60 50 20],...
        'Callback', @pushbutton_callback); 
    function pushbutton_callback(src,event)
        global is_set;
        is_set = 1;
        display('Set Button pressed');
    end

end

function reset_button()
btn = uicontrol('Style', 'pushbutton', 'String', 'Reset',...
    'Position', [20 40 50 20],...
        'Callback', @pushbutton_callback); 
    function pushbutton_callback(src,event)
        display('Reset Button pressed');
        global reset;
        reset = 1;
    end
end

function ready_button( )
 btn = uicontrol('Style', 'pushbutton', 'String', 'Ready',...
        'Position', [20 20 50 20],...
        'Callback', @pushbutton_callback); 
    function pushbutton_callback(src,event)
        global ready;
        ready = 1;
        display('Ready Button pressed');
    end
end