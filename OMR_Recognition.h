#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <dirent.h>
#include <cmath>
#include <iostream>
#include <direct.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <ctime>

 using namespace std;
 using namespace cv;

typedef pair<int, int> PAIR;

class OMR {

private:
	
	Mat omr;
	
	string Input_Path, Output_Path, Path;
	
	char Pixel[5], Character;
	
	int Pixel_String_Length, Number_of_Blocks, Block_Number, Number_Of_Cells, Number_Of_Sections, Number_Of_Questions;
	
	PAIR Pixel_Density[10];
	
	double Density;
	
	int Section_Start_X, Section_Start_Y, Cell_Diff_X, Cell_Diff_Y, Block_Diff_X, Section_Diff_Y, Section_Diff_X; // X denotes rows, Y denotes Columns 

	int id_startx, id_starty, id_diff_x, id_diff_y;

public:
	OMR();

private:
	
	void Parameters_Read(); // Read the Input Parameters
	
	void OMR_Input_Path_Init(); //Input path to images and output path to txt files.
	
	void OMR_Read(); //Read the OMR Sheeet
	
	inline int Get_Pixel_Color_Value(int x, int y); // Get pixel color code.
	
	void Section_Processing( int startx, int starty ); // Main Process
	
	void OMR_Processing(); //Generate the text files of all the sections
	
	void id_processing(); // To calculate the id of the OMR sheet



	void OMR_Output_Path_Init(); //Input path to txt files and output to a csv file.
	
	void Answer_Evaluation(); // Evaluate generated text files.

	void id_evaluation( FILE *); // to evalute the id of the OMR sheet


	void debug(); //Only used for debugging!! Remove after completion!!

public:

	void OMR_Evaluate(); // Generate the output csv file of the OMR folder.

	void compute_skew();//To compute the skew angle of the OMR sheet

	void rotate(Mat &src,double angle,Mat &dst);//Rotates the OMR sheet by given angle

};