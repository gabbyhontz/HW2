// hw2_hontz.cpp : Defines the entry point for the application.
//

#include "hw2_hontz.h"
//#include "HW2_Visualizer (1).h"

using namespace std;

//question 2 //question 3
//class named plane with the following class members

//constructor that takes in two strings from and to as input
Plane::Plane(const string& from, const string& to) {
	origin = from; //input string from in origin variable
	destination = to; //input string to in destination variable

	//distance equal to origin and destination airports
	flight_distance["SCE"]["PHL"] = 160;
	flight_distance["SCE"]["ORD"] = 640;
	flight_distance["SCE"]["EWR"] = 220;
	distance = flight_distance[origin][destination];

	//initialize the values of variables to zero
	pos = 0;
	vel = 0;
	wait_time = 0;
	loiter_time = 0;
	at_SCE = 0;

}

//virtual deconstructor left empty
Plane::~Plane() {}

//function named operate with double variables dt as an input and return nothing
void Plane::operate(double dt) {
	if (loiter_time != 0) {
		loiter_time -= dt;
	}
	else if (wait_time != 0) {
		wait_time -= dt;
	}
	else if (pos < distance) {
		pos += vel * dt;
		at_SCE = 0;
	}
	else if (destination == "SCE") {
		at_SCE = 1;
		time_on_ground();

		//swap the value of destination and origin
		string swap;
		swap = origin;
		origin = destination;
		destination = swap;

		pos = 0.0;
	}
	else {
		time_on_ground();

		//swap the value of destination and origin
		string swap;
		swap = origin;
		origin = destination;
		destination = swap;

		pos = 0.0;
	}
}

//get function for pos 
double Plane::get_pos() const {
	return pos;
}

//get functions for vel 
double Plane::get_vel() const {
	return vel;
}

//get functions for loiter_time
double Plane::get_loiter_time() const {
	return loiter_time;
}

//get function for origin
string Plane::get_origin() const {
	return origin;
}

//get function for destination
string Plane::get_destination() const {
	return destination;
}

//get functionfor at_SCE
bool Plane::get_at_SCE() const {
	return at_SCE;
}

//set functions for vel
void Plane::set_vel(double vel2) {
	vel = vel2;
}

//set functions for loiter_time
void Plane::set_loiter_time(double loiter_time2) {
	loiter_time = loiter_time2;
}

//a function names distance_to_SCE that return double
//returns difference between distance and pos if and only if destination is a string SCE
double Plane::distance_to_SCE() {
	if (destination == "SCE") {
		return distance - pos;
	}
	else {
		return 0.0;
	}
}

//a virtual function named time_on_ground
double Plane::time_on_ground() {

	return 0.0;
}

//a virtual function named plane_type that returns string
//return string GA
string Plane::plane_type() {
	return "GA";
}

//a static function named draw_from_normal_dist that take two double variables and returns back a random number from a normal distriution
//includes <random> header file
double Plane::draw_from_normal_dist(double mean, double std_dev) {
	random_device rd{};
	mt19937 gen{ rd() };
	normal_distribution<> d{ mean, std_dev };
	return d(gen);
}

//airliner class //question 4

//constructor takes in airline, from, and to; stores input sirline in airline; and passes from anf to to plane class
Airliner::Airliner(const string& Airline, const string& from, const string& to) :Plane(from, to), Airline(Airline) {}

//empty deconstructor
Airliner::~Airliner() {};

//overridden function plane type that returns airline
string Airliner::plane_type() {
	return Airline;
}

//overridden function that returns wait time which is drawn from draw from normal distfunction using a 
//mean and stdv of 1800 and 600
double Airliner::time_on_ground() {
	return draw_from_normal_dist(1800, 600);
}

//general aviation class //question 4

	//constructor that takes in from and to and passes inputs to class plane
GeneralAviation::GeneralAviation(const string& from, const string& to) :Plane(from, to) {}

//empty deconstructor 
GeneralAviation::~GeneralAviation() {};

//overridden function time on ground that returns wait time drawn from draw from normal dist function using
//mean and stdv of 600 and 60
double GeneralAviation::time_on_ground() {
	return draw_from_normal_dist(600, 60);
}

//question 6
//empty constructor
ATC::ATC() {};

//empty deconstructor
ATC::~ATC() {};

//function register_plane takes in an airplane object to store in container
void ATC::register_plane(Plane& plane) {
	registered_planes.push_back(&plane);
}

//idk if this is correct
//function call for control_traffic
void ATC::control_traffic() {
	int landed_planes = 0; //initialize landed_planes
	int i = 0; //initialize i

	//for loop to determine that if i is less than registered planes the the following will be set
	for (Plane* a_plane : registered_planes) {
			landed_planes += a_plane->get_at_SCE();
			i++;

			//if statement to determine if landed planes is greater than or equal to the following will be set
			if (landed_planes >= MAX_LANDED_PLANE_NUM) {
				i = 0; //set i equal to zero

				//for loop to determine if i is less than registered planes then the if stetment will be set
				for (Plane* b_plane : registered_planes) {

					//if statement to set the loiter time and i++ values under specific conditions 
					if (b_plane->get_at_SCE() == 0 && b_plane->distance_to_SCE() <= ATC::AIRSPACE_DISTANCE && b_plane->get_loiter_time() == 0) {
						b_plane->set_loiter_time(100);
						i++;
					}
				}
			}
	}
}

int main()
{
	//define container //question 1
	multimap<string, pair<string, int>> flight_distance; //container from Q1' 
	flight_distance.insert(make_pair("SCE", make_pair("PHL", 160)));
	flight_distance.insert(make_pair("SCE", make_pair("ORD", 640)));
	flight_distance.insert(make_pair("SCE", make_pair("EWR", 220)));

	//question 5
	//seven objects representing aircraft in the table
	//velocities in table are in miles per hour //multipled to be miles per second
	Airliner American1("AA", "SCE", "PHL");
	American1.set_vel(470 * 0.00027778);

	Airliner United1("UU", "SCE", "ORD");
	United1.set_vel(515 * 0.00027778);

	Airliner United2("UU", "SCE", "EWR");
	United2.set_vel(480 * 0.00027778);

	Airliner American2("AA", "SCE", "ORD");
	American2.set_vel(500 * 0.00027778);

	GeneralAviation General1("SCE", "PHL");
	General1.set_vel(140 * 0.00027778);

	GeneralAviation General2("SCE", "EWR");
	General2.set_vel(160 * 0.00027778);

	GeneralAviation General3("SCE", "ORD");
	General3.set_vel(180 * 0.00027778);

	//question 7
	//creating a vector to store all of the airline data in
	//create atc from class ATC
	ATC atc;
	atc.register_plane(American1);
	atc.register_plane(United1);
	atc.register_plane(United2);
	atc.register_plane(American2);
	atc.register_plane(General1);
	atc.register_plane(General2);
	atc.register_plane(General3);

	//question 8
	//HW2_VIZ viz; // instantiate an object name dviz from a class HW2_VIZ

	double timestep = 52.0; //time step between [10,100] //s

	//idk not working 
	//create while (true) statement and call operate
	while (true) {
		
		for (Plane* c_plane : atc.registered_planes) {
			c_plane->operate(timestep); //call operate with time step input
			atc.control_traffic();

			//print out the position of all airplanes at each timestep
			cout << "From: " << c_plane->get_origin() << " To: " << c_plane->get_destination() << " Plane Type: " << c_plane->plane_type() << endl;
			cout << "Position: " << c_plane->get_pos() << " miles" << endl;
			cout << endl;

			//inputs plane type, origin, destination, and position, after the operate and control_traffic functions
			//idk doesn't work
			//viz.visualize_plane(c_plane->plane_type(), c_plane->get_origin(), c_plane->get_destination(), c_plane->get_pos());

			//call update with timestep as a an input
			//read source code HW2_Visualizer.cpp
			//viz.update(timestep);

		}
		//return 0;
	}

	return 0;
}
