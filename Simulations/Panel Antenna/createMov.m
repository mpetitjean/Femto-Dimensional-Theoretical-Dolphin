  
filename = input('Enter the basename of input files : ', 's');
filename_out = input('Enter the name of output movies : ', 's');
mov = raw2movie(filename,1,5);

v = VideoWriter(filename_out);

sat = size(mov(1).cdata);
for i = 2:max(size(mov))
    mov(i).cdata = mov(i).cdata(1:sat(1),1:sat(2),:);
end

open(v)
writeVideo(v, mov);
close(v)