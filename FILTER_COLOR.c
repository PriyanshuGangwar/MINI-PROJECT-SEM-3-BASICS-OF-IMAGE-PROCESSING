
#include <stdio.h>
#include <stdlib.h>

void averagefilter( int height ,int width, int *arr[3000]);
void read(char *infile,int *arr[1500],unsigned char header[54],unsigned char colortable[1024])
{   int i,j;
    FILE *in = fopen(infile, "rb");
       
    if (in == NULL)
    {
    printf("\n %s doesn't exist !!!\n",infile);
    return;
    }

    
    fread(header, sizeof(unsigned char), 54, in);
    
    int  width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int  bitDepth  = *(int*)&header[28];
    int size=width*height*3;
    
    if(bitDepth <= 8)
        {fread(colortable, sizeof(unsigned char), 1024, in);
         
        }

    printf("width: %d\n",width);
    printf("height: %d\n",height );
    printf("size: %d\n",size );
    printf("bit count: %d\n",bitDepth );

    int padding = 0;

    while ((width * 3 + padding) % 4 != 0)
        padding++;

    int widthnew = width * 3 + padding;
    unsigned char* data = (unsigned char *)malloc(widthnew * sizeof (unsigned int));


    for (i = 0; i<height; i++)
    {

        fread(data, sizeof(unsigned char), widthnew, in);

        for ( j = 0; j < width * 3; j += 3)
        {
          //  int tmp = data[j];
          //  data[j] = data[j+2];
          //  data[j+2] = tmp;


            arr[i][j]= (int)data[j] ;
            arr[i][j+1]= (int)data[j+1];
            arr[i][j+2]= (int)data[j+2];
        }
    }


   fclose(in);
 }

   


void write(char *outfile ,int *arr[1500] ,unsigned char header[54],unsigned char colortable[1024])
{
    int i,j;
      FILE *out = fopen(outfile,"wb");
    int  width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int  bitDepth  = *(int*)&header[28];

    fwrite(header, sizeof(unsigned char), 54, out);
     if(bitDepth <= 8)
        {
         fwrite(colortable, sizeof(unsigned char), 1024, out);
        }
     int padding = 0;

    while ((width * 3 + padding) % 4 != 0)
        padding++;

    int widthnew = width * 3 + padding;
    
      unsigned char* data = (unsigned char *)malloc(widthnew * sizeof (unsigned int));

     for ( i = 0; i<height; i++)
    {
        for ( j = 0; j < widthnew; j += 3)
        {
            //int tmp = data[j];
           // data[j] = data[j+2];
           // data[j+2] = tmp;


            data[j] = arr[i][j] ;
            data[j+1] = arr[i][j+1];
            data[j+2] = arr[i][j+2];
        }
      
        fwrite(data, sizeof(unsigned char), widthnew, out);
    }
    fclose(out);
}
void average( int height ,int width, int *arr[3000])
 {  int i,j,m,n,k;
    int *r[height],*g[height],*b[height],in;
    for ( in=0; in<height; in++)
         r[in] = (int *)malloc(width*sizeof(int));
     for ( in=0; in<height; in++)
         g[in] = (int *)malloc(width*sizeof(int));
    for ( in=0; in<height; in++)
         b[in] = (int *)malloc(width*sizeof(int));

    for ( i = 0; i<height; i++)
    
      for(j=0,k=0 ; j<width*3 ; j+=3,k++)
       {  
          r[i][k]= arr[i][j];
          g[i][k]= arr[i][j+1];
          b[i][k]= arr[i][j+2];
       }
    averagefilter(height,width,r);
    averagefilter(height,width,g);
    averagefilter(height,width,b);
   for ( i = 0; i<height; i++)
    
      for(j=0,k=0 ; j<width*3 ; j+=3,k++)
       {  
          arr[i][j]=r[i][k];
          arr[i][j+1]=g[i][k];
          arr[i][j+2]=b[i][k];
       }

 }

void averagefilter( int height ,int width, int *arr[3000])
 {  int i,j,m,n;
    
    for ( i = 0; i<height; i++)
    
      for(j=0 ; j<width ; j++)
       {  
          int sum=0,c=0;
          for(m=i-2; m<=i+2 ; m++)
            {
               for(n=j-2; n<=j+2 ; n++)
                 {
                     if(m<0 || n<0 || m>=height || n>=width)
                        continue;
                     else
                        {
                          sum = sum+arr[m][n];
                          c=c+1;
                        } 
                 }
            }
         
         arr[i][j]=sum/c; 
       }


 }

void sort(int *ar,int s)
{ int i,j;
  for(i=0;i<s-1;i++)
    for(j=i+1;j<s;j++)
      {
      
          if (ar[j] < ar[i]) 
            {
               int t=ar[j];
                  ar[j]=ar[i];
                  ar[i]=t; 
            }
       
      }

}
void medianfilter( int height ,int width, int *arr[3000])
 {  int i,j,med[80],m,n;
    
    for ( i = 0; i<height; i++)
    
      for(j=0 ; j<width ; j++)
       {  
           int c=0;
           for(m=i-2; m<=i+2 ; m++)
            {
               for(n=j-2; n<=j+2 ; n++)
                 {
                     if(m< 0 || n< 0 || m>=height | n>=width)
                        continue;
                     else
                        {
                          med[c]=arr[m][n];
                          c++;
                        } 
                 }
            }
        
         sort(med,c);
         arr[i][j]=med[c/2];; 
            
       }


 }

void median( int height ,int width, int *arr[3000])
 {  int i,j,m,n,k;
    int *r[height],*g[height],*b[height],in;
    for ( in=0; in<height; in++)
         r[in] = (int *)malloc(width*sizeof(int));
     for ( in=0; in<height; in++)
         g[in] = (int *)malloc(width*sizeof(int));
    for ( in=0; in<height; in++)
         b[in] = (int *)malloc(width*sizeof(int));

    for ( i = 0; i<height; i++)
    
      for(j=0,k=0 ; j<width*3 ; j+=3,k++)
       {  
          r[i][k]= arr[i][j];
          g[i][k]= arr[i][j+1];
          b[i][k]= arr[i][j+2];
       }
    medianfilter(height,width,r);
    medianfilter(height,width,g);
    medianfilter(height,width,b);
   for ( i = 0; i<height; i++)
    
      for(j=0,k=0 ; j<width*3 ; j+=3,k++)
       {  
          arr[i][j]=r[i][k];
          arr[i][j+1]=g[i][k];
          arr[i][j+2]=b[i][k];
       }

 }


void main(int argv, char *argc[])
{
    int *arr1[3000],i;
    for ( i=0; i<3000; i++)
         arr1[i] = (int *)malloc(3000 *3* sizeof(int));

     int *arr2[3000];
    for ( i=0; i<3000; i++)
         arr2[i] = (int *)malloc(3000 *3* sizeof(int));

    
    unsigned char header[54],colortable[1024];
    read(argc[1],arr1,header,colortable);
    read(argc[1],arr2,header,colortable);

    int  width = *(int*)&header[18];
    int height = *(int*)&header[22];

    average(height,width,arr1);
    write(argc[2] ,arr1,header,colortable);
    
    median(height,width,arr2);
    write(argc[3] ,arr2,header,colortable);



}








