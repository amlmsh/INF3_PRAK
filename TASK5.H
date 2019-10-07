/*
 * TASK5.H
 *
 *  Created on: 30.09.2019
 *      Author: aml
 */


/**
 *
 * \file TASK5.H
 *
 * \brief Contains the namespace TASK5. Namespace TASK5
 * contains the definition of the interfaces
 * of the classes implementing subject the observer
 * design patterns. In addition some demos can be found
 * that make use of video image capturing functionality
 * of openCV.
 *
 */




#ifndef TASK5_H_
#define TASK5_H_



//opencv
#include <opencv2/opencv.hpp>


using namespace std;



/**
 *
 * \namespace TASK5
 *
 * \brief Contains the definition of the interfaces
 * of the classes implementing subject the observer
 * design patterns. In addition some demos can be found
 * that make use of video image capturing functionality
 * of openCV.
 *
 */
namespace TASK5{




class IObserver;
class ISubject;

/**
 *
 *  \interface IObserver
 *  \brief     A class defining the interface of an observer
 * 	used for the classical observer design pattern.
 *
 */
class IObserver {

 public:

	/**
	 *
	 * \brief Destructor
	 *
	 */
	virtual ~IObserver() {};

 	/**
 	 *
 	 * \brief This method is used to receive an update
 	 * notification from subject.
 	 *
 	 */
 	virtual void notify() = 0;

 	/**
 	 *
 	 * \brief This method is used to receive an update
 	 * notification from subject.
 	 *
 	 */
 	virtual void notify(ISubject *s) = 0;

};

/**
 *
 *  \interface ISubject
 *  \brief     A class defining the interface of a subject
 * 	used for the classical observer design pattern.
 *
 */
class ISubject {

 public:

	/**
	 *
	 * \brief Destructor
	 *
	 */
	virtual ~ISubject() {};

	/**
	 *
	 * \brief Add the given observer for the subject.
	 * \param *observer IObserver.
	 */
	virtual void attach(IObserver *observer) = 0;

	/**
	 *
	 * \brief Remove the first occurrence of the given observer for the subject.
	 *
	 * If this observer is listed several times the others remain in this list.
	 * \param *observer IObserver.
	 */
	virtual void detach(IObserver *observer) = 0;

	/**
	 *
	 * \brief Notification of all registers observers.
	 */
	virtual void notify() = 0;
};









/**
 *
 *  \class Subject
 *  \brief     The class defining the  of a subject
 * 	used for the classical observer-pattern.
 *
 */
class Subject : public ISubject {

public:

	/**
	 *
	 * \brief Constructor
	 *
	 */
	Subject();

	/**
	 *
	 * \brief Destructor
	 *
	 */
	virtual ~Subject();



	virtual void attach(IObserver *observer);

	virtual void detach(IObserver *observer);

	void notify();


	/**
	 *
	 * \brief Returns the number of observer attached to the subject object.
	 *
	 * \return number of observers attached (>= 0).
	 */
	int nmbObservers();

	/**
	 *
	 *  \brief Returns the size of the container storing observers.
	 *
	 *  \return capacity of the subject
	 */
	int size();

	/**
	 *
	 * \brief Returns whether or not the subject objects contains observer objects.
	 *
	 * \param  observer reference of an observer object
	 * \return bool, false if no observer is stored, true otherwise.
	 */
	bool containsObserver(IObserver *observer);


protected:


	/**
	 *
	 * \brief Array of pointers of type IObserver.
	 *
	 * Container of the observers stored.
	 */
	IObserver **ptrObservers_;



	/**
	 *
	 * \brief Number of observer objects stored.
	 */
	int nmbObservers_;


	/**
	 *
	 * \brief Capacity of the obsever object storage.
	 *
	 */
	int size_;

};



/**
 *
 * \class WebCamSubject
 *
 * \brief Implements the data source of a webcam.
 *
 * This class is derived from class \ref Subject. Thus, it implements
 * the subject of the observer design pattern.
 *
 * The access to the webcam is done based on the  openCV libraries (www.openCV.org).
 *
 */
class WebCamSubject : public Subject{
public:

	/**
	 *
	 * \brief Constructor
	 *
	 */
	WebCamSubject() : Subject() {captureData_ = nullptr; rgbData_ = nullptr;};

	/**
	 *
	 * \brief Captures permanently image data from the webcam.
	 *
	 * The method implements an endless-loop. Thus, once called the method does not terminate.
	 *
	 */
	void run();


	/**
	 *
	 * \brief RGB image data storage to be directly accessed.
	 *
	 */
	IplImage   *rgbData_;
private:

	/**
	 *
	 * \brief Image data of the raw image data captured from the webcam.
	 *
	 */
	CvCapture  *captureData_;

};



/**
 *
 * \class WebCamObserver
 *
 * \brief Implements the view of the RGB image data.
 *
 * This class implements \ref IObserver Thus, it implements
 * the observer of the observer design pattern.
 *
 * The display to the webcam is done based on the  openCV libraries (www.openCV.org).
 *
 */
class WebCamObserver : public IObserver{
public:

	/**
	 *
	 * \brief Constructor
	 *
	 * \param idStr  std::string the string is the unique ID of  the window displayed
	 */
	WebCamObserver(std::string idStr);


	/**
	 *
	 * \brief Destructor
	 *
	 */
	~WebCamObserver();


	/**
	 *
	 * \brief Set the subject the observer is
	 *
	 */
	void setSubject(ISubject *sub);


	void notify();

	void notify(ISubject *s);
protected:

	/**
	 *
	 * \brief ID string for the view window.
	 *
	 * The ID must  be unique otherwise the
	 * windows representing the corresponding data is not displayed.
	 */
	std::string idStr_;


	/**
	 *
	 * \brief Reference to the subject
	 */
	ISubject *ptrSubject_;
};



/**
 *
 * \class WebCamObserverGray
 *
 * \brief Implements the view of the gray value image data.
 *
 * This class is derived from observer \ref WebCamObserver. Thus, it implements
 * the observer of the observer design pattern.
 *
 * The display to the webcam is done based on the  openCV libraries (www.openCV.org).
 *
 */
class WebCamObserverGray : public WebCamObserver{
public:

	/**
	 *
	 * \brief Constructor
	 *
	 *\param idStr  std::string the string is the unique ID of  the window displayed
	 */
	WebCamObserverGray(std::string idStr);

	/**
	 *
	 * \brief Destructor
	 *
	 */
	~WebCamObserverGray();


	void notify();
protected:

	/**
	 *
	 * \brief Pointer referring to the gray value image data.
	 */
	IplImage      *gray_;
};


/**
 *
 * \class WebCamObserverDownscale
 *
 * \brief Implements the view of the down scaled rgb image data.
 *
 * This class is derived from observer \ref WebCamObserver. Thus, it implements
 * the observer of the observer design pattern.
 *
 * The display to the webcam is done based on the  openCV libraries (www.openCV.org).
 *
 */
class WebCamObserverDownscale : public WebCamObserver{
public:

	/**
	 *
	 * \brief Constructor
	 *
	 * \param idStr  std::string the string is the unique ID of  the window displayed
	 */
	WebCamObserverDownscale(std::string idStr);

	/**
	 *
	 * \brief Destructor
	 */
	~WebCamObserverDownscale();

	void notify();
protected:

	/**
	 *
	 * \brief Pointer referring to the down scaled rgb  image data.
	 */
	IplImage      *img_;
};







class ConcreteSubject : public Subject{
public:
	ConcreteSubject() : Subject() {state_ = ""; nmbStateChanges_ = 0;};
	~ConcreteSubject() {};
	void setState(std::string s){
		state_ = s;
		nmbStateChanges_++;
		notify();
	};
	std::string getState(){return state_;};

	int nmbStateChanges_;
protected:
	std::string state_;

};




class ConcreteObserver : public IObserver{
public:
	ConcreteObserver() {
		ConcreteObserver::counter_++;
		ConcreteObserver::newID_++;
		ID_ = ConcreteObserver::newID_;
		ptrSubject_ = nullptr;
	};

	ConcreteObserver(ISubject *s) {
		ConcreteObserver::counter_++;
		ConcreteObserver::newID_++;
		ID_ = ConcreteObserver::newID_;
		ptrSubject_ = s;
	};

	~ConcreteObserver(){ ConcreteObserver::counter_--;};

	void notify(){
		std::string msg = "???";
		if(ptrSubject_ != nullptr){
			msg = ((ConcreteSubject *) ptrSubject_)->getState();
		};
		std::cout << "observer having ID=" << ID_ <<
				" received state change (nmb=" <<
				((ConcreteSubject *) ptrSubject_)->nmbStateChanges_ <<
				") notification:"  << msg <<
				std::endl;


		//if(ptrSubject_ != nullptr){
		//	((ConcreteSubject *) ptrSubject_)->setState(ID_ + "got it!");
		//};

	};

	void notify(ISubject *S){
		this->notify();
	}


	void setSubject(ISubject *s) {ptrSubject_ = s;};

	int getID(){return ID_;};

private:
	static int counter_;
	static int newID_;
	int ID_;
	ISubject *ptrSubject_;
};



void demoOpenCV00();
void demoOpenCV01();
void demoOB00();
void demoOB01();


} // end namespace TASK5



#endif /* TASK5_H_ */
