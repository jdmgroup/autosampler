s = autosampler_open();

%autosampler('0',s) % valve to waste at start

for i = 1:7
    i
    
    % collect
    autosampler('1',s)
    
    % waste
    autosampler('0',s)
    
    % switch
    autosampler('2',s)
    
end

%autosampler('0',s)

s = autosampler_close(s);