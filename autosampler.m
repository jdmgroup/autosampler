function autosampler(command,s)
% AUTOSAMPLER: send COMMAND to device on serial object s.
%% New line automatically added to COMMAND.
% Prints Arduino response.

fprintf(s,command) % 10])
pause(3)

% use fscanf instead of fread because fscanf just reads everything until it
% meets the terminator specififed in s.terminator.
% (N.B. Arduino serial.println uses CR/LF)
msg = fscanf(s);
fprintf('%s: %s\n',strcat(datestr(now)),msg)
pause(2)
end
