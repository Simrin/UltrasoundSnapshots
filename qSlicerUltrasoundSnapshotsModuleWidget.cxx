
// Qt includes
#include <QDebug>

// SlicerQt includes
#include "qSlicerUltrasoundSnapshotsModuleWidget.h"
#include "ui_qSlicerUltrasoundSnapshotsModule.h"

#include "vtkSlicerUltrasoundSnapshotsLogic.h"

// MRML includes
#include "vtkMRMLScalarVolumeNode.h"
#include "vtkMRMLModelNode.h"
#include "vtkMRMLSliceSnapshotCollectionNode.h"

// VTK includes
#include <vtkSmartPointer.h>

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerUltrasoundSnapshotsModuleWidgetPrivate: public Ui_qSlicerUltrasoundSnapshotsModule
{
  Q_DECLARE_PUBLIC( qSlicerUltrasoundSnapshotsModuleWidget );
protected:
  qSlicerUltrasoundSnapshotsModuleWidget* const q_ptr;
public:
  qSlicerUltrasoundSnapshotsModuleWidgetPrivate( qSlicerUltrasoundSnapshotsModuleWidget& object );
  vtkSlicerUltrasoundSnapshotsLogic* logic() const;
  //vtkSmartPointer<vtkMRMLSliceSnapshotCollectionNode> MRMLSliceSnapshotCollectionNode;
  //virtual void init();
  void setupUi(qSlicerWidget* widget);
};


//-----------------------------------------------------------------------------
// qSlicerUltrasoundSnapshotsModuleWidgetPrivate methods


//-----------------------------------------------------------------------------
qSlicerUltrasoundSnapshotsModuleWidgetPrivate::qSlicerUltrasoundSnapshotsModuleWidgetPrivate( qSlicerUltrasoundSnapshotsModuleWidget& object )
 : q_ptr( &object )
{
}


vtkSlicerUltrasoundSnapshotsLogic*
qSlicerUltrasoundSnapshotsModuleWidgetPrivate::logic() const
{
  Q_Q( const qSlicerUltrasoundSnapshotsModuleWidget );
  return vtkSlicerUltrasoundSnapshotsLogic::SafeDownCast( q->logic() );
}

// -----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// qSlicerAnnotationModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
void qSlicerUltrasoundSnapshotsModuleWidgetPrivate::setupUi(qSlicerWidget* widget)
{
  Q_Q(qSlicerUltrasoundSnapshotsModuleWidget);



  this->Ui_qSlicerUltrasoundSnapshotsModule::setupUi(widget);

  //q->connect(this->ModuleComboBox, SIGNAL( currentNodeChanged( vtkMRMLNode* ) ), SLOT( onModuleNodeSelected(vtkMRMLNode*) ) );
  //this->GetMRMLScene()->RegisterNodeClass(vtkSmartPointer <vtkMRMLSliceSnapshotCollectionNode>::New());
  q->connect(this->UltrasoundImageComboBox, SIGNAL(currentNodeChanged(vtkMRMLNode*)), SLOT(onCurrentMRMLUSSourceNodeChanged(vtkMRMLNode*)));
  
  q->connect(this->AddSnapshotButton, SIGNAL( clicked() ), SLOT( OnAddSnapshotClicked() ) );
  // connect( d->ClearSnapshotsButton, SIGNAL( clicked() ), this, SLOT( OnClearSnapshotsClicked() ) );



}



//-----------------------------------------------------------------------------
// qSlicerUltrasoundSnapshotsModuleWidget methods



qSlicerUltrasoundSnapshotsModuleWidget
::~qSlicerUltrasoundSnapshotsModuleWidget()
{
}
/*
void qSlicerUltrasoundSnapshotsModuleWidget::onModuleNodeSelected(vtkMRMLNode* node)
{
  Q_D( qSlicerUltrasoundSnapshotsModuleWidget );
 

  vtkMRMLSliceSnapshotCollectionNode* SnapshotCollectionNode = vtkMRMLSliceSnapshotCollectionNode::SafeDownCast( node );
  
  d->logic()->SetSnapshotCollectionNode( SnapshotCollectionNode );

}
*/
/*
void qSlicerUltrasoundSnapshotsModuleWidgetPrivate::init()
{
  Q_Q(qSlicerUltrasoundSnapshotsModuleWidget);
  q->setupUi(this);

  QStringList nodeTypes = QStringList();
  nodeTypes.append("vtkMRMLModelNode");
  q->setNodeTypes(nodeTypes);
  //q->setNodeTypes(QStringList(QString()));
  //q->setBaseName("Model");
  connect(d->UltrasoundImageComboBox, SIGNAL(currentNodeChanged(vtkMRMLNode*)),this, SLOT(onCurrentMRMLUSSourceNodeChanged(vtkMRMLNode*)));
  
  connect( d->AddSnapshotButton, SIGNAL( clicked() ), this, SLOT( OnAddSnapshotClicked() ) );
  // connect( d->ClearSnapshotsButton, SIGNAL( clicked() ), this, SLOT( OnClearSnapshotsClicked() ) );

}

*/



qSlicerUltrasoundSnapshotsModuleWidget
::qSlicerUltrasoundSnapshotsModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerUltrasoundSnapshotsModuleWidgetPrivate( *this ) )
{
	//Q_D(qMRMLUltrasoundSnapshotModuleWidget);
	//d->init();
}

void
qSlicerUltrasoundSnapshotsModuleWidget
::OnAddSnapshotClicked()
{
  Q_D(qSlicerUltrasoundSnapshotsModuleWidget);
  
  vtkMRMLNode* cnode = d->UltrasoundImageComboBox->currentNode();
  vtkMRMLScalarVolumeNode* vnode = NULL;
  if ( cnode != NULL )
  {
    vnode = vtkMRMLScalarVolumeNode::SafeDownCast( cnode );
  }
  //vtkMRMLSliceSnapshotCollectionNode* snapshotCollectionNode = d->MRMLSliceSnapshotCollectionNode; 
  if ( vnode != NULL )
  {
    
    d->logic()->AddSnapshot( vnode );
  }
}



void
qSlicerUltrasoundSnapshotsModuleWidget
::OnClearSnapshotsClicked()
{
  Q_D(qSlicerUltrasoundSnapshotsModuleWidget);
  
  d->logic()->ClearSnapshots();
}




void
qSlicerUltrasoundSnapshotsModuleWidget
::setup()
{
  Q_D(qSlicerUltrasoundSnapshotsModuleWidget);

  this->Superclass::setup();
  d->setupUi(this);
}


// --------------------------------------------------------------------------
vtkMRMLScalarVolumeNode* 
qSlicerUltrasoundSnapshotsModuleWidget
::mrmlUSSourceNode()const
{
  Q_D(const qSlicerUltrasoundSnapshotsModuleWidget);
  return vtkMRMLScalarVolumeNode::SafeDownCast(
    d->UltrasoundImageComboBox->currentNode());
}

// --------------------------------------------------------------------------
void qSlicerUltrasoundSnapshotsModuleWidget::setMRMLUSSourceNode(vtkMRMLNode* usSourceNode)
{
  Q_D(qSlicerUltrasoundSnapshotsModuleWidget);
  d->UltrasoundImageComboBox->setCurrentNode(usSourceNode);
}

// --------------------------------------------------------------------------
void qSlicerUltrasoundSnapshotsModuleWidget::onCurrentMRMLUSSourceNodeChanged(vtkMRMLNode* node)
{
  Q_D(qSlicerUltrasoundSnapshotsModuleWidget);

  vtkMRMLScalarVolumeNode* usSourceNode = vtkMRMLScalarVolumeNode::SafeDownCast(node);

  if (!usSourceNode)
    {
    return;
    }

  vtkSlicerUltrasoundSnapshotsLogic *logic =
    vtkSlicerUltrasoundSnapshotsLogic::SafeDownCast(this->logic());
/* not sure if needed yet
  // see if the volume has any display node for a current viewer
  vtkMRMLVolumeRenderingDisplayNode *dnode =
    logic->GetFirstVolumeRenderingDisplayNode(volumeNode);
  if (!this->mrmlScene()->IsClosing())
    {
    if (!dnode)
      {
      dnode = d->createVolumeRenderingDisplayNode(volumeNode);
      }
    else
      {
      // Because the displayable manager can only display 1 volume at
      // a time, here the displayable manager is told that the display node
      // is the new "current" display node and it should be displayed
      // instead of whichever current one.
      dnode->Modified();
      }
    }

  this->setMRMLDisplayNode(dnode);
  */
}

