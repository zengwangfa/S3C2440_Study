
#include "framebuffer.h"

/*
 * http://blog.csdn.net/p1126500468/article/details/50428613
 */
 
 void draw_circle(int x, int y, int r, int color)  
 {	
	 int a, b, num;  
	 a = 0;  
	 b = r;  
	 while(22 * b * b >= r * r) 		 // 1/8圆即可  
	 {	
		 fb_draw_dot(x + a, y - b,color); // 0~1  
		 fb_draw_dot(x - a, y - b,color); // 0~7  
		 fb_draw_dot(x - a, y + b,color); // 4~5  
		 fb_draw_dot(x + a, y + b,color); // 4~3  
   
		 fb_draw_dot(x + b, y + a,color); // 2~3  
		 fb_draw_dot(x + b, y - a,color); // 2~1  
		 fb_draw_dot(x - b, y - a,color); // 6~7  
		 fb_draw_dot(x - b, y + a,color); // 6~5  
		   
		 a++;  
		 num = (a * a + b * b) - r*r;  
		 if(num > 0)  
		 {	
			 b--;  
			 a--;  
		 }	
	 }	
 }	
   
 //-----------画线。参数：起始坐标，终点坐标，颜色--------	
 void draw_line(int x1,int y1,int x2,int y2,int color)	
 {	
	 int dx,dy,e;  
	 dx=x2-x1;	 
	 dy=y2-y1;	
	 if(dx>=0)	
	 {	
		 if(dy >= 0) // dy>=0  
		 {	
			 if(dx>=dy) // 1/8 octant  
			 {	
				 e=dy-dx/2;  
				 while(x1<=x2)	
				 {	
					 fb_draw_dot(x1,y1,color);  
					 if(e>0){y1+=1;e-=dx;}	   
					 x1+=1;  
					 e+=dy;  
				 }	
			 }	
			 else		 // 2/8 octant	
			 {	
				 e=dx-dy/2;  
				 while(y1<=y2)	
				 {	
					 fb_draw_dot(x1,y1,color);  
					 if(e>0){x1+=1;e-=dy;}	   
					 y1+=1;  
					 e+=dx;  
				 }	
			 }	
		 }	
		 else			// dy<0  
		 {	
			 dy=-dy;   // dy=abs(dy)  
			 if(dx>=dy) // 8/8 octant  
			 {	
				 e=dy-dx/2;  
				 while(x1<=x2)	
				 {	
					 fb_draw_dot(x1,y1,color);  
					 if(e>0){y1-=1;e-=dx;}	   
					 x1+=1;  
					 e+=dy;  
				 }	
			 }	
			 else		 // 7/8 octant	
			 {	
				 e=dx-dy/2;  
				 while(y1>=y2)	
				 {	
					 fb_draw_dot(x1,y1,color);  
					 if(e>0){x1+=1;e-=dy;}	   
					 y1-=1;  
					 e+=dx;  
				 }	
			 }	
		 }	   
	 }	
	 else //dx<0  
	 {	
		 dx=-dx;	 //dx=abs(dx)  
		 if(dy >= 0) // dy>=0  
		 {	
			 if(dx>=dy) // 4/8 octant  
			 {	
				 e=dy-dx/2;  
				 while(x1>=x2)	
				 {	
					 fb_draw_dot(x1,y1,color);  
					 if(e>0){y1+=1;e-=dx;}	   
					 x1-=1;  
					 e+=dy;  
				 }	
			 }	
			 else		 // 3/8 octant	
			 {	
				 e=dx-dy/2;  
				 while(y1<=y2)	
				 {	
					 fb_draw_dot(x1,y1,color);  
					 if(e>0){x1-=1;e-=dy;}	   
					 y1+=1;  
					 e+=dx;  
				 }	
			 }	
		 }	
		 else			// dy<0  
		 {	
			 dy=-dy;   // dy=abs(dy)  
			 if(dx>=dy) // 5/8 octant  
			 {	
				 e=dy-dx/2;  
				 while(x1>=x2)	
				 {	
					 fb_draw_dot(x1,y1,color);  
					 if(e>0){y1-=1;e-=dx;}	   
					 x1-=1;  
					 e+=dy;  
				 }	
			 }	
			 else		 // 6/8 octant	
			 {	
				 e=dx-dy/2;  
				 while(y1>=y2)	
				 {	
					 fb_draw_dot(x1,y1,color);  
					 if(e>0){x1-=1;e-=dy;}	   
					 y1-=1;  
					 e+=dx;  
				 }	
			 }	
		 }	   
	 }	
 }	

