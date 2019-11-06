/*
 * TASK5.C
 *
 *  Created on: 30.09.2019
 *      Author: aml
 */


#include "TASK5.H"

using namespace std;



namespace TASK5{

int ConcreteObserver::counter_ = 0;
int ConcreteObserver::newID_ = 0;


Subject::Subject(){
	size_ = 16;
	nmbObservers_ = 0;
	ptrObservers_ = new  (std::nothrow) IObserver*[size_]();
	if (ptrObservers_ == nullptr){
		size_ = 0;
	};
};

Subject::~Subject(){
	delete [] ptrObservers_;
};

int Subject::size(){
	return size_;
}

int Subject::nmbObservers(){
	return nmbObservers_;
}

bool Subject::containsObserver(IObserver *observer){
	if((observer == nullptr) || (observer == nullptr)) {return false;};
	for(int i=0; i < this->size_; i++){
		if(observer == this->ptrObservers_[i]){
			return true;
		};
	};
	return false;
}

void Subject::attach(IObserver *observer){
	if((observer == nullptr) || (observer == nullptr)) {return;};

	if(this->nmbObservers_ >= this->size_){
		// allocate new memory
		IObserver **tmpPtr = new (std::nothrow) IObserver*[2*this->size_];

		if(tmpPtr == nullptr) return; // no memory, no new observer added
		// copy all ptr into the new memory array
		for(int i=0; i < size_;i++){
			tmpPtr[i] = this->ptrObservers_[i];
		}
		delete [] this->ptrObservers_;
		this->ptrObservers_ = tmpPtr;
		size_ = 2*this->size_;
	};
	ptrObservers_[this->nmbObservers_] = observer;
	this->nmbObservers_++;
	return;
};


void Subject::detach(IObserver *observer){
	if((observer == nullptr) || (observer == nullptr)) {return;};
	int samples = this->nmbObservers_;

	for(int i=0; i < samples; i++){
		if(observer == this->ptrObservers_[i]){
			this->ptrObservers_[i] = this->ptrObservers_[this->nmbObservers_ - 1];
			this->ptrObservers_[this->nmbObservers_ - 1] = nullptr;
			this->nmbObservers_--;
			return;
		};
	};
};


void Subject::notify(){
	for(int i = 0; i < this->nmbObservers_; i++){
			this->ptrObservers_[i]->notify();
	};
};



void WebCamSubject::run(){
	this->captureData_   = cvCaptureFromCAM(-1);
	this->rgbData_ = cvQueryFrame(this->captureData_ );

	while(true){
		cv::waitKey(5); //Wait
		this->rgbData_ = cvQueryFrame(this->captureData_ );
		if( this->rgbData_ == 0 ) break;
		this->notify();
	}
};



WebCamObserver::WebCamObserver(std::string idStr = "Default" ) {
	ptrSubject_ = nullptr;
	idStr_ = idStr;
	cvNamedWindow(this->idStr_.c_str(), CV_WINDOW_AUTOSIZE );
	cv::moveWindow(this->idStr_.c_str(),200,200);
};

WebCamObserver::~WebCamObserver(){};

void WebCamObserver::setSubject(ISubject *sub) { ptrSubject_ = sub;};

void WebCamObserver::notify(){
	cvShowImage(this->idStr_.c_str(), ((WebCamSubject *) ptrSubject_)->rgbData_);
}

void WebCamObserver::notify(ISubject *s){
	this->notify();
}






WebCamObserverGray::WebCamObserverGray(std::string idStr) : WebCamObserver(idStr) {
	gray_ = nullptr;
};
WebCamObserverGray::~WebCamObserverGray(){
	if(gray_ != nullptr) { cvReleaseImage(&gray_);};
};
void WebCamObserverGray::notify(){
	if(gray_ != nullptr) { cvReleaseImage(&gray_);};
	gray_   = cvCreateImage(cvGetSize(((WebCamSubject *) ptrSubject_)->rgbData_),IPL_DEPTH_8U,1);
	cvCvtColor( ((WebCamSubject *) ptrSubject_)->rgbData_,gray_,CV_RGB2GRAY);
	cvShowImage(this->idStr_.c_str(), gray_);
}





WebCamObserverDownscale::WebCamObserverDownscale(std::string idStr) : WebCamObserver(idStr)  {
	img_ = nullptr;
};
WebCamObserverDownscale::~WebCamObserverDownscale(){
	if(img_ != nullptr) { cvReleaseImage(&img_);};
};
void WebCamObserverDownscale::notify(){
	if(img_ != nullptr) { cvReleaseImage(&img_);};
	IplImage *tmpSrc = ((WebCamSubject *) ptrSubject_)->rgbData_;
	img_ = cvCreateImage ( cvSize(256,256), tmpSrc->depth, tmpSrc->nChannels );
	cvResize(tmpSrc,img_);
	cvShowImage(this->idStr_.c_str(), img_);
}







void demoOpenCV01(){
	cvNamedWindow("X0", CV_WINDOW_AUTOSIZE );
	cvNamedWindow("X1", CV_WINDOW_AUTOSIZE );
	cv::moveWindow("X0",200,200);
	cv::moveWindow("X1",200,200);
	CvCapture  *capture   = cvCaptureFromCAM(-1);
	IplImage       *rgb   = cvQueryFrame( capture );
	IplImage      *gray   = cvCreateImage(cvGetSize(rgb),IPL_DEPTH_8U,1);
	while(true){
		rgb = cvQueryFrame( capture );
		if( rgb==0 ) break;
		cvCvtColor(rgb,gray,CV_RGB2GRAY);

		cvShowImage( "X0", rgb );
		cvShowImage( "X1", gray );
		if( cv::waitKey(10) == 27 ) {
			cv::moveWindow("X0",100,100);
			cv::moveWindow("X1",100,100);
		};
		cv::waitKey(5); //Wait of 100 ms
	}
	return;
}


void demoOpenCV00(){


	std::string winName = "this is you, smile! :)";
    cv::VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(0))
        return;
    for(;;)
    {
          cv::Mat frame;
          cap >> frame;
          if( frame.empty() ) break; // end of video stream
          imshow(winName, frame);
          if( cv::waitKey(10) == 27 ) { cv::moveWindow(winName,100,100);};
    }
    // the camera will be closed automatically upon exit
    cap.release();
    return;

}


void demoOB00(){
	ConcreteObserver *o;
	int nmbObs = 3;

	ConcreteSubject subject;

	for(int i = 0; i < nmbObs; i++){
		o = new ConcreteObserver();
		o->setSubject(&subject);
		subject.attach(o);
	}
	subject.setState("Hello World!");
	subject.setState("New Data");

	/*
	std::cout << "\n remove observer:" << o->getID() << "\n\n";
	subject.detach(o);

	subject.setState("Hello Dark side of the moon!");
	*/

}

void demoOB01(){

	WebCamSubject cam;
	WebCamObserver ob0("RGB0");
	WebCamObserverGray ob1("Gray");
	WebCamObserverDownscale ob2("down scaled 00");
	WebCamObserverDownscale ob3("down scaled 01");


	ob0.setSubject(&cam);
	ob1.setSubject(&cam);
	ob2.setSubject(&cam);
	ob3.setSubject(&cam);

	cam.attach(&ob0);
	cam.attach(&ob1);
	cam.attach(&ob2);
	cam.attach(&ob3);

	std::cout << "#observers: " << cam.nmbObservers() << std::endl;

	cam.run();

}



} // end namespace TASK5

