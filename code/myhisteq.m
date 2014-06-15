function f=myhisteq(X) 
X=im2uint8(X); 
f1=X; 
[m,n]=size(X); 
num=m*n; %���ص��ܺ� 
r=zeros(1,256); %����0����,��¼�仯ǰ�ĸ��Ҷȼ��ж��ٸ����� 
s=zeros(1,256);%����0����,�ڸ��Ҷȼ��ϼ�¼Ӧ�ñ�ɻҶȼ���ֵ 

%����൱��get histogram
for i=1:m
    for j=1:n
        k=X(i,j);  
        r(k+1)=r(k+1)+1; 
    end 
end

%����൱��get cdf
s(1)=r(1);
for i=2:256
    s(i)=s(i-1)+r(i);
end

%����൱��run point operation
for i=1:m 
    for j=1:n 
        k=X(i,j);
        f1(i,j)=s(k+1)*256/num;
    end 
end 

f1 = uint8(f1);
f=f1;
end