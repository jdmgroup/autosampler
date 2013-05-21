clear
clc

for i = 1:7
    i
    
    % collect
    autosampler('1')
    
    pause(480)
    
    % waste
    autosampler('0')
    
    % switch
    autosampler('2')
end