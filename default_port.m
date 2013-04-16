function port = default_port()
% DEFAULT_PORT returns the default ports for the autosampler
if ispc == true
    port = 'COM3';
elseif ismac == true
    port = '/dev/tty.usbmodemfa131';
end

end