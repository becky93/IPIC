f=imread('G:\\seg17\\SAM_1082.JPG');%��ȡHSVͼ��
f=imresize(f,0.8); 
A=REG__HSI(f);
H=A(:,:,1);
S=A(:,:,2);
X=A(:,:,3);


X=im2uint8(X); 
f1=X; 
[m,n]=size(X); 
num=m*n; %���ص��ܺ� 
r=zeros(1,256); %����0����,��¼�仯ǰ�ĸ��Ҷȼ��ж��ٸ����� 
s=zeros(1,256);%����0����,�ڸ��Ҷȼ��ϼ�¼Ӧ�ñ�ɻҶȼ���ֵ 

%����൱��run point operation
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