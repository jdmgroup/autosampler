function [s,status] = open_autosampler(port)
% OPEN_AUTOSAMPLER opens the serial port to the autosampler on PORT
% Returns the serial object s

% Some defaults - laziness
if nargin == 0
    port = default_port();
end

%% check if serial port is already open
% if it's not, open and give a warning

s = instrfind('port',port,'status','open');

if length(s) == 1
    warning('Serial port %s already open.',port)
elseif length(s) == 0
    s = serial(port);
    s.baudrate = 9600;
    s.terminator = 'LF';
    fopen(s)
end

pause(2.5)

if strcmp(s.status,'open')
    status = 1;
else
    status = 0;
end

end