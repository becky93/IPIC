function lenna_equ=histeq_gray(lenna);
lenna = rgb2gray(lenna);
%lenna = rgb2gray(lenna);
[row, col] = size(lenna);
lenna_equ=zeros(row,col);
histogram=zeros(256);
cdf=zeros(256);

%imhist(lenna)

%get histogram
for i=1:row
   for j=1:col
      k=lenna(i,j);
      histogram(k+1)=histogram(k+1)+1;
   end
end
%get cdf
cdf(1)=histogram(1);
for i=2:256
   cdf(i)=cdf(i-1)+histogram(i);
end
%run point operation
for i=1:row
   for j=1:col
		k=lenna(i,j);
      lenna_equ(i,j)=((cdf(k+1))*256/(row*col));
   end
end
lenna_equ = uint8(lenna_equ);

%生成直方图均衡化后的lenna图

