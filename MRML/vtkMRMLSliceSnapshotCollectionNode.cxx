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

// MRML includes
#include "vtkMRMLSliceSnapshotCollectionNode.h"
#include "vtkMRMLModelNode.h"
#include "vtkMRMLModelDisplayNode.h"
#include "vtkMRMLScene.h"
#include "vtkSmartPointer.h"


//----------------------------------------------------------------------------
//vtkMRMLNodeNewMacro(vtkMRMLSliceSnapshotCollectionNode);

//----------------------------------------------------------------------------
vtkMRMLSliceSnapshotCollectionNode* vtkMRMLSliceSnapshotCollectionNode::New()
{
  vtkObject* ret = vtkObjectFactory::CreateInstance("vtkMRMLSliceSnapshotCollectionNode");
  if(ret)
  {
    return(vtkMRMLSliceSnapshotCollectionNode*)ret;
  }
  return new vtkMRMLSliceSnapshotCollectionNode;
}

vtkMRMLNode* vtkMRMLSliceSnapshotCollectionNode::CreateNodeInstance()
{
  vtkObject* ret = vtkObjectFactory::CreateInstance("vtkMRMLSliceSnapshotCollectionNode");
  if(ret)
  {
    return(vtkMRMLSliceSnapshotCollectionNode*)ret;
  }
  return new vtkMRMLSliceSnapshotCollectionNode;
}
//----------------------------------------------------------------------------
vtkMRMLSliceSnapshotCollectionNode::vtkMRMLSliceSnapshotCollectionNode()
{
  this->SnapshotNodeRef = NULL;
  this->HideFromEditors = 1;

}

//----------------------------------------------------------------------------
vtkMRMLSliceSnapshotCollectionNode::~vtkMRMLSliceSnapshotCollectionNode()
{
  this->SetSnapshotNodeRef(NULL);
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

	 if(!strcmp(attName, "SnapshotNodeRef"))
	 {
	   this->SetSnapshotNodeRef(attValue);
	 }
  }

  //this->WriteXML(std::cout,1);
}

//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::WriteXML(ostream& of, int nIndent)
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
void vtkMRMLSliceSnapshotCollectionNode::Copy(vtkMRMLNode *anode)
{
  Superclass::Copy(anode);
  vtkMRMLSliceSnapshotCollectionNode *node = vtkMRMLSliceSnapshotCollectionNode::SafeDownCast(anode);
  this->SetSnapshotNodeRef(node->SnapshotNodeRef);
  //this->DisableModifiedEventOn();


}

//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);

  os << indent << "SnapshotNodeRef: " <<
	  (this->SnapshotNodeRef ? this->SnapshotNodeRef: "(none)") << "\n";

}

//----------------------------------------------------------------------------

vtkMRMLModelDisplayNode* vtkMRMLSliceSnapshotCollectionNode::GetSnapshotNode()
{

  vtkMRMLModelDisplayNode* node = NULL;
  if (this->GetScene() && this->SnapshotNodeRef != NULL)
  {
    vtkMRMLNode* snode = this->GetScene()->GetNodeByID(this->SnapshotNodeRef);
    node = vtkMRMLModelDisplayNode::SafeDownCast(snode);
  }
  return node;
}


//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::UpdateReferences()
{
  Superclass::UpdateReferences();
  
  if (this->SnapshotNodeRef != NULL && this->Scene->GetNodeByID(this->SnapshotNodeRef) == NULL)
  {
    this->SetSnapshotNodeRef(NULL);
  }
}

//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::UpdateReferenceID(const char *oldID, const char *newID)
{
  Superclass::UpdateReferenceID(oldID, newID);

  if (this->SnapshotNodeRef && !strcmp(oldID, this->SnapshotNodeRef))
  {
    this->SetSnapshotNodeRef(newID);
  }
}

//----------------------------------------------------------------------------
void vtkMRMLSliceSnapshotCollectionNode::UpdateScene(vtkMRMLScene *scene)
{
  Superclass::UpdateScene(scene);
}

// End
