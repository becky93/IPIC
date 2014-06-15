function EI = histeq_color(I)%��HSIͼ�е�I���о��⻯Ok
[row, col, channel] = size(I);
EI = zeros(row, col, channel);

%��RGBת��ΪHSIͼ��

% ����ͼ����һ����ɫ���ص�M��N��3�����飬  
% ����ÿһ����ɫ���ض����ض��ռ�λ�õĲ�ɫͼ���ж�Ӧ�졢�̡�������������  
% �������е�RGB�����Ǿ���ģ���ôHSIת������δ����ġ�  
% ����ͼ�������double��ȡֵ��Χ��[0, 1]����uint8�� uint16��  
%  
% ���HSIͼ����double��  
% ����hsi(:, :, 1)��ɫ�ȷ��������ķ�Χ�ǳ���2*pi���[0, 1]��  
% hsi(:, :, 2)�Ǳ��Ͷȷ�������Χ��[0, 1]��  
% hsi(:, :, 3)�����ȷ�������Χ��[0, 1]��   
% ��ȡͼ�����  
I = im2double(I);  
r = I(:, :, 1);  
g = I(:, :, 2);  
b = I(:, :, 3);  
  
% ִ��ת������  
num = 0.5*((r - g) + (r - b));  
den = sqrt((r - g).^2 + (r - b).*(g - b));  
theta = acos(num./(den + eps)); %��ֹ����Ϊ0  
  
h = theta;  
h(b > g) = 2*pi - h(b > g);  
h = h/(2*pi);  
  
num = min(min(r, g), b);  
den = r + g + b;  
den(den == 0) = eps; %��ֹ����Ϊ0  
s = 1 - 3.* num./den;  
  
h(s == 0) = 0;  
  
i = (r + g + b)/3;  
  
% ��3���������ϳ�Ϊһ��HSIͼ��  
X = cat(3, h, s, i); 

h2=X(:,:,1);%��ȡ������
s2=X(:,:,2);
i2=X(:,:,3);

i2=im2uint8(i2); 
f1=i2; 
[m,n]=size(i2); 
num=m*n; %���ص��ܺ� 
r3=zeros(1,256); %����0����,��¼�仯ǰ�ĸ��Ҷȼ��ж��ٸ����� 
s3=zeros(1,256);%����0����,�ڸ��Ҷȼ��ϼ�¼Ӧ�ñ�ɻҶȼ���ֵ 

%����൱��get histogram
for i=1:m
    for j=1:n
        k=i2(i,j);  
        r3(k+1)=r3(k+1)+1; 
    end 
end

%����൱��get cdf
s3(1)=r3(1);
for i=2:256
    s3(i)=s3(i-1)+r3(i);
end

%����൱��run point operation
for i=1:m 
    for j=1:n 
        k=i2(i,j);
        f1(i,j)=s3(k+1)*256/num;
    end 
end 

f1 = uint8(f1);
f=f1;

f=im2double(f);%����ת��

B=cat(3,h2,s2,f);%���µ�ͼ��ƴ�ӳ�HSIͼ��

%��HSIת��ΪRGBͼ��
HV=B(:,:,1);
HV=HV*2;
HV=HV*pi;
SV=B(:,:,2);
IV=B(:,:,3);
R1=zeros(size(HV));
G1=zeros(size(HV));
B1=zeros(size(HV));

%RG Sector
id=find((0<=HV)& (HV<2*pi/3));%�൱����if else��䣬id�ڴ���һ�������ж�
B1(id)=IV(id).*(1-SV(id));
R1(id)=IV(id).*(1+SV(id).*cos(HV(id))./cos(pi/3-HV(id)));
G1(id)=3*IV(id)-(R1(id)+B1(id));

%BG Sector
id=find((2*pi/3<=HV)& (HV<4*pi/3));
R1(id)=IV(id).*(1-SV(id));
G1(id)=IV(id).*(1+SV(id).*cos(HV(id)-2*pi/3)./cos(pi-HV(id)));
B1(id)=3*IV(id)-(R1(id)+G1(id));

%BR Sector
id=find((4*pi/3<=HV)& (HV<2*pi));
G1(id)=IV(id).*(1-SV(id));
B1(id)=IV(id).*(1+SV(id).*cos(HV(id)-4*pi/3)./cos(5*pi/3-HV(id)));
R1(id)=3*IV(id)-(G1(id)+B1(id));
C=cat(3,R1,G1,B1);
C=max(min(C,1),0);

EI=C;
%% fill the following section to equalize the historam of I, put the result in EI

%%
