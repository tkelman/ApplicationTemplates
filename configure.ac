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
#                              COIN components                              #
#############################################################################

AC_COIN_HAS_PROJECT(OS)
AC_COIN_HAS_PROJECT(Bcp)
AC_COIN_HAS_PROJECT(CoinUtils)
AC_COIN_HAS_PROJECT(Osi)
AC_COIN_HAS_PROJECT(Clp)
AC_COIN_HAS_PROJECT(Cbc)
AC_COIN_HAS_PROJECT(Cgl)
AC_COIN_HAS_PROJECT(SYMPHONY)
AC_COIN_HAS_PROJECT(DyLP)
AC_COIN_HAS_PROJECT(Vol)
AC_COIN_HAS_PROJECT(Ipopt)
AC_COIN_HAS_PROJECT(Couenne)
AC_COIN_HAS_PROJECT(Bonmin)
AC_COIN_HAS_PROJECT(cppad)
AC_COIN_HAS_PROJECT(GamsUtils)
AC_COIN_HAS_PROJECT(OS)


AC_ARG_WITH([boncouenne],
            AC_HELP_STRING([--with-boncouenne],
                           [Compile Bonmin with Couenne parallel version]),
            [use_couenne="$withval"], [use_couenne=no])
if test "$use_couenne" = yes; then
  if test $m4_tolower(coin_has_$1) = unavailable ||
     test $m4_tolower(coin_has_$1) = skipping; then
     AC_MSG_ERROR([You specified --with-boncouenne, but Couenne is not available])
  fi
fi
AM_CONDITIONAL(COMPILE_BONCOUENNE, test "$use_couenne" = yes)
  




if test $coin_has_cppad = skipping &&
   test $coin_has_ipopt != skipping ; then
       AC_MSG_ERROR([Ipopt is present, but not the necessary cppad])   
fi

if test $coin_has_ipopt = skipping &&
   test $coin_has_bonmin != skipping ; then
       AC_MSG_ERROR([Bonmin is present, but not the necessary Ipopt])   
fi

if test $coin_has_bonmin = skipping &&
   test $coin_has_couenne != skipping ; then
       AC_MSG_ERROR([Couenne is present, but not the necessary Bonmin])   
fi



if test $coin_has_coinutils != unavailable &&
   test $coin_has_coinutils != skipping; then
  case $CXX in
    cl*)
       coinutilslib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libCoinUtils.lib';;
     *)
       coinutilslib="-L\$(INSTALLIBDIR) -lCoinUtils";;
  esac
  AC_SUBST(coinutilslib) 
  else
    AC_MSG_ERROR([cannot find CoinTuils which is necessary to build OS])   
fi

if test $coin_has_clp != unavailable &&
   test $coin_has_clp != skipping; then
  case $CXX in
    cl*)
       clplib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libClp.lib'
       osiclplib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libOsiClp.lib';;
     *)
       clplib="-L\$(INSTALLIBDIR) -lClp"
       osiclplib="-L\$(INSTALLIBDIR) -lOsiClp";;
  esac
  AC_SUBST(clplib)
  AC_SUBST(osiclplib) 
  else
    AC_MSG_ERROR([cannot find Clp which is necessary to build OS])   
fi

if test $coin_has_cbc != unavailable &&
   test $coin_has_cbc != skipping; then
  case $CXX in
    cl*)
       cbclib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libCbcSolver.lib    `$(CYGPATH_W) $(INSTALLIBDIR)`\\libCbc.lib'
       osicbclib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libOsiCbc.lib';;
     *)
       cbclib="-L\$(INSTALLIBDIR) -lCbcSolver -lCbc"
       osicbclib="-L\$(INSTALLIBDIR) -lOsiCbc";;
  esac
  AC_SUBST(cbclib) 
  AC_SUBST(osicbclib)
  else
    AC_MSG_ERROR([cannot find Cbc which is necessary to build OS])   
fi 


if test $coin_has_cgl != unavailable &&
   test $coin_has_cgl != skipping; then
  case $CXX in
    cl*)
       cgllib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libCgl.lib';;
     *)
       cgllib="-L\$(INSTALLIBDIR) -lCgl";;
  esac
  AC_SUBST(cgllib) 
  else
    AC_MSG_ERROR([cannot find Cgl which is necessary to build OS])   
fi





if test $coin_has_osi != unavailable &&
   test $coin_has_osi != skipping; then
  case $CXX in
    cl*)
       osilib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libOsi.lib';;
     *)
       osilib="-L\$(INSTALLIBDIR) -lOsi";;
  esac
  AC_SUBST(osilib) 
  else
    AC_MSG_ERROR([cannot find Osi which is necessary to build OS])   
fi


if test $coin_has_dylp != unavailable &&
   test $coin_has_dylp != skipping; then
  case $CXX in
    cl*)
       osiglpklib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libOsiGlpk.lib';;
     *)
       osiglpklib="-L\$(INSTALLIBDIR) -lOsiGlpk";;
  esac
  AC_SUBST(osiglpklib) 
fi





if test $coin_has_dylp != unavailable &&
   test $coin_has_dylp != skipping; then
  case $CXX in
    cl*)
       dylplib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libDylp.lib'
       osidylplib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libOsiDylp.lib';;
     *)
       dylplib="-L\$(INSTALLIBDIR) -lDylp"
       osidylplib="-L\$(INSTALLIBDIR) -lOsiDylp";;
  esac
  AC_SUBST(dylplib) 
  AC_SUBST(osidylplib) 
fi


if test $coin_has_vol != unavailable &&
   test $coin_has_vol != skipping; then
  case $CXX in
    cl*)
       vollib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libVol.lib'
       osivollib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libOsiVol.lib';;
     *)
       vollib="-L\$(INSTALLIBDIR) -lVol"
       osivollib="-L\$(INSTALLIBDIR) -lOsiVol";;
  esac
  AC_SUBST(vollib) 
  AC_SUBST(osivollib) 
fi


if test $coin_has_bcp != unavailable &&
   test $coin_has_bcp != skipping; then
  case $CXX in
    cl*)
       bcplib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libbcp.lib';;
     *)
       bcplib="-L\$(INSTALLIBDIR) -lBcp";;
  esac
  AC_SUBST(bcplib)
fi




if test $coin_has_symphony != unavailable &&
   test $coin_has_symphony != skipping; then
  case $CXX in
    cl*)
       symphonylib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libSym.lib'
       osisymphonylib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libOsiSym.lib';;
     *)
       symphonylib="-L\$(INSTALLIBDIR) -lSym"
       osisymphonylib="-L\$(INSTALLIBDIR) -lOsiSym";;
  esac
  AC_SUBST(symphonylib) 
  AC_SUBST(osisymphonylib)  
fi

if test $coin_has_ipopt != unavailable &&
   test $coin_has_ipopt != skipping; then
  case $CXX in
    cl*)
       ipoptlib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libipopt.lib';;
    xl*)
       AC_DEFINE([XLC_],[1],[use if XLC is the compiler]);;
     *)
       ipoptlib="-L\$(INSTALLIBDIR) -lipopt";;
  esac
  AC_SUBST(ipoptlib)  
fi


if test $coin_has_couenne != unavailable &&
   test $coin_has_couenne != skipping; then
  case $CXX in
    cl*)
       couennelib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libboncouenne.lib  `$(CYGPATH_W) $(INSTALLIBDIR)`\\libcouennereadnl.lib   `$(CYGPATH_W) $(INSTALLIBDIR)`\\libcouenne.lib        ';;
     *)
       couennelib="-L\$(INSTALLIBDIR) -lBonCouenne -lCouenneReadnl -lCouenne ";;
  esac
  AC_SUBST(couennelib)  
fi


if test $coin_has_bonmin != unavailable &&
   test $coin_has_bonmin != skipping; then
  case $CXX in
    cl*)
       bonminlib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libbonmin.lib';;
     *)
       bonminlib="-L\$(INSTALLIBDIR) -lbonminampl -lbonmin";;
  esac
  AC_SUBST(bonminlib)  
fi


if test $coin_has_os != unavailable &&
   test $coin_has_os != skipping; then
  case $CXX in
    cl*)
       oslib='`$(CYGPATH_W) $(INSTALLIBDIR)`\\libos.lib';;
     *)
       oslib="-L\$(INSTALLIBDIR) -lOS";;
  esac
  AC_SUBST(oslib)
fi



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


     if test $enable_static != yes; then
         USE_ASL_LIB=$ASLLIB
     fi

AC_SUBST(USE_ASL_LIB)

AC_COIN_HAS_ASL

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
AC_COIN_VPATH_LINK(osDip/own.sty)
AC_COIN_VPATH_LINK(osDip/osDip.tex)
AC_COIN_VPATH_LINK(osDip/osDip.pdf)

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
AC_COIN_VPATH_LINK(data/CoinOS.opt)
AC_COIN_VPATH_LINK(data/CppADTestLag.osil)
AC_COIN_VPATH_LINK(data/bonminEx1.nl)
AC_COIN_VPATH_LINK(data/eastborne.gms)
AC_COIN_VPATH_LINK(data/eastborne.mod)
AC_COIN_VPATH_LINK(data/eastborne.nl)
AC_COIN_VPATH_LINK(data/eastborne.osil)
AC_COIN_VPATH_LINK(data/knock.ospl)
AC_COIN_VPATH_LINK(data/nonconvex.osil)
AC_COIN_VPATH_LINK(data/p0033.osil)
AC_COIN_VPATH_LINK(data/parinc.mps)
AC_COIN_VPATH_LINK(data/parincLinear.osil)
AC_COIN_VPATH_LINK(data/rosenbrockmod.osil)
AC_COIN_VPATH_LINK(data/sendWithJobID.osol)
AC_COIN_VPATH_LINK(data/wayneQuadratic.osil)

AC_COIN_VPATH_LINK(data/spl1.osil)
AC_COIN_VPATH_LINK(data/spl2.osil)
AC_COIN_VPATH_LINK(data/spl3.osil)
AC_COIN_VPATH_LINK(data/genAssign.osil)
AC_COIN_VPATH_LINK(data/smallIPBook.osil)

AC_COIN_VPATH_LINK(data/spl1.osol)
AC_COIN_VPATH_LINK(data/spl1-b.osol)
AC_COIN_VPATH_LINK(data/spl2.osol)
AC_COIN_VPATH_LINK(data/spl3.osol)
AC_COIN_VPATH_LINK(data/spl2-b.osol)
AC_COIN_VPATH_LINK(data/genAssign.osol)
AC_COIN_VPATH_LINK(data/smallIPBook.osol)


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

AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/algorithmicDiff.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/branchCutPrice.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/cglCuts.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/instanceGenerator.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/osModificationDemo.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/osRemoteTest.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/osResultDemo.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/osSolverDemo.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/template.vcproj)
AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/VISUALSTUDIOREADME.txt)
AC_COIN_VPATH_LINK(MSVisualStudioOSExamples/osExamples.sln)

##############################################################################
#                   Finishing up by writing all the output                   #
##############################################################################

# Here list all the files that configure should create (except for the
# configuration header file)
AC_CONFIG_FILES([Makefile
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



