#include "OMR_Recognition.h"

OMR::OMR() { 
	//Initialization
	Density = 0.0 ;
	Input_Path = Output_Path = "" ;
	Path = "" ;
}

void OMR::OMR_Read() {
	
	DIR *directory;
	struct dirent *entry;

	if( directory = opendir( Input_Path.c_str() ) ) { 

		while( entry = readdir(directory) ) {
			
			if( strcmp(entry -> d_name , "Input") == 0 )
				continue;

			if( strcmp( entry -> d_name, "." ) == 0)
				continue;
			
			if( strcmp(entry -> d_name, ".." ) == 0)
				continue;
			
			string name = entry -> d_name;
			omr = imread( Input_Path + name, -1 ); 
			string output = name.substr(0, name.find(".")) + ".txt" ;
			freopen( (Output_Path + output).c_str(), "w", stdout ) ;
			
			id_processing();

			OMR_Processing();

			putchar('\n');

		}

	} else {

		printf("The given directory is not present!!\n");
		printf("Please make sure that the specified directory to the OMR images is CORRECT!!\n");
		throw "Error";

	}
}

void OMR::debug() {  
	
	omr = imread("C:/Users/manu/Desktop/my stuff/study/all sem/sem 7/mini project/OMR/Good/scan0001.jpg", -1);
	
	for(int i = 1; i <= 10; ++i ){
		Scalar v = omr.at<uchar>(370, 546 + i );
		cout << v << endl;
	}

}

void OMR::OMR_Input_Path_Init() { 
	Path += "/";
	Input_Path = Path;
	string temp = "";

	_mkdir("Input") ;
	system("rmdir /S /Q Input");

	_mkdir( "Input" );
	temp = "Input/";

	Output_Path = temp ;
}

int OMR::Get_Pixel_Color_Value(int x, int y) {  
	Scalar Location;
	Location = omr.at<uchar>(Point(y, x) );
	return Location[0];
}

void OMR::Parameters_Read() {
	try {
		if(!freopen("input.txt", "r", stdin))
			throw "Error";
		}catch(...) {  
			printf("Input file not found error!!\n");
			printf("Please make sure that 'input.txt' file is present in the path where your program is!!\n");
			throw "Error";
		};
	try {
		char s[1010], foo[1010];
		int l, i;
		if( !gets(s) )
			throw "Error";
		sscanf(s, "%d %d %s", &id_startx, &id_starty, foo);
		if( !gets(s) )
			throw "Error";
		sscanf(s, "%d %s", &id_diff_x, foo);
		if( !gets(s) )
			throw "Error";
		sscanf(s, "%d %s", &id_diff_y, foo) ;
		if( !gets(s) )
			throw "Error";
		sscanf(s, "%d %d %s", &Section_Start_X, &Section_Start_Y, foo);
		if(!gets(s))
			throw "Error";
		sscanf(s, "%d %s", &Cell_Diff_X, foo);
		if(!gets(s))
			throw "Error";
		sscanf(s, "%d %s", &Cell_Diff_Y, foo);
		if(!gets(s))
			throw "Error";
		sscanf(s, "%d %s", &Block_Diff_X, foo);
		if(!gets(s))
			throw "Error";
		sscanf(s, "%d %s", &Number_Of_Cells, foo);
		if(!gets(s))
			throw "Error";
		sscanf(s, "%d %s", &Number_Of_Questions, foo);
		if(!gets(s))
			throw "Error";
		sscanf(s, "%d %s", &Number_Of_Sections, foo);
		if(!gets(s))
			throw "Error";
		sscanf(s, "%d %s", &Section_Diff_X, foo);
		if(!gets(s))
			throw "Error";
		sscanf(s, "%d %s", &Section_Diff_Y, foo);
		if(!gets(s))
			throw "Error";
		Path = s;
	}
	catch(...) { 
		printf("Format of 'input.txt' does not match the required format!!\n");	
		throw "Error";
	};
}


void OMR::id_processing() {
	
	int startx, starty, sx, sy, i, pi, pj;
	
	startx = id_startx ;
	starty = id_starty ;

	for( i = 1; i <= 16; ++i ){  
	
		sx = startx ;
		sy = starty + ( i - 1 ) * (id_diff_y + 5);
		if( i >= 6 ){

			sy = sy + 2 ;
			sx = sx - 2 ;

		}
		if( i >= 10 ) {
			
			sy = sy + 2 ;
			sx = sx - 2 ;
		
		}

		for( pi = 1; pi <= id_diff_y ; ++pi ) 
			for( pj = 1; pj <= id_diff_x ; ++pj ) 
				printf("%dx", Get_Pixel_Color_Value(sx + pj, sy + pi) );
	
		printf("n");
	}

}


void OMR::Section_Processing( int startx, int starty ) {

	int i, j, k, pi, pj;
	int sx, sy, f = 1, s = 1;  

	for( i = 1 ; i <= Number_Of_Questions ; ++i ) { 
	
		sx = startx + (i - 1) * Block_Diff_X; 
		
		for( j = 1 ; j <= Number_Of_Cells ; ++j ) {  
			
			sy = starty + (j - 1) * (Cell_Diff_Y + 4);
				
			for( pi = 1 ; pi <= Cell_Diff_Y ; ++pi ) { 
				
				for( pj = 1 ; pj <= Cell_Diff_X ; ++pj ) {  
				
					printf("%dx", Get_Pixel_Color_Value( sx + pj, sy + pi ) ) ;

				}
			
			}
			
			printf("n");
			
		} 

		if( f == (6 * s) ){
				startx = startx - 8;
				s = s + 1;
		}

		++f;

	}
	
}

void OMR::OMR_Processing() {
	
	int startx , starty, i;

	startx = Section_Start_X ;
	starty = Section_Start_Y ;

	for( i = 1; i <= Number_Of_Sections ; ++i ) { 
		
		Section_Processing( startx, starty ) ;
		
		startx += Section_Diff_X ; 
		starty += Section_Diff_Y ;

	}

}

void OMR::OMR_Output_Path_Init() {

	string temp = Path.substr(0, Path.find("Good") ) ;

	_mkdir( ( temp + "Output").c_str() ) ;
	Input_Path = "Input/";
	Output_Path = temp + "Output/";

}

void OMR::id_evaluation( FILE *input ) {

	int i , counter = 1, position = 0, value ;
	int black_pixel_count , total_pixel_count , ID;

	black_pixel_count = total_pixel_count = ID =  0 ;

	while( 1 ) {
	
		if( counter == 17 )
			break;

		Character = fgetc( input ) ;
		
		if( Character == 'x' ) {

			Pixel[position] = '\0' ;
			value = atoi( Pixel );
			if( value <= 200 ) 
				black_pixel_count++;
			position = 0;
			total_pixel_count++;

		}
		else
		if( Character == 'n' ) {
		
			Density =  (double) black_pixel_count / (double) total_pixel_count ;
			if( Density >= 0.5 ) 
				ID += (int) pow( 2, 16 - counter ) ;
			black_pixel_count = total_pixel_count = 0 ;
			++counter ; 

		}
		else
			Pixel[ position++ ] = Character ;

	} 
	
	printf("%d,", ID );

}

void OMR::Answer_Evaluation() { 
	
	int i, j;

	int position, black_pixel_count, total_pixel_count, flag, value, cell, display;

	position = black_pixel_count = total_pixel_count = cell = 0;
	
	flag  = 1 ;

	DIR *directory;
	struct dirent *entry;
	
	freopen( ( Output_Path + "Output.csv" ).c_str() , "w", stdout);

	printf("Serial No., File Name");

	for( i = 1; i <= Number_Of_Sections ; ++i ) { 
	
		for( j = 1; j <= Number_Of_Questions ; ++j )
			printf(",%c%d", 'A' + i - 1, j);

	}
	putchar('\n');

	if( directory = opendir( Input_Path.c_str() ) ) {
	
		while( entry = readdir( directory ) ) {
		
			if( strcmp(entry -> d_name , "." ) == 0 )
				continue;

			if( strcmp( entry -> d_name , ".." ) == 0 )
				continue;

			string filename;
			filename = "Input/" ;

			string temp = entry -> d_name;

			for( i= 0; i < temp.length(); ++i )
				filename += temp[i] ;

			FILE *input = fopen( filename.c_str(), "r" );

			if( input == NULL )
				throw "Error";

			id_evaluation( input ) ;
			
			printf( "%s", entry -> d_name );

			while(1){
			
				Character = fgetc( input );
				
				if( Character == '\n'  || Character == NULL )
					break;

				if(Character == 'x'){
					
					Pixel[position] = '\0';
					value = atoi( Pixel );
					if(value <= 200)
						++black_pixel_count;
					position = 0;
					++total_pixel_count;

				}
				else
				if( Character == 'n' ){
					
					if(flag <= Number_Of_Cells){
						
						flag++;
						Pixel_Density[cell].first = black_pixel_count;
						Pixel_Density[cell].second = total_pixel_count;
						black_pixel_count = 0;
						total_pixel_count = 0;
						++cell;

					}
					if( flag == Number_Of_Cells + 1 ){
						
						flag = 1;
						Density = 0.0;
						display = -1;
						cell = 0;
						double temp;
						for(i = 0; i < Number_Of_Cells; ++i ){
							temp = (double) Pixel_Density[i].first / (double) Pixel_Density[i].second ;
							if(temp > Density && temp >= 0.3){
								
								Density = temp;
								display = i + 1;
							
							}
						
						}

						if(display == -1)
							printf(",None");
						else
							printf(",%c",(char) ( display + 64 ) );

					}

				}
				else
					Pixel[position++] = Character ;

			}

			printf("\n");
			fclose(input);

		}
	
	
	}

}

void OMR::OMR_Evaluate(){
	
	try{
	
		Parameters_Read();
		OMR_Input_Path_Init();
		OMR_Read();

		OMR_Output_Path_Init();
		Answer_Evaluation();

	}catch(...) {
		printf("There is error in the Input file\n");
		return;
	}
}

void OMR::compute_skew(){
	
	Mat src = imread("C:/Users/manu/Desktop/my stuff/study/all sem/sem 7/mini project/OMR_RECOGNITION/ChallengeImages/rotate.jpg",0);
	Size size = src.size();
	cout<<size<<endl;
	bitwise_not(src,src);
	imwrite("C:/Users/manu/Desktop/my stuff/study/all sem/sem 7/mini project/OMR_RECOGNITION/ChallengeImages/complement.jpg",src);
	vector<Vec4i> lines;
	HoughLinesP(src,lines,1,CV_PI/180,100,size.width/2.f,20);
	Mat disp_lines(size,CV_8UC1,Scalar(0,0,0));
	double angle = 0.0;
	unsigned nb_lines = lines.size();
	for(unsigned i = 0; i < nb_lines; ++i){
		line(disp_lines,Point( lines[i][0], lines[i][1] ),
                 Point(lines[i][2], lines[i][3]), Scalar(255, 0 ,0) );
		angle += atan2((double)lines[i][3] - lines[i][1],
                       (double)lines[i][2] - lines[i][0]);
	}
	angle /= nb_lines;
	cout<<"File angle = "<<angle * 180 / CV_PI<<endl;
	imwrite("+C:/Users/manu/Desktop/my stuff/study/all sem/sem 7/mini project/OMR_RECOGNITION/ChallengeImages/lines.jpg",disp_lines);
	
}

void OMR::rotate(Mat &src,double angle,Mat &dst){

	int len  = max(src.cols,src.rows);
	Point2f pt(len/2.,len/2.);
	Mat r = getRotationMatrix2D(pt,angle,1.0);
	warpAffine(src,dst,r,Size(len,len));
}



