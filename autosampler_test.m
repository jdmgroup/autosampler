% Test script that goes around the whole carousel: valve on, pause, off and
% advance to the next position.

cmd = repmat([1 0 2],1,7)

pausetime = input('Enter pause time in seconds:\n')

for i = 1:length(cmd)

    i
    cmd(i)
    
if cmd(i) == 0
    fprintf('%s: pausing for %i s before sending command\n',...
        datestr(now),pausetime)
    pause(pausetime)
end

autosampler(num2str(cmd(i)))

end