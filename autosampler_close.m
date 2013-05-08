function s = autosampler_close(s)
% CLOSE_AUTOSAMPLER close the serial port object s
% Returns the serial object s

% check if it's open, try to close it if so
if strcmp(s.status,'open')
    fclose(s);
    
    % if it wasn't closed, warn
    if ~strcmp(s.status,'closed')
        warning('Serial port not closed.')
    end
    
% if it's not open, do nothing
elseif strcmp(s.status,'closed')
    warning('Already closed serial port.')
end

end