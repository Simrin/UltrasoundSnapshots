

// UltrasoundSnapshots Logic includes
#include "vtkSlicerUltrasoundSnapshotsLogic.h"

// MRML includes
#include <vtkMRMLConfigure.h>
#include "vtkMRMLModelDisplayNode.h"
#include "vtkMRMLModelNode.h"
#include "vtkMRMLTransformNode.h"
#include "vtkMRMLSliceSnapshotCollectionNode.h"


// VTK includes
#include <vtkCollection.h>
#include <vtkImageData.h>
#include <vtkNew.h>
#include <vtkPlaneSource.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include <vtksys/SystemTools.hxx> 


// STD includes
#include <cassert>
#include <algorithm>

// Logic includes
#include "vtkSlicerModelsLogic.h"

//----------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerUltrasoundSnapshotsLogic);

//----------------------------------------------------------------------------
vtkSlicerUltrasoundSnapshotsLogic::vtkSlicerUltrasoundSnapshotsLogic()
{
  this->SnapshotCollectionNode = NULL;
}

//----------------------------------------------------------------------------
vtkSlicerUltrasoundSnapshotsLogic::~vtkSlicerUltrasoundSnapshotsLogic()
{
  if ( this->SnapshotCollectionNode != NULL )
  {
    this->SnapshotCollectionNode->Delete();
    this->SnapshotCollectionNode = NULL;
  }
}



void
vtkSlicerUltrasoundSnapshotsLogic
::PrintSelf( ostream& os, vtkIndent indent )
{
  this->Superclass::PrintSelf( os, indent );
}


//---------------------------------------------------------------------------
// Register the MRML node classes to the attached scene.
//---------------------------------------------------------------------------
void 
vtkSlicerUltrasoundSnapshotsLogic
::RegisterNodes()
{
  if (!this->GetMRMLScene())
    {
    vtkWarningMacro("RegisterNodes: no scene");
    return;
    }

  //
  // The core nodes
  //

  this->GetMRMLScene()->RegisterNodeClass(vtkSmartPointer< vtkMRMLSliceSnapshotCollectionNode >::New());

  /*
  // base nodes
  vtkMRMLModelNode* modelNode = vtkMRMLModelNode::New();
  this->GetMRMLScene()->RegisterNodeClass(modelNode);
  modelNode->Delete();
*/

  
}

//---------------------------------------------------------------------------
// Return the toplevel Annotation hierarchy node ID or create one if there is none.
// If an optional annotationNode is given, insert the toplevel hierarchy before it. If not,
// just add the toplevel hierarchy node.
//---------------------------------------------------------------------------
bool vtkSlicerUltrasoundSnapshotsLogic::AddModelNodeID(vtkMRMLModelNode* modelNode)
{
  if (this->GetMRMLScene() == NULL)
    {
    return false;
    }

  /*
  vtkCollection* nodes = this->GetMRMLScene() ? this->GetMRMLScene()->GetNodes() : 0;
  if (nodes == 0 || modelNode == 0)
    {
    return 0;
    }

*/

  char *modelNodeID = modelNode->GetID();


  this->GetSnapshotCollectionNode()->AddModelNodeID(modelNodeID);
  //int numSnapshots = snapshotCollectionNode->GetNumberOfModelNodeIDs();
   
  return true;
/*
  vtkMRMLNode *node;
  vtkCollectionSimpleIterator it;
  for (nodes->InitTraversal(it);
       (node = vtkMRMLNode::SafeDownCast(nodes->GetNextItemAsObject(it))) ;)
    {
    vtkMRMLSliceSnapshotCollectionNode* snapshotCollectionNode = vtkMRMLSliceSnapshotCollectionNode::SafeDownCast(node);
    if (snapshotCollectionNode)
      {
      snapshotCollectionNode->AddModelNodeID(modelNodeID);
	  int numSnapshots = snapshotCollectionNode->GetNumberOfModelNodeIDs();
      }
    }
  */
 // vtkMRMLSliceSnapshotCollectionNode *snapshotCollectionNode = vtkMRMLSliceSnapshotCollectionNode::SafeDownCast(node);
  /*
  if (!toplevelNode)
    {
    // no top level hierarchy node is currently in the scene, create a new one
    toplevelNode = vtkMRMLAnnotationHierarchyNode::New();
    
    toplevelNode->HideFromEditorsOff();
    toplevelNode->SetName(this->GetMRMLScene()->GetUniqueNameByString(topLevelName));
    
    if (!node)
      {
      this->GetMRMLScene()->AddNode(toplevelNode);
      }
    else
      {
      this->GetMRMLScene()->InsertBeforeNode(node, toplevelNode);
      }
    toplevelNodeID = toplevelNode->GetID();
    if (this->AddDisplayNodeForHierarchyNode(toplevelNode) == NULL)
      {
      vtkErrorMacro("GetTopLevelHierarchyNodeID: error adding a display node for new top level node " << toplevelNodeID);
      }
    this->InvokeEvent(HierarchyNodeAddedEvent, toplevelNode);
    toplevelNode->Delete();
    }
  else
    {
    toplevelNodeID = toplevelNode->GetID();
    }
	
  col->RemoveAllItems();
  col->Delete();
  return ModelNodeID;
  */
}

void
vtkSlicerUltrasoundSnapshotsLogic
::AddSnapshot( vtkMRMLScalarVolumeNode* InputNode )
{
  if ( InputNode == NULL )
  {
    return;
  }



  vtkSmartPointer< vtkMRMLModelDisplayNode > snapshotDisp = vtkSmartPointer< vtkMRMLModelDisplayNode >::New();
  
  this->GetMRMLScene()->AddNode( snapshotDisp );
  snapshotDisp->SetScene( this->GetMRMLScene() );
  snapshotDisp->SetDisableModifiedEvent( 1 );
  snapshotDisp->SetOpacity( 1.0 );
  snapshotDisp->SetColor( 1.0, 1.0, 1.0 );
  snapshotDisp->SetAmbient( 1.0 );
  snapshotDisp->SetBackfaceCulling( 0 );
  snapshotDisp->SetDiffuse( 0.0 );
  snapshotDisp->SetSaveWithScene( 0 );
  snapshotDisp->SetDisableModifiedEvent( 0 );


  std::stringstream nameStream;  // Use stream because later we may add other info in the name, e.g. number.
  nameStream << "Snapshot";
  vtkSmartPointer< vtkMRMLModelNode > snapshotModel = vtkSmartPointer< vtkMRMLModelNode >::New();
  //vtkMRMLModelNode* snapshotModel = snapshotCollection->GetModelNode();
  this->GetMRMLScene()->AddNode( snapshotModel );
  snapshotModel->SetName( nameStream.str().c_str() );
  snapshotModel->SetDescription( "Live Ultrasound Snapshot" );
  snapshotModel->SetScene( this->GetMRMLScene() );
  snapshotModel->SetAndObserveDisplayNodeID( snapshotDisp->GetID() );
  snapshotModel->SetHideFromEditors( 0 );
  snapshotModel->SetSaveWithScene( 0 );



    
    //if (    if (annotationNode && annotationNode->GetScene() && annotationNode->GetID()))
	//{
      bool modelNodeAdded = AddModelNodeID(snapshotModel);
	//}
    //else
    //{
      //vtkSmartPointer< vtkMRMLSliceSnapshotCollectionNode > snapshotCollectionNode = vtkSmartPointer< vtkMRMLSliceSnapshotCollectionNode >::New();
	  //this->GetMRMLScene()->AddNode(snapshotCollectionNode);
	  //bool modelNodeAdded = AddModelNodeID(snapshotModel, snapshotCollectionNode);
    //}
  //}


  //SnapshotCollectionNode->AddModelNodeID(snapshotModel->GetID());
  
  int dims[ 3 ] = { 0, 0, 0 };
  InputNode->GetImageData()->GetDimensions( dims );
  if ( dims[ 0 ] == 0  &&  dims[ 1 ] == 0  && dims[ 2 ] == 0 )
  {
    return;
  }
  
  vtkSmartPointer< vtkPlaneSource > plane = vtkSmartPointer< vtkPlaneSource >::New();
  plane->Update();
  snapshotModel->SetAndObservePolyData( plane->GetOutput() );
  
  vtkPolyData* slicePolyData = snapshotModel->GetPolyData();
  vtkPoints* slicePoints = slicePolyData->GetPoints();
  
  vtkSmartPointer< vtkTransform > ParentTransform = vtkSmartPointer< vtkTransform >::New();
  ParentTransform->Identity();
  if ( InputNode->GetParentTransformNode() != NULL )
  {
    vtkSmartPointer< vtkMatrix4x4 > ParentMatrix = vtkSmartPointer< vtkMatrix4x4 >::New();
    InputNode->GetParentTransformNode()->GetMatrixTransformToWorld( ParentMatrix );
    ParentTransform->GetMatrix()->DeepCopy( ParentMatrix );
    ParentTransform->Update();
  }
  
  vtkSmartPointer< vtkTransform > InImageTransform = vtkSmartPointer< vtkTransform >::New();
  InImageTransform->Identity();
  InputNode->GetIJKToRASMatrix( InImageTransform->GetMatrix() );
  
  vtkSmartPointer< vtkTransform > tImageToRAS = vtkSmartPointer< vtkTransform >::New();
  tImageToRAS->Identity();
  tImageToRAS->PostMultiply();
  tImageToRAS->Concatenate( ParentTransform );
  tImageToRAS->Concatenate( InImageTransform );
  tImageToRAS->Update();
  
    // Four corners of the image in Image coordinate system.
  
  double point1Image[ 4 ] = { 0.0,       0.0,       0.0, 1.0 };
  double point2Image[ 4 ] = { dims[ 0 ], 0.0,       0.0, 1.0 };
  double point3Image[ 4 ] = { 0.0,       dims[ 1 ], 0.0, 1.0 };
  double point4Image[ 4 ] = { dims[ 0 ], dims[ 1 ], 0.0, 1.0 };
  
    // Four corners of the image in RAS coordinate system.
  
  double point1RAS[ 4 ] = { 0, 0, 0, 0 };
  double point2RAS[ 4 ] = { 0, 0, 0, 0 }; 
  double point3RAS[ 4 ] = { 0, 0, 0, 0 }; 
  double point4RAS[ 4 ] = { 0, 0, 0, 0 };
  
  tImageToRAS->MultiplyPoint( point1Image, point1RAS );
  tImageToRAS->MultiplyPoint( point2Image, point2RAS );
  tImageToRAS->MultiplyPoint( point3Image, point3RAS );
  tImageToRAS->MultiplyPoint( point4Image, point4RAS );
  
    // Position of the PolyData of the new model node.
  
  slicePoints->SetPoint( 0, point1RAS );
  slicePoints->SetPoint( 1, point2RAS );
  slicePoints->SetPoint( 2, point3RAS );
  slicePoints->SetPoint( 3, point4RAS );
  
    // Add image texture.
  
  vtkSmartPointer< vtkImageData > image = vtkSmartPointer< vtkImageData >::New();
  image->DeepCopy( InputNode->GetImageData() );
  snapshotModel->GetModelDisplayNode()->SetAndObserveTextureImageData( image );
}

//----------------------------------------------------------------------------
vtkMRMLModelNode* vtkSlicerUltrasoundSnapshotsLogic::LoadSliceSnapshot(const char* filename)
{
  

  // load models
  
  vtkSlicerModelsLogic* modelsLogic = vtkSlicerModelsLogic::New();

  modelsLogic->SetMRMLScene(this->GetMRMLScene());
  vtkMRMLModelNode* modelNode= modelsLogic->AddModel(filename);
  
  return modelNode;
}


//----------------------------------------------------------------------------
int vtkSlicerUltrasoundSnapshotsLogic::LoadSliceSnapshotCollection(const char* dirname, const char* suffix)
{

  // load models
  
  vtkSlicerModelsLogic* modelsLogic = vtkSlicerModelsLogic::New();

  modelsLogic->SetMRMLScene(this->GetMRMLScene());
  int res = modelsLogic->AddModels(dirname,suffix);
  
  //change reference ids


  return res;
}


void
vtkSlicerUltrasoundSnapshotsLogic
::ClearSnapshots()
{
  // TODO: Using this function causes a crash in Slicer that I could debug. So it's not used now.
  
  vtkCollection* collection = this->GetMRMLScene()->GetNodesByName( "Snapshot" );
  
  vtkMRMLModelNode* ModelNode = NULL;
  for ( int i = 0; i < collection->GetNumberOfItems(); ++ i )
  {
    ModelNode = vtkMRMLModelNode::SafeDownCast( collection->GetItemAsObject( i ) );
    if ( ModelNode != NULL )
    {
      vtkMRMLDisplayNode* ModelDisplayNode = ModelNode->GetDisplayNode();
      this->GetMRMLScene()->RemoveNode( ModelDisplayNode );
      this->GetMRMLScene()->RemoveNode( ModelNode );
      // ModelDisplayNode->RemoveAllObservers();
      // ModelNode->RemoveAllObservers();
      // ModelDisplayNode->Delete();
      // ModelNode->Delete();
      ModelNode = NULL;
    }
  }
  
  collection->Delete();  
}

//---------------------------------------------------------------------------
void vtkSlicerUltrasoundSnapshotsLogic
::ProcessMRMLSceneEvents(vtkObject *caller, unsigned long event, void *callData)
{
  this->Superclass::ProcessMRMLSceneEvents(caller, event, callData);

  vtkMRMLSliceSnapshotCollectionNode* snapshotCollectionNode = vtkMRMLSliceSnapshotCollectionNode::SafeDownCast(
    reinterpret_cast<vtkObject*>(callData));
/* 
  if (snapshotCollectionNode)
  {
    switch (event)
      {
      case vtkMRMLScene::NodeAddedEvent:
        this->OnMRMLSceneNodeAdded(annotationNode);
        break;
      }
    return;
    }
  }
  */
}

//---------------------------------------------------------------------------
void vtkSlicerUltrasoundSnapshotsLogic::SetMRMLSceneInternal(vtkMRMLScene * newScene)
{
  vtkNew<vtkIntArray> events;
  events->InsertNextValue(vtkMRMLScene::NodeAddedEvent);
  events->InsertNextValue(vtkMRMLScene::NodeRemovedEvent);
  events->InsertNextValue(vtkMRMLScene::EndBatchProcessEvent);
  this->SetAndObserveMRMLSceneEventsInternal(newScene, events.GetPointer());
}


//---------------------------------------------------------------------------
void vtkSlicerUltrasoundSnapshotsLogic::UpdateFromMRMLScene()
{
  assert(this->GetMRMLScene() != 0);
}

//---------------------------------------------------------------------------
void vtkSlicerUltrasoundSnapshotsLogic
::OnMRMLSceneNodeAdded(vtkMRMLNode* vtkNotUsed(node))
{
  
}

//---------------------------------------------------------------------------
void vtkSlicerUltrasoundSnapshotsLogic
::OnMRMLSceneNodeRemoved(vtkMRMLNode* vtkNotUsed(node))
{
}

void vtkSlicerUltrasoundSnapshotsLogic
::SetCollectionNode( vtkMRMLSliceSnapshotCollectionNode* node )
{
  vtkSetMRMLNodeMacro( this->SnapshotCollectionNode, node );
  this->Modified();
}