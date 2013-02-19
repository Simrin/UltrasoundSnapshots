/*=auto=========================================================================

Portions (c) Copyright 2005 Brigham and Women\"s Hospital (BWH) All Rights Reserved.

See COPYRIGHT.txt
or http://www.slicer.org/copyright/copyright.txt for details.

Program:   3D Slicer
Module:    $RCSfile: vtkMRMLSliceSnapshotCollectionNode.cxx,v $
Date:      $Date: 2006/03/17 15:10:10 $
Version:   $Revision: 1.2 $

=========================================================================auto=*/

// VTK includes
#include <vtkCommand.h>
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkPlaneSource.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkNew.h>
#include <vtkCollection.h>

// MRML includes
#include "vtkMRMLSliceSnapshotCollectionNode.h"
#include "vtkMRMLModelNode.h"
#include "vtkMRMLModelDisplayNode.h"
#include "vtkMRMLScene.h"
#include "vtkSmartPointer.h"
#include "vtkMRMLScalarVolumeNode.h"
#include "vtkMRMLTransformNode.h"
#include "vtkMRMLHierarchyNode.h"

// STD includes
#include <sstream>
#include <algorithm>

//vtkCxxSetObjectMacro(vtkMRMLSliceSnapshotCollectionNode, SnapshotCollection, vtkSliceSnapshotCollection);
//vtkCxxSetObjectMacro(vtkMRMLCameraNode, AppliedTransform, vtkMatrix4x4);
//vtkCxxSetReferenceStringMacro(vtkMRMLCameraNode, InternalActiveTag);


//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLSliceSnapshotCollectionNode);


//----------------------------------------------------------------------------
vtkMRMLSliceSnapshotCollectionNode::vtkMRMLSliceSnapshotCollectionNode()
{

  this->ModelNodeIDs.clear();
  //vtkCamera *camera = vtkCamera::New();

  this->HideFromEditors = 1;

}

//----------------------------------------------------------------------------
vtkMRMLSliceSnapshotCollectionNode::~vtkMRMLSliceSnapshotCollectionNode()
{
  this->ModelNodeIDs.clear();
}

//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::ReadXMLAttributes(const char** atts)
{
  std::cerr << "Reading SliceSnapshotCollection param node!" << std::endl;
  Superclass::ReadXMLAttributes(atts);

  // Read all MRML node attributes from two arrays of names and values
  const char* attName;
  const char* attValue;
  
  while(*atts != NULL)
  {
     attName = *(atts++);
	 attValue = *(atts++);

    if (!strcmp(attName, "modelNodeID") )
    {
      std::stringstream ss(attValue);
      while (!ss.eof())
        {
        std::string id;
        ss >> id;
        this->AddModelNodeID(id.c_str());
        }
    
     }
  }
}


//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::WriteXML(ostream& of, int nIndent)
{
  Superclass::WriteXML(of, nIndent);

  vtkIndent indent(nIndent);
  
  for (unsigned int n=0; n < this->ModelNodeIDs.size(); n++)
  {
	  if (this->ModelNodeIDs[n] != std::string(NULL))
    {
      of << indent << " ModelNodeID=\"" << this->ModelNodeIDs[n] << "\"";
    }

  }


}

//----------------------------------------------------------------------------
// Copy the node\"s attributes to this object.
// Does NOT copy: ID, FilePrefix, Name, SliceID
void vtkMRMLSliceSnapshotCollectionNode::Copy(vtkMRMLNode *anode)
{
  int disabledModify = this->StartModify(); 
  Superclass::Copy(anode);
  vtkMRMLSliceSnapshotCollectionNode *node = vtkMRMLSliceSnapshotCollectionNode::SafeDownCast(anode);
  const int ndnodes = node->GetNumberOfModelNodeIDs();
  for (int i=0; i<ndnodes; i++)
    {
    this->AddModelNodeID(node->ModelNodeIDs[i].c_str());
    }

  this->EndModify(disabledModify);
}

//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);
  
  for (unsigned int n=0; n < this->ModelNodeIDs.size(); n++)
  {
    os << indent << "ModelNode ID = " <<
      (this->ModelNodeIDs[n].c_str() ? this->ModelNodeIDs[n].c_str() : "(none)") << "\n";
    
  }

}



//-------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::AddModelNodeID(const char* modelNodeID)
{
  if (modelNodeID == 0)
    {
    return;
    }

  if (this->IsModelNodeIDPresent(modelNodeID))
    {
    return; // already exists, do nothing
    }

  this->ModelNodeIDs.push_back(std::string(modelNodeID));
  if (this->Scene)
    {
    this->Scene->AddReferencedNodeID(modelNodeID, this);
    }

  this->Modified();
}

//-------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::RemoveModelNodeID(char* modelNodeID)
{
  if (modelNodeID == NULL)
    {
    return;
    }
  std::vector< std::string > modelNodeIDs;
  for(unsigned int i=0; i<this->ModelNodeIDs.size(); i++)
    {
    if (std::string(modelNodeID) != this->ModelNodeIDs[i])
      {
      modelNodeIDs.push_back(this->ModelNodeIDs[i]);
      }
    }
  if (modelNodeIDs.size() != this->ModelNodeIDs.size())
    {
    this->Scene->RemoveReferencedNodeID(modelNodeID, this); 
    this->ModelNodeIDs = modelNodeIDs;
    this->Modified();
    }
  else
    {
    vtkErrorMacro("vtkMRMLSliceSnapshotCollectionNode::RemoveModelNodeID() id " << modelNodeID << " not found");
    }
}

//-------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::RemoveAllModelNodeIDs()
{
  for(unsigned int i=0; i<this->ModelNodeIDs.size(); i++)
    {
    this->Scene->RemoveReferencedNodeID(ModelNodeIDs[i].c_str(), this); 
    }
  this->ModelNodeIDs.clear();
  this->Modified();
}

//-------------------------------------------------------
const char* vtkMRMLSliceSnapshotCollectionNode::GetNthModelNodeID(unsigned int index)
{
  if (index >= ModelNodeIDs.size())
    {
    vtkErrorMacro("vtkMRMLSliceSnapshotCollectionNode::GetNthModelNodeID() index " << index << " outside the range 0-" << ModelNodeIDs.size()-1 );
    return NULL;
    }
  return ModelNodeIDs[index].c_str();
}

//-------------------------------------------------------
bool vtkMRMLSliceSnapshotCollectionNode::IsModelNodeIDPresent(const char* modelNodeID)const
{
  if (modelNodeID == 0)
  {
    return false;
  }
  if (this->ModelNodeIDs.empty()){
	return false;
  }
  std::string value(modelNodeID);
  std::vector< std::string >::const_iterator it =
    std::find(this->ModelNodeIDs.begin(), this->ModelNodeIDs.end(), value);
  return it != this->ModelNodeIDs.end();
}


std::vector<vtkMRMLModelNode*>& vtkMRMLSliceSnapshotCollectionNode::GetAllModelNodes()
{
  std::vector<vtkMRMLModelNode*> ModelNodes(ModelNodeIDs.size());
  if (this->GetScene() && !this->ModelNodeIDs.empty())
  {
    for(unsigned int n=0; n < ModelNodeIDs.size(); n++)
	{
	  ModelNodes[n] = vtkMRMLModelNode::SafeDownCast(this->GetScene()->GetNodeByID(this->ModelNodeIDs[n]));
	}
  }
  return ModelNodes;
}



//---------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::ProcessMRMLEvents ( vtkObject *caller,
                                           unsigned long event, 
                                           void *callData )
{
  Superclass::ProcessMRMLEvents(caller, event, callData);
/*
  vtkMRMLModelNode *dnode = this->GetModelNode();
  if (dnode != NULL && dnode == vtkMRMLModelNode::SafeDownCast(caller) &&
      event ==  vtkCommand::ModifiedEvent)
    {
    this->InvokeEvent(vtkCommand::ModifiedEvent, NULL);
    }
  return;
  */
}
/*
//---------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::SetModelIDs()
{
  const int numModels = this->GetNumberOfModelNodeIDs();
  // reset the names
  this->ModelNodeIDs.resize(numModels);

  for (int i = 0; i < numModels; ++i)
    {
#ifndef NDEBUG
    bool res =
#endif
      this->SetModelID(i);
    // There is no reason why SetNameFromColor would fail because we control
    // the array size.
    assert(res);
    }
  //this->NamesInitialisedOn();
}

//---------------------------------------------------------------------------
bool vtkMRMLColorNode::SetModelID(int index)
{
  double rgba[4];
  bool res = this->GetColor(index, rgba);
  std::stringstream ss;
  ss.precision(3);
  ss.setf(std::ios::fixed, std::ios::floatfield);
  ss << "R=";
  ss << rgba[0];
  ss << " G=";
  ss << rgba[1];
  ss << " B=";
  ss << rgba[2];
  ss << " A=";
  ss << rgba[3];
  vtkDebugMacro("SetNamesFromColors: " << index << " Name = " << ss.str().c_str());
  if (this->SetColorName(index, ss.str().c_str()) == 0)
    {
    vtkErrorMacro("SetNamesFromColors: Error setting color name " << index << " Name = " << ss.str().c_str());
    return false;
    }
  return res;
}
*/
//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::UpdateReferences()
{
  Superclass::UpdateReferences();
  std::vector< std::string > modelNodeIDs;
  for (unsigned int i=0; i < this->ModelNodeIDs.size(); i++)
    {
    if (this->Scene->GetNodeByID(this->ModelNodeIDs[i]) != NULL)
      {
      modelNodeIDs.push_back(this->ModelNodeIDs[i]);
      }    
    }
  if (this->ModelNodeIDs.size() != modelNodeIDs.size())
    {
    modelNodeIDs = this->ModelNodeIDs;
    this->Modified();
    }

}

//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::UpdateReferenceID(const char *oldID, const char *newID)
{
  Superclass::UpdateReferenceID(oldID, newID);
  bool modified = false;
  for (unsigned int i=0; i<this->ModelNodeIDs.size(); i++)
  {
    if ( std::string(oldID) == this->ModelNodeIDs[i])
    {
      this->ModelNodeIDs[i] =  std::string(newID);
      modified = true;
	}
  }
  if (modified)
  {
    this->Modified();
  }

}

//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::UpdateScene(vtkMRMLScene *scene)
{
  Superclass::UpdateScene(scene);
}

// End
