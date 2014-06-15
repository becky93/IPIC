function f=myhisteq(X) 
X=im2uint8(X); 
f1=X; 
[m,n]=size(X); 
num=m*n; %像素的总和 
r=zeros(1,256); %生成0矩阵,记录变化前的各灰度级有多少个像素 
s=zeros(1,256);%生成0矩阵,在各灰度级上记录应该变成灰度级数值 

%类比相当于get histogram
for i=1:m
    for j=1:n
        k=X(i,j);  
        r(k+1)=r(k+1)+1; 
    end 
end

%类比相当于get cdf
s(1)=r(1);
for i=2:256
    s(i)=s(i-1)+r(i);
end

%类比相当于run point operation
for i=1:m 
    for j=1:n 
        k=X(i,j);
        f1(i,j)=s(k+1)*256/num;
    end 
end 

f1 = uint8(f1);
f=f1;
end