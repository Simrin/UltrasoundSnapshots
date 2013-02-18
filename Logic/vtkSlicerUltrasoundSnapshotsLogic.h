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

// .NAME vtkSlicerUltrasoundSnapshotsLogic - slicer logic class for volumes manipulation
// .SECTION Description
// This class manages the logic associated with reading, saving,
// and changing propertied of the volumes


#ifndef __vtkSlicerUltrasoundSnapshotsLogic_h
#define __vtkSlicerUltrasoundSnapshotsLogic_h

// Slicer includes
#include "vtkSlicerModuleLogic.h"

// MRML includes
#include "vtkMRMLScalarVolumeNode.h"
#include "vtkMRMLModelNode.h"
class vtkMRMLSliceSnapshotCollectionNode;

// STD includes
#include <cstdlib>

#include "vtkSlicerUltrasoundSnapshotsModuleLogicExport.h"


/// \ingroup Slicer_QtModules_ExtensionTemplate
class VTK_SLICER_ULTRASOUNDSNAPSHOTS_MODULE_LOGIC_EXPORT vtkSlicerUltrasoundSnapshotsLogic :
  public vtkSlicerModuleLogic
{
public:

  static vtkSlicerUltrasoundSnapshotsLogic *New();
  vtkTypeMacro(vtkSlicerUltrasoundSnapshotsLogic, vtkSlicerModuleLogic);
  void PrintSelf(ostream& os, vtkIndent indent);
    /// Register MRML Node classes to Scene. Gets called automatically when the MRMLScene is attached to this logic class.
  virtual void RegisterNodes();
  void AddSliceSnapshotCollection(vtkMRMLScalarVolumeNode* InputNode);
  //void AddSnapshot( vtkMRMLSliceSnapshotCollectionNode* snapshotCollection );
  void AddSnapshot( vtkMRMLScalarVolumeNode* InputNode, vtkMRMLSliceSnapshotCollectionNode* snapshotCollectionNode );
  void ClearSnapshots(); //not used
    /// Load a fiducial list from file, returns NULL on failure
  vtkMRMLModelNode* LoadSliceSnapshot(const char* filename);
  int LoadSliceSnapshotCollection(const char* dirname, const char* suffix);
  
protected:
  vtkSlicerUltrasoundSnapshotsLogic();
  virtual ~vtkSlicerUltrasoundSnapshotsLogic();

  virtual void SetMRMLSceneInternal(vtkMRMLScene* newScene);
  virtual void UpdateFromMRMLScene();
  virtual void OnMRMLSceneNodeAdded(vtkMRMLNode* node);
  virtual void OnMRMLSceneNodeRemoved(vtkMRMLNode* node);
private:

  vtkSlicerUltrasoundSnapshotsLogic(const vtkSlicerUltrasoundSnapshotsLogic&); // Not implemented
  void operator=(const vtkSlicerUltrasoundSnapshotsLogic&);               // Not implemented
};

#endif
