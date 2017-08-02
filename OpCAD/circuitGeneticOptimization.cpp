/*
 * Copyright (C) 1998-2004
 * Lehrstuhl fuer Technische Informatik, RWTH-Aachen, Germany
 * 
 * This file is part of the LTI-Computer Vision Library (LTI-Lib)
 *
 * The LTI-Lib is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License (LGPL)
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * The LTI-Lib is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public 
 * License along with the LTI-Lib; see the file LICENSE.  If
 * not, write to the Free Software Foundation, Inc., 59 Temple Place -
 * Suite 330, Boston, MA 02111-1307, USA.  
 */ 

#include "ltiObject.h"
#include "ltiGeneticsTester.h"
#include "ltiParetoFront.h"
#include "ltiStreamProgressInfo.h"

#include <iostream>
#include <fstream>
#include <getopt.h>
#include <cstdlib>

namespace lti {

  /**
   * The real class
   */
  class example {
  public:
    void operator()(int argc,char *argv[]);
    void usage(char* argv[]);
  };

  
  void example::usage(char* argv[]) {
    std::cout << "Usage: " << argv[0] << " [options] \n\n";
    std::cout << "Options:\n";
    std::cout << "-f | --force        Forces optimization from scratch\n";
    std::cout << "-r | --resume       Resumes previous optimization\n";
    std::cout << "-h | --help         Print this message\n";
    std::cout << "-c | --config file  Use given configuration file";
    std::cout << std::endl;
  }

  // use getopt for fast parsing of command line arguments
  static const char shortOptions [] = "c:hrf";
  
  static const struct option
  longOptions [] = {
    { "config",     required_argument,      NULL,           'c' },
    { "help",       no_argument,            NULL,           'h' },
    { "resume",     no_argument,            NULL,           'r' },
    { "force",      no_argument,            NULL,           'f' },
    { 0, 0, 0, 0 }
  };

  void example::operator()(int argc,char *argv[]) {

    // default options
    bool forceStart = false; // -f will do this true
    bool forceResume = false; // -r will do this true
    std::string file = "pareto_basic.cfg";
    int index;

    // parse the command line looking for valid arguments 
    while(true) {
      int c = getopt_long(argc,argv,shortOptions,longOptions,&index);
      if (c == -1) {
        break;
      }

      switch(c) {
        case 0:
          break;
        case 'r':
          forceResume = true;
          break;
        case 'f':
          forceStart = true;
          break;
        case 'c':
          file = optarg;
          break;
        case 'h':
          usage(argv);
          break;
        default:
          std::cerr<<"Invalid option\n";
          usage(argv);
      }
    }

    paretoFront::parameters pfPar;
    geneticsTester::parameters csPar;//////////////////////////////////////////////////////////////////
    bool showProgress = true;
    int verboseLevel = 5;

    std::ifstream in(file.c_str());
    bool write=true; // assume we have to write the config file first
    if (in) { // if file found, just read it
      lispStreamHandler lsh;
      lsh.use(in);
      write=!(lti::read(lsh,"showProgress",showProgress) &&
              lti::read(lsh,"verboseLevel",verboseLevel) &&
              lti::read(lsh,"pareto",pfPar) &&
              lti::read(lsh,"genetics",csPar)); // if successful, don't write
    }
    if (write) { // the file does not exist or is not correct, write it again!
      std::ofstream out(file.c_str());
      lispStreamHandler lsh;
      lsh.use(out);
      lti::write(lsh,"showProgress",showProgress);
      lti::write(lsh,"verboseLevel",verboseLevel);
      lti::write(lsh,"pareto",pfPar);
      lti::write(lsh,"genetics",csPar);

      std::cout << "Please edit file " << file 
                << " and ensure that the list of images is available."
                << std::endl;
      return;
    }

    // first a genetics object, with its corresponding parameters
    geneticsTester csg(csPar);
    // tell the parameters of the pareto front to use the given genetics object
    pfPar.setGeneticsObject(csg);
    // create a pareto object with the proper parameters
    paretoFront pf(pfPar);

    // we need to visualize progress
    streamProgressInfo progInfo;
    pf.setProgressObject(progInfo);
    pf.getProgressObject().setDetailLevel(verboseLevel);


    // The 'resume' framework is relatively simple:
    // first, check if the log file exist
    std::ifstream lf(pfPar.logFilename.c_str());
    bool resume = true;

    if (lf) {
      // the log file exists!
      lf.close(); // but we don't need it open any more
      if (forceStart) {
        resume = false;
      } else if (!forceResume) {
        char c = 'y';
        std::cout << "Log file '" << pfPar.logFilename << "' already exists."
                  << "\nDo you want to start from scratch [y|N]? "
                  << std::flush;
        std::cin >> c;
        if ((c == 'y') || (c == 'Y')) {
          resume = false;
        }
      }
    } else {
      resume = false; // it seems the file does not exist!
    }

    dmatrix front;
    if (resume) {
      std::cout << "Resuming optimization from '" << pfPar.logFilename << "'"
                << std::endl;
       pf.resume(front);
    } else {
      // and now, find the pareto front
      pf.apply(front);
    }
  }
}

int main(int argc,char *argv[]) {
  int command = system("rm graphData.txt");

  if(command == 0)
    std::cout << "Deleted dataGraph file" << std::endl;

  try {
    lti::example testObj;
    testObj(argc,argv);
    std::cout << "Test at the end!" << std::endl;
  }
  catch (lti::exception& exp) {
    std::cout << "An LTI::EXCEPTION was thrown: ";
    std::cout << exp.what() << std::endl;
  }
  catch (std::exception& exp) {
    std::cout << "std::exception was thrown: ";
    std::cout << exp.what() << std::endl;
  }
  catch (...) {
    std::cout << "Unknown exception thrown!" << std::endl;
  }
  return 0;

} // main
