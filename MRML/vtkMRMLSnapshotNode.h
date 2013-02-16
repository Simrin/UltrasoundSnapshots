/*=========================================================================



=========================================================================*/


#ifndef __vtkMRMLSnapshotNode_h
#define __vtkMRMLSnapshotNode_h

#include "vtkObject.h"

class VTK_COMMON_EXPORT vtkMRMLSnapshotNode : public vtkObject
{


public:

  // Description:
  // Construct a snapshot
  static vtkMRMLSnapshotNode *New();

  vtkTypeMacro(vtkMRMLSnapshotNode,vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Description:
  // Set the elements of the matrix to the same values as the elements
  // of the source Matrix.
  //void DeepCopy(const vtkMRMLSnapshotNode *source)
    //{vtkMRMLSnapshotNode::DeepCopy(*this->Element,source); this->Modified(); }


protected:
  vtkMRMLSnapshotNode();
  ~vtkMRMLSnapshotNode();
  

private:
  void operator= (const vtkMRMLSnapshotNode&);  // Not implemented
};


#endif