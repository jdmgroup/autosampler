function autosampler(cmd)

s = serial('COM3');
s.baudrate = 9600;
s.terminator = '';

fopen(s);
fprintf(s,cmd);

cont = false;
while cont == false
    pause(0.5)
    q1 = s.bytesavailable()
    
    if q1 == 0
        cont = false;               % restart loop
    elseif q1 > 0
        pause(0.1)                  
        q2 = s.bytesavailable()    % check again
        
        if q1 == q2                 % same number of bytes as last time?
            cont = true;            % exit loop and read buffer
        else
            cont = false;           % restart loop
        end
    end
end

response = fread(s,q2);

response = char(response');

fprintf('%s: %s\n',datestr(now),response)

fclose(s)

end