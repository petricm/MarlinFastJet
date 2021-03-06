/*
 * FastJetProcessor.h
 *
 *  Created on: 25.05.2010
 *      Author: Lars Weuste (MPP Munich) - weuste@mpp.mpg.de
 *			iterative inclusive algorithm based on design by Marco Battaglia (CERN)
 *- Marco.Battaglia@cern.ch
 */

#ifndef FASTJETPROCESSOR_H_
#define FASTJETPROCESSOR_H_

#include "EClusterMode.h"

#include "EVENT/LCCollection.h"
#include "EVENT/ReconstructedParticle.h"
#include "IMPL/LCCollectionVec.h"
#include "LCIOSTLTypes.h"
#include "marlin/Processor.h"
#include "marlin/VerbosityLevels.h"

#include <fastjet/JetDefinition.hh>
#include <fastjet/PseudoJet.hh>

#include <string>
#include <vector>

// Forward Declaration
class FastJetUtil;
typedef std::vector<fastjet::PseudoJet> PseudoJetList;

class FastJetProcessor : marlin::Processor {
 public:
  FastJetProcessor();
  virtual ~FastJetProcessor();

  virtual Processor* newProcessor() {
    return new FastJetProcessor();
  }

  /** Called at the begin of the job before anything is read.
   * Use to initialize the processor, e.g. book histograms.
   */
  virtual void init();

  /** Called for every run.
   */
  virtual void processRunHeader( LCRunHeader* ){};

  /** Called for every event - the working horse.
   */
  virtual void processEvent( LCEvent* evt );

  virtual void check( LCEvent* ){};

  /** Called after data processing for clean up.
   */
  virtual void end();

  friend class FastJetUtil;

 private:
  // the LC Collection names for input/output
  std::string _lcParticleInName;
  std::string _lcParticleOutName;
  std::string _lcJetOutName;

  EVENT::ReconstructedParticle* getRecPar( fastjet::PseudoJet& fj, const PseudoJetList& constituents );

  LCCollection* _reconstructedPars;

  int  _statsFoundJets;
  int  _statsNrEvents;
  int  _statsNrSkippedEmptyEvents;
  int  _statsNrSkippedFixedNrJets;
  int  _statsNrSkippedMaxIterations;
  bool _storeParticlesInJets;

  FastJetUtil* _fju;

 private:
  FastJetProcessor( const FastJetProcessor& rhs );
  FastJetProcessor& operator=( const FastJetProcessor& ) {
    return *this;
  }
};

std::ostream& operator<<( std::ostream& out, EClusterMode& m );

#endif /* FASTJETPROCESSOR_H_ */
