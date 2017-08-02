/*
 * Copyright (C) 2006
 * Pablo Alvarado, ITCR
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

/**
 * \file   ltiGeneticsTester.cpp
 *         Example class for lti::genetics
 * \author Pablo Alvarado
 * \date   20.08.06
 *
 * $Id: ltiGeneticsTester.cpp,v 1.4 2015-01-21 06:20:26 alvarado Exp $
 */

#include "ltiGeneticsTester.h"
#include "ltiFactory.h"
#include "ltiMath.h"
#include "ClientSocket.h"
#include "SocketException.h"
#include <sstream>

#undef _LTI_DEBUG
#define _LTI_DEBUG 1
#include "ltiDebug.h"

namespace lti {

  // --------------------------------------------------
  // dummyFunctor::parameters
  // --------------------------------------------------

  // default constructor
  dummyFunctor::parameters::parameters()
    : functor::parameters() {
        L1 = float(1);
        W1 = float(1);
        L2 = float(1);
        W2 = float(1);
        L3 = float(1);
        W3 = float(1);
        L4 = float(1);
        W4 = float(1);
        L5 = float(1);
        W5 = float(1);
        L6 = float(1);
        W6 = float(1);
        L7 = float(1);
        W7 = float(1);
        L8 = float(1);
        W8 = float(1);
        L9 = float(1);
        W9 = float(1);
        L10 = float(1);
        W10 = float(1);
        L11 = float(1);
        W11 = float(1);
        L12 = float(1);
        W12 = float(1);
        L13 = float(1);
        W13 = float(1);
        L14 = float(1);
        W14 = float(1);
  }

  // copy constructor
  dummyFunctor::parameters::parameters(const parameters& other)
    : functor::parameters() {
    copy(other);
  }

  // destructor
  dummyFunctor::parameters::~parameters() {
  }

  // get type name
  const std::string& dummyFunctor::parameters::name() const {
    _LTI_RETURN_CLASS_NAME
  }

  // copy member

  dummyFunctor::parameters& 
  dummyFunctor::parameters::copy(const parameters& other) {
    functor::parameters::copy(other);

        L1 = other.L1;
        W1 = other.W1;
        L2 = other.L2;
        W2 = other.W2;
        L3 = other.L3;
        W3 = other.W3;
        L4 = other.L4;
        W4 = other.W4;
        L5 = other.L5;
        W5 = other.W5;
        L6 = other.L6;
        W6 = other.W6;
        L7 = other.L7;
        W7 = other.W7;
        L8 = other.L8;
        W8 = other.W8;
        L9 = other.L9;
        W9 = other.W9;
        L10 = other.L10;
        W10 = other.W10;
        L11 = other.L11;
        W11 = other.W11;
        L12 = other.L12;
        W12 = other.W12;
        L13 = other.L13;
        W13 = other.W13;
        L14 = other.L14;
        W14 = other.W14;
      
    return *this;
  }

  // alias for copy member
  dummyFunctor::parameters&
  dummyFunctor::parameters::operator=(const parameters& other) {
    return copy(other);
  }

  // clone member
  dummyFunctor::parameters* dummyFunctor::parameters::clone() const {
    return new parameters(*this);
  }

  // new instance member
  dummyFunctor::parameters* dummyFunctor::parameters::newInstance() const {
    return new parameters();
  }

  /*
   * write the parameters in the given ioHandler
   * @param handler the ioHandler to be used
   * @param complete if true (the default) the enclosing begin/end will
   *        be also written, otherwise only the data block will be written.
   * @return true if write was succeful
   */
  bool dummyFunctor::parameters::write(ioHandler& handler,
                                         const bool& complete) const {
    bool b = true;
    if (complete) {
      b = handler.writeBegin();
    }

    if (b) {
      lti::write(handler,"L1",L1);
      lti::write(handler,"W1",W1);
      lti::write(handler,"L2",L2);
      lti::write(handler,"W2",W2);
      lti::write(handler,"L3",L3);
      lti::write(handler,"W3",W3);
      lti::write(handler,"L4",L4);
      lti::write(handler,"W4",W4);
      lti::write(handler,"L5",L5);
      lti::write(handler,"W5",W5);
      lti::write(handler,"L6",L6);
      lti::write(handler,"W6",W6);
      lti::write(handler,"L7",L7);
      lti::write(handler,"W7",W7);
      lti::write(handler,"L8",L8);
      lti::write(handler,"W8",W8);
      lti::write(handler,"L9",L9);
      lti::write(handler,"W9",W9);
      lti::write(handler,"L10",L10);
      lti::write(handler,"W10",W10);
      lti::write(handler,"L11",L11);
      lti::write(handler,"W11",W11);
      lti::write(handler,"L12",L12);
      lti::write(handler,"W12",W12);
      lti::write(handler,"L13",L13);
      lti::write(handler,"W13",W13);
      lti::write(handler,"L14",L14);
      lti::write(handler,"W14",W14);
    }

    b = b && functor::parameters::write(handler,false);

    if (complete) {
      b = b && handler.writeEnd();
    }

    return b;
  }

  /*
   * read the parameters from the given ioHandler
   * @param handler the ioHandler to be used
   * @param complete if true (the default) the enclosing begin/end will
   *        be also read, otherwise only the data block will be read.
   * @return true if read was succeful
   */
  bool dummyFunctor::parameters::read(ioHandler& handler,
                                        const bool& complete) {
    bool b = true;
    if (complete) {
      b = handler.readBegin();
    }

    if (b) {
      lti::read(handler,"L1",L1);
      lti::read(handler,"W1",W1);
      lti::read(handler,"L2",L2);
      lti::read(handler,"W2",W2);
      lti::read(handler,"L3",L3);
      lti::read(handler,"W3",W3);
      lti::read(handler,"L4",L4);
      lti::read(handler,"W4",W4);
      lti::read(handler,"L5",L5);
      lti::read(handler,"W5",W5);
      lti::read(handler,"L6",L6);
      lti::read(handler,"W6",W6);
      lti::read(handler,"L7",L7);
      lti::read(handler,"W7",W7);
      lti::read(handler,"L8",L8);
      lti::read(handler,"W8",W8);
      lti::read(handler,"L9",L9);
      lti::read(handler,"W9",W9);
      lti::read(handler,"L10",L10);
      lti::read(handler,"W10",W10);
      lti::read(handler,"L11",L11);
      lti::read(handler,"W11",W11);
      lti::read(handler,"L12",L12);
      lti::read(handler,"W12",W12);
      lti::read(handler,"L13",L13);
      lti::read(handler,"W13",W13);
      lti::read(handler,"L14",L14);
      lti::read(handler,"W14",W14);
    }

    b = b && functor::parameters::read(handler,false);

    if (complete) {
      b = b && handler.readEnd();
    }

    return b;
  }

  // --------------------------------------------------
  // dummyFunctor
  // --------------------------------------------------

  // default constructor
  dummyFunctor::dummyFunctor()
    : functor() {

    // create an instance of the parameters with the default values
    parameters defaultParameters;
    // set the default parameters
    setParameters(defaultParameters);
  }

  // default constructor
  dummyFunctor::dummyFunctor(const parameters& par)
    : functor() {

    // set the given parameters
    setParameters(par);
  }


  // copy constructor
  dummyFunctor::dummyFunctor(const dummyFunctor& other)
    : functor() {
    copy(other);
  }

  // destructor
  dummyFunctor::~dummyFunctor() {
  }

  // returns the name of this type
  const std::string& dummyFunctor::name() const {
    _LTI_RETURN_CLASS_NAME;
  }

  // copy member
  dummyFunctor& dummyFunctor::copy(const dummyFunctor& other) {
    functor::copy(other);

    return (*this);
  }

  // alias for copy member
  dummyFunctor& dummyFunctor::operator=(const dummyFunctor& other) {
    return (copy(other));
  }


  // clone member
  dummyFunctor* dummyFunctor::clone() const {
    return new dummyFunctor(*this);
  }

  // clone member
  dummyFunctor* dummyFunctor::newInstance() const {
    return new dummyFunctor();
  }

  // return parameters
  const dummyFunctor::parameters& dummyFunctor::getParameters() const {
    const parameters* par =
      dynamic_cast<const parameters*>(&functor::getParameters());
    if(isNull(par)) {
      throw invalidParametersException(name());
    }
    return *par;
  }

  // -------------------------------------------------------------------
  // The apply-methods!
  // -------------------------------------------------------------------

  
  // On copy apply for type double!
  bool dummyFunctor::apply(const double& src,double& dest) const {

    return true;
  }

  // --------------------------------------------------
  //
  // P A R E T O   T E S T E R
  //
  // --------------------------------------------------

  // In factory<genetics> register this class
  _LTI_REGISTER_IN_FACTORY(genetics,geneticsTester)


  // --------------------------------------------------
  // geneticsTester
  // --------------------------------------------------

  // default constructor
  geneticsTester::geneticsTester()
    : genetics() {
    parameters defPar;
    setParameters(defPar);
  }

  // default constructor
  geneticsTester::geneticsTester(const parameters& par)
    : genetics() {
    setParameters(par);
  }

  // destructor
  geneticsTester::~geneticsTester() {
  }

  // returns the name of this type
  const std::string& geneticsTester::name() const {
    _LTI_RETURN_CLASS_NAME
  }

  geneticsTester* geneticsTester::clone() const {
    return new geneticsTester(*this);
  }

  geneticsTester* geneticsTester::newInstance() const {
    return new geneticsTester();
  }

  /*
   * Convert a binary-chain representation of a chromosome to a valid
   * parameter object.
   */
  bool geneticsTester::chromosomeToPhenotype(const chromosome& genotype,
                                        functor::parameters& phenotype) const {
    
    dummyFunctor::parameters* par = 
      dynamic_cast<dummyFunctor::parameters*>(&phenotype);

    if (isNull(par)) {
      return false;
    }

    int pos=0;
    double L1Res;
    double W1Res;
    double L2Res;
    double W2Res;
    double L3Res;
    double W3Res;
    double L4Res;
    double W4Res;
    double L5Res;
    double W5Res;
    double L6Res;
    double W6Res;
    double L7Res;
    double W7Res;
    double L8Res;
    double W8Res;
    double L9Res;
    double W9Res;
    double L10Res;
    double W10Res;
    double L11Res;
    double W11Res;
    double L12Res;
    double W12Res;
    double L13Res;
    double W13Res;
    double L14Res;
    double W14Res;

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L1Res);
    par->L1 = static_cast<float>(L1Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W1Res);
    par->W1 = static_cast<float>(W1Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L2Res);
    par->L2 = static_cast<float>(L2Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W2Res);
    par->W2 = static_cast<float>(W2Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L3Res);
    par->L3 = static_cast<float>(L3Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W3Res);
    par->W3 = static_cast<float>(W3Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L4Res);
    par->L4 = static_cast<float>(L4Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W4Res);
    par->W4 = static_cast<float>(W4Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L5Res);
    par->L5 = static_cast<float>(L5Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W5Res);
    par->W5 = static_cast<float>(W5Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L6Res);
    par->L6 = static_cast<float>(L6Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W6Res);
    par->W6 = static_cast<float>(W6Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L7Res);
    par->L7 = static_cast<float>(L7Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W7Res);
    par->W7 = static_cast<float>(W7Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L8Res);
    par->L8 = static_cast<float>(L8Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W8Res);
    par->W8 = static_cast<float>(W8Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L9Res);
    par->L9 = static_cast<float>(L9Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W9Res);
    par->W9 = static_cast<float>(W9Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L10Res);
    par->L10 = static_cast<float>(L10Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W10Res);
    par->W10 = static_cast<float>(W10Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L11Res);
    par->L11 = static_cast<float>(L11Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W11Res);
    par->W11 = static_cast<float>(W11Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L12Res);
    par->L12 = static_cast<float>(L12Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W12Res);
    par->W12 = static_cast<float>(W12Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L13Res);
    par->L13 = static_cast<float>(L13Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W13Res);
    par->W13 = static_cast<float>(W13Res);

    pos = binToDouble(genotype,pos,bitsForL,1.1,15.0,L14Res);
    par->L14 = static_cast<float>(L14Res);

    pos = binToDouble(genotype,pos,bitsForW,1.1,15.0,W14Res);
    par->W14 = static_cast<float>(W14Res);

    return true;

    
  }

  /*
   * Return a fresh allocated parameters for the evaluated functor, which is
   * equivalent to the given genotype.
   */
  functor::parameters* 
  geneticsTester::chromosomeToPhenotype(const chromosome& genotype) const {

    dummyFunctor::parameters* par = new dummyFunctor::parameters;
    chromosomeToPhenotype(genotype,*par);

    return par;
  }

  /*
   * Convert a valid parameters object (phenotype) into binary-chain
   * representation of a chromosome.
   */
  bool geneticsTester::phenotypeToChromosome(
                                          const functor::parameters& phenotype,
                                          chromosome& genotype) const {
    const dummyFunctor::parameters* par = 
      dynamic_cast<const dummyFunctor::parameters*>(&phenotype);

    if (isNull(par)) {
      return false;
    }

    genotype.resize(bitsForL*14 + bitsForW*14);
    int pos = 0;

    pos = doubleToBin(par->L1, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W1, pos, bitsForW, 0.0, 15.0, genotype);
    pos = doubleToBin(par->L2, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W2, pos, bitsForW, 0.0, 15.0, genotype);   
    pos = doubleToBin(par->L3, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W3, pos, bitsForW, 0.0, 15.0, genotype); 
    pos = doubleToBin(par->L4, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W4, pos, bitsForW, 0.0, 15.0, genotype); 
    pos = doubleToBin(par->L5, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W5, pos, bitsForW, 0.0, 15.0, genotype); 
    pos = doubleToBin(par->L6, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W6, pos, bitsForW, 0.0, 15.0, genotype); 
    pos = doubleToBin(par->L7, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W7, pos, bitsForW, 0.0, 15.0, genotype); 
    pos = doubleToBin(par->L8, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W8, pos, bitsForW, 0.0, 15.0, genotype); 
    pos = doubleToBin(par->L9, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W9, pos, bitsForW, 0.0, 15.0, genotype); 
    pos = doubleToBin(par->L10, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W10, pos, bitsForW, 0.0, 15.0, genotype); 
    pos = doubleToBin(par->L11, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W11, pos, bitsForW, 0.0, 15.0, genotype); 
    pos = doubleToBin(par->L12, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W12, pos, bitsForW, 0.0, 15.0, genotype);
    pos = doubleToBin(par->L13, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W13, pos, bitsForW, 0.0, 15.0, genotype);
    pos = doubleToBin(par->L14, pos, bitsForL, 0.0, 15.0, genotype);
    pos = doubleToBin(par->W14, pos, bitsForW, 0.0, 15.0, genotype); 

    return true;
  }
   
  /*
   * Return the length in bits for a chromosome.
   *
   * This method needs to be reimplemented, in order to get some 
   * default implementations to work.
   */
  int geneticsTester::getChromosomeSize() const {

    return bitsForL*14 + bitsForW*14;
  }

  /*
   * Evaluate Chromosome
   *
   * This method is one of the most important ones for the pareto evaluation.
   * Its task is to produce a multidimensional fitness measure for a given
   * chromosome.
   *
   * It returns true if the evaluation was successful, of false if the
   * phenotype represents some invalid parameterization.  It is highly 
   * recomended that the mutation and crossover methods are reimplemented to 
   * avoid invalid parameterizations.
   *
   * There are mainly two types of fitness measures that can be
   * analyzed with this functor of this kind: empirical goodness and
   * empirical discrepancy (Zhang).  The empirical goodness computes some
   * measure using exclusively the test data, without requiring any ground
   * truth.  The empirical discrepancy assumes the existency of ground truth
   * and provides as measure some distance between the result of an algorithm
   * and the ground truth.  Each class derived from geneticsTester should
   * specify clearly which kind of fitness measures it provides.
   * 
   */
  bool geneticsTester::evaluateChromosome(const chromosome& individual,
                                                dvector& fitness) const {
    
    // usually there will be a huge test set and some statistics for all
    // results will be used to build the multidimensional fitness measure.
    
    // Here we assume that dummyFunctor provides already a fitness measure
    // and that one of its parameters tell already how long it will take.
    dummyFunctor::parameters circPar;
    chromosomeToPhenotype(individual,circPar);
    dummyFunctor df(circPar);

    fitness.allocate(2);

/*
    std::cout << "Valores de L1, W1: " << circPar.L1 << " " << circPar.W1 << std::endl;
    std::cout << "Valores de L2, W2: " << circPar.L2 << " " << circPar.W2 << std::endl;
*/


try
    {

      ClientSocket client_socket ( "localhost", 8080 );
     std::string reply;
     std::ostringstream sstr;
 

      sstr << "L=" << circPar.L1 <<"e-6 " 
           << "W=" << circPar.W1 <<"e-6 " 
           << "L=" << circPar.L2 <<"e-6 " 
           << "W=" << circPar.W2 <<"e-6 "
           << "L=" << circPar.L3 <<"e-6 " 
           << "W=" << circPar.W3 <<"e-6 "
           << "L=" << circPar.L4 <<"e-6 " 
           << "W=" << circPar.W4 <<"e-6 "
           << "L=" << circPar.L5 <<"e-6 " 
           << "W=" << circPar.W5 <<"e-6 "
           << "L=" << circPar.L6 <<"e-6 " 
           << "W=" << circPar.W6 <<"e-6 "
           << "L=" << circPar.L7 <<"e-6 " 
           << "W=" << circPar.W7 <<"e-6 "
           << "L=" << circPar.L8 <<"e-6 " 
           << "W=" << circPar.W8 <<"e-6 "
           << "L=" << circPar.L9 <<"e-6 " 
           << "W=" << circPar.W9 <<"e-6 "
           << "L=" << circPar.L10 <<"e-6 " 
           << "W=" << circPar.W10 <<"e-6 "
           << "L=" << circPar.L11 <<"e-6 " 
           << "W=" << circPar.W11 <<"e-6 "
           << "L=" << circPar.L12 <<"e-6 " 
           << "W=" << circPar.W12 <<"e-6 "
           << "L=" << circPar.L13 <<"e-6 " 
           << "W=" << circPar.W13 <<"e-6 "
           << "L=" << circPar.L14 <<"e-6 " 
           << "W=" << circPar.W14 <<"e-6";
       
     
     std::string str;
     str = sstr.str();
     
     try
       {
   client_socket << str; //"Test message: fitness.at(1)";
   client_socket >> reply;
       }
     catch ( SocketException& ) {}
     
     std::cout << "We received this response from the server:\n\"" << reply << "\"\n";
     
     std::istringstream ist(reply);
     std::string foo;
     ist >> foo >> fitness.at(0) >> foo >> fitness.at(1); //AQUI MODIFICACION

     _lti_debug3("Fitness: " << fitness.at(0) << "," << fitness.at(1) <<std::endl); //AQUI MODIFICACION
     std::cout << "Valor Consumo de potencia: " << fitness.at(0) << std::endl;
     std::cout << "Valor Ganancia: " << fitness.at(1) << std::endl;
     
    }
      catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }
      //end of sockets code



    return true;
  }


}

