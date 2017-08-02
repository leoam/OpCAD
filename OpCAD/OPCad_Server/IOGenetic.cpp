/*
 ██████╗ ██████╗  ██████╗ █████╗ ██████╗        ██╗ 
██╔═══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗    ██╗╚██╗
██║   ██║██████╔╝██║     ███████║██║  ██║    ╚═╝ ██║
██║   ██║██╔═══╝ ██║     ██╔══██║██║  ██║    ██╗ ██║
╚██████╔╝██║     ╚██████╗██║  ██║██████╔╝    ╚═╝██╔╝
 ╚═════╝ ╚═╝      ╚═════╝╚═╝  ╚═╝╚═════╝        ╚═╝ 
                                                                                                
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <map>
#include <math.h>

using namespace std;

/*
   ____ _       _           _  __     __         _       _     _           
  / ___| | ___ | |__   __ _| | \ \   / /_ _ _ __(_) __ _| |__ | | ___  ___ 
 | |  _| |/ _ \| '_ \ / _` | |  \ \ / / _` | '__| |/ _` | '_ \| |/ _ \/ __|
 | |_| | | (_) | |_) | (_| | |   \ V / (_| | |  | | (_| | |_) | |  __/\__ \
  \____|_|\___/|_.__/ \__,_|_|    \_/ \__,_|_|  |_|\__,_|_.__/|_|\___||___/
                                                                                                                                                                                                                                                                                                                                                           
*/
/*
This constan represents the number of parameters present on the circuit.
For example, if the circuit contains 2 transistors and each one has L and W, 
it will be 4, it corresponds to L1, W1, L2, W2
*/
int numberOfParameters;

/*
These two variables contains the amount of fitness and it's name
*/
string fitnessName[100];
int numberOfFitness;

/*
numberOfTests is the constant that represent the number of data elements within the circuit.raw file
*/
int numberOfTests;

/*
These two constants contains the names of the netlist (circuit.spi) and the result file (circuit.raw)
*/
char const* netlistName = "circuit.spi";
char const* resultfileName = "circuit.raw";

/*
Definition of parameters {L1, W1, L2, W2}, for example
*/
double parameters[100]   =    {8e-6}; 
std::string parametersTemp[10000];

/*
Definition of the fitness array. It contains all the fitness elements of the circuit.
For example: Gain, Power Consumption, etc.
*/
double fitness[100]; 

/*
Definition of the arrays that will store the data comming directly from .raw file
*/
double Vin[100000];//Vin
double Vout[100000];//Vout
double currentVDD[100000]; //Current in the main power source
double currentVin[100000]; //Current in the variable in power source
double VDD[100000]; //VDD, main power source

/*
Arrays that will store fitness calculations
*/
double Gain[100000];//Gain
double powerConsumption[100000];//Power Comsumption


/*
  _____                 _   _                   _           _                 _   _                 
 |  ___|   _ _ __   ___| |_(_) ___  _ __     __| | ___  ___| | __ _ _ __ __ _| |_(_) ___  _ __  ___ 
 | |_ | | | | '_ \ / __| __| |/ _ \| '_ \   / _` |/ _ \/ __| |/ _` | '__/ _` | __| |/ _ \| '_ \/ __|
 |  _|| |_| | | | | (__| |_| | (_) | | | | | (_| |  __/ (__| | (_| | | | (_| | |_| | (_) | | | \__ \
 |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|  \__,_|\___|\___|_|\__,_|_|  \__,_|\__|_|\___/|_| |_|___/
                                                                                                                                                                                                           
*/

int system (const char *string);



/*
     _                _____                 _   _                 
    / \  _   ___  __ |  ___|   _ _ __   ___| |_(_) ___  _ __  ___ 
   / _ \| | | \ \/ / | |_ | | | | '_ \ / __| __| |/ _ \| '_ \/ __|
  / ___ \ |_| |>  <  |  _|| |_| | | | | (__| |_| | (_) | | | \__ \
 /_/   \_\__,_/_/\_\ |_|   \__,_|_| |_|\___|\__|_|\___/|_| |_|___/
                                                                  
*/

/*
executionParameters.txt contains the relevant data needed for the execution.
For example, the name and the number of the parameters.
This function reads this information and saves it in variables
*/
void prepareExecutionParameters(){

    int contFitness = 0;
    std::ifstream input( "../executionParameters.txt" );

    //Browse the complete file
    for( std::string line; getline( input, line ); ){

      //Verify that the line is'n a comment or a blank line
      if(line.substr(0,1).compare("") != 0 && line.substr(0,1).compare("#") != 0){
        //std::cout << "Line " << line << std::endl;
        //Get the number of parameters
        if(line.compare("Number of parameters:") == 0){
          getline( input, line );
          numberOfParameters = atoi(line.c_str());
        }

        //Get the number of fitness
        if(line.compare("Number of fitness:") == 0){
          getline( input, line );
          numberOfFitness = atoi(line.c_str());
        }

        //Get the number of tests
        if(line.compare("Number of tests:") == 0){
          getline( input, line );
          numberOfTests = atoi(line.c_str());
          numberOfTests--;
        }

        //Get the fitness
        if(line.compare("Fitness:") == 0)
          while(contFitness < numberOfFitness){
              getline( input, line );
              fitnessName[contFitness] = line;
              contFitness++;
          }

      }
    }


    //To print the fitness given by the file
    for (int i = 0; i < numberOfFitness; i++)
    {
      std::cout << "Fitness: " << fitnessName[i] << std::endl;
    }

    std::cout << "Number of parameters: " << numberOfParameters << std::endl;
    std::cout << "Number of fitness: " << numberOfFitness << std::endl;
    std::cout << "Number of tests: " << numberOfTests << std::endl;

 
}

/*
This function is in charge of convert from exponential to engineering notation.
For example, 1e-6 m -> 1 um
*/
void expToEng(){
	string exponent;
	string line;
	int position;

	for (int i = 0; i < numberOfParameters; i++)
	{
		line = parametersTemp[i];
		position = line.find("e");

		if (position != std::string::npos){
			exponent = line.substr(position);

			if(exponent == "e+0")
				exponent = "";
			else if(exponent == "e-3")
				exponent = "M";
			else if(exponent == "e-6")
				exponent = "U";
			else if(exponent == "e-9")
				exponent = "N";
			else if(exponent == "e-12")
				exponent = "P";
			else if(exponent == "e-15")
				exponent = "F";
			else if(exponent == "e-18")
				exponent = "A";
			else if(exponent == "e-21")
				exponent = "Z";
			else if(exponent == "e-24")
				exponent = "Y";
			else{
				cout << "Problems converting the exponents. The default exponent is U (e-6)" << endl;
				cout << "Line: " << line << endl;
				exponent = "U";
			}

			line = line.substr(0, position) + exponent;
			parametersTemp[i] = line;
	}
	}
}

/*
Auxiliar function that receive an string and store the relevant information in a temporal vector
*/
void writeOnParameters(std::string data){
	//std::cout << "It was received in Write On Parameters: " << data << std::endl;
	int dataSize = data.length();
	string parameter;
	string delimiter = " ";
	int position;

	for (int i = 0; i < numberOfParameters; ++i)
	{
		//Make a split to the input line using the blank space as delimiter
		position = data.find(delimiter);
		parameter = data.substr(0, position);
		parametersTemp[i]=parameter.substr(parameter.find("=") + 1, parameter.length());
		data = data.substr(position + 1, dataSize);
	}

	//Convert from exp to eng notation
	expToEng();
}


/*
This function is in charge of receive the information from the client (genetic algorithm) and write it down
in the corresponding places in the netlist file (circuit.spi). The string that could come from the server would have
the following form:

					"L=3.68431e-6 W=4.82157e-6 L=7.38039e-6 W=13.4078e-6"

and have to be written in the right place of the netlist file:

					Mnmos@0 out in gnd gnd NMOS L=3.68431U W=4.82157U
					Mpmos@0 out in vdd vdd PMOS L=7.38039U W=13.4078U

It is what this function does!
*/
void writeparameters (std::string data){
	//std::cout << "Data: " << data << std::endl;
	writeOnParameters(data);
	int delimiterPosition, delimiterPositionOld = 0, spacePosition, lineSize;
	int parametersCont = 0;
	int cont = 0;

	std::ifstream input(netlistName);//Open the original file
	std::ofstream outfile ("temp.spi");//Create a temporal file

	for( std::string line; getline( input, line ); )
	{
		cont++;
    	delimiterPosition = line.find("=");
		if(delimiterPosition != std::string::npos){
			lineSize = line.length();
			do{
				if(delimiterPosition < lineSize){ 
					spacePosition = line.find(" ", delimiterPosition);//Looks for the second blank space in the second part of the line
					if(spacePosition != -1) 
						line = line.substr(0, delimiterPosition + 1) + parametersTemp[parametersCont] + line.substr(spacePosition);
					else
						line = line.substr(0, delimiterPosition + 1) + parametersTemp[parametersCont];
					lineSize = line.length();
					parametersCont++;					
					delimiterPosition = line.find("=", delimiterPosition + 1);
				}else
					break;
			} while (delimiterPosition != std::string::npos);
		
		}

		outfile << line << std::endl;//Write down in the temporal file

	}

	remove(netlistName);//Delete the original netlist file
	rename("temp.spi",netlistName);//Rename the temporal with the original name. Now it is the new original.
	outfile.close();
	input.close();
}


/*
Function that converts Spice string to double
*/
double conv_double(string temp){
	int length=temp.length(); //Get the length of the string
	double out=0;
	string prefix=temp.substr(length-1,1).c_str(); //Get the value's prefix: M, U ,N, P, etc.
	
	//Most common prefixes
	//First, it's converted the numeric part of the string; after it, it is multiplied by the corresponding exponent
	if(prefix=="F")	
		out=atof(temp.substr(0,length-1).c_str())*1e-15;
	else if(prefix=="P")	
		out=atof(temp.substr(0,length-1).c_str())*1e-12;
	else if(prefix=="N")	
		out=atof(temp.substr(0,length-1).c_str())*1e-9;
	else if(prefix=="U")	
		out=atof(temp.substr(0,length-1).c_str())*1e-6;
	else if(prefix=="M")	
		out=atof(temp.substr(0,length-1).c_str())*1e-3;
	else out=atof(temp.c_str());
return out;
}


/*
Function in charge of read the data from the output file and store it in the parameters array
*/
void readparameters (string busqueda){
	string temp;
	string leer;
	int cont=0;
	int countsamples = 0;
	// Define the file to read with the results, read only.
	fstream OutFile (resultfileName, ios::in ); 
  	bool control=true;

 	while (control){
  		OutFile >> leer;
  		
  		if (leer == busqueda) { 
 	 		control=false;
	 		while (countsamples <= numberOfTests){ 
	 			/*
	 			The order is as follows:
				Number of samples 							TRASH
				0	vdcvoltag@0	voltage						VIN
				1	V(net@94)	voltage						TRASH
				2	V(net@0)	voltage						TRASH
				3	V(vdd)		voltage						VDD
				4	V(ib2)		voltage						TRASH
				5	V(v+)		voltage						TRASH
				6	V(ib1)		voltage						TRASH
				7	V(v-)		voltage						TRASH
				8	V(net@3)	voltage						TRASH
				9	V(net@81)	voltage						TRASH
				10	V(out)		voltage						VOUT
					...
				72	I(Vdd)		device_current				Ivdd
				73	I(Vdcvoltag@0)	device_current			Ivin
	 			*/
	 			OutFile >> temp; //trash
	 			OutFile >> temp; //VIN
				Vin[countsamples]=conv_double(temp);
	 			OutFile >> temp; //trash
	 			OutFile >> temp; //trash
				OutFile >> temp; //VDD
				VDD[countsamples]=conv_double(temp);
				OutFile >> temp; //trash
				OutFile >> temp; //trash
				OutFile >> temp; //trash
				OutFile >> temp; //trash
				OutFile >> temp; //trash
				OutFile >> temp; //trash
				OutFile >> temp; //VOUT
				Vout[countsamples]=conv_double(temp); //convert to double

				for (int i = 0; i < 61; i++)
				{
					OutFile >> temp; //trash
				}
				
				OutFile >> temp; //IVdd
				currentVDD[countsamples]=conv_double(temp);
				OutFile >> temp; //IVin
				currentVin[countsamples]=conv_double(temp);

				/*
				cout <<countsamples<<" Vout: "<<Vout[countsamples] << " Vin: " << Vin[countsamples] 
				<< " VDD: " << VDD[countsamples] << " Ivin: " << currentVin[countsamples] 
				<< " IVDD: " << currentVDD[countsamples] << endl; //para visualizar
				*/

       			countsamples++;
       			}

       		
      		} 		 
        
   	}

	OutFile.close();
}

/*
Function that finds the minimum element within the array
*/
int findmin (double qarray[], int size){
	int min = 0;
	double minvalue = qarray[0];

	for (int i=0; i < size; i++){
 		if (qarray[i] < minvalue) {
 			min = i;
			minvalue = qarray[i];
		}
		
	}

	//cout << "Element min: " << min << " min: " << qarray[min] << endl;
	return  min;
}


/*
Function that finds the minimum element within the array
*/
int findmax (double qarray[], int size){
	int max = 0;
	double maxvalue = qarray[0];

	for (int i=0; i <= size; i++){
		//cout<< "elemento " << qarray[i] << endl;
	 	if (qarray[i] > maxvalue) {
	 		max = i;
			maxvalue = qarray[i];
		}
	}
	
	//cout <<"Element max: " << max << " max: " << qarray[max] << endl;
	return  max;
}


/*
  ______ _ _                       _        __                  _   _                 
 |  ____(_) |                     ( )      / _|                | | (_)                
 | |__   _| |_ _ __   ___  ___ ___|/ ___  | |_ _   _ _ __   ___| |_ _  ___  _ __  ___ 
 |  __| | | __| '_ \ / _ \/ __/ __| / __| |  _| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
 | |    | | |_| | | |  __/\__ \__ \ \__ \ | | | |_| | | | | (__| |_| | (_) | | | \__ \
 |_|    |_|\__|_| |_|\___||___/___/ |___/ |_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/                                                                                    
*/                                                                               

/*
Is calculated the gain for all the Vout and Vin
*/
void Gain_curve(){
	for(int i=0; i<numberOfTests;i++){
		if(Vin[i] == 0)
			Gain [i] = -1;//To avoid an indefinition in the division
		else
			Gain[i]=Vout[i]/Vin[i];

		//cout << Gain[i] << endl;
	}
}


/*
Is calculated the total power consumed by the circuit
*/
void totalPowerConsumption(){
	//Total Power Consumption = VDD * Ivdd + Vin * Ivin
	for(int i=0; i < numberOfTests; i++){
		powerConsumption[i] = VDD[i]*currentVDD[i] + Vin[i]*currentVin[i];

		if(powerConsumption[i] < 0)
			powerConsumption[i] = powerConsumption[i] * -1;
		if(powerConsumption[i] == 0) //If the power is equal to zero (wich doesn't make sense), it's placed in a high value
			powerConsumption[i] = 1000000;
	}
}


/*
Function in charge of call the others functions and save the fitness values.
IMPORTANT!
	If you want to maximize a fitness value, place it in a normal asignation. For example:
		fitness[0] = Gain[posmax];
	But, if you want to minimize the value, place it in the inverse form:
		fitness[0] = 1/powerConsumption[posmin];
*/
void FitGen (){

	int posmax = 0;
	int posmin = 0;
	Gain_curve (); //Gets the gain graph
	totalPowerConsumption();//It fills the power consumption array

	posmin = findmin(powerConsumption, numberOfTests); //Find the maximun value of the power consumption
	fitness[0] = 1/powerConsumption[posmin]; 

	posmax = findmax(Gain, numberOfTests); //Find the maximun value of the gain
	fitness[1] = Gain[posmax];
}




/*
  __  __       _          __                  _   _             
 |  \/  |     (_)        / _|                | | (_)            
 | \  / | __ _ _ _ __   | |_ _   _ _ __   ___| |_ _  ___  _ __  
 | |\/| |/ _` | | '_ \  |  _| | | | '_ \ / __| __| |/ _ \| '_ \ 
 | |  | | (_| | | | | | | | | |_| | | | | (__| |_| | (_) | | | |
 |_|  |_|\__,_|_|_| |_| |_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|
                                                                                                         
*/

 int main () {

   std::cout << "running IOGenetic...\n";
   prepareExecutionParameters();

     try
         {
	       // Create the socket
	       ServerSocket server (8080);
	       std::cout << "Server started\n" << std::endl;
	       
	       while ( true ){

		       ServerSocket new_sock;
		       server.accept ( new_sock );
		       
		       try
		       {

			       while ( true )
			       {
				       std::string data;
				       new_sock >> data;
				       cout << "We received this data from the client: " << data << endl;
				    
				       writeparameters(data);
				       int comma = system("sh start"); //Executes the simulation
				       
				       if (comma<0)
				       	cout <<  "error !!!!" << endl;
				       
				       readparameters("Values:");
				       FitGen ();

				       ostringstream sstr;

				       //Prepara the string to be sent
				       for (int i = 0; i < numberOfFitness; i++)
				       {
				       	sstr << fitnessName[i] << "= " << fitness[i] << " ";
				       }

				       string circuitfitness;
				       circuitfitness = sstr.str();
				       //socket sending
				       new_sock << circuitfitness;
			       }


			       }
			       catch ( SocketException& ) { }
		       
	      }
	       }
	       catch ( SocketException& e ){
	       std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}
	


	//writeparameters("L=1.1e-6 W=2.2e-6 L=3.3e-6 W=4.4e-6 L=5.5e-6 W=6.6e-6 L=7.7e-6 W=8.8e-6 L=9.9e-6 W=10.10e-6 L=11.11e-6 W=12.12e-6 L=13.13e-6 W=14.14e-6 L=15.15e-6 W=16.16e-6 L=17.17e-6 W=18.18e-6 L=19.19e-6 W=20.20e-6 L=21.21e-6 W=22-22e-6 L=23.23e-6 W=24.24e-6 L=25.25e-6 W=26.26e-6 L=27.27e-6 W=28.28e-6"); //llama la funcion para escribir los parametros en el netlist luego de la palabra parameters.
	//readparameters("Values:");
	

/*
	//writeparameters("L=1.68431e+0 W=2.82157e-9 L=3.38039e-12 W=4.4078e-3"); //llama la funcion para escribir los parametros en el netlist luego de la palabra parameters.
	readparameters("Values:");     //llama la funcion para leer los resultados de la simulacion
	FitGen ();
	//cout << "El mejor valor de fitness es Gain: " << fitness[0];
*/

	return 0;
	       
}
