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

// MRML includes


// CropModuleMRML includes
#include "vtkMRMLUltrasoundSnapshotsNode.h"

// AnnotationModuleMRML includes


// STD includes

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLUltrasoundSnapshotsNode);

//----------------------------------------------------------------------------
vtkMRMLUltrasoundSnapshotsNode::vtkMRMLUltrasoundSnapshotsNode()
{
  this->HideFromEditors = 1;

}

//----------------------------------------------------------------------------
vtkMRMLUltrasoundSnapshotsNode::~vtkMRMLUltrasoundSnapshotsNode()
{

}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsNode::ReadXMLAttributes(const char** atts)
{
  std::cerr << "Reading UltrasoundSnapshots param node!" << std::endl;
  Superclass::ReadXMLAttributes(atts);

  const char* attName;
  const char* attValue;
  

  this->WriteXML(std::cout,1);
}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsNode::WriteXML(ostream& of, int nIndent)
{
  Superclass::WriteXML(of, nIndent);

  vtkIndent indent(nIndent);


}

//----------------------------------------------------------------------------
// Copy the node\"s attributes to this object.
// Does NOT copy: ID, FilePrefix, Name, SliceID
void vtkMRMLUltrasoundSnapshotsNode::Copy(vtkMRMLNode *anode)
{
  Superclass::Copy(anode);
  vtkMRMLUltrasoundSnapshotsNode *node = vtkMRMLUltrasoundSnapshotsNode::SafeDownCast(anode);
  this->DisableModifiedEventOn();


}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);


}

// End
