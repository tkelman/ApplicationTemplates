/* $Id: template.cpp 2710 2009-06-10 21:13:43Z kmartin $ */
/** @file osTestCode.cpp
 * 
 * @author  Horand Gassmann, Jun Ma, Kipp Martin, 
 * @version 1.0, 10/05/2005
 * @since   OS1.0
 *
 * \remarks
 * Copyright (C) 2005, Jun Ma, Kipp Martin,
 * Northwestern University, and the University of Chicago.
 * All Rights Reserved.
 * This software is licensed under the Common Public License. 
 * Please see the accompanying LICENSE file in root directory for terms.
 * 
 */ 
 
//#include <cppad/cppad.hpp> 
#include "OSConfig.h"
#include "OSCoinSolver.h"
#include "OSIpoptSolver.h"
#include "OSResult.h" 
#include "OSiLReader.h"        
#include "OSiLWriter.h"   
#include "OSrLReader.h"          
#include "OSrLWriter.h"  
#include "OSoLWriter.h"  
#include "OSInstance.h"  
#include "OSFileUtil.h"   
#include "OSDefaultSolver.h"     
#include "OShL.h"     
#include "OSErrorClass.h"
#include "OSmps2osil.h"   
#include "OSBase64.h"
#include "OSErrorClass.h"
#include "OSMathUtil.h"
#include "CoinFinite.hpp"

#include "ClpSimplex.hpp"
#include "ClpInterior.hpp"
#include "ClpCholeskyBase.hpp"
#include "ClpQuadraticObjective.hpp"

#include<iostream> 
#include <ostream>
#include <sstream>
#include <streambuf>

#include<stdio.h>
 
using std::cout;   
using std::endl;




int main(int argC, char* argV[]){
	WindowsErrorPopupBlocker();
	FileUtil *fileUtil = NULL; 
	fileUtil = new FileUtil();
	
	//ClpSimplex*  qpClpModel;
    ClpInterior*  qpClpModel;
    
    
	qpClpModel = NULL;
	// template -- add your code here -- //
	std::cout << "Hello World" << std::endl;
	
	try{

        int i;
 

		const char dirsep =  CoinFindDirSeparator();
		std::string osil;
		// Set directory containing mps data files.
		std::string dataDir;
		std::string osilFileName;
		//dataDir = dirsep == '/' ? "../../data/" : "..\\..\\data\\";
		dataDir = dirsep == '/' ? "../data/" : "..\\data\\";
		// first declare a generic solver
		DefaultSolver *solver  = NULL;
		
		OSiLReader *osilreader = NULL;
		OSInstance *osinstance = NULL;
		OSoLWriter *osolwriter = NULL;
		OSOption* osoption = NULL;
		

		
		/******************** Start Clp Example *************************/
		std::cout << std::endl << std::endl;
		std::cout << "CLP EXAMPLE" << std::endl;
		
		/******************** STEP 1 ************************
		* Get an instance in mps format, and create an OSInstance object
		*/
		std::string qpFileName;
		qpFileName =  dataDir  +  "parincQuadratic.osil";
		// convert to the OS native format
		osil = fileUtil->getFileAsString( qpFileName.c_str() );
		osilreader = new OSiLReader(); 
		osinstance = osilreader->readOSiL( osil);
		
		
		/******************** STEP 2 ************************
		* Create an OSOption object and give the solver options
		*/		
		osoption = new OSOption();
		/** 
		 *  here is the format for setting options:
		 *	bool setAnotherSolverOption(std::string name, std::string value, std::string solver, 
		 *	std::string category, std::string type, std::string description);
		 */
		 // normally most output is turned off, here we turn it back on
		osoption->setAnotherSolverOption("OsiHintTry","","osi","","OsiHintStrength","");
		osoption->setAnotherSolverOption("OsiDoReducePrint","false","osi","","OsiHintParam","");
		osolwriter = new OSoLWriter();
		std::cout << osolwriter-> writeOSoL( osoption);
		
		
		/******************** STEP 3 ************************
		* Create the solver object -- for a CoinSolver we must specify
		* which solver to use
		*/
		//solver = new CoinSolver();
		//solver->sSolverName ="clp"; 
		

		//qpClpModel = new ClpSimplex();
        qpClpModel = new  ClpInterior();
		
	    CoinPackedMatrix* matrix;
	    bool columnMajor = true;
	    double maxGap = 0;
		matrix = new CoinPackedMatrix(
		columnMajor, //Column or Row Major
		columnMajor? osinstance->getConstraintNumber() : osinstance->getVariableNumber(), //Minor Dimension
		columnMajor? osinstance->getVariableNumber() : osinstance->getConstraintNumber(), //Major Dimension
		osinstance->getLinearConstraintCoefficientNumber(), //Number of nonzeroes
		columnMajor? osinstance->getLinearConstraintCoefficientsInColumnMajor()->values : osinstance->getLinearConstraintCoefficientsInRowMajor()->values, //Pointer to matrix nonzeroes
		columnMajor? osinstance->getLinearConstraintCoefficientsInColumnMajor()->indexes : osinstance->getLinearConstraintCoefficientsInRowMajor()->indexes, //Pointer to start of minor dimension indexes -- change to allow for row storage
		columnMajor? osinstance->getLinearConstraintCoefficientsInColumnMajor()->starts : osinstance->getLinearConstraintCoefficientsInRowMajor()->starts, //Pointers to start of columns.
		0,   0, maxGap ); 
		
		qpClpModel->setOptimizationDirection( -1);
		qpClpModel->loadProblem( *matrix, osinstance->getVariableLowerBounds(), 
				osinstance->getVariableUpperBounds(),  
				osinstance->getDenseObjectiveCoefficients()[0], 
				osinstance->getConstraintLowerBounds(), osinstance->getConstraintUpperBounds()
		);
		
		
        //now for the quadratic part
        
        int *start = NULL;
        int *idx = NULL;
        double *nonz = NULL;

        start = new int[3];
        idx = new int[2]; //index the columns
        nonz = new double[2];
        
        start[ 0] = 0;
        start[ 1] = 1;
        start[ 2] = 2;
        
        idx[0] = 0;
        idx[1] = 1;
        
        nonz[ 0] = -.06666666*2;
        nonz[ 1] = -.2*2;

        qpClpModel->loadQuadraticObjective( qpClpModel->numberColumns(), start, idx, nonz);
        
        qpClpModel->writeMps("quad.mps");
        
        
        //call solver
		//qpClpModel->primal();
        ClpCholeskyBase * cholesky = new ClpCholeskyBase();
        cholesky->setKKT(true);
        qpClpModel->setCholesky(cholesky);
        qpClpModel->primalDual();
		
        double *primal;
        double *dual;
        primal = qpClpModel->primalColumnSolution();
        dual = qpClpModel->dualRowSolution();
	
		
        int numberColumns = qpClpModel->numberColumns();
        int numberRows = qpClpModel->numberRows();
        for (i = 0; i < numberColumns; i++) {
             if (fabs(primal[i]) > 1.0e-8)
                  printf("%d primal %g\n", i, primal[i]);
        }
        for (i = 0; i < numberRows; i++) {
             if (fabs(dual[i]) > 1.0e-8)
                  printf("%d dual %g\n", i, dual[i]);
        }
	 
        
        std::cout << osinstance->printModel();
        
        
        std::cout << "NUMBR OF OBJTERMS = " << osinstance->getNumberOfQuadraticTerms() << std::endl;
        
        QuadraticTerms* quadTerms = NULL;
        
        quadTerms = osinstance->getQuadraticTerms();
        
        for(i = 0; i < osinstance->getNumberOfQuadraticTerms(); i++){
        	
        	std::cout << "Row Indexes " << quadTerms->rowIndexes[i]  << std::endl;
        	std::cout << "Var One Indexes " << quadTerms->varOneIndexes[i]  << std::endl;
        	std::cout << "Var Two Indexes " << quadTerms->varTwoIndexes[i]  << std::endl;
        	std::cout << "Coefficients " << quadTerms->coefficients[i]  << std::endl;
        	
        }
        	

        
		/******************** STEP 4 ************************
		* Give the solver the instance and options and solve
		*/	
		//solver->osinstance = osinstance;
		//solver->osoption = osoption;	
		//solver->solve();
		
		
		/******************** STEP 5 ************************
		* Create a result object and get the optimal objective
		* and primal variable values
		*/	
		//getOSResult( solver->osrl);
		
		//OSResult *osr = solver->osresult;
		//int numOfBasisVar = osr->getNumberOfBasisVar(0);
		//std::cout << "NUMBER OF BASIS VARS = " << numOfBasisVar << std::endl;
		

		
		
		//do garbage collection
		delete osilreader;
		osilreader = NULL;
		delete solver;
		solver = NULL;
		delete osoption;
		osoption = NULL;
		delete osolwriter;
		osolwriter = NULL;
		delete qpClpModel;
		qpClpModel = NULL;
		//finish garbage collection

		
		/******************** End Clp Example *************************/	
	
	
	
	delete fileUtil;
	fileUtil = NULL;	
	return 0;
	
	}
	catch(const ErrorClass& eclass){
		delete fileUtil;
		fileUtil = NULL;
		delete qpClpModel;
		qpClpModel = NULL;
		std::cout << eclass.errormsg <<  std::endl;
		return 0;
	} 

}// end main

