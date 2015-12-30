/*
 * resistor.cpp
 *
 *  Created on: Dec 12, 2015
 *      Author: mperaltm
 */

#include <iostream>
#include <string.h>
#include <map>

using namespace std;


class Resistor
{

private:
	const char * color1;
	const char * color2;
	const char * color3;
	const char * color4;
     int  resistance;
     enum colorValue {black,brown,red,orange,yellow,green,blue,lavender,grey,white};
     map <const char *,colorValue> resistor_codes;
     map <const char *,float> mult_codes;
     static int numofResistors;

public:

   #define HUNDREDTH_OAO         0.01
   #define TENTH_OAO             0.1
   #define ONE_OHM               1.0
   #define TEN_OHMS              10.0
   #define ONE_HUNDRED_OHMS      100.0
   #define ONE_THOUSAND_OHMS     1000.0
   #define TEN_THOUSAND_OHMS     10000.0
   #define HUNDRED_THOUSAND_OHMS 100000.0
   #define ONE_MILLION_OHMS      1000000.0
   #define TEN_MILLION_OHMS      10000000.0

	void get_colors(void){

		cout << "Resistor has these color bands:" << endl;

		cout << color1 << " " \
			 << color2 << " " \
			 << color3 << " " \
			 << color4 << " " \
			 << endl;

	}
	int set_colors(const char * colr1, const char *colr2, const char *colr3, const char *colr4){

		short int check,check1,check2,check3,check4;

		check1 = (strcmp(colr1,"black"))?1:resistor_codes[colr2];
		check2 = (strcmp(colr2,"black"))?1:resistor_codes[colr2];
		check3 = (strcmp(colr3,"black"))?1:resistor_codes[colr3];
		check4 = mult_codes[colr4];

        cout << "check1 = " << check1 << "check2 = "<< check2 << "check3 = " << check3 << "check4 = " << check4 << endl;

		check = check1&&check2&&check3&&check4;

		if (check){

		mult_codes["silver"]   =    HUNDREDTH_OAO;
		mult_codes["gold"]     =    TENTH_OAO;
		mult_codes["black"]    =    ONE_OHM;
		mult_codes["brown"]    =    TEN_OHMS;
		mult_codes["red"]      =    ONE_HUNDRED_OHMS;
		mult_codes["orange"]   =    ONE_THOUSAND_OHMS;
		mult_codes["yellow"]   =    TEN_THOUSAND_OHMS;
		mult_codes["green"]    =    HUNDRED_THOUSAND_OHMS;
		mult_codes["blue"]     =    ONE_MILLION_OHMS;
		mult_codes["lavender"] =    TEN_MILLION_OHMS;

		resistor_codes["black"]    = colorValue(black);
		resistor_codes["brown"]    = colorValue(brown);
		resistor_codes["red"]      = colorValue(red);
		resistor_codes["orange"]   = colorValue(orange);
		resistor_codes["yellow"]   = colorValue(yellow);
		resistor_codes["green"]    = colorValue(green);
		resistor_codes["blue"]     = colorValue(blue);
		resistor_codes["lavender"] = colorValue(lavender);
		resistor_codes["grey"]     = colorValue(grey);
		resistor_codes["white"]    = colorValue(white);

		color1 = colr1;
		color2 = colr2;
		color3 = colr3;
		color4 = colr4;

        resistance = resistor_codes[color1]*100 + resistor_codes[color2]*10 + resistor_codes[color3];

        resistance = mult_codes[color4]*resistance;
        cout << "resistance is " << resistance << " ohms." << endl<<endl;
        return 1;
		}
        cout << "invalid color combination. One of your four colors is invalid."<< endl;
        this->~Resistor();
        return check;
	}

	int get_resistance(void){

        return resistance;
	}

	void setAll();

	Resistor();
	Resistor(const char * ,const char * ,const char * ,const char * );
	~Resistor();
	static int getnumofResistors(void){return numofResistors;}

};

// Declaration and initialiation of class variable done outside of class definition.
int Resistor::numofResistors = 0;

// Declaration of constructor with no input arguments.
Resistor::Resistor(){
	set_colors("black","black","black","black");
	Resistor::numofResistors++;
}
void Resistor::setAll()
{
    // Default is a 100 ohm resistor.
	this->color1 = "brown";
    this->color2 = "black";
    this->color3 = "black";
    this->color4 =  "black";

    Resistor::numofResistors++;
}

// Declaration of constructor with input arguments.
Resistor::Resistor(const char * colr1,const char *  colr2,const char *  colr3,const char *  colr4){

	int check=0;

	check = set_colors(colr1, colr2, colr3, colr4);
	Resistor::numofResistors++;

	if (!check) {cout << "invalid color combination."<< endl;
	this->~Resistor();}

};

// Declaration of destructor with output message.
Resistor::~Resistor(){

	cout << endl << "resistor " << numofResistors << " has been deleted" << endl;
	numofResistors--;

}

//New class with Resistor inheritance.
class Series_Resistors : public  Resistor {

private:
	int resistor_sum;
	static int numofSeriesresistors;
public:
	int sum_resistors();
	int sum_resistors(Resistor& a1, Resistor& a2){

		resistor_sum = a1.get_resistance() + a2.get_resistance();

		return resistor_sum;
	}
	static int getnumSeries(void){
		cout << "there are "<< numofSeriesresistors;
		return numofSeriesresistors;
	};
 // Prototypes of constructors and destructors and static int class variables
 Series_Resistors();
 Series_Resistors(Resistor&,Resistor&);
 ~Series_Resistors();
};

 Series_Resistors::~Series_Resistors(){
	cout << endl << numofSeriesresistors << " series resistor destroyed." << endl;
}

 Series_Resistors::Series_Resistors(Resistor& a1,Resistor& a2){
     resistor_sum = 0;
	 numofSeriesresistors++;
	 sum_resistors(a1, a2);
	 cout << numofSeriesresistors << " series resistors created." << endl;
}

 Series_Resistors::Series_Resistors(){
     resistor_sum = 0;
	 numofSeriesresistors++;
	cout << numofSeriesresistors << " series resistors created." << endl;
}

 // Parallel resistors
class Parallel_Resistors : public Resistor{
private:
	int parallel_resistor ;
	static int numofParallelresistors;
public:
	int parallel_resistors(Resistor& a1, Resistor& a2){

		parallel_resistor = a1.get_resistance() * a2.get_resistance();
        parallel_resistor = parallel_resistor/(a1.get_resistance()+a2.get_resistance());
		return parallel_resistor;
	}

	static int getnumParallel(void){
		cout << "there are "<< numofParallelresistors;
		return numofParallelresistors;
	};
 // Prototypes of constructors and destructors and static int class variables
 Parallel_Resistors();
 Parallel_Resistors(Resistor&,Resistor&);
 ~Parallel_Resistors();
};
Parallel_Resistors::~Parallel_Resistors(){
	cout << endl << numofParallelresistors << " Parallel resistors destroyed." << endl;
}

Parallel_Resistors::Parallel_Resistors(Resistor& a1,Resistor& a2){
	parallel_resistor = 0;
	 numofParallelresistors++;
	 parallel_resistor = parallel_resistors(a1,a2);
	 cout << numofParallelresistors << " Parallel resistors created." << endl;
}

Parallel_Resistors::Parallel_Resistors(){
	parallel_resistor = 0;
	 numofParallelresistors++;
	cout << numofParallelresistors << " Parallel resistors created." << endl;
}

int Parallel_Resistors::numofParallelresistors = 0;
int Series_Resistors::numofSeriesresistors = 0;


int main()
{

	Resistor Hundred_Ohms ("brown","black","black","brown");
	Resistor Thousand_Ohms("brown","black","black","brown");

    Resistor r1("brown","black","black","black"),r2("brown","black","black","brown"),\
    		 r3("brown","black","black","black"),r4("brown","black","black","brown");

    Parallel_Resistors parallel;

    Series_Resistors series;

	cout << "number of resistors is " << series.getnumofResistors() << endl<<endl;
	cout << "resistor r1 and r2 in series is " << series.sum_resistors(r1,r2) << endl<<endl;
	cout << "resistor r1 and r2 in parallel is " << parallel.parallel_resistors(r3,r4) << endl<<endl;


    cout << "program terminated." << endl;
}
