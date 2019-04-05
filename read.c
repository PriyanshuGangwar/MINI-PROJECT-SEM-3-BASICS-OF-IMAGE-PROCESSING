#include <stdio.h>
#include <stdlib.h>
void read(char *filename)
{   int i,j;
    FILE *in = fopen(filename, "rb");
    FILE *out = fopen("outimage.bmp","wb");

    if (in == NULL)
    {
    printf("\n %s doesn't exist !!!\n",filename);
    return;
    }

    unsigned char header[54];

    fread(header, sizeof(unsigned char), 54, in);
    fwrite(header, sizeof(unsigned char), 54, out);

    int  width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int  bitDepth  = *(int*)&header[28];
    int size=width*height*3;

	printf("width: %d\n",width);
	printf("height: %d\n",height );
    printf("size: %d\n",size );
    printf("bit count: %d\n",bitDepth );

    int padding = 0;

    while ((width * 3 + padding) % 4 != 0)
        padding++;

    int widthnew = width * 3 + padding;



    unsigned char* data = (unsigned char *)malloc(widthnew * sizeof (unsigned int));

    int *arr[height];
    for ( i=0; i<height; i++)
         arr[i] = (int *)malloc(width *3* sizeof(int));

    for ( i = 0; i<height; i++)
    {

        fread(data, sizeof(unsigned char), widthnew, in);
        fwrite(data, sizeof(unsigned char), widthnew, out);

        for ( j = 0; j < width * 3; j += 3)
        {
            int tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;


            arr[i][j]= (int)data[j] ;
            arr[i][j+1]= (int)data[j+1];
            arr[i][j+2]= (int)data[j+2];
        }
    }


  /*  for (int i = 0; i<height; i++)
    {

        printf("\n");
        for (int j = 0; j < width * 3; j += 3)
        {

            printf(" (%d,%d,%d) , ",arr[i][j],arr[i][j+1],arr[i][j+2]);
        }
    }*/




    fclose(out);
    fclose(in);
}

void main()
{
    //read("11.bmp");
    read("MARBLES.BMP");
}
