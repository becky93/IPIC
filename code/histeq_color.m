function EI = histeq_color(I)%对HSI图中的I进行均衡化Ok
[row, col, channel] = size(I);
EI = zeros(row, col, channel);

%将RGB转化为HSI图像

% 输入图像是一个彩色像素的M×N×3的数组，  
% 其中每一个彩色像素都在特定空间位置的彩色图像中对应红、绿、蓝三个分量。  
% 假如所有的RGB分量是均衡的，那么HSI转换就是未定义的。  
% 输入图像可能是double（取值范围是[0, 1]），uint8或 uint16。  
%  
% 输出HSI图像是double，  
% 其中hsi(:, :, 1)是色度分量，它的范围是除以2*pi后的[0, 1]；  
% hsi(:, :, 2)是饱和度分量，范围是[0, 1]；  
% hsi(:, :, 3)是亮度分量，范围是[0, 1]。   
% 抽取图像分量  
I = im2double(I);  
r = I(:, :, 1);  
g = I(:, :, 2);  
b = I(:, :, 3);  
  
% 执行转换方程  
num = 0.5*((r - g) + (r - b));  
den = sqrt((r - g).^2 + (r - b).*(g - b));  
theta = acos(num./(den + eps)); %防止除数为0  
  
h = theta;  
h(b > g) = 2*pi - h(b > g);  
h = h/(2*pi);  
  
num = min(min(r, g), b);  
den = r + g + b;  
den(den == 0) = eps; %防止除数为0  
s = 1 - 3.* num./den;  
  
h(s == 0) = 0;  
  
i = (r + g + b)/3;  
  
% 将3个分量联合成为一个HSI图像  
X = cat(3, h, s, i); 

h2=X(:,:,1);%获取三分量
s2=X(:,:,2);
i2=X(:,:,3);

i2=im2uint8(i2); 
f1=i2; 
[m,n]=size(i2); 
num=m*n; %像素的总和 
r3=zeros(1,256); %生成0矩阵,记录变化前的各灰度级有多少个像素 
s3=zeros(1,256);%生成0矩阵,在各灰度级上记录应该变成灰度级数值 

%类比相当于get histogram
for i=1:m
    for j=1:n
        k=i2(i,j);  
        r3(k+1)=r3(k+1)+1; 
    end 
end

%类比相当于get cdf
s3(1)=r3(1);
for i=2:256
    s3(i)=s3(i-1)+r3(i);
end

%类比相当于run point operation
for i=1:m 
    for j=1:n 
        k=i2(i,j);
        f1(i,j)=s3(k+1)*256/num;
    end 
end 

f1 = uint8(f1);
f=f1;

f=im2double(f);%类型转换

B=cat(3,h2,s2,f);%将新的图像拼接成HSI图像

%将HSI转化为RGB图像
HV=B(:,:,1);
HV=HV*2;
HV=HV*pi;
SV=B(:,:,2);
IV=B(:,:,3);
R1=zeros(size(HV));
G1=zeros(size(HV));
B1=zeros(size(HV));

%RG Sector
id=find((0<=HV)& (HV<2*pi/3));%相当于用if else语句，id在此是一个条件判断
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
