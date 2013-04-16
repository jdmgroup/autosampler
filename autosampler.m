function status = autosampler(command,s)
% AUTOSAMPLER: send COMMAND to device on serial object s.
% Returns true or false depending whether Arduino responded correctly
% New line automatically added to COMMAND.

fwrite(s,[command 10])

pause(2)
read_byte = fread(s,s.bytesavailable);

%% check arduino responded correctly
returned = char(read_byte');
expected = strcat('received:',command);
status = strfind(returned,expected);

end
