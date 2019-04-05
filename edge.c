
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
void sovelmask( int height ,int width, int arr[][1000],int arr1[][1000])
 {  int i,j,m,n,k,l;

    int maskv[5][5];
    maskv[0][0]=-1;  
    maskv[0][1]=0;    
    maskv[0][2]=1;     
    maskv[1][0]=-2;  
    maskv[1][1]=0;    
    maskv[1][2]=2; 
    maskv[2][0]=-1;  
    maskv[2][1]=0;    
    maskv[2][2]=1; 
    
       int maskh[5][5];
    maskh[0][0]=1;  
    maskh[0][1]=2;    
    maskh[0][2]=1;     
    maskh[1][0]=0;  
    maskh[1][1]=0;    
    maskh[1][2]=0; 
    maskh[2][0]=-1;  
    maskh[2][1]=-2;    
    maskh[2][2]=-1;   

    for ( i = 0; i<height; i++)
    { 
      for(j=0 ; j<width ; j++)
       {  
          int sum1=0,sum2=0;
          for(m=i-1,k=0; m<=i+1 ; m++,k++)
            {
               for(n=j-1,l=0; n<=j+1 ; n++,l++)
                 {
                     if(m<0 || n<0 || m>=height || n>=width)
                        continue;
                     else
                        {
                          sum1+=arr[m][n]*maskv[k][l];
			  sum2+=arr[m][n]*maskh[k][l];
                        } 
                 }
            }
         arr1[i][j]=sqrt((sum1*sum1)+(sum2*sum2));
        
         
       }
      }

}




void main(int argv, char *argc[])
{
   int arr1[1000][1000],arr2[1000][1000];   
   unsigned char header[54],colortable[1024];
   
    read(argc[1],arr1,header,colortable);
   
    int  width = *(int*)&header[18];
    int height = *(int*)&header[22];

 
    sovelmask(height,width,arr1,arr2);
    write(argc[2] ,arr2,header,colortable);
 

}








