% getData
clear; close all;
basename = 'SAR';
start = 0;
len = 97;
frame=start;
data = zeros(201,201,len);
filename = sprintf('%s.%d',basename,frame);
fid = fopen(filename,'rb');

if fid == -1
  error(['raw2movie: initial frame not found: ',filename])
end

while frame < start+len
  size_x = fread(fid,1,'single');
  size_y = fread(fid,1,'single');

  data(:,:,frame-start+1) = flipud(transpose(...
           reshape(...
             fread(fid,size_x*size_y,'single'),size_x,size_y)...
	 ));
 
 frame=frame+1;
  filename = sprintf('%s.%d',basename,frame);
  fid = fopen(filename,'rb');
end


RMS = rms(data,3);
l = 29/2;
L = 38/2;
indy = 0;
indx = 0;
changex = 0;
for mm = 1:201
    changex = 1;
    %indy = 0;
    xLocation = mm - 100 -1;
    for nn = 1:201
        yLocation = nn - 100 -1;
        if (((xLocation/L)^2+(yLocation/l)^2)<=1)
            indy = indy +1;
            if changex
                indx = indx +1;
                changex = 0;
            end
            %URMS{indx,1}(indy) = RMS(mm,nn);  
            URMS(indy) = RMS(mm,nn);
        end
    end
end

1.3*sum(abs(URMS).^2)/(1.08*pi*29*38/4)
