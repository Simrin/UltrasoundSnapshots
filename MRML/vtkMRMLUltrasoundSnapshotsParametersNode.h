/*=auto=========================================================================

  Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer
  Module:    $RCSfile: vtkMRMLUltrasoundSnapshotsParametersNode.h,v $
  Date:      $Date: 2006/03/19 17:12:29 $
  Version:   $Revision: 1.3 $

=========================================================================auto=*/
// .NAME vtkMRMLUltrasoundSnapshotsParametersNode - MRML node for storing a slice through RAS space
// .SECTION Description
// This node stores the information about the currently selected volume
//
//

#ifndef __vtkMRMLUltrasoundSnapshotsParametersNode_h
#define __vtkMRMLUltrasoundSnapshotsParametersNode_h

#include "vtkMRML.h"
#include "vtkMRMLScene.h"
#include "vtkMRMLNode.h"
#include "vtkSlicerUltrasoundSnapshotsModuleMRMLExport.h"



/// \ingroup Slicer_QtModules_UltrasoundSnapshots
class VTK_SLICER_ULTRASOUNDSNAPSHOTS_MODULE_MRML_EXPORT vtkMRMLUltrasoundSnapshotsParametersNode : public vtkMRMLNode
{
  public:   

  static vtkMRMLUltrasoundSnapshotsParametersNode *New();
  vtkTypeMacro(vtkMRMLUltrasoundSnapshotsParametersNode,vtkMRMLNode);
  void PrintSelf(ostream& os, vtkIndent indent);

  virtual vtkMRMLNode* CreateNodeInstance();

  // Description:
  // Set node attributes
  virtual void ReadXMLAttributes( const char** atts);

  // Description:
  // Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);

  // Description:
  // Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);

  // Description:
  // Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "UltrasoundSnapshotsParameters";};



protected:
  vtkMRMLUltrasoundSnapshotsParametersNode();
  ~vtkMRMLUltrasoundSnapshotsParametersNode();

  vtkMRMLUltrasoundSnapshotsParametersNode(const vtkMRMLUltrasoundSnapshotsParametersNode&);
  void operator=(const vtkMRMLUltrasoundSnapshotsParametersNode&);


};

#endif

