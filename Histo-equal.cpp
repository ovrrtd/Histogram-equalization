#include <cv.h>
#include <highgui.h>
#include <iostream>

using namespace cv;
using namespace std;

int alpha;
int beta;
float hist[256];
float hist2[256];
float CP[256];
int a,b;
int j,countmax,countmin,jumlah;
int intensitas;
Mat image = imread("images.jpeg",0);
Mat new_image = Mat::zeros( image.size(), image.type() );
void mean()//untuk mencari nilai ratarata dengan penjumlahan array hist
{

    int  ratarata,x,y;
    jumlah=0;
    for( y= 0; y < image.rows; y++ )
    { for( x = 0; x < image.cols; x++ )
         {
      jumlah+=( image.at<uchar>(y,x) );

    }
    }
    ratarata=jumlah/(x*y);

    cout<<"nilai jumlah :"<<jumlah<<endl;
    cout<<"nilai mean :"<<ratarata<<endl;
}

void mean2()//untuk mencari nilai ratarata dengan penjumlahan array hist
{

    int  ratarata,x,y;
    jumlah=0;
    ratarata=0;
    for( y= 0; y < new_image.rows; y++ )
    { for( x = 0; x < new_image.cols; x++ )
         {
      jumlah+=( new_image.at<uchar>(y,x) );

    }
    }
    ratarata=jumlah/(x*y);

    cout<<"nilai mean baru :"<<ratarata<<endl;
}


void histo()//untuk counting jumlah tiap intensitas
{
    cout<<"nilai histogram gambar lama"<<endl;
    for( int y = 0; y < image.rows; y++ ){
    for( int x = 0; x < image.cols; x++ ){

      a= image.at<uchar>(y,x) ;

        for(b=0;b<256;b++){
            if(b==a){
            hist[b]+=1;

            }
        }
     }
     }
    for(b=0;b<256;b++){

    cout<<"hist ["<<b<<"]="<<hist[b]<<", ";

    }

}
    void counthisto(){ //cari nilai maksimal dan minimum dari array histogram
        histo();

        for(j=0;j<255;j++){
            if(j==0){
            countmin=0;
            countmax=0;
            }

            if(hist[countmax]<hist[j]){
                countmax=j;}
            else if (hist[countmin]>hist[j]){

            countmin=j;}


        }
        cout<<endl<<"maksimal count adalah hist ["<<countmax<<"]= "<<hist[countmax]<<endl;
        cout<<"minimal count adalah hist ["<<countmin<<"]= "<<hist[countmin]<<endl;
}
void histo2()//untuk counting jumlah tiap intensitas
{
    cout<<"nilai histogram gambar baru"<<endl;
    for( int y = 0; y < new_image.rows; y++ ){
    for( int x = 0; x < new_image.cols; x++ ){

      a= saturate_cast<uchar>(new_image.at<uchar>(y,x)) ;

        for(b=0;b<256;b++){
            if(b==a){
            hist2[b]+=1;

            }
        }
     }
     }
    for(b=0;b<256;b++){
    cout<<"hist ["<<b<<"]="<<hist2[b]<<", ";

    }

}
    void counthisto2(){ //cari nilai maksimal dan minimum dari array histogram
        histo2();

        for(j=0;j<256;j++){
            if(j==0){
            countmin=0;
            countmax=0;
            }

            else if(hist2[countmax]<hist2[j]){
                countmax=j;}
            else if (hist2[countmin]>hist2[j]){

            countmin=j;}


        }





    cout<<endl<<"maksimal count adalah hist ["<<countmax<<"]= "<<hist2[countmax]<<endl;
    cout<<"minimal count adalah hist ["<<countmin<<"]= "<<hist2[countmin]<<endl;
    }

    void nilaiintesitasmaks()
    {
        int i=255;
        int maks;
        histo();
        while(hist[i]>0){
            maks=i;


        }

        cout<<maks;


    }

void nilaiintesitasmin()
    {
        int i=0;
        int minm;
        histo();
        while(hist[i]>0){
            minm=i;


        }

        cout<< minm;


    }



void histequ(){

    int matrik=image.cols*image.rows;
    CP[0]=hist[0]/matrik;
    for(j=1;j<256;j++){
    CP[j]=(hist[j]/matrik)+CP[j-1];
    }




    }



int main( )
{

 counthisto();
 mean();
 histequ();


 cout<<"* masukkan nilai range atas histo equalization 1 hingga (nilai default 255): ";cin>>alpha; //untuk memberi nilai pada rumus,nilai batas atas default nya 255
 for( int y = 0; y < image.rows; y++ )
    { for( int x = 0; x < image.cols; x++ )
         { intensitas=saturate_cast<uchar> ( image.at<uchar>(y,x));
      new_image.at<uchar>(y,x)=
           floor(CP[intensitas] * alpha) ;
        //rumus persaamaan untuk kontras stretching
    }

    }

 counthisto2();
 namedWindow("Original Image", 1); // membuat window dengan flag bernilai 1 agar window autosized
 namedWindow("New Image", 1);

 imshow("Original Image", image);//menampilkan gambar
 imshow("New Image", new_image);
 /// Wait until user press some key


 waitKey();
 return hist2[0];
}
