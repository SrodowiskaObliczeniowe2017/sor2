#include "ApproxSTDhybrid.h"
#include "../include/external_utils.h"
//#include "../include/fv_compiler.h"
#include <memory>

#ifdef FV_DEBUG
#include<iostream>
using namespace std;
#endif

using namespace Approx;

namespace ApproximationSTDh {

class ApproximatorSTDhybrid : public IApproximator {
public:
	ApproximatorSTDhybrid(){
	#ifdef FV_DEBUG
		std::cout << "Constructor: ApproximatorSTDhybrid" << std::endl;
		std::cout.flush();
	#endif

	}
	~ApproximatorSTDhybrid(){
	#ifdef FV_DEBUG
		std::cout << "Destructor: ApproximatorSTDhybrid" << std::endl;
		std::cout.flush();
	#endif
	}

	//apr_init_field(APC_READ,Mesh_id,-1,-1,101,const_cast<char*>(Filename),NULL);
	#include "../include/interface.inl"
	int create_constr_data(int Field_id)
	{
		return apr_create_constr_data(Field_id);
	}

	double apr_elem_calc(
		/* returns: Jacobian determinant at a point, either for */
		/* 	volume integration if Vec_norm==NULL,  */
		/* 	or for surface integration otherwise */
		int Control,/* in: control parameter (what to compute): */
					/*	1  - shape functions and values */
					/*	2  - derivatives and jacobian */
					/* 	>2 - computations on the (Control-2)-th */
					/*	     element's face */
		int Nreq,	    /* in: number of equations */
		int *Pdeg_vec,	    /* in: element degree of polynomial */
		int Base_type,	    /* in: type of basis functions: */
					/* 	1 (APC_TENSOR) - tensor product */
					/* 	2 (APC_COMPLETE) - complete polynomials */
		double *Eta,	    /* in: local coordinates of the input point */
		double *Node_coor,  /* in: array of coordinates of vertices of element */
		double *Sol_dofs,   /* in: array of element' dofs */
		double *Base_phi,   /* out: basis functions */
		double *Base_dphix, /* out: x-derivatives of basis functions */
		double *Base_dphiy, /* out: y-derivatives of basis functions */
		double *Base_dphiz, /* out: z-derivatives of basis functions */
		double *Xcoor,	    /* out: global coordinates of the point*/
		double *Sol,        /* out: solution at the point */
		double *Dsolx,      /* out: derivatives of solution at the point */
		double *Dsoly,      /* out: derivatives of solution at the point */
		double *Dsolz,      /* out: derivatives of solution at the point */
		double *Vec_nor     /* out: outward unit vector normal to the face */
	)
	{
		return apr_elem_calc_3D(Control,Nreq,Pdeg_vec,Base_type,Eta,Node_coor,
			Sol_dofs,Base_phi,Base_dphix,Base_dphiy,Base_dphiz,Xcoor,Sol,
			Dsolx,Dsoly,Dsolz,Vec_nor);
	}
};

class ApproxSTDhybrid : public ApproxServer::ApproxEngin {
public:
	ApproximatorSTDhybrid * Self;
	// Conmstructo
	DLL_MAPPING ApproxSTDhybrid() : Self(0) {}
	// Destructor
	DLL_MAPPING virtual ~ApproxSTDhybrid() { 

		if( Self) delete Self;
		Self = NULL;

	#ifdef _DEBUG
		std::cout << "Destrucktor ApproxSTDhybrid" << std::endl;
		std::cout.flush();
	#endif
	}

	// Get the name of the libray
	DLL_MAPPING virtual const std::string& GetName() const {
		static const std::string sName(stdhDllName);
		return sName;
	}

	DLL_MAPPING IApproximator * CreateApproximator() {
		Self = new ApproximatorSTDhybrid();
		return Self;
		//return auto_ptr<IApproximator>(new ApproximatorSTD());
	}

	DLL_MAPPING IApproximator* GetApproximator() {
		if( ! Self )  {
		#ifdef _DEBUG
			cout << "Creating new Approximator\n";
		#endif
			return CreateApproximator();
		}
		return Self;
	}



};

extern "C" DLL_MAPPING int GetEnginVersion() {
	return 1;
}

extern "C" DLL_MAPPING void RegisterPlugin(ApproxManager& AM) {
	AM.GetApproxServer().AddApproxModule(
		std::auto_ptr<ApproxServer::ApproxEngin>(new ApproxSTDhybrid()));
}


} // end namespace ApproximationSTDh
