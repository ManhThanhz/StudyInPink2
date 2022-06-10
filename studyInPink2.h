/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2022
* Author: Vu Van Tien
* Date: 15.02.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

class Point {
private:
    int x;
    int y;
public:
    Point(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    };
    string toString() const {
        string x1 = to_string(x);
        string y1 = to_string(y);
        return "<Point[" + x1 + "," + y1 + "]>";
    };

    int distanceTo(const Point& otherPoint) const {
        double d = sqrt((((otherPoint.x) - x) * ((otherPoint.x) - x)) + (((otherPoint.y) - y) * ((otherPoint.y) - y)));
		return (int)ceil(d);
	};
};

class Node {
private:
    Point point;
    Node* next;

    friend class Path;

public:
    Node(const Point& point = Point(), Node* next = NULL) {
		this->point = point;
		this->next = next;
		
	};
    string toString() const {
		string x1 = this->point.toString();
		return "<Node[" + x1 + "]>";
    };
};


class Path {
private:
    Node* head;
    Node* tail;
    int count;
    int length;

public:
    Path() {
		head = NULL;
	    tail = NULL;
		count = 0;
		length = -1;
    };
    ~Path() {
        Node* temp = head;
        while (temp != NULL) {
            Node* temp2 = temp;
            temp = temp->next;
            delete temp2;
        }
    };

    int getCount() {
		return count;
    }

    int getLength() {
		return length;
	}

    void addPoint(int x, int y) {
        Node* temp = new Node;
		temp->point = Point(x, y);
        temp->next = NULL;
        count = count + 1;
        if (count == 1) {
            length = 0;
            head = temp;
            tail = temp;
        }
        else if (count > 1) {
			int distance = tail->point.distanceTo(temp->point);
            length = length + distance;
            tail->next = temp;
            tail = temp;
        }
    };
    string toString() const {
        if (count == 0) {
            string s = "<Path[count:0,length:-1,[]]>";
            return s;
        }
        
        else {
			string s = "<Path[count:" + to_string(count) + ",length:" + to_string(length) + ",[";
			Node* temp = head;
            while (temp != NULL) {
                s = s + temp->toString();
                temp = temp->next;
                if (temp != NULL) {
                    s = s + ",";
                }
            }
            return s + "]]>";
        }
    };
    Point getLastPoint() const {
		return tail->point;
	};
};

class Character {
private:
    string name;
    Path* path;

public:
    Character(const string& name = "") {
        this->name = name;
        path = new Path;
    };
    ~Character() {
        if (path->getCount() >= 1) {
            delete path;
        }
    };

    string getName() const {
        return name;
    };
    void setName(const string& name) {
		this->name = name;
    };

    void moveToPoint(int x, int y) {
		path->addPoint(x, y);
    };
    string toString() const {
		return "<Character[name:" + name + ",path:" + path->toString() + "]>";
    };

    int getPath() const {
        return path->getLength();
    }

    Point getPosition() const {
		return path->getLastPoint();
    }
};

bool rescueSherlock(
    const Character& chMurderer,
    const Character& chWatson,
    int maxLength,
    int maxDistance,
    int& outDistance
) {
    double l1 = ceil(chWatson.getPath());
    double l2 = ceil(chMurderer.getPath());
    if (l1 - l2 <= maxLength) {
        outDistance = chMurderer.getPosition().distanceTo(chWatson.getPosition());
        if (outDistance <= maxDistance) {
            return true;
        }
        else {
            return false;
        }
	}
	else {
        outDistance = -1;
		return false;
    }
    return true;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */
