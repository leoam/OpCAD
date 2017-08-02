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
 * \file   ltiGeneticsTester.h
 *         Example class for lti::genetics
 * \author Pablo Alvarado
 * \date   20.08.06
 *
 * $Id: ltiGeneticsTester.h,v 1.3 2015-01-21 06:20:26 alvarado Exp $
 */

#ifndef _LTI_GENETICS_TESTER_H_
#define _LTI_GENETICS_TESTER_H_

#include "ltiGenetics.h"

namespace lti {

  /**
   * A dummy functor that is evaluated with the paretoFront
   */
  class dummyFunctor : public functor {
  public:
    /**
     * The parameters for the class dummyFunctor
     */
    class parameters : public functor::parameters {
    public:
      /**
       * Default constructor
       */
      parameters();

      /**
       * Copy constructor
       * @param other the parameters object to be copied
       */
      parameters(const parameters& other);

      /**
       * Destructor
       */
      ~parameters();

      /**
       * Returns name of this type
       */
      const std::string& name() const;

      /**
       * Copy the contents of a parameters object
       * @param other the parameters object to be copied
       * @return a reference to this parameters object
       */
      parameters& copy(const parameters& other);

      /**
       * Copy the contents of a parameters object
       * @param other the parameters object to be copied
       * @return a reference to this parameters object
       */
      parameters& operator=(const parameters& other);

      /**
       * Returns a pointer to a clone of the parameters
       */
      virtual parameters* clone() const;

      /**
       * Returns a pointer to a clone of the parameters
       */
      virtual parameters* newInstance() const;

      /**
       * Write the parameters in the given ioHandler
       * @param handler the ioHandler to be used
       * @param complete if true (the default) the enclosing begin/end will
       *        be also written, otherwise only the data block will be written.
       * @return true if write was successful
       */
      virtual bool write(ioHandler& handler,const bool& complete=true) const;

      /**
       * Read the parameters from the given ioHandler
       * @param handler the ioHandler to be used
       * @param complete if true (the default) the enclosing begin/end will
       *        be also written, otherwise only the data block will be written.
       * @return true if write was successful
       */
      virtual bool read(ioHandler& handler,const bool& complete=true);

      // ------------------------------------------------
      // the parameters
      // ------------------------------------------------

      float L1, W1, 
            L2, W2, 
            L3, W3, 
            L4, W4, 
            L5, W5, 
            L6, W6, 
            L7, W7, 
            L8, W8, 
            L9, W9, 
            L10, W10, 
            L11, W11, 
            L12, W12, 
            L13, W13, 
            L14, W14;


    };

    /**
     * Default constructor
     */
    dummyFunctor();

    /**
     * Construct a functor using the given parameters
     */
    dummyFunctor(const parameters& par);

    /**
     * Copy constructor
     * @param other the object to be copied
     */
    dummyFunctor(const dummyFunctor& other);

    /**
     * Destructor
     */
    virtual ~dummyFunctor();

    /**
     * Returns the name of this type ("dummyFunctor")
     */
    virtual const std::string& name() const;

    /**
     * Copy data of "other" functor.
     * @param other the functor to be copied
     * @return a reference to this functor object
     */
    dummyFunctor& copy(const dummyFunctor& other);

    /**
     * Alias for copy member
     * @param other the functor to be copied
     * @return a reference to this functor object
     */
    dummyFunctor& operator=(const dummyFunctor& other);

    /**
     * Returns a pointer to a clone of this functor.
     */
    virtual dummyFunctor* clone() const;

    /**
     * Returns a pointer to a clone of this functor.
     */
    virtual dummyFunctor* newInstance() const;

    /**
     * Returns used parameters
     */
    const parameters& getParameters() const;

    /**
     * operates on a copy of the given %parameters.
     * @param src double with the source data.
     * @param dest double where the result will be left.
     * @return true if apply successful or false otherwise.
     */
    bool apply(const double& src,double& dest) const;
  };
  
  // -------------------------------------------------------------------------
  //
  // G E N E T I C S   T E S T E R
  //
  // -------------------------------------------------------------------------



  /**
   * The Pareto Front Tester functor is a simple example of an evaluation
   * framework using the Pareto Front class. 
   */
  class geneticsTester : public genetics {
  public:

    typedef genetics::parameters parameters;

    /**
     * Default constructor
     */
    geneticsTester();

    /**
     * Construct with parameters
     */
    geneticsTester(const parameters& par);

    /**
     * Destructor
     */
    virtual ~geneticsTester();

    /**
     * Returns the name of this type ("geneticsTester")
     */
    virtual const std::string& name() const;

    /**
     * Returns a pointer to a clone of this functor.
     */
    virtual geneticsTester* clone() const;

    /**
     * Returns a pointer to a clone of this functor.
     */
    virtual geneticsTester* newInstance() const;

    /**
     * @name Public methods to be reimplemented
     */
    //@{

    /**
     * Convert a binary-chain representation of a chromosome to a valid
     * parameter object.
     */
    virtual bool chromosomeToPhenotype(const chromosome& genotype,
                                       functor::parameters& phenotype) const;

    /**
     * Return a fresh allocated parameters for the evaluated functor, which is
     * equivalent to the given genotype.
     */
    virtual functor::parameters* 
    chromosomeToPhenotype(const chromosome& genotype) const;

    /**
     * Convert a valid parameters object (phenotype) into binary-chain
     * representation of a chromosome.
     */
    virtual bool phenotypeToChromosome(const functor::parameters& phenotype,
                                       chromosome& genotype) const;

    /**
     * Return the length in bits for a chromosome.
     *
     * This method needs to be reimplemented, in order to get some 
     * default implementations to work.
     */
    virtual int getChromosomeSize() const;

    /**
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
    virtual bool evaluateChromosome(const chromosome& individual,
                                    dvector& fitness) const; 

    //@}
  private:
    enum {
      bitsForL = 16,
      bitsForW = 16
    };

  };
}

#endif

