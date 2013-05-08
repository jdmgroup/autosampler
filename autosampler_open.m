function s = autosampler_open(port)
% OPEN_AUTOSAMPLER opens the serial port to the autosampler on PORT
% Returns the serial object s

% Some defaults - laziness
if nargin == 0
    port = default_port();
end

%% check if serial port is already open
% if it's not, open and give a warning

s = instrfind('port',port,'status','open');

if isempty(s)
    s = serial(port);
    s.baudrate = 9600;
    s.terminator = 'CR/LF';
    fopen(s);
else
    warning('Serial port %s already open.',port)
end

pause(3)
end