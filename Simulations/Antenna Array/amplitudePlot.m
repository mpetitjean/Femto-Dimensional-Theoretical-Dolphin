filename = input('Enter the name of the input file : ', 's');

fid = fopen(filename,'rb');
if fid == -1
  error(['raw2image: could not open data file ',filename])
end

% determine image size
size_x = fread(fid,1,'single');
size_y = fread(fid,1,'single');

% read data
data = flipud(transpose(...
    reshape(fread(fid,size_x*size_y,'single'),size_x,size_y)...
    ));

start_x = 70;
end_x = 100;
start_y = 30;
end_y = 60;

figure;
surf(start_y:end_y, start_x:end_x, data(start_y:end_y, start_x:end_x))
xlabel('Y coordinate')
ylabel('X coordinate')
zlabel('Relative amplitude of the field (log)')
