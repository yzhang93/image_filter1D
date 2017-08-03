#include <iostream>
#include <time.h>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

void filter(int height, int width){
    
    srand((unsigned) time(NULL));
    unsigned char matrix[height][width];
   
    const int fx[] = {-1,0,1};
    const int fy[] = {-1,0,1};
    const int f_size = 3;
    
    int dx_output[height][width];
    int dy_output[height][width];
    
    
    // Fill the matrix with random values
    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            
            matrix[r][c] = (unsigned char) (rand() & 0x00ff);
            //cout << static_cast<unsigned>(matrix[r][c]) << ' '; 

        }
        //cout << endl;
    }
    

    clock_t t1,t2,t3;
    t1=clock();
    
    // Method 1: use the definition of convolution
    int max_dx = INT_MIN;
    int max_dy = INT_MIN;
    int min_dx = INT_MAX;
    int min_dy = INT_MAX;

    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            
            // Compute derivates dx, max_dx, min_dx
            if (c==0 || c==width-1) dx_output[r][c] = 0;
            else{
                dx_output[r][c] = 0;
                for (int i=-1; i<f_size-1; i++){
                    dx_output[r][c] += matrix[r][c+i]*fx[1-i];
                }
                
                if (dx_output[r][c]>max_dx) max_dx = dx_output[r][c];
                if (dx_output[r][c]<min_dx) min_dx = dx_output[r][c];
            }
            
            // Compute derivates dy, max_dy, min_dy
            if (r==0 || r==height-1) dy_output[r][c] = 0;
            else{
                dy_output[r][c] = 0;
                for (int i=-1; i<f_size-1; i++){
                    dy_output[r][c] += matrix[r+i][c]*fy[1-i];
                }
                
                if (dy_output[r][c]>max_dy) max_dy = dy_output[r][c];
                if (dy_output[r][c]<min_dy) min_dy = dy_output[r][c];
            }
            //cout << dx_output[r][c] << ' ';
            
        }
        //cout << endl;
    }
    
    t2=clock();   
    
    // Method 2: use the difference of translated matrices
    max_dx = INT_MIN;
    max_dy = INT_MIN;
    min_dx = INT_MAX;
    min_dy = INT_MAX;
    
    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            
            // Compute derivates dx, max_dx, min_dx
            if (c==0 || c==width-1) dx_output[r][c] = 0;
            else{
                dx_output[r][c] = matrix[r][c-1]-matrix[r][c+1];
                if (dx_output[r][c]>max_dx) max_dx = dx_output[r][c];
                if (dx_output[r][c]<min_dx) min_dx = dx_output[r][c];
            }
            
            // Compute derivates dy, max_dy, min_dy
            if (r==0 || r==height-1) dy_output[r][c] = 0;
            else{
                dy_output[r][c] = matrix[r-1][c]-matrix[r+1][c];
                if (dy_output[r][c]>max_dy) max_dy = dy_output[r][c];
                if (dy_output[r][c]<min_dy) min_dy = dy_output[r][c];
            }
            //cout << dy_output[r][c] << ' ';
            
        }
        //cout << endl;
    }
    
    t3=clock();    
    
    double dif1 = (double)(t2-t1)/CLOCKS_PER_SEC;
    double dif2 = (double)(t3-t2)/CLOCKS_PER_SEC;

    printf ("The max value of dx is %d，and the min value of dx is %d.\n" , max_dx, min_dx);
    printf ("The max value of dy is %d，and the min value of dy is %d.\n" , max_dy, min_dy);
    printf ("Elasped time for method 1 is %.6lf seconds.\n", dif1 );
    printf ("Elasped time for method 2 is %.6lf seconds.\n", dif2 );
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cerr << "Usage: " << "Please Input Height and Width!" << std::endl;
        return 1;
    }
    int height = atoi(argv[1]);
    int width = atoi(argv[2]);

    filter(height, width);
    return 0;
}
