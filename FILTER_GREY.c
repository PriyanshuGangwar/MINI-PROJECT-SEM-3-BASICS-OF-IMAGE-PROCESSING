
#include <stdio.h>
#include <stdlib.h>
void read(char *infile,int arr[][1000],unsigned char header[54],unsigned char colortable[1024])
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




    unsigned char* data = (unsigned char *)malloc(width * sizeof (unsigned int));



    for ( i = 0; i<height; i++)
    {

        fread(data, sizeof(unsigned char), width, in);
 
        for ( j = 0; j < width ; j++)
        {
          arr[i][j]= (int)data[j] ;

        }
    }


  


    fclose(in);
}

void write(char *outfile ,int arr[][1000] ,unsigned char header[54],unsigned char colortable[1024])
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
    
      unsigned char* data = (unsigned char *)malloc(width * sizeof (unsigned int));

     for ( i = 0; i<height; i++)
        { 

     
        for ( j = 0; j < width ; j++)
        {
          data[j]=arr[i][j] ;

        }
       fwrite(data, sizeof(unsigned char), width, out);

    }  

    fclose(out);

}
void averagefilter( int height ,int width, int arr[][1000])
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
void medianfilter( int height ,int width, int arr[][1000])
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


void main(int argv, char *argc[])
{
   int arr1[1000][1000],arr2[1000][1000];   
   unsigned char header[54],colortable[1024];
   
    read(argc[1],arr1,header,colortable);
    read(argc[1],arr2,header,colortable);
    int  width = *(int*)&header[18];
    int height = *(int*)&header[22];

 
    averagefilter(height,width,arr1);
    write(argc[2] ,arr1,header,colortable);
    medianfilter(height,width,arr2);
    write(argc[3] ,arr2,header,colortable);



}








