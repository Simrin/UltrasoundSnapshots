/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/
// .NAME vtkMRMLUltrasoundSnapshotsNode - MRML node for storing a slice through RAS space
// .SECTION Description
// This node stores the information about the currently selected volume
//
//

#ifndef __vtkMRMLUltrasoundSnapshotsNode_h
#define __vtkMRMLUltrasoundSnapshotsNode_h

// MRML includes
#include "vtkMRML.h"
#include "vtkMRMLScene.h"
#include "vtkMRMLNode.h"
#include "vtkMRMLStorageNode.h"
#include "vtkSlicerUltrasoundSnapshotsModuleMRMLExport.h"


class vtkMRMLModelDisplayNode;
class vtkMRMLModelNode;

/// \ingroup Slicer_QtModules_UltrasoundSnapshots
class VTK_SLICER_ULTRASOUNDSNAPSHOTS_MODULE_MRML_EXPORT vtkMRMLUltrasoundSnapshotsNode : public vtkMRMLNode
{
  public:   

  // Standard MRML node methods

  static vtkMRMLUltrasoundSnapshotsNode *New();
  vtkTypeMacro(vtkMRMLUltrasoundSnapshotsNode,vtkMRMLNode);
  void PrintSelf(ostream& os, vtkIndent indent);

  virtual vtkMRMLNode* CreateNodeInstance();

  // Set node attributes
  virtual void ReadXMLAttributes( const char** atts);

  // Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);

  // Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);

  // Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "UltrasoundSnapshots";};

  //
  //virtual void SetSceneReferences();

  // Updates this node if it depends on other nodes when the node is deleted in the scene
  virtual void UpdateReferences();

  // Update the stored reference to another node in the scene
  virtual void UpdateReferenceID(const char *oldID, const char *newID);

  virtual void UpdateScene(vtkMRMLScene *scene);


  // Public interface
  
  vtkSetReferenceStringMacro(SnapshotNodeRef);
  vtkGetStringMacro(SnapshotNodeRef);
  
  /// Get associated display MRML node
  vtkMRMLModelDisplayNode* GetSnapshotNode();

protected:
  // Constructor/destructor
  vtkMRMLUltrasoundSnapshotsNode();
  ~vtkMRMLUltrasoundSnapshotsNode();

  vtkMRMLUltrasoundSnapshotsNode(const vtkMRMLUltrasoundSnapshotsNode&);
  void operator=(const vtkMRMLUltrasoundSnapshotsNode&);

  // Protected member variables

  char *SnapshotNodeRef;

};

#endif

