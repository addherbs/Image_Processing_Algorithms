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
	
int copy_image[DIM][DIM];
	int i, j, k;

	int diff1 = 0, diff2 = 0;
	int row_minus = 0, col_minus = 0, exact = 0;

	/*

	*/
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			copy_image[i][j] = image[i][j];
		}
	}

	/*

	*/
	for (i = 1; i < DIM; i++) {
		for (j = 1; j < DIM; j++) {
			row_minus = copy_image[i - 1][j];
			col_minus = copy_image[i][j - 1];
			exact = copy_image[i][j];

			diff1 = abs(row_minus - exact);
			diff2 = abs(col_minus - exact);

			if (diff1 == diff2) {
				exact = diff1;
			}
			else {
				exact = diff1 < diff2 ? diff1 : diff2;
			}

			copy_image[i][j] = exact;
		}
	}

	/*

	*/
	for (i = 0; i < DIM; i++) {
		for (j = 0; j < DIM; j++) {
			proc_img[i][j] = copy_image[i][j];
		}
	}




}
