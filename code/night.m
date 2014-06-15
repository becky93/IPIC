f=imread('G:\\seg17\\SAM_1082.JPG');%获取HSV图像
f=imresize(f,0.8); 
A=rgb2hsv(f);
H=A(:,:,1);
S=A(:,:,2);
V=A(:,:,3);
H=myhisteq(H);%对H分量均衡化
H=im2double(H);
B=cat(3,H,S,I);
C=hsv2rgb (B);
imwrite(C,'G:\\seg17\\night.jpg');