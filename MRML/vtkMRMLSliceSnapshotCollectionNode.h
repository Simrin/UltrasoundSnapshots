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
#include "vtkMRMLDisplayableHierarchyNode.h"
class vtkMRMLModelDisplayNode;
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
  void PrintSelf(ostream& os, vtkIndent indent);

  virtual vtkMRMLNode* CreateNodeInstance();

  // Set node attributes
  virtual void ReadXMLAttributes( const char** atts);

  // Write this node's information to a MRML file in XML format.
  virtual void WriteXML(ostream& of, int indent);

  // Copy the node's attributes to this object
  virtual void Copy(vtkMRMLNode *node);

  // Get node XML tag name (like Volume, Model)
  virtual const char* GetNodeTagName() {return "SliceSnapshotCollection";};

  // Updates this node if it depends on other nodes when the node is deleted in the scene
  virtual void UpdateReferences();

  // Update the stored reference to another node in the scene
  virtual void UpdateReferenceID(const char *oldID, const char *newID);

  virtual void UpdateScene(vtkMRMLScene *scene);

  /// 
  /// Get associated model MRML node
  std::vector<vtkMRMLModelNode*>& GetAllModelNodes();

  //vtkMRMLModelNode* GetModelNode();
  /// 
  /// alternative method to propagate events generated in Display nodes
  virtual void ProcessMRMLEvents ( vtkObject * /*caller*/, 
                                   unsigned long /*event*/, 
                                   void * /*callData*/ );

  /// Add View Node ID for the view to display this node in.
  /// \sa ViewNodeIDs, RemoveViewNodeID(), RemoveAllViewNodeIDs()
  void AddModelNodeID(const char* viewNodeID);

  /// Remove View Node ID for the view to display this node in.
  /// \sa ViewNodeIDs, AddViewNodeID(), RemoveAllViewNodeIDs()
  void RemoveModelNodeID(char* viewNodeID);
  /// Remove All View Node IDs for the views to display this node in.
  /// \sa ViewNodeIDs, AddViewNodeID(), RemoveViewNodeID()
  void RemoveAllModelNodeIDs();
  /// Get number of View Node ID's for the view to display this node in.
  /// If 0, display in all views
  /// \sa ViewNodeIDs, GetViewNodeIDs(), AddViewNodeID()
  inline int GetNumberOfModelNodeIDs()const;
  /// Get View Node ID's for the view to display this node in.
  /// If NULL, display in all views
  /// \sa ViewNodeIDs, GetViewNodeIDs(), AddViewNodeID()
  const char* GetNthModelNodeID(unsigned int index);
  /// Get all View Node ID's for the view to display this node in.
  /// If empty, display in all views
  /// \sa ViewNodeIDs, GetNthViewNodeID(), AddViewNodeID()
  inline std::vector< std::string > GetModelNodeIDs()const;
  /// True if the view node id is present in the viewnodeid list
  /// false if not found
  /// \sa ViewNodeIDs, IsDisplayableInView(), AddViewNodeID()
  bool IsModelNodeIDPresent(const char* viewNodeID)const;



protected:
  // Constructor/destructor
  vtkMRMLSliceSnapshotCollectionNode();
  ~vtkMRMLSliceSnapshotCollectionNode();

  vtkMRMLSliceSnapshotCollectionNode(const vtkMRMLSliceSnapshotCollectionNode&);
  void operator=(const vtkMRMLSliceSnapshotCollectionNode&);

  // Protected member variables


 /// Data


  std::vector< std::string > ModelNodeIDs;


};

//----------------------------------------------------------------------------
int vtkMRMLSliceSnapshotCollectionNode::GetNumberOfModelNodeIDs()const
{
  return static_cast<int>(this->ModelNodeIDs.size());
}

#endif

