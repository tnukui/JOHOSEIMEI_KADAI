#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>


void sizeof_string(FILE* fpx, FILE* fpy, long* x_num, long* y_num)
{
    *x_num=0;
    *y_num=0;
    for(*x_num=0; ; (*x_num)++){
        int ch=fgetc(fpx);
        if(ch==EOF) break;
        else if(ch=='\n' || ch==' ') (*x_num)--;
    }
    for(*y_num=0; ; (*y_num)++){
        int ch=fgetc(fpy);
        if(ch==EOF) break;
        else if(ch=='\n' || ch==' ') (*y_num)--;
    }
    if((*x_num)<=0 ||(*y_num)<=0){
        printf("file size is zero\n");
        exit(0);
    }
    
}

void file_read(FILE* fpx, FILE* fpy, long x_num, long y_num, char* str_x, char* str_y)
{
    long i;
    for(i=0; ; i++){
        int ch=fgetc(fpx);
        if(ch==EOF) break;
        else if(ch=='\n' || ch==' ') i--;
        else if(i<x_num) str_x[i]=ch;
    }
    for(i=0; ; i++){
        int ch=fgetc(fpy);
        if(ch==EOF) break;
        else if(ch=='\n' || ch==' ') i--;
        else if(i<y_num) str_y[i]=ch;
    }
    str_x[x_num]=0;
    str_y[y_num]=0;
}

void file_open(FILE** fpx, FILE** fpy, char* file_x_name, char* file_y_name)
{
    *fpx=fopen(file_x_name, "r");
    *fpy=fopen(file_y_name, "r");
    
    if(*fpx==NULL || *fpy==NULL){
        printf("file cannot open");
        exit(0);
    }
}

double my_maxof(double a, double b, double c, double d)
{
    double ans=a;
    if(ans<b) ans=b;
    if(ans<c) ans=c;
    if(ans<d) ans=d;
    return ans;
}

double smith_waterman(long x_num, long y_num, char* str_x, char* str_y, double match, double mismatch, double gap)
{
    double** matrix=(double**)calloc(x_num+1, sizeof(double*));
    matrix[0]=(double*)calloc((x_num+1)*(y_num+1), sizeof(double));
    long i;
    for(i=1; i<x_num+1; i++){
        matrix[i]=matrix[0]+(y_num+1)*i;
    }
    
    long j;
    for(i=0; i<x_num+1; i++){matrix[i][0]=0.0;}
    for(i=0; i<y_num+1; i++){matrix[0][i]=0.0;}
    
    double diff=0.0;
    double max_score=0.0;
    for(i=1; i<x_num+1; i++){
        for(j=1; j<y_num+1; j++){
            if(str_x[i-1]==str_y[j-1]){diff=match;}
            else{diff=mismatch;}
            matrix[i][j]=my_maxof(matrix[i-1][j-1]+diff, matrix[i-1][j]+gap, matrix[i][j-1]+gap,0);
            if(matrix[i][j]>max_score)
                max_score=matrix[i][j];
        }
    }
    
    for(i=0; i<x_num; i++){
        for(j=0; j<y_num; j++){
            printf("%.2f ",matrix[i][j]);
        }
        printf("\n");
    }
    return max_score;
}





int main(int argc, char* argv[])
{
    
    FILE* fpx=NULL, *fpy=NULL;
    file_open(&fpx, &fpy, "test_x.txt", "test_y.txt");
    long x_num=0, y_num=0;
    
    sizeof_string(fpx, fpy, &x_num, &y_num);
    
    fclose(fpx); fclose(fpy);
    printf("x_num=%ld y_num=%ld\n", x_num, y_num);
    char *str_x=(char*)calloc(x_num+1, sizeof(char));
    char *str_y=(char*)calloc(y_num+1, sizeof(char));
    file_open(&fpx, &fpy, "test_x.txt", "test_y.txt");
    file_read(fpx, fpy, x_num, y_num, str_x, str_y);
    fclose(fpx); fclose(fpy);
    printf("%s\n%s\n", str_x, str_y);
    smith_waterman(x_num, y_num, str_x, str_y, 1, -2, -1.5);
    
    
    
    return(0);
}
