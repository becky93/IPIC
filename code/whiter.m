f=imread('G:\\seg17\\SAM_1082.JPG');%获取HSV图像
f=imresize(f,0.8); 
A=REG__HSI(f);
H=A(:,:,1);
S=A(:,:,2);
X=A(:,:,3);


X=im2uint8(X); 
f1=X; 
[m,n]=size(X); 
num=m*n; %像素的总和 
r=zeros(1,256); %生成0矩阵,记录变化前的各灰度级有多少个像素 
s=zeros(1,256);%生成0矩阵,在各灰度级上记录应该变成灰度级数值 

%类比相当于run point operation
for i=1:m 
    for j=1:n 
        k=X(i,j);
        f1(i,j)=k+50;
    end 
end 

f1 = uint8(f1);
f=f1;

I=im2double(f);
B=cat(3,H,S,I);
X=HSI__REG(B);

imwrite(X,'G:\\seg17\\whiter.jpg');