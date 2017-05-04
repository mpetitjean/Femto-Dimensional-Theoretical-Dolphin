filename = 'arr.0';

fid = fopen(filename,'rb');

if fid == -1
  error('File not found')
end

size_x = fread(fid,1,'single');
size_y = fread(fid,1,'single');

data = flipud(transpose(...
       reshape(fread(fid,size_x*size_y,'single'),size_x,size_y)));
r = 330;
centerX = -8;
centerY = 250;
ii = 1;

for theta = -pi/4:pi/64:pi/4
    x = round(r*cos(theta));
    y = round(r*sin(theta));
    power(ii) = abs(data(centerX+x, centerY+y))^2;
    % 6.25 sylla
    theta = theta + pi/2+pi/6;
    th(ii) = (sin(theta)^3) * (sin(4*pi*cos(theta))^2) / (sin(pi*cos(theta))^2);
    ii = ii+1;
end
% power = power+abs(min(power))
power = power/max(power);
th = th/max(th);

for ii = 1:length(power)
    if power(ii) == 1
        power(ii) = 0;
    end
end

figure
polarplot([-pi/4:pi/64:pi/4]+pi/20,power,'bo');
hold on;
polarplot([-pi/4:pi/64:pi/4],th,'r')
%polarplot(11*pi/6,1,'bo')
legend('Simulation', 'Theory')


% A = [ ([-pi/4:pi/64:pi/4]+pi/6)' power' [-pi/4:pi/64:pi/4]' th' ];
% A = [ pol2cart(A(:,1),A(:,2)) pol2cart(A(:,3),A(:,4)) ];
% csvwrite('array.csv',A);