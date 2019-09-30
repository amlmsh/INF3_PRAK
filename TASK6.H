/*
 * TASK6.H
 *
 *  Created on: 01.10.2019
 *      Author: aml
 */

#ifndef TASK6_H_
#define TASK6_H_

#include <fstream>

using namespace std;

namespace TASK6{

/**
 *
 *  \class Element
 *  \@param T Type
 *  \brief     A template class definition. The class
 *  contains the value  of the item and two references.
 *  One refers to the preceding and to the next list element.
 *
 *  \author  m.huelse
 *  \date   30.06.2018
 *
 */
template<typename T>
class Element {
public:


	/**
	 *
	 *
	 * \brief Reference to the preceding list element
	 *
	 */
	Element<T> *pre_ = nullptr;

	/**
	 *
	 *
	 * \brief Reference to the next list element
	 */
	Element<T> *post_ = nullptr;

	/**
	 *
	 * The value of the list element.
	 *
	 */
	T value_;
};



/**
 *
 *  \class List
 *  \@param T Type
 *  \brief     A template class definition. The class
 *  contains the start and end element of the list.
 *  It implements a doubly linked list.
 *
 */
template<typename T>
class List {
public:

	/**
	 *
	 * \brief Adds a new list element before the current
	 * start element of the list. The new list element
	 * contains the given value.
	 *
	 * @param value Value of the new list element
	 *
	 *
	 */
	virtual void prepend(T value){
		Element<T> *tmp = new Element<T>;
		tmp->value_ = value;
		tmp->pre_   = nullptr;
		tmp->post_  = nullptr;

		if(isEmpty()){
			ptrStart_ = tmp;
			ptrEnd_   = tmp;
		}

		// neues element zeigt auf start
		// als Nachfolger
		tmp->post_  = ptrStart_;
		// ehemaliger start zeigt auf neues Element
		// als Vorgaenger
		ptrStart_->pre_ = tmp;

		// start zeigt auf neues Element
		ptrStart_ = tmp;
		return;
	}

	/**
	 *
	 * \brief Adds a new list element after the current
	 * end element of the list. The new list element
	 * contains the given value.
	 *
	 * @param value Value of the new list element
	 *
	 */
	virtual void append (T value){
		if(isEmpty()){
			prepend(value);
			return;
		}

		Element<T> *tmp = new Element<T>;
		tmp->value_ = value;
		tmp->pre_   = nullptr;
		tmp->post_  = nullptr;

		// neues element zeigt auf end
		// als vorgänger
		tmp->pre_  = ptrEnd_;
		// ehemaliges ende zeigt auf neues Element
		// als Nachfolger
		ptrEnd_->post_ = tmp;

		// end zeigt auf neues Element
		ptrEnd_ = tmp;
		return;
	}

	/**
	 *
	 * \brief Removes the start element of the list
	 * and returns the value of the element removed.
	 *
	 * @return T value of the list element removed.
	 *
	 * \throws string "list is empty" if list is empty
	 *
	 */
	virtual T removeFirst(){
		if (isEmpty()) {
			throw string("list is empty");
		}

		T tmp = ptrStart_->value_;

		if(ptrStart_ == ptrEnd_){ // nur ein Element in Liste
			delete ptrStart_;
			ptrStart_ = nullptr;
			ptrEnd_   = nullptr;
		}else{ // mehr als ein Element in Liste
			// start zeigt auf ehemaligen Nachfolger
			//  als neuen start
			ptrStart_ = ptrStart_->post_;

			// gebe Speicher des ehemaligen start Element
			// frei
			delete ptrStart_->pre_;
			ptrStart_->pre_ = nullptr;

		}
		return tmp;
	};


	/**
	 *
	 * \brief Removes the end element of the list
	 * and returns the value of the element removed.
	 *
	 * @return T value of the list element removed.
	 *
	 * \throws string "list is empty" if list is empty
	 *
	 */
	virtual T removeLast (){
		if (isEmpty()) {
			throw string("list is empty");
		}

		T tmp = ptrEnd_->value_;

		if(ptrStart_ == ptrEnd_){ // nur ein Element in Liste
			delete ptrStart_;
			ptrStart_ = nullptr;
			ptrEnd_   = nullptr;
		}else{
			// ende zeigt auf ehemaligen Vorgaenger
			//  als neues ende
			ptrEnd_ = ptrEnd_->pre_;

			// gebe Speicher des ehemaligen end Elements
			// frei
			delete ptrEnd_->post_;
			ptrEnd_->post_ = nullptr;
		};
		return tmp;
	};

	/**
	 *
	 * \brief Tests whether or not the list is empty.
	 * It return true if the list is empty otherwise false.
	 *
	 * @return bool  true if list is empty otherwise false.
	 *
	 */
	virtual bool isEmpty(){
		return((ptrStart_ == nullptr) && (ptrEnd_ == nullptr));
	};

	/**
	 *
	 * \brief Prints the content of the list on the
	 * standard output.
	 *
	 * @return void
	 *
	 */
	virtual void print(){
		Element<T> *ptrElem;
		cout << "[";
		ptrElem = ptrStart_;
		while (ptrElem != nullptr) {
			cout << ptrElem->value_;
			ptrElem = ptrElem->post_;
			if (ptrElem != nullptr) {
				cout << ", ";
			}
		}
		cout << "]";
		cout.flush();
	};

protected:

	/**
	 *
	 * \brief Start element of the list.
	 *
	 */
	Element<T> *ptrStart_ = nullptr;

	/**
	 *
	 * \brief End element of the list.
	 *
	 */
	Element<T> *ptrEnd_ = nullptr;
};



/**
 *
 *  \class Queue
 *  \@param T Type
 *  \brief     A template class definition. The class
 *  implements a queue-container.
 *
 */
template<typename T>
class Queue: protected List<T> {
public:

	/**
	 *
	 * \brief Adds a new element to the queue.
	 * The new element has the given value.
	 *
	 * @param value Value of the new queue element.
	 *
	 */
	void enqueue(T value){ List<T>::prepend(value);};

	/**
	 *
	 * \brief Removes one element from the queue.
	 * The value of the removed queue element
	 * is returned.
	 *
	 * @return T value of the queue element removed.
	 *
	 * \throws string "list is empty" if queue is empty
	 *
	 */
	T    dequeue() { return (List<T>::removeLast());};

	/**
	 *
	 * \brief Returns the value of the queue element
	 * to be removed next when calling method dequeue().
	 *
	 * @return T value of the element the be removed
	 * next when calling method dequeue().
	 *
	 * \throws string "list is empty" if queue is empty
	 *
	 */
	T peek(){
		T tmp;
		tmp = List<T>::removeLast();
		append(tmp);
		return tmp;
	};

	/**
	 *
	 * \brief Prints the content of the queue on the
	 * standard output.
	 *
	 * @return void
	 *
	 */
	void print(){List<T>::print();};

	/**
	 *
	 * \brief Tests whether or not the queue is empty.
	 * It return true if the queue is empty otherwise false.
	 *
	 * @return bool  true if queue is empty otherwise false.
	 *
	 */
	bool isEmpty(){return (List<T>::isEmpty());};
};



class ITestItem{
public:
	virtual void   testExecution()              = 0;
	virtual bool   getResult()                  = 0;
	virtual string getName()                    = 0;
	virtual string toXmlStr()                   = 0;
	virtual void   addTestItem(ITestItem *item) = 0;
};


class TestItem : public ITestItem{
public:
	TestItem(string s = string("undefined test item")){name_ = s; result_ = false;};
	virtual string getName(){ return name_;};
	virtual bool   getResult(){return result_;};
	virtual void   addTestItem(ITestItem *item) {throw "TestItem cannot add TestItem\n";};
protected:
	string name_;
	bool   result_ = false;
};


class TestCase : public TestItem{
public:
	TestCase(string s = string("undefined test case")) : TestItem(s){};

	void testExecution(){
		result_ = testRun();
	}

	string toXmlStr(){
		string s("");
		s += "<TestCase name=\"" + getName() + "\">";
		if(result_){
			s += "PASSED";
		}else{
			s += "FAILED";
		};
		s += "</TestCase>";

		return s;
	}
protected:
	virtual bool testRun(){
		return false;
	}

};


class TestSuite : public TestItem{
public:
	TestSuite(string s = string("undefined test suite")) : TestItem(s){

	};

	virtual void testExecution(){
		result_ = true;
		TestItem *ptrTC;
		Queue<TestItem*> tmpTC;
		while(!testItems_.isEmpty()){
			ptrTC = testItems_.dequeue();
			ptrTC->testExecution();
			result_ = result_ && ptrTC->getResult();
			tmpTC.enqueue(ptrTC);
		}

		while(!tmpTC.isEmpty()){
			ptrTC = tmpTC.dequeue();
			testItems_.enqueue(ptrTC);
		}
	};

	virtual string  toXmlStr(){
		string s("");
		s += "<" + this->testType_ + " name=\"" + this->name_   + "\" status=\"";
		if(getResult()){
			s += "PASSED\">";
		}else{
			s += "FAILED\">";
		}

		TestItem *ptrTC;
		Queue<TestItem*> tmpTC;
		while(!testItems_.isEmpty()){
			ptrTC = testItems_.dequeue();
			s += ptrTC->toXmlStr();
			tmpTC.enqueue(ptrTC);
		}

		while(!tmpTC.isEmpty()){
			ptrTC = tmpTC.dequeue();
			testItems_.enqueue(ptrTC);
		}

		s += "</" + testType_ + ">";

		return s;
	}

	virtual void   addTestItem(TestItem *tc) {
		testItems_.enqueue(tc);
	};

protected:
	Queue<TestItem *> testItems_;
	string testType_ = "TestSuite";
};


class UnitTest : public TestSuite{
public:
	UnitTest(string s = "undefined unit test") : TestSuite(s){
		testType_ = "UnitTest";
	};

	void writeResultsToFile(string fileName){
		std::ofstream file(fileName);
		file <<  toXmlStr();
		file.close();
		return;
	}

};

} // end namespace TASK6


#endif /* TASK6_H_ */
