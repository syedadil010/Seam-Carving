# Seam-Carving for Content Aware Image Resizing

The objective of seam carving algorithm is to perform content aware resizing of images. This allows image to be resized without losing meaningful content from cropping or scaling. The idea is to locate the image's optimal seams, connected pixel paths going from top to bottom or left to right, to remove or insert while preserving the photorealism of the image. Furthermore, manipulating the gradient energy map that describes how optimal a seam is allows for functionality such as object removal.

## Process
Original Image:  
  
![A](BroadwayTowerSeamCarvingA.png)

Image with low energy seams identified:  
  
![B](BroadwayTowerSeamCarvingC.png)


Resized Image:  
  
![C](BroadwayTowerSeamCarvingA.png) 

## Prerequisites:

cmake, opencv


## To compile on your own machine

cd build/  
cmake ../  
make  


## To run

In the build folder:  
./sc image1 new_width new_height image2

 
