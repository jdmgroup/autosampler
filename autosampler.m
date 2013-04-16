function status = autosampler(command,port)
    % AUTOSAMPLER: send COMMAND to device on serial port PORT.
    % Returns true or false depending whether Arduino responded correctly
    % New line automatically added to COMMAND.

%% Default arguments for testing/convenience
if nargin <= 1
    if ispc == true
        port = 'COM3';
    elseif ismac == true
        port = '/dev/tty.usbmodemfa131';
    end
end

if nargin == 0
    command = '1,2';
end

%% serial commands
s = serial(port);
s.baudrate = 9600;
s.terminator = 'LF';

fopen(s)
pause(2.5)

% use try catch so that the connection is always closed
try
    % For some reason the Arduino always ignores the first load of bytes
    % written to it, so just write a new line before the command.
    % fwrite(s,49)
    
    fwrite(s,[command 10])
    
    pause(2)
    read_byte = fread(s,s.bytesavailable);
    fclose(s)
    
catch exception
    fclose(s)
    throw(exception)
end

%% check arduino responded correctly
returned = char(read_byte');
expected = strcat('received:',command);
status = strfind(returned,expected);

end
