s = autosampler_open()

autosampler('0,0',s) % valve to waste at start

% sample 1
autosampler('0,1',s) % valve to samples
autosampler('0,0',s) % valve to waste

% sample 2
autosampler('1,2',s) % move to new position
autosampler('0,1',s) % valve to samples
autosampler('0,0',s) % valve to waste

% sample 3
autosampler('2,3',s) % move to new position
autosampler('0,1',s) % valve to samples
autosampler('0,0',s) % valve to waste

% sample 4
autosampler('3,4',s) % move to new position
autosampler('0,1',s) % valve to samples

s = autosampler_close(s); % and switch valve to waste
