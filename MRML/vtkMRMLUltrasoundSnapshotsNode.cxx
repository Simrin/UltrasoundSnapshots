/*=auto=========================================================================

Portions (c) Copyright 2005 Brigham and Women\"s Hospital (BWH) All Rights Reserved.

See COPYRIGHT.txt
or http://www.slicer.org/copyright/copyright.txt for details.

Program:   3D Slicer
Module:    $RCSfile: vtkMRMLUltrasoundSnapshotsNode.cxx,v $
Date:      $Date: 2006/03/17 15:10:10 $
Version:   $Revision: 1.2 $

=========================================================================auto=*/

// VTK includes
#include <vtkCommand.h>
#include <vtkObjectFactory.h>
#include <vtkSmartPointer.h>

// MRML includes
#include "vtkMRMLUltrasoundSnapshotsNode.h"
#include "vtkMRMLSnapshotNode.h"
#include "vtkMRMLScene.h"
#include "vtkSmartPointer.h"


//----------------------------------------------------------------------------
//vtkMRMLNodeNewMacro(vtkMRMLUltrasoundSnapshotsNode);

//----------------------------------------------------------------------------
vtkMRMLUltrasoundSnapshotsNode* vtkMRMLUltrasoundSnapshotsNode::New()
{
  vtkObject* ret = vtkObjectFactory::CreateInstance("vtkMRMLUltrasoundSnapshotsNode");
  if(ret)
  {
    return(vtkMRMLUltrasoundSnapshotsNode*)ret;
  }
  return new vtkMRMLUltrasoundSnapshotsNode;
}

vtkMRMLNode* vtkMRMLUltrasoundSnapshotsNode::CreateNodeInstance()
{
  vtkObject* ret = vtkObjectFactory::CreateInstance("vtkMRMLUltrasoundSnapshotsNode");
  if(ret)
  {
    return(vtkMRMLUltrasoundSnapshotsNode*)ret;
  }
  return new vtkMRMLUltrasoundSnapshotsNode;
}
//----------------------------------------------------------------------------
vtkMRMLUltrasoundSnapshotsNode::vtkMRMLUltrasoundSnapshotsNode()
{
  this->SnapshotNodeRef = NULL;
  this->HideFromEditors = 1;

}

//----------------------------------------------------------------------------
vtkMRMLUltrasoundSnapshotsNode::~vtkMRMLUltrasoundSnapshotsNode()
{
  this->SetSnapshotNodeRef(NULL);
}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsNode::ReadXMLAttributes(const char** atts)
{
  std::cerr << "Reading UltrasoundSnapshots param node!" << std::endl;
  Superclass::ReadXMLAttributes(atts);

  // Read all MRML node attributes from two arrays of names and values
  const char* attName;
  const char* attValue;
  
  while(*atts != NULL)
  {
     attName = *(atts++);
	 attValue = *(atts++);

	 if(!strcmp(attName, "SnapshotNodeRef"))
	 {
	   this->SetSnapshotNodeRef(attValue);
	 }
  }

  //this->WriteXML(std::cout,1);
}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsNode::WriteXML(ostream& of, int nIndent)
{
  Superclass::WriteXML(of, nIndent);

  vtkIndent indent(nIndent);
  
  if (this->SnapshotNodeRef != NULL)
  {
     of << indent << " SnapshotNodeRef=\"" << this->SnapshotNodeRef << "\"";
  }

}

//----------------------------------------------------------------------------
// Copy the node\"s attributes to this object.
// Does NOT copy: ID, FilePrefix, Name, SliceID
void vtkMRMLUltrasoundSnapshotsNode::Copy(vtkMRMLNode *anode)
{
  Superclass::Copy(anode);
  vtkMRMLUltrasoundSnapshotsNode *node = vtkMRMLUltrasoundSnapshotsNode::SafeDownCast(anode);
  this->SetSnapshotNodeRef(node->SnapshotNodeRef);
  //this->DisableModifiedEventOn();


}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);

  os << indent << "SnapshotNodeRef: " <<
	  (this->SnapshotNodeRef ? this->SnapshotNodeRef: "(none)") << "\n";

}

//----------------------------------------------------------------------------

vtkMRMLSnapshotNode *vtkMRMLUltrasoundSnapshotsNode::GetSnapshotNode()
{
  
  if (this->GetScene() && this->SnapshotNodeRef != NULL )
  {
	  //return vtkMRMLSnapshotNode::SafeDownCast(this->GetScene()->GetNodeByID(this->SnapshotNodeRef));
  }
  
  return NULL;
  
}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsNode::UpdateReferences()
{
  Superclass::UpdateReferences();
  
  if (this->SnapshotNodeRef != NULL && this->Scene->GetNodeByID(this->SnapshotNodeRef) == NULL)
  {
    this->SetSnapshotNodeRef(NULL);
  }
}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsNode::UpdateReferenceID(const char *oldID, const char *newID)
{
  Superclass::UpdateReferenceID(oldID, newID);

  if (this->SnapshotNodeRef && !strcmp(oldID, this->SnapshotNodeRef))
  {
    this->SetSnapshotNodeRef(newID);
  }
}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsNode::UpdateScene(vtkMRMLScene *scene)
{
  Superclass::UpdateScene(scene);
}

// End
