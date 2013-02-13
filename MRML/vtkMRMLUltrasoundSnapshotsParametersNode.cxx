/*=auto=========================================================================

Portions (c) Copyright 2005 Brigham and Women\"s Hospital (BWH) All Rights Reserved.

See COPYRIGHT.txt
or http://www.slicer.org/copyright/copyright.txt for details.

Program:   3D Slicer
Module:    $RCSfile: vtkMRMLUltrasoundSnapshotsParametersNode.cxx,v $
Date:      $Date: 2006/03/17 15:10:10 $
Version:   $Revision: 1.2 $

=========================================================================auto=*/

// VTK includes
#include <vtkCommand.h>
#include <vtkObjectFactory.h>

// MRML includes


// CropModuleMRML includes
#include "vtkMRMLUltrasoundSnapshotsParametersNode.h"

// AnnotationModuleMRML includes


// STD includes

//----------------------------------------------------------------------------
vtkMRMLNodeNewMacro(vtkMRMLUltrasoundSnapshotsParametersNode);

//----------------------------------------------------------------------------
vtkMRMLUltrasoundSnapshotsParametersNode::vtkMRMLUltrasoundSnapshotsParametersNode()
{
  this->HideFromEditors = 1;

}

//----------------------------------------------------------------------------
vtkMRMLUltrasoundSnapshotsParametersNode::~vtkMRMLUltrasoundSnapshotsParametersNode()
{

}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsParametersNode::ReadXMLAttributes(const char** atts)
{
  std::cerr << "Reading UltrasoundSnapshots param node!" << std::endl;
  Superclass::ReadXMLAttributes(atts);

  const char* attName;
  const char* attValue;
  

  this->WriteXML(std::cout,1);
}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsParametersNode::WriteXML(ostream& of, int nIndent)
{
  Superclass::WriteXML(of, nIndent);

  vtkIndent indent(nIndent);


}

//----------------------------------------------------------------------------
// Copy the node\"s attributes to this object.
// Does NOT copy: ID, FilePrefix, Name, SliceID
void vtkMRMLUltrasoundSnapshotsParametersNode::Copy(vtkMRMLNode *anode)
{
  Superclass::Copy(anode);
  vtkMRMLUltrasoundSnapshotsParametersNode *node = vtkMRMLUltrasoundSnapshotsParametersNode::SafeDownCast(anode);
  this->DisableModifiedEventOn();


}

//----------------------------------------------------------------------------
void vtkMRMLUltrasoundSnapshotsParametersNode::PrintSelf(ostream& os, vtkIndent indent)
{
  Superclass::PrintSelf(os,indent);


}

// End
