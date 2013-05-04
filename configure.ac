# Copyright (C) 2006 International Business Machines.
# All Rights Reserved.
# This file is distributed under the Common Public License.

## $Id: configure.ac 786 2006-06-01 04:10:46Z andreasw $

# Author:  Andreas Waechter            IBM    2006-04-13

#############################################################################
#                       Names and other basic things                        #
#############################################################################

AC_PREREQ(2.59)

AC_INIT([examples],[1.0],[])

AC_COPYRIGHT([
Copyright 2006 International Business Machines and others.
All Rights Reserved.
This file is part of the open source package Coin which is distributed
under the Common Public License.])

# List one file in the package so that the configure script can test
# whether the package is actually there
AC_CONFIG_SRCDIR(osSolverDemo/OSSolverDemo.cpp)

# Where should everything be installed by default?  Here, we want it
# to be installed directly in 'bin', 'lib', 'include' subdirectories
# of the directory where configure is run.  The default would be
# /usr/local.
AC_PREFIX_DEFAULT([`pwd`])

#############################################################################
#                         Standard build tool stuff                         #
#############################################################################
# Get the system type
AC_CANONICAL_BUILD

# Initialise ADDLIBS and FADDLIBS
AC_COIN_PROJECTDIR_INIT

LIBS_without_ADDLIBS="$LIBS"






# Check if user wants to produce debugging code
AC_COIN_DEBUG_COMPILE(examples)

# Get the name of the C++ compiler and appropriate compiler options
coin_opt_cxxflags="-O3"
AC_COIN_PROG_CXX

# Check if we have a Fortran compiler; if we do, acquire the appropriate
# options. This has to be done before we call AC_COIN_INIT_AUTO_TOOLS, else
# it will helpfully set FFLAGS to an incorrect value.
AC_COIN_FIND_F77
if test "$F77" != unavailable ; then
  AC_COIN_PROG_F77
  AC_COIN_F77_WRAPPERS
fi

# Initialize automake and libtool
AC_COIN_INIT_AUTO_TOOLS

# And determine whether we're big-endian or little-endian. This is necessary to
# define the correct patterns for IEEE infinity and quiet_nan, in the event
# that we can't get them any other way. This will define WORDS_BIGENDIAN if
# we're on a big-endian machine, and do nothing otherwise. Also necessary for
# the David Gay dtoa

AC_C_BIGENDIAN

# We also need to worry about long long 
# if -pedantic used for OSdtoa then we crash without
# the following was added to autoconf 2.60 -- put in when build tools switches over
# this will define HAVE_LONG_LONG_INT
#AC_TYPE_LONG_LONG_INT 
#for now assume C++
#AC_DEFINE([SIZEOF_LONG_LONG],[0],[in C++ make sure SIZEOF_LONG_LONG is less than 8])
#KIPP deal with the above

AC_LANG_PUSH( C++)



# the following does not work for cached variables
#AC_CHECK_SIZEOF( long long)
AC_CHECK_SIZEOF( int)
AC_CHECK_SIZEOF( double)
AC_CHECK_SIZEOF( long)









#############################################################################
#                             Need to know if we have MS cl                           #
#############################################################################
case $CXX in
    cl*)
    cl_compiler=yes  ;;
esac

AM_CONDITIONAL(MSCL_, test x$cl_compiler = xyes)





#############################################################################
#                         OS-specific configuration                         #
#############################################################################


  case $build in
     *-mingw*)
         AC_DEFINE([WIN_],[1],[use if OS is Windows]) ;;
      *-cygwin*)
         AC_DEFINE([WIN_],[1],[use if OS is Windows])
		   case $CXX in
		    g*)
		      AC_DEFINE([USE_OLD_UNISTD],[1],[use if OS is Cygwin and complier is gnu]);;
		     *)
		     AC_MSG_WARN("DONT HAVE GCC COMPILER WITH GYGWIN");;   
		  esac   
		  AC_DEFINE([NOMINMAX],[1],[use if OS is Cygwin]);;
       *-win*)
         AC_DEFINE([WIN_],[1],[use if OS is Windows]) ;;
    *-linux-*)
	 ;;
    *-darwin*)
        AC_DEFINE([MACOSX_],[1],[use if OS is MACOSX])
        mac_osx=yes ;;
    *-ibm-*)
         ;;
    *-hp-*)
         ;;
    *-sun-*)
	 ;;
    *)
	 ;;
  esac



#############################################################################
# Define the root of the examples project###
#############################################################################

AC_SUBST(EXAMPLESROOT_DIR)
EXAMPLESROOT_DIR=`pwd`
AC_DEFINE_UNQUOTED([EXAMPLESROOT_DIR], ["$EXAMPLESROOT_DIR"],
    [Define the path to the examples root])


#############################################################################
#  See if we are disabling shared libs###
#############################################################################


#     if test $enable_static != yes; then
#         USE_ASL_LIB=$ASLLIB
#     fi
#
#AC_SUBST(USE_ASL_LIB)

#AC_COIN_HAS_ASL

##############################################################################
#                   VPATH links for example C++ source-code files                      #
##############################################################################

#AC_PROG_LN_S
#For this project we want hard links
LN_S='ln'
AC_COIN_CHECK_VPATH

# In case this is a VPATH configuration we need to make sure that the
# input files for the examples are available in the VPATH directory.
#### EXAMPLE SOURCE CODE
AC_COIN_VPATH_LINK(osSolverDemo/OSSolverDemo.cpp)

AC_COIN_VPATH_LINK(cglCuts/OSCglCuts.cpp)

AC_COIN_VPATH_LINK(cglCuts/OSCglCuts.cpp)

AC_COIN_VPATH_LINK(algorithmicDiff/OSAlgorithmicDiffTest.cpp)

AC_COIN_VPATH_LINK(instanceGenerator/OSInstanceGenerator.cpp)

AC_COIN_VPATH_LINK(osModificationDemo/OSModificationDemo.cpp)

AC_COIN_VPATH_LINK(instanceGenerator/OSInstanceGenerator.cpp)

AC_COIN_VPATH_LINK(osRemoteTest/OSRemoteTest.cpp)

AC_COIN_VPATH_LINK(osResultDemo/OSResultDemo.cpp)

AC_COIN_VPATH_LINK(template/template.cpp)

AC_COIN_VPATH_LINK(osDip/OSDip_Main.cpp)
AC_COIN_VPATH_LINK(osDip/OSDipApp.cpp)
AC_COIN_VPATH_LINK(osDip/OSDipApp.h)
AC_COIN_VPATH_LINK(osDip/OSDipBlockSolver.cpp)
AC_COIN_VPATH_LINK(osDip/OSDipBlockSolver.h)
AC_COIN_VPATH_LINK(osDip/OSDipFactoryInitializer.h)
AC_COIN_VPATH_LINK(osDip/OSDipBlockSolverFactory.h)
AC_COIN_VPATH_LINK(osDip/OSDipBlockSolverFactory.cpp)
AC_COIN_VPATH_LINK(osDip/OSDipInterface.cpp)
AC_COIN_VPATH_LINK(osDip/OSDipInterface.h)
AC_COIN_VPATH_LINK(osDip/OSDipParam.h)



AC_COIN_VPATH_LINK(osDip/solvers/OSDipBlockCoinSolver.cpp)
AC_COIN_VPATH_LINK(osDip/solvers/OSDipBlockCoinSolver.h)
AC_COIN_VPATH_LINK(osDip/solvers/OSDipBlockSlpSolver.cpp)
AC_COIN_VPATH_LINK(osDip/solvers/OSDipBlockSlpSolver.h)
AC_COIN_VPATH_LINK(osDip/solvers/OSDipBlockBearcatSolver.cpp)
AC_COIN_VPATH_LINK(osDip/solvers/OSDipBlockBearcatSolver.h)


##############################################################################
#                  The Bcp Files                     #
##############################################################################



AC_COIN_COPY_FROM_FILELIST(branchCutPrice, branchCutPrice/examplefiles.txt)

# In case this is a VPATH configuration we need to make sure that the
# input files for the examples are available in the VPATH directory.


##############################################################################
#                   Copy over the examples                                   #
##############################################################################

AC_DEFUN([AC_COPY_FROM_FILE], 
[
	if test -f $2 ; then 
		AC_MSG_CHECKING(Creating target dir $1)
	    mkdir -p $1
		cd $1
		for f in `cat $srcdir/$2` ; do
			if test ! -e $srcdir/`dirname $2`/$f ; then
			    mkdir -p `dirname $f`
			    $LN_S $srcdir/`dirname $2`/$f $f
			fi
		done
	fi
])


##############################################################################
#                   VPATH links for example data files                      #
##############################################################################
#### EXAMPLE DATA FILES

#### AMPL FILES
AC_COIN_VPATH_LINK(data/amplFiles/bonminEx1.nl)
AC_COIN_VPATH_LINK(data/amplFiles/eastborne.mod)
AC_COIN_VPATH_LINK(data/amplFiles/eastborne.nl)


##### CONFIG FILES

AC_COIN_VPATH_LINK(data/configFiles/kill.config)
AC_COIN_VPATH_LINK(data/configFiles/testLocal.config)
AC_COIN_VPATH_LINK(data/configFiles/testcalclp.config)
AC_COIN_VPATH_LINK(data/configFiles/testRemote.config)
AC_COIN_VPATH_LINK(data/configFiles/testRemoteKnock.config)
AC_COIN_VPATH_LINK(data/configFiles/testRemoteRetrieve.config)
AC_COIN_VPATH_LINK(data/configFiles/testRemoteSend.config)

##### DIP FILES
AC_COIN_VPATH_LINK(data/dipFiles/spl1.osil)
AC_COIN_VPATH_LINK(data/dipFiles/spl2.osil)
AC_COIN_VPATH_LINK(data/dipFiles/spl3.osil)
AC_COIN_VPATH_LINK(data/dipFiles/genAssign.osil)
AC_COIN_VPATH_LINK(data/dipFiles/smallIPBook.osil)
AC_COIN_VPATH_LINK(data/dipFiles/spl1.osol)
AC_COIN_VPATH_LINK(data/dipFiles/spl1-b.osol)
AC_COIN_VPATH_LINK(data/dipFiles/spl2.osol)
AC_COIN_VPATH_LINK(data/dipFiles/spl3.osol)
AC_COIN_VPATH_LINK(data/dipFiles/spl2-b.osol)
AC_COIN_VPATH_LINK(data/dipFiles/genAssign.osol)
AC_COIN_VPATH_LINK(data/dipFiles/smallIPBook.osol)

#####GAMS Files
AC_COIN_VPATH_LINK(data/gamsFiles/eastborne.gms)
AC_COIN_VPATH_LINK(data/gamsFiles/CoinOS.opt)

#####MATLAB Files
AC_COIN_VPATH_LINK(data/matlabFiles/osdip.parm)

#####MPS FILES
AC_COIN_VPATH_LINK(data/mps/parinc.mps)

##### OSIL FILES
AC_COIN_VPATH_LINK(data/osilFiles/CppADTestLag.osil)
AC_COIN_VPATH_LINK(data/osilFiles/eastborne.osil)
AC_COIN_VPATH_LINK(data/osilFiles/nonconvex.osil)
AC_COIN_VPATH_LINK(data/osilFiles/p0033.osil)
AC_COIN_VPATH_LINK(data/osilFiles/parincLinear.osil)
AC_COIN_VPATH_LINK(data/osilFiles/parincQuadratic.osil)
AC_COIN_VPATH_LINK(data/osilFiles/rosenbrockmod.osil)
AC_COIN_VPATH_LINK(data/osilFiles/wayneQuadratic.osil)

##### OSOL FILES
AC_COIN_VPATH_LINK(data/kill.osol)
AC_COIN_VPATH_LINK(data/parsertest.osol)
AC_COIN_VPATH_LINK(data/remoteSolve1.osol)
AC_COIN_VPATH_LINK(data/remoteSolve2.osol)
AC_COIN_VPATH_LINK(data/retrieve.osol)
AC_COIN_VPATH_LINK(data/sendWithJobID.osol)
AC_COIN_VPATH_LINK(data/solveroptions.osol)


##### OSPL FILES
AC_COIN_VPATH_LINK(data/osplFiles/knock.ospl)
AC_COIN_VPATH_LINK(data/osplFiles/demo.ospl)
AC_COIN_VPATH_LINK(data/osplFiles/result.ospl)












##############################################################################
#                   VPATH links for Excel files                              #
##############################################################################
AC_COIN_VPATH_LINK(Excel/OSWebServiceGUI.xlsm)
AC_COIN_VPATH_LINK(Excel/clsws_OSSolverServiceServic.cls)
AC_COIN_VPATH_LINK(Excel/parIncVBA.xlsm)
AC_COIN_VPATH_LINK(Excel/clsOSInstance.cls)


##############################################################################
#                   VPATH links for other files                              #
##############################################################################
AC_COIN_VPATH_LINK(AUTHORS)
AC_COIN_VPATH_LINK(README)


##############################################################################
#                   VPATH links for example Visual Studio project files      #
##############################################################################

AC_COIN_VPATH_LINK(MSVisualStudio-v9/algorithmicDiff/algorithmicDiff.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/algorithmicDiff/algorithmicDiff.vcproj.user)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/branchCutPrice/branchCutPrice.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/branchCutPrice/branchCutPrice.vcproj.user)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/cglCuts/cglCuts.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/cglCuts/cglCuts.vcproj.user)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/instanceGenerator/instanceGenerator.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/instanceGenerator/instanceGenerator.vcproj.user)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osDip/osDip.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osDip/osDip.vcproj.user)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osModificationDemo/osModificationDemo.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osModificationDemo/osModificationDemo.vcproj.user)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osRemoteTest/osRemoteTest.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osRemoteTest/osRemoteTest.vcproj.user)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osResultDemo/osResultDemo.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osResultDemo/osResultDemo.vcproj.user)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osSolverDemo/osSolverDemo.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osSolverDemo/osSolverDemo.vcproj.user)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/template/template.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/template/template.vcproj.user)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/VISUALSTUDIOREADME.txt)
AC_COIN_VPATH_LINK(MSVisualStudio-v9/osExamples.sln)

##############################################################################
#                   Finishing up by writing all the output                   #
##############################################################################

# Here list all the files that configure should create (except for the
# configuration header file)
AC_CONFIG_FILES([Makefile
  Makefile.Examples
  osDip/Makefile
  osDip/osdip.parm
  algorithmicDiff/Makefile
  instanceGenerator/Makefile
  cglCuts/Makefile
  osModificationDemo/Makefile
  osRemoteTest/Makefile
  osSolverDemo/Makefile
  osResultDemo/Makefile
  template/Makefile
  branchCutPrice/Makefile])

          


# Finally, we let configure write all the output...
AC_COIN_FINALIZE



