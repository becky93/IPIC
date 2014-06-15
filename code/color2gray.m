f=imread('E:\\seg17\\SAM_1082.JPG');%»ñÈ¡HSVÍ¼Ïñ
f=imresize(f,0.8); 
A=rgb2gray(f);
imwrite(A,'E:\\seg17\\gray.jpg');