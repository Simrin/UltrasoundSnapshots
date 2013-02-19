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
// .NAME vtkMRMLSliceSnapshotCollectionNode - MRML node for storing a slice through RAS space
// .SECTION Description
// This node stores the information about the currently selected volume
//
//

#ifndef __vtkMRMLSliceSnapshotCollectionNode_h
#define __vtkMRMLSliceSnapshotCollectionNode_h

// MRML includes
#include "vtkMRML.h"
#include "vtkMRMLScene.h"
#include "vtkMRMLNode.h"
#include "vtkMRMLStorageNode.h"
#include "vtkSlicerUltrasoundSnapshotsModuleMRMLExport.h"
#include "vtkMRMLScalarVolumeNode.h"
class vtkMRMLModelNode;

#include <string>
#include <vector>

/// \ingroup Slicer_QtModules_UltrasoundSnapshots
class VTK_SLICER_ULTRASOUNDSNAPSHOTS_MODULE_MRML_EXPORT vtkMRMLSliceSnapshotCollectionNode : public vtkMRMLNode
{
  public:   

  // Standard MRML node methods

  static vtkMRMLSliceSnapshotCollectionNode *New();
  vtkTypeMacro(vtkMRMLSliceSnapshotCollectionNode,vtkMRMLNode);

  virtual vtkMRMLNode* CreateNodeInstance();

  // Set node attributes
  virtual void ReadXMLAttributes( const char** atts);

  // Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);

  // Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);

  // Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "SliceSnapshotCollection";};

  void PrintSelf(ostream& os, vtkIndent indent);
  
  // Updates this node if it depends on other nodes when the node is deleted in the scene
  virtual void UpdateReferences();

  // Update the stored reference to another node in the scene
  virtual void UpdateReferenceID(const char *oldID, const char *newID);

  virtual void UpdateScene(vtkMRMLScene *scene);

  //alternative method to propagate events generated in slicersnapshotcollection nodes
  virtual void ProcessMRMLEvents ( vtkObject * /*caller*/, 
                                   unsigned long /*event*/, 
                                   void * /*callData*/ );

  // Add specific Model Node ID to the vector ModelNodeIDs
  void AddModelNodeID(const char* modelNodeID);

  // Remove specific Model Node ID from the vector ModelNodeIDs
  void RemoveModelNodeID(char* modelNodeID);

  // Remove all Model Node ID from the vector ModelNodeIDs
  void RemoveAllModelNodeIDs();

  // Returns the number of Model Node IDs currently in ModelNodeIDs
  inline int GetNumberOfModelNodeIDs()const;

  // Returns all the Model Node string IDs currently in ModelNodeIDs
  inline std::vector< std::string > GetModelNodeIDs()const;
  
  // Returns true if the Model Node ID is present in ModelNodeIDs
  bool IsModelNodeIDPresent(const char* viewNodeID)const;

protected:
  // Constructor/destructor
  vtkMRMLSliceSnapshotCollectionNode();
  ~vtkMRMLSliceSnapshotCollectionNode();

  vtkMRMLSliceSnapshotCollectionNode(const vtkMRMLSliceSnapshotCollectionNode&);
  void operator=(const vtkMRMLSliceSnapshotCollectionNode&);

  // Protected member variables
  std::vector< std::string > ModelNodeIDs;

};

//----------------------------------------------------------------------------
int vtkMRMLSliceSnapshotCollectionNode::GetNumberOfModelNodeIDs()const
{
  return this->ModelNodeIDs.size();
}

//----------------------------------------------------------------------------
std::vector< std::string > vtkMRMLSliceSnapshotCollectionNode::GetModelNodeIDs()const
{
  return this->ModelNodeIDs;
}

#endif

