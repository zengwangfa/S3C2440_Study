#include <stdio.h>
#include "jpeglib.h"
#include <setjmp.h>


/*
	Allocate and initialize a JPEG decompression object    // 1.分配和初始化一个decompression结构体
	Specify the source of the compressed data (eg, a file) // 2.指定源文件
	Call jpeg_read_header() to obtain image info           // 用jpeg_read_header获得jpg信息
	Set parameters for decompression                       // 设置解压参数,比如放大、缩小
	jpeg_start_decompress(...);                            // 启动解压：jpeg_start_decompress
	while (scan lines remain to be read)
		jpeg_read_scanlines(...);                            // 循环调用jpeg_read_scanlines
	jpeg_finish_decompress(...);                           // jpeg_finish_decompress
	Release the JPEG decompression object                  // 释放decompression结构体

*/

/* Usage: jpg2rgb <jpg_file>
*/

int main(int argc,char **argv)
{
	/*
	* 1.You must initialize the error handler structure, 
	* store a pointer to it intothe JPEG object's "err" field,
	* and then call jpeg_create_compress() toinitialize the rest of the JPEG object
	*/
	struct jpeg_decompress_struct cinfo;	
	struct jpeg_error_mgr jerr;
	FILE * infile;
	
	cinfo.err = jpeg_std_error(&jerr);	
	jpeg_create_decompress(&cinfo);

	/* 2.Specify the destination for the compressed data */
	if ((infile = fopen(argv[1], "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", argv[1]);
    return -1;
	}
	jpeg_stdio_src(&cinfo, infile);//指定源文件

	/* 3.Call jpeg_read_header() to obtain image info */
	jpeg_read_header(&cinfo, TRUE);

	/* 源图像信息 */
	printf("image width  = %d\n",cinfo.image_width);
	printf("image height = %d\n",cinfo.image_height);
	printf("image num components = %d\n",cinfo.num_components);//一个像素包含几个单元
	
	/* 4.Set parameters for decompression */
	printf("enter M/N:\n");//缩放因子为:(scale_num /scale_denom)，即0.5
	scanf( "%d/%d", &cinfo.scale_num, &cinfo.scale_denom);
  printf("scale to %d/%d\n", cinfo.scale_num, cinfo.scale_denom);	    
	 
	/* 5.jpeg_start_decompress */
	jpeg_start_decompress(&cinfo);
	/* 输出的图象的信息 */
	printf("output_width = %d\n", cinfo.output_width);
	printf("output_height = %d\n", cinfo.output_height);
	printf("output_components = %d\n", cinfo.output_components);

	/* 6.while (scan lines remain to be read)一行一行的获取解压的数据 */
	//jpeg_read_scanlines(&cinfo); 

	/* 7.jpeg_finish_decompress */
	jpeg_finish_decompress(&cinfo);

	/* 8.Release the JPEG decompression object */
	jpeg_destroy_decompress(&cinfo);

	
	return 0;
}

