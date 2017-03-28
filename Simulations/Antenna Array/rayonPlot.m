function data =rayonPlot(filename, centerX, centerY, r)

fid = fopen(filename,'rb');
if fid == -1
  error(['rrayonPlot: could not open data file ',filename])
end

% determine image size
size_x = fread(fid,1,'single');
size_y = fread(fid,1,'single');

% read data
data = flipud(transpose(...
    reshape(fread(fid,size_x*size_y,'single'),size_x,size_y)...
    ));

figure;
theta = -pi/2:pi/64:pi/2;
x = round(r*cos(theta));
y = round(r*sin(theta));

rayon = zeros(1, length(theta));
for i=1:length(theta)
    rayon(i) = max(data(centerX+x(i)-3:centerX+x(i)+3, centerY+y(i)));
end
rayon = rayon + min(min(rayon));

polar(theta, rayon);
