#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp_header.h"

#define LENGHT 50

typedef struct{
	unsigned char blue, green, red;
}pixel;

void task1(FILE *bmp_file, char nume_fisier[LENGHT], pixel input_color, struct bmp_fileheader file_header,struct bmp_infoheader info_header){
	char nume_nou[LENGHT];
	pixel img_pix;

	strcpy(nume_nou, strtok(nume_fisier, "."));
	strcat(nume_nou, "_task1.bmp");

	FILE *new_image;
	new_image = fopen(nume_nou, "wb");

	fwrite(&file_header.fileMarker1, 1, 1, new_image);
	fwrite(&file_header.fileMarker2, 1, 1, new_image);
	fwrite(&file_header.bfSize, 4, 1, new_image);
	fwrite(&file_header.unused1, 2, 2, new_image);
	fwrite(&file_header.imageDataOffset, 4, 1, new_image);
	fwrite(&info_header.biSize, 4, 1, new_image);
	fwrite(&info_header.width, 4, 1, new_image);
	fwrite(&info_header.height, 4, 1, new_image);
	fwrite(&info_header.planes, 2, 1, new_image);
	fwrite(&info_header.bitPix, 2, 1, new_image);
	fwrite(&info_header.biCompression, 4, 1, new_image);
	fwrite(&info_header.biSizeImage, 4, 1, new_image);
	fwrite(&info_header.biXPelsPerMeter, 4, 1, new_image);
	fwrite(&info_header.biYPelsPerMeter, 4, 1, new_image);
	fwrite(&info_header.biClrUsed, 4, 1, new_image);
	fwrite(&info_header.biClrImportant, 4, 1, new_image);

	fseek(bmp_file, 54, SEEK_SET);
	int i, j, p;
	int pitch = info_header.width * 3;

	if(pitch % 4 != 0){
		pitch += 4 - (pitch % 4);
	}

	int padding = pitch - (info_header.width * 3);
	const int zero = 0;
	for(i = 0; i < info_header.height; i++){
		for (j = 0; j < info_header.width; j++)
		{	
			fread(&img_pix, 3, 1, bmp_file);
			if((img_pix.blue < 255) && (img_pix.green < 255) && (img_pix.red < 255)){
				fwrite(&input_color, 3, 1, new_image);
				printf("x");
			}else
			{
				img_pix.blue = img_pix.green = img_pix.red = 255;
				fwrite(&img_pix, 3, 1, new_image);
				printf(".");
			}
		}
		for(p = 0; p < padding; p++){
			fwrite(&zero, 1, 1, new_image);
			fseek(bmp_file, 1, SEEK_CUR);
		}
		printf("\n");
	}	
	fclose(new_image);
}

int main()
{
	struct bmp_fileheader file_header;
	struct bmp_infoheader info_header;
	char nume_fisier[LENGHT], culori[15];
	FILE *bmp_file;
	pixel input_color;

	//Read the input file
	fgets(nume_fisier, sizeof(nume_fisier), stdin);
	nume_fisier[strcspn(nume_fisier, "\n")] = '\0';

	//Read the input colors
	fgets(culori, sizeof(culori), stdin);
	culori[strcspn(culori, "\n")] = '\0';
	input_color.blue = atoi(strtok(culori, " "));
	input_color.green = atoi(strtok(NULL, " "));
	input_color.red = atoi(strtok(NULL, " \n"));
/*
	//Numbers to eliminate
	fgets(cifre_elim, sizeof(cifre_elim), stdin);
	cifre_elim[strcspn(cifre_elim, "\n")] = '\0';

	//Bonus
	fgets(nume_bonus, sizeof(nume_bonus), stdin);
	nume_bonus[strcspn(nume_bonus, "\n")] = '\0';

	printf("nume fisier %s\n", nume_fisier);
	printf("Blue: %d\tGreen: %d\tRed: %d\n", input_color.blue, input_color.green, input_color.red);
*/
	bmp_file = fopen(nume_fisier, "rb");

	if(bmp_file != NULL){
			//FileType
		fread(&file_header.fileMarker1, 1, 1, bmp_file);
		fread(&file_header.fileMarker2, 1, 1, bmp_file);

		//Size of the file in bytes
		fread(&file_header.bfSize, 4, 1, bmp_file);

		//Going to data offset
		file_header.unused1 = file_header.unused2 = 0;
		fseek(bmp_file, 4, SEEK_CUR);
		fread(&file_header.imageDataOffset, 4, 1, bmp_file);

		//DIB header
		fread(&info_header.biSize, 4, 1, bmp_file);

		//Read Width and Height
		fread(&info_header.width, 4, 1, bmp_file);
		fread(&info_header.height, 4, 1, bmp_file);

		//Planes
		fread(&info_header.planes, 2, 1, bmp_file);

		//Number of bits per pixel
		fread(&info_header.bitPix, 2, 1, bmp_file);

		//Compression
		fread(&info_header.biCompression, 4, 1, bmp_file);

		//Image size
		fread(&info_header.biSizeImage, 4, 1, bmp_file);

		//For printing
		fread(&info_header.biXPelsPerMeter, 4, 1, bmp_file);
		fread(&info_header.biYPelsPerMeter, 4, 1, bmp_file);

		//Colors
		fread(&info_header.biClrUsed, 4, 1, bmp_file);	

		//Important Colors
		fread(&info_header.biClrImportant, 4, 1, bmp_file);

		task1(bmp_file, nume_fisier, input_color, file_header, info_header);
		
		fclose(bmp_file);
	}
	else
	{
		printf("Invalid file\n");
		return 1;
	}


	return 0;
}