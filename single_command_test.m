if ispc == true
    port = 'COM3';
elseif ismac == true
    port = '/dev/tty.usbmodemfa131';
end

s = serial(port)
s.baudrate = 9600;
s.terminator = '';

cmd = '0'

try 
    fopen(s)
    fprintf(s,cmd)
    
    cont = false;
    while cont == false
        % short pause, then check the number of bytes available
        pause(0.1)
        q1 = s.bytesavailable()
        
        if q1 == 0                  % no bytes available
            cont = false            % restart loop
        elseif q1 > 0              % bytes available
            pause(0.5)              % wait
            q2 = s.bytesavailable() % check again
            
            if q1 == q2             % same number of bytes as last time?
               cont = true          % exit loop
            else
                cont = false        % continue loop
            end
        end
    end
  
    response = fread(s,q2)
    char(response')
    fclose(s)

catch 
    fclose(s)
end