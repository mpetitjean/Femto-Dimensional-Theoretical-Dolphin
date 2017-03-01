  
filename = input('Enter the basename of input files : ', 's');
filename_out = input('Enter the name of output movies : ', 's');
mov = raw2movie(filename);

v = VideoWriter(filename_out);

sat = size(mov(1).cdata);
for i = 2:max(size(mov))
    mov(i).cdata = mov(i).cdata(:,end-sat(2)+1:end,:);
end

open(v)
writeVideo(v, mov);
close(v)