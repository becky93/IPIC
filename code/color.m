f=imread('G:\\seg17\\SAM_1082.JPG');%��ȡHSIͼ��
f=imresize(f,0.8);
A=REG__HSI(f); 
H=A(:,:,1);
S=A(:,:,2);
I=A(:,:,3);
H=myhisteq(H);%��H�������⻯
H=im2double(H);
B=cat(3,H,S,I);
C=HSI__REG(B);
imwrite(C,'G:\\seg17\\HSI_H.jpg');

f=imread('G:\\seg17\\SAM_1082.JPG');%��ȡHSIͼ��
f=imresize(f,0.8);
A=REG__HSI(f);
H=A(:,:,1);
S=A(:,:,2);
I=A(:,:,3);
S=myhisteq(S);;%��S�������⻯
S=im2double(S);
B=cat(3,H,S,I);
C=HSI__REG(B);
imwrite(C,'G:\\seg17\\HSI_S.jpg');

f=imread('G:\\seg17\\SAM_1082.JPG');%��ȡHSIͼ��
f=imresize(f,0.8); 
A=REG__HSI(f);
H=A(:,:,1);
S=A(:,:,2);
I=A(:,:,3);
I=myhisteq(I);;%��I�������⻯
I=im2double(I);
B=cat(3,H,S,I);
C=HSI__REG(B);
imwrite(C,'G:\\seg17\HSI_I.jpg');

f=imread('G:\\seg17\\SAM_1082.JPG');%��ȡHSVͼ��
f=imresize(f,0.8); 
A=rgb2hsv(f);
H=A(:,:,1);
S=A(:,:,2);
V=A(:,:,3);
H=myhisteq(H);%��H�������⻯
H=im2double(H);
B=cat(3,H,S,I);
C=hsv2rgb (B);
imwrite(C,'G:\\seg17\\HSV_H.jpg');

f=imread('G:\\seg17\\SAM_1082.JPG');%��ȡHSVͼ��
f=imresize(f,0.8); 
A=rgb2hsv(f);
H=A(:,:,1);
S=A(:,:,2);
V=A(:,:,3);
S=myhisteq(S);%��S�������⻯
S=im2double(S);
B=cat(3,H,S,I);
C=hsv2rgb (B);
imwrite(C,'G:\\seg17\\HSV_S.jpg');

f=imread('G:\\seg17\\SAM_1082.JPG');%��ȡHSVͼ��
f=imresize(f,0.8); 
A=rgb2hsv(f);
H=A(:,:,1);
S=A(:,:,2);
V=A(:,:,3);
V=myhisteq(V);%��V�������⻯
V=im2double(V);
B=cat(3,H,S,I);
C=hsv2rgb (B);
imwrite(C,'G:\\seg17\\HSV_V.jpg');

f=imread('G:\\seg17\\HSV_V.jpg');%��ȡHSIͼ��
f=imresize(f,0.8); 
f = rgb2gray(f);
%%imhist(f);