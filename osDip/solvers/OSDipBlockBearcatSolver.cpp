/* $Id: OSBlockBearcatSolver.cpp 3038 2009-11-07 11:43:44Z kmartin $ */
/** @file OSBlockBearcatSolver.cpp
 * 
 *
 * @author  Gus Gassmann, Jun Ma, Kipp Martin, 
 * @version 1.0, 21/July/2008
 * @since   OS1.1
 *
 * \remarks
 * Copyright (C) 2005-2008, Gus Gassmann, Jun Ma, Kipp Martin,
 * Dalhousie University,  Northwestern University, and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Common Public License. 
 * Please see the accompanying LICENSE file in root directory for terms.
 * 
 */
#include "OSDipBlockBearcatSolver.h"
#include "OSErrorClass.h" 
#include "OSDataStructures.h"

#include <sstream>;
using std::ostringstream;


OSDipBlockBearcatSolver::OSDipBlockBearcatSolver():
	m_osinstance(NULL) {
	std::cout << "INSIDE OSDipBlockBearcatSolver CONSTRUCTOR" << std::endl;
}//end OSDipBlockBearcatSolver


OSDipBlockBearcatSolver::OSDipBlockBearcatSolver( OSInstance *osinstance,  OSOption *osoption) {
	  std::cout << "INSIDE OSDipBlockBearcatSolver CONSTRUCTOR" << std::endl;
	  std::cout << "whichBlock = " << m_whichBlock<< std::endl;
	try{
		m_osinstance = osinstance;
		m_numberOfVar = m_osinstance->getVariableNumber();
		
		m_osoption = osoption;
		m_demand = NULL;
		//now get data
		std::vector<SolverOption*> solverOptions;
		std::vector<SolverOption*>::iterator vit;
		std::vector<int >demand;

		
		solverOptions = m_osoption->getSolverOptions("Dip");
		//iterate over the vector
		
		int tmpVal;

		for (vit = solverOptions.begin(); vit != solverOptions.end(); vit++) {
			
			
			std::cout << (*vit)->name << std::endl;
			
			//(*vit)->name.compare("initialCol") == 0
			//if(rowNames[ i3].find("routeCapacity(1)") == string::npos )
			
			if( (*vit)->name.find("numHubs") !=  std::string::npos){
				
				std::istringstream buffer( (*vit)->value);
				buffer >> m_numHubs;
				std::cout << "numHubs = " << m_numHubs <<  std::endl;
				
			}else{
				
				if((*vit)->name.find("numNodes") !=  std::string::npos){
					
					std::istringstream buffer( (*vit)->value);
					buffer >> m_numNodes;
					std::cout << "numNodes = " <<  m_numNodes <<  std::endl;
					
				}else{
					if((*vit)->name.find("totalDemand") !=  std::string::npos){
						
						std::istringstream buffer( (*vit)->value);
						buffer >> m_totalDemand;
						std::cout << "m_totalDemand = " << m_totalDemand <<  std::endl;
						
					}else{
						if((*vit)->name.find("minDemand") !=  std::string::npos){
							
							std::istringstream buffer( (*vit)->value);
							buffer >> m_minDemand;
							std::cout << "m_minDemand = " << m_minDemand <<  std::endl;
						
						}else{
							if( (*vit)->name.find("demand") !=  std::string::npos ){
								
								std::istringstream buffer( (*vit)->value);
								buffer >> tmpVal;
								demand.push_back( tmpVal);
								std::cout << "demand = " << tmpVal <<  std::endl;
								
							}
						}
					}
				}
			}//end if on solver options
			
		}//end for loop on options
		
		//now fill in demand
		m_demand = new int[ m_numNodes];
		if(m_numNodes != demand.size( ) ) throw ErrorClass("inconsistent number of demand nodes");
		int i;
		for (i = 0; i < m_numNodes; i++) {
			
			m_demand[ i] = demand[i];
			
		}
	} catch (const ErrorClass& eclass) {

		throw ErrorClass(eclass.errormsg);

	}	

}//end OSDipBlockBearcatSolver

OSDipBlockBearcatSolver::~OSDipBlockBearcatSolver(){
	
	std::cout << "INSIDE ~OSDipBlockBearcatSolver()" << std::endl;


	std::vector<IndexValuePair*>::iterator  vit;
	
	for (vit = m_primalVals.begin(); vit != m_primalVals.end(); vit++) {
		
		delete *vit;
	}
	
	if(m_demand != NULL) delete[] m_demand;
	//if(m_osrlreader != NULL) delete m_osrlreader;
}//end ~OSDipBlockBearcatSolver

void OSDipBlockBearcatSolver::solve(double *cost, std::vector<IndexValuePair*> *solIndexValPair, double *optVal){

	try{
		struct IndexValuePair *primalValPair;

		std::vector<IndexValuePair*>::iterator  vit;
		
		for (vit = m_primalVals.begin(); vit != m_primalVals.end(); vit++) {
			
			delete *vit;
		}
		m_primalVals.clear();
		//sum up negative coefficient
		// -- critical -- we assume last variable is the y variable
		// this is just for illustration
		*optVal = 0;
		for(int i = 0 ; i < m_numberOfVar - 1; i++){
			
			m_osinstance->instanceData->objectives->obj[0]->coef[i]->value 
					= cost[ i];
			
			
			primalValPair = new IndexValuePair();
			
			primalValPair->value = 0.0;
			primalValPair->idx = i;
			
			if (cost[ i] < 0){
				
				*optVal = *optVal + cost[ i];
				 primalValPair->value = 1.0;
			}
			
			m_primalVals.push_back( primalValPair);
			
			
		}//end for
		
		//now set the y variable to 1 if optVal is negative
		//otherwise 0
		primalValPair = new IndexValuePair();
		primalValPair->idx = m_numberOfVar - 1;
		
		if(*optVal < 0){
			
			primalValPair->value = 1.0;
			*optVal = *optVal + cost[ m_numberOfVar - 1];
			
		}else{
			
			primalValPair->value = 0.0;	
		}
		
		m_primalVals.push_back( primalValPair);
		
		
		m_osinstance->bObjectivesModified = true;
		std::cout << m_osinstance->printModel( ) << std::endl;
		//
		
		std::cout << "NUMBER OF VARIABLES m_primalVals = " <<  m_primalVals.size() << std::endl;
		
		for (vit = m_primalVals.begin(); vit != m_primalVals.end(); vit++) {
			
			//solIndexValPair.push_back( *vit);
			
		}
		
		 *solIndexValPair = m_primalVals;
		// the argument is the solution index
		
		
		//solStatus = m_osresult->getSolutionStatusType( 0 );
		
		//std::cout << "SOLUTION STATUS " << solStatus << std::endl;
		// if solStatus is optimal get the optimal solution value
		//if( solStatus.find("ptimal") != string::npos ){
		//first index is objIdx, second is solution index
		//	*optVal = m_osresult->getOptimalObjValue( -1, 0);
		//	*solIndexValPair = m_osresult->getOptimalPrimalVariableValues( 0);			
		//}else{
		//	throw ErrorClass("problem -- did not optimize a subproblem");
		//}	
			
	} catch (const ErrorClass& eclass) {

		throw ErrorClass(eclass.errormsg);

	}	
	
}//end solve


void OSDipBlockBearcatSolver::solve(double *cost, std::string *osrl){

	
	try{
		//not implemented
			
	} catch (const ErrorClass& eclass) {

		throw ErrorClass(eclass.errormsg);

	}	
	
}//end solve

