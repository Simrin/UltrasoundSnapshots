/*=auto=========================================================================

  Portions (c) Copyright 2005 Brigham and Women's Hospital (BWH) 
  All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   3D Slicer

=========================================================================auto=*/

#include "vtkMRMLUltrasoundSnapshotsNode.h"

#include <vtkPolyData.h>


#include "vtkMRMLCoreTestingMacros.h"

int vtkMRMLUltrasoundSnapshotsNodeTest1(int , char * [] )
{
  vtkSmartPointer< vtkMRMLUltrasoundSnapshotsNode > node1 = vtkSmartPointer< vtkMRMLUltrasoundSnapshotsNode >::New();

  EXERCISE_BASIC_OBJECT_METHODS( node1 );
  
  return EXIT_SUCCESS;
}
