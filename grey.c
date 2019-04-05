
#include <stdio.h>
#include <stdlib.h>
void read(char *infile, char *outfile)
{   int i,j;
    FILE *in = fopen(infile, "rb");
    FILE *out = fopen(outfile,"wb");

    if (in == NULL)
    {
    printf("\n %s doesn't exist !!!\n",infile);
    return;
    }

    unsigned char header[54],colortable[1024];

    fread(header, sizeof(unsigned char), 54, in);
    fwrite(header, sizeof(unsigned char), 54, out);

    int  width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int  bitDepth  = *(int*)&header[28];
    int size=width*height*3;

    if(bitDepth <= 8)
        {fread(colortable, sizeof(unsigned char), 1024, in);
         fwrite(colortable, sizeof(unsigned char), 1024, out);
        }
    printf("width: %d\n",width);
    printf("height: %d\n",height );
    printf("size: %d\n",size );
    printf("bit count: %d\n",bitDepth );




    unsigned char* data = (unsigned char *)malloc(width * sizeof (unsigned int));

    int *arr[height];
    for ( i=0; i<height; i++)
         arr[i] = (int *)malloc(width * sizeof(int));

    for ( i = 0; i<height; i++)
    {

        fread(data, sizeof(unsigned char), width, in);
        fwrite(data, sizeof(unsigned char), width, out);

        for ( j = 0; j < width ; j += 1)
        {
          arr[i][j]= (int)data[j] ;

        }
    }


  /*  for ( i = 0; i<height; i++)
    {

        printf("\n");
        for ( j = 0; j < width ; j += 1)
        {

            printf(" %d , ",arr[i][j]);
        }
    }*/




    fclose(out);
    fclose(in);
}

void main(int argv, char *argc[])
{
     
    read(argc[1],argc[2],);
}
