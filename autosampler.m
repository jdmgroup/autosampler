function msg = autosampler(command,s)
% AUTOSAMPLER: send COMMAND to device on serial object s.
% Returns Arduino response MSG
% New line automatically added to COMMAND.

fwrite(s,[command 10])
pause(1)

read_byte = fread(s,s.bytesavailable);
fprintf('%s: %s\n',strcat(datestr(now)),char(read_byte'))
end
