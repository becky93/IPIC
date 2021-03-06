f=imread('G:\\seg17\\SAM_1082.JPG');%获取HSI图像
f=imresize(f,0.8);
A=REG__HSI(f); 
H=A(:,:,1);
S=A(:,:,2);
I=A(:,:,3);
H=myhisteq(H);%对H分量均衡化
H=im2double(H);
B=cat(3,H,S,I);
C=HSI__REG(B);
imwrite(C,'G:\\seg17\\HSI_H.jpg');

f=imread('G:\\seg17\\SAM_1082.JPG');%获取HSI图像
f=imresize(f,0.8);
A=REG__HSI(f);
H=A(:,:,1);
S=A(:,:,2);
I=A(:,:,3);
S=myhisteq(S);;%对S分量均衡化
S=im2double(S);
B=cat(3,H,S,I);
C=HSI__REG(B);
imwrite(C,'G:\\seg17\\HSI_S.jpg');

f=imread('G:\\seg17\\SAM_1082.JPG');%获取HSI图像
f=imresize(f,0.8); 
A=REG__HSI(f);
H=A(:,:,1);
S=A(:,:,2);
I=A(:,:,3);
I=myhisteq(I);;%对I分量均衡化
I=im2double(I);
B=cat(3,H,S,I);
C=HSI__REG(B);
imwrite(C,'G:\\seg17\HSI_I.jpg');

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
imwrite(C,'G:\\seg17\\HSV_H.jpg');

f=imread('G:\\seg17\\SAM_1082.JPG');%获取HSV图像
f=imresize(f,0.8); 
A=rgb2hsv(f);
H=A(:,:,1);
S=A(:,:,2);
V=A(:,:,3);
S=myhisteq(S);%对S分量均衡化
S=im2double(S);
B=cat(3,H,S,I);
C=hsv2rgb (B);
imwrite(C,'G:\\seg17\\HSV_S.jpg');

f=imread('G:\\seg17\\SAM_1082.JPG');%获取HSV图像
f=imresize(f,0.8); 
A=rgb2hsv(f);
H=A(:,:,1);
S=A(:,:,2);
V=A(:,:,3);
V=myhisteq(V);%对V分量均衡化
V=im2double(V);
B=cat(3,H,S,I);
C=hsv2rgb (B);
imwrite(C,'G:\\seg17\\HSV_V.jpg');

f=imread('G:\\seg17\\HSV_V.jpg');%获取HSI图像
f=imresize(f,0.8); 
f = rgb2gray(f);
%%imhist(f);