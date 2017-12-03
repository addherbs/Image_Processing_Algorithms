/* This program contains the code for template matching */

#include <stdio.h>
#include <math.h>
#include <X11/Xlib.h>

#define DIM 512

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

	for (int i = 0; i < size[1]; i++) 
		for (int j = 0; j < size[0]; j++)
			proc_img[i][j] = 0;

	/* now take a convolution with the filter */	
	for (int i = 0; i < size[1]; i++) {
		for (int j = 0; j < size[0]; j++) {
			/* code for template denominator */

			/* initialize all the values to zero */
			/* calculate the local max for all pixel values and then mean */
			int temp1 = 0;
			for (int i1 = i; i1 < roi.height; i1++) 
				for (int j1 = 0; j1 < roi.width; j1++)
					if (image[i1][j1] > temp1)
						temp1 = image[i1][j1];
			float mean_image = ((float) temp1)/((float) (roi.width * roi.height));
			temp1 = 0;
			/* calculate mean of template */
			for (int i1 = roi.y; i1 < roi.y + roi.height; i1++)
				for (int j1 = roi.x; j1 < roi.x + roi.width; j1++)
					if (image[i1][j1] > temp1)
						temp1 = image[i1][j1];
			float mean_template = ((float) temp1)/((float) (roi.width * roi.height));

			/* normalization factor needs to be calculated */
			float norm1 = 0.0;
			float norm2 = 0.0;
			for (int i1 = i; i1 < roi.height; i1++) 
				for (int j1 = 0; j1 < roi.width; j1++)
					norm1 += pow(image[i1][j1] - mean_image, 2);
			for (int i1 = roi.y; i1 < roi.y + roi.height; i1++)
				for (int j1 = roi.x; j1 < roi.x + roi.width; j1++)
					norm2 += pow(image[i][j] - mean_template, 2);
			float norm_factor = pow(norm1 * norm2, 0.5);

			/* endcode */


			for (int k = 0; k < roi.height; k++) {
				/* int est_row = roi.height - 1 - k; */
				for (int l = 0; l < roi.width; l++) {
					/* int est_column = roi.width - 1 - l; */
					float temp = 0.0;
					int image_row = i + k;
					int image_column = j + l;
					int template_row = roi.y + k;
					int template_column = roi.x + l;	
					if (image_row >=0 && image_row < size[1] && image_column >= 0 && image_column < size[0]) {
						temp += (image[image_row][image_column] - mean_image);
						temp *= (image[template_row][template_column] - mean_template);
						proc_img[i][j] = (int) 255 * temp / (norm_factor + 0.001);
					}
	
				}
			}
		}
	}	
}
