/*
 *
 *                 #####    #####   ######  ######  ###   ###
 *               ##   ##  ##   ##  ##      ##      ## ### ##
 *              ##   ##  ##   ##  ####    ####    ##  #  ##
 *             ##   ##  ##   ##  ##      ##      ##     ##
 *            ##   ##  ##   ##  ##      ##      ##     ##
 *            #####    #####   ##      ######  ##     ##
 *
 *
 *             OOFEM : Object Oriented Finite Element Code
 *
 *               Copyright (C) 1993 - 2013   Borek Patzak
 *
 *
 *
 *       Czech Technical University, Faculty of Civil Engineering,
 *   Department of Structural Mechanics, 166 29 Prague, Czech Republic
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef htselement_h
#define htselement_h
#include "structuralelement.h"
#include "gaussintegrationrule.h"

namespace oofem {
class HTSelement : public StructuralElement
{
protected:
    int numberOfEdges;
    int numberOfGaussPoints;
    //debug
    double lambda, mu;
    double cgX,cgY;
    int numberOfStressDofs;
    int numberOfDofs;

public:
    HTSelement(int n, Domain *d);
    virtual ~HTSelement() { }

    virtual IRResultType initializeFrom(InputRecord *ir);

    virtual const char *giveClassName() const { return "HTSelement"; }
    virtual classType giveClassID() const { return HTSelementClass; }

protected:
    virtual void computeBmatrixAt(GaussPoint *gp, FloatMatrix &answer,int, int){;}
    virtual void computeNmatrixAt(GaussPoint *gp, FloatMatrix &answer){;}
    virtual void computeStiffnessMatrix(FloatMatrix &answer, MatResponseMode rMode, TimeStep *tStep);
    virtual double computeVolumeAround(GaussPoint *gp, int elemSideNumber);    
    Node* giveSideNode(int elementSideNumber, int nodeNumber);
    double  giveSideLength(int sideNumber);
    virtual int computeNumberOfDofs(EquationID ut) { return 4*numberOfEdges; }
    virtual void computeGaussPoints();
    virtual void giveDofManDofIDMask(int inode, EquationID,IntArray &) const;
    virtual StructuralElement* giveStructuralElement() { return this; }
    //jak se pocita deformace???
    virtual void computeStrainVector(FloatArray &answer, GaussPoint *gp, TimeStep *stepN){answer.resize(numberOfStressDofs);}
    //dodelat vypocet napeti!!!
    virtual void computeStressVector(FloatArray &answer, GaussPoint *gp, TimeStep *stepN){answer.resize(numberOfStressDofs);}
    //dodelat internal forces, budou potreba pro nelinearni vypocet
    virtual void giveInternalForcesVector(FloatArray &answer,TimeStep *tStep, int useUpdatedGpRecord){answer.resize(numberOfDofs);}
    virtual void computeForceLoadVector(FloatArray &answer, TimeStep *stepN, ValueModeType mode);

    void computePuVectorAt(FloatArray &answer, FloatMatrix N, FloatArray u, GaussPoint *gp,int sideNumber);
    void computePsVectorAt(FloatArray &answer, FloatArray t, GaussPoint *gp);
    void computePrescribedDisplacementLoadVectorAt(FloatArray &answer, TimeStep *stepN, ValueModeType mode);
    virtual void computeEdgeLoadVectorAt(FloatArray &answer, Load *load,int iEdge, TimeStep *tStep, ValueModeType mode);
    virtual int testElementExtension(ElementExtension ext) { return ( ext == Element_EdgeLoadSupport ); }


    void computeFMatrixAt(FloatMatrix &answer,FloatMatrix N, GaussPoint *gp, int sideNumber);
    void computeAMatrixAt(FloatMatrix &answer, FloatMatrix N,GaussPoint *gp, int sideNumber);
    void computeUvMatrixAt(FloatMatrix &answer, GaussPoint* gp, int sideNubmer);
    void computeSvMatrixAt(FloatMatrix &answer, GaussPoint* gp, int sideNumber);
    void computeUgammaMatrixAt(FloatMatrix &answer, GaussPoint* gp);
    void computeOutwardNormalMatrix(FloatMatrix &answer, int sideNumber);  


    void computeCenterOfGravity();
    virtual int giveNumberOfNodes() const { return numberOfEdges; }
    //uv functions
    void uv1(FloatArray &answer, double x, double y);
    void uv2(FloatArray &answer, double x, double y);
    void uv3(FloatArray &answer,double x, double y);
    void uv4(FloatArray &answer,double x, double y);
    void uv5(FloatArray &answer,double x, double y);
    void uv6(FloatArray &answer,double x, double y);
    void uv7(FloatArray &answer,double x, double y);
    void uv8(FloatArray &answer,double x, double y);
    void uv9(FloatArray &answer,double x, double y);
    void uv10(FloatArray &answer,double x, double y);
    void uv11(FloatArray &answer,double x, double y);
    void uv12(FloatArray &answer,double x, double y);
    void uv25_4(FloatArray &answer,double x, double y);

    //sv functions
    void sv1(FloatArray &answer,double x, double y);
    void sv2(FloatArray &answer,double x, double y);
    void sv3(FloatArray &answer,double x, double y);
    void sv4(FloatArray &answer,double x, double y);
    void sv5(FloatArray &answer,double x, double y);
    void sv6(FloatArray &answer,double x, double y);
    void sv7(FloatArray &answer,double x, double y);
    void sv8(FloatArray &answer,double x, double y);
    void sv9(FloatArray &answer,double x, double y);
    void sv10(FloatArray &answer,double x, double y);
    void sv11(FloatArray &answer,double x, double y);
    void sv12(FloatArray &answer,double x, double y);
    void sv25_4(FloatArray &answer,double x, double y);

    //u_gamma functions
    double u_gammaConst(GaussPoint *gp);
    double u_gammaLin(GaussPoint *gp);


};
} // end namespace oofem
#endif // htselement_h
