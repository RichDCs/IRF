
#include "manage_img.h"
extern int reduction_factor ;

void extractImage(Mat& src, Mat& dst, int x1, int y1, int x2, int y2)
{
	Mat image;
	Rect region_of_interest = Rect(x1, y1, x2-x1, y2-y1);
	dst = src(region_of_interest);
}

void saveImage(Mat& src, string name){
	;
}

struct database_picto db_picto[] = {
	{"img/pictos/bombe.png", "bombe"},
	{"img/pictos/flamme.png", "flamme"},
	{"img/pictos/parking.png", "parking"},
	{"img/pictos/homme.png", "homme"},
	{"img/pictos/voiture.png", "voiture"},
	/*vous pouvez ajouter directement des lignes ici -> les boucles utilisent des "sizeof(struct)" pour le nb d'elements */
};

struct database_picto db_text[] = {
	{"img/text/large.png", "large"},
	{"img/text/medium.png", "medium"},
	{"img/text/small.png", "small"},
	/*vous pouvez ajouter directement des lignes ici -> les boucles utilisent des "sizeof(struct)" pour le nb d'elements */
};

int match_img(Mat& img_extract, int type_base){
	int match_method = 5;
	int id_picto = 0 ;

	Mat img_picto;
	Mat result ;

	double minVal,maxVal,matchVal,max_matchVal=0;
	Point minLoc, maxLoc, matchLoc;

	int database_size ;
	struct database_picto *db_use ;

	if(type_base == MATCH_IMG ){
		database_size = sizeof(db_picto)/sizeof(struct database_picto) ;
		db_use = db_picto;
	}
	else if(type_base == MATCH_TXT ){
		database_size = sizeof(db_text)/sizeof(struct database_picto) ;
		db_use = db_text;
	}
	else
		exit(52);

	for(int i = 0 ; i < database_size ; i++){
		img_picto = imread(db_use[i].path, 1);

		if (img_extract.empty() || img_picto.empty()){
			cout << "Error : Image cannot be loaded..!!" << endl;
		}

		Size size_image_test( img_picto.cols/reduction_factor, img_picto.rows/reduction_factor);
		resize(img_picto, img_picto, size_image_test );

		int result_cols =  img_extract.cols - img_picto.cols + 1;
		int result_rows = img_extract.rows - img_picto.rows + 1;
		//printf("P:%d-%d\n",result_cols,result_rows);
		result.create( result_cols, result_rows, CV_32FC1 );
		matchTemplate( img_extract, img_picto, result, match_method );

		/// Localizing the best match with minMaxLoc
		minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

		/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
		if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED ){
			matchLoc = minLoc;
			matchVal = minVal;
		}else{
			matchLoc = maxLoc;
			matchVal = maxVal;
		}

		printf("v:%0.2lf | ",matchVal);
		if(matchVal > max_matchVal){
			max_matchVal = matchVal;
			id_picto = i;
		}
	}

	if(max_matchVal > 0.5)
		printf("\n--> good match> max_v:%0.2lf | id:%d | description:   %s", max_matchVal, id_picto, db_use[id_picto].description.c_str() );
	else
		printf("\nno match");
	cout << "\n" ;

	return id_picto;
}