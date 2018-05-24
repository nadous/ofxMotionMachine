/* -------------------------------------------------------------------------------------------- */
/* 																								*/
/* 	This file is part of MotionMachine                                                          */
/* 																								*/
/* 	Motion Machine of University of MONS – Numediart Institute (N. d'Alessandro, J. Tilmanne,   */
/*  T. Ravet, M. Tits, A. Moinet, F. Grisard, P.H. Dedeken, S. Laraba) is free software: you    */
/*  can redistribute it and/or modify it under the terms of the Lesser GNU General Public       */
/*  License as published by  the Free Software Foundation, either version 3 of the License, or  */
/*  any later version.                          												*/
/* 																								*/
/* 	MotionMachine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;  */
/*  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   */
/*  See the Lesser GNU General Public License for more details. You should have received a      */
/*  copy of the GNU General Public License along with this software.                            */
/*  If not, see http://www.gnu.org/licenses/                                                    */
/*                                                                                              */
/* 	Each use of this software must be attributed to University of MONS – Numediart Institute    */
/*  (see list of authors above).                                                                */
/*                                                                                              */
/*  Any other additional authorizations may be asked to avre@umons.ac.be.                       */
/*                                                                                              */
/* 																								*/
/* 	Copyright 2015 University of Mons :															*/
/* 																								*/
/* 			Numediart Institute for Creative Technologies ( www.numediart.org )					*/
/* 																								*/
/* 																								*/
/* 	 Developed by :																				*/
/* 																								*/
/* 		Nicolas d'Alessandro, Joelle Tilmanne, Thierry Ravet, Mickael Tits, Alexis Moinet,      */
/*      Fabien Grisard, Pierre-Henri Dedeken, Sohaib Laraba                                     */
/*                                                                                              */
/* -------------------------------------------------------------------------------------------- */

/**
 *
 *  @file mmBoneList.h
 *  @brief MotionMachine header file for BoneList class.
 *  @copyright Numediart Institute, UMONS (c) 2014-2015
 *
 */

#ifndef __mmMutatedBoneList__
#define __mmMutatedBoneList__

#include <vector>
#include <map>
#include <cstring>
#include <sstream>
#include <iostream>
#include <fstream>
#include <armadillo>
#include "mmQuaternion.h"
#include "mmBoneList.h"
namespace MoMa
{
struct MutatedBoneData;
typedef std::map<std::string, MutatedBoneData> MutatedBoneMapType;
struct MutatedBoneData
{
	MutatedBoneData(){};
	MutatedBoneData(int a, int b, std::vector<int> c)
	{
		boneId = a;
		jointParent = b;
		jointChildren = c;
		visible = true;
		preScale << 1 << 1 << 1 << arma::endr;
		defaultColor = true;
		frameDelay = 0;
		trackIndex = 0;
	};
	int boneId;
	int jointParent;
	std::vector<int> jointChildren;
	std::vector<MutatedBoneMapType::iterator> boneChildrenIt;

	quaternion preRot;
	arma::vec3 preTransl;
	arma::vec3 preScale;
	arma::vec4 color;

	bool defaultColor;
	bool visible;

	int trackIndex;

	int frameDelay;
	inline MutatedBoneData &operator=(BoneData a)
	{
		(*this) = MutatedBoneData(a.boneId, a.jointParent, a.jointChildren);
		return (*this);
	}
};

class MutatedBoneList : public MutatedBoneMapType
{

  public:
	MutatedBoneList(void) : MutatedBoneMapType()
	{									   //hasOrigNodeRot_as_boneRot=true;
	}									   // Constructor
	MutatedBoneList(std::string fileName); // Create object from text file
	bool load(std::string fileName);	   // Load bones from text file
	void print(void);					   // Print the list of bones
										   //bool hasOrigNodeRot_as_boneRot;//difference between V3D BVH skel and kinect
										   // TODO add a push function
	int getParentNode(std::string boneName) { return (this->find(boneName) != this->end() ? this->at(boneName).jointParent : -1); }
	std::vector<int> getChildrenNodes(std::string boneName) { return (this->find(boneName) != this->end() ? this->at(boneName).jointChildren : std::vector<int>()); }
	std::string getParentBoneName(int NodeId);
	int getBoneId(std::string boneName) { return (this->find(boneName) != this->end() ? this->at(boneName).boneId : -1); };
	std::string getName(int boneId)
	{
		for (MutatedBoneMapType::iterator it = this->begin(); it != this->end(); it++)
			if (it->second.boneId == boneId)
				return (it->first);
		return std::string("");
	};
	void updateBoneChildrenName();
	std::vector<MutatedBoneMapType::iterator> rootIt;
};
} // namespace MoMa

#endif //__mmMutatedBoneList__
