#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>

#define DIM 512
#define N 3

/******************************************************************/
/* This structure contains the coordinates of a box drawn with    */
/* the left mouse button on the image window.                     */
/* roi.x , roi.y  - left upper corner's coordinates               */
/* roi.width , roi.height - width and height of the box           */
/******************************************************************/
extern XRectangle roi;


/******************************************************************/
/* Main processing routine. This is called upon pressing the      */
/* Process button of the interface.                               */
/* image  - the original greyscale image                          */
/* size   - the actual size of the image                          */
/* proc_image - the image representation resulting from the       */
/*              processing. This will be displayed upon return    */
/*              from this function.                               */
/******************************************************************/
void process_image(image, size, proc_img)
unsigned char image[DIM][DIM];
int size[2];
unsigned char proc_img[DIM][DIM];
{
	int height = size[0], width = size[1];
//	int new_image_vertical[DIM-2][DIM-2];
	int new_image_horizontal[DIM - 2][DIM - 2];
	int i, j, k;

	int horizontal[N][N] = { { -1,-1,-1 },
							{ 0,0,0 },
							{ 1,1,1 }
	};
	int sum = 0, row1 = 0, row2 = 0, row3 = 0;

	for (i = 0; i < DIM - 2; i++) {
		for (j = 0; j < DIM - 2; j++) {
			
			row1 = (double) image[i][j] * horizontal[0][0] + (double) image[i][j + 1] * horizontal[0][1] + (double) image[i][j + 2] * horizontal[0][2];
			row2 = (double) image[i + 1][j] * horizontal[1][0] + (double) image[i + 1][j + 1] * horizontal[1][1] + (double) image[i + 1][j + 2] * horizontal[1][2];
			row3 = (double) image[i + 2][j] * horizontal[2][0] + (double) image[i + 2][j + 1] * horizontal[2][1] + (double) image[i + 2][j + 2] * horizontal[2][2];
			sum = row1 + row2 + row3;
			new_image_horizontal[i][j] = sum;
			sum = 0; row1 = 0; row2 = 0; row3 = 0;
		}
	}
	
// Update the proc image file
	for (i = 0; i < DIM - 2; i++) {
		for (j = 0; j < DIM - 2; j++) {
			proc_img[i][j] = new_image_horizontal[i][j];
		}
	}


}
