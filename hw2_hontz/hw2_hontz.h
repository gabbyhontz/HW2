// hw2_hontz.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <random>
#include <vector>
using namespace std;

//question 2 //question 3
//class named plane with the following class members
class Plane {

protected:
	//double variable named wait time
	double wait_time;

private:
	//double variables pos, vel, distance, and loiter_time
	double pos, vel, distance, loiter_time;
	bool at_SCE; //boolean variable at_SCE
	string origin, destination; //string variables origin and destination
	map<string, map<string, int>> flight_distance; //container from Q1

public:
	//constructor that takes in two strings from and to as input
	Plane(const string& from, const string& to);

	//virtual deconstructor left empty
	virtual ~Plane();

	//function named operate with double variables dt as an input and return nothing
	void operate(double dt);

	//get function for pos 
	double get_pos() const;

	//get functions for vel 
	double get_vel() const;

	//get functions for loiter_time
	double get_loiter_time() const;

	//get function for origin
	string get_origin() const;

	//get function for destination
	string get_destination() const;

	//get functionfor at_SCE
	bool get_at_SCE() const;

	//set functions for vel
	void set_vel(double vel2);

	//set functions for loiter_time
	void set_loiter_time(double loiter_time2);

	//a function names distance_to_SCE that return double
	//returns difference between distance and pos if and only if destination is a string SCE
	double distance_to_SCE();

	//a virtual function named time_on_ground
	virtual double time_on_ground();

	//a virtual function named plane_type that returns string
	//return string GA
	virtual string plane_type();

	//a static function named draw_from_normal_dist that take two double variables and returns back a random number from a normal distriution
	//includes <random> header file
	static double draw_from_normal_dist(double mean, double std_dev);

};

class Airliner : public Plane {

private:
	string Airline;

public:

	//constructor takes in airline, from, and to; stores input sirline in airline; and passes from anf to to plane class
	Airliner(const string& Airline, const string& from, const string& to);

	//empty deconstructor
	virtual ~Airliner();

	//overridden function plane type that returns airline
	virtual string plane_type() override;

	//overridden function that returns wait time which is drawn from draw from normal distfunction using a 
	//mean and stdv of 1800 and 600
	virtual double time_on_ground() override;

};

class GeneralAviation : public Plane {
public:
	//constructor that takes in from and to and passes inputs to class plane
	GeneralAviation(const string& from, const string& to);

	//empty deconstructor 
	~GeneralAviation();

	//overridden function time on ground that returns wait time drawn from draw from normal dist function using
	//mean and stdv of 600 and 60
	virtual double time_on_ground() override;
};

//question 6
class ATC {
private:
	//container named registered_planes to store plane objects from question 5
	vector<Plane*> registered_planes;

	//initialize positive integers
	const int MAX_LANDED_PLANE_NUM = 2;
	const int AIRSPACE_DISTANCE = 5;

public:
	////////////////////////////////////////////////////////////////////////idk if this is right
	//return container values
	vector <Plane*>& get_registered_planes() {
		return registered_planes;
	};

	//constructor that is empty
	ATC();

	//empty deconstructor
	~ATC();

	//function register_plane takes in an airplane object to store in container
	void register_plane(Plane& plane);
	
	//function called control_traffic contains the flow chart
	void control_traffic();
};

// TODO: Reference additional headers your program requires here.