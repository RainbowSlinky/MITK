#include "mitkGeometry2DDataMapper2D.h"
#include "BaseRenderer.h"
#include "PlaneGeometry.h"
#include "mitkColorProperty.h"
#include "mitkFloatProperty.h"

//##ModelId=3E639E100243
mitk::Geometry2DDataMapper2D::Geometry2DDataMapper2D()
{
}

//##ModelId=3E639E100257
mitk::Geometry2DDataMapper2D::~Geometry2DDataMapper2D()
{
}

//##ModelId=3E6423D20341
const mitk::Geometry2DData *mitk::Geometry2DDataMapper2D::GetInput(void)
{
	if (this->GetNumberOfInputs() < 1)
	{
		return 0;
	}

    return static_cast<const mitk::Geometry2DData * > ( GetData() );
}


//##ModelId=3E67D77A0109
void mitk::Geometry2DDataMapper2D::Paint(mitk::BaseRenderer * renderer)
{
    if(IsVisible(renderer)==false) return;

    //	FIXME: Logik fuer update
    bool updateNeccesary=true;

    if (updateNeccesary) {
        // ok, das ist aus GenerateData kopiert

        mitk::Geometry2DData::Pointer input  = const_cast<mitk::Geometry2DData*>(this->GetInput());

        PlaneGeometry::ConstPointer input_planeGeometry = dynamic_cast<const PlaneGeometry *>(input->GetGeometry2D());
        PlaneGeometry::ConstPointer worldPlaneGeometry = dynamic_cast<const PlaneGeometry*>(renderer->GetWorldGeometry());

        if((input_planeGeometry.IsNotNull()) && (worldPlaneGeometry.IsNotNull()))
        {
            mitk::DisplayGeometry::Pointer displayGeometry = renderer->GetDisplayGeometry();
            assert(displayGeometry);

			//we want to take the transform of the datatreenode into account. Thus, copy
			//the geometry and transform it with the transform of the datatreenode.
			PlaneGeometry::Pointer planeGeometry = PlaneGeometry::New();
			planeGeometry->SetPlaneView(input_planeGeometry->GetPlaneView());
			planeGeometry->TransformGeometry(GetDataTreeNode()->GetVtkTransform());

            //calculate intersection of the plane data with the border of the world geometry rectangle
	        Point2D lineFrom;
	        Point2D lineTo;
    		bool intersecting = worldPlaneGeometry->GetPlaneView().intersectPlane2D( planeGeometry->GetPlaneView(), lineFrom, lineTo );

            if(intersecting)
            {
                //convert intersection points (until now mm) to display coordinates (units )
                displayGeometry->MMToDisplay(lineFrom, lineFrom);
                displayGeometry->MMToDisplay(lineTo, lineTo);

                //convert display coordinates ( (0,0) is top-left ) in GL coordinates ( (0,0) is bottom-left )
//                float toGL=//displayGeometry->GetDisplayHeight(); displayGeometry->GetWorldGeometry()->GetHeightInUnits();
//                lineFrom.y=toGL-lineFrom.y;
//                lineTo.y=toGL-lineTo.y;

                //apply color and opacity read from the PropertyList
                ApplyProperties(renderer);

                //draw
                glBegin (GL_LINE_LOOP);
                    glVertex2fv(&lineFrom.x);
                    glVertex2fv(&lineTo.x);
                    glVertex2fv(&lineFrom.x);
                glEnd ();
            }
        }
    }
}

//##ModelId=3E67E1B90237
void mitk::Geometry2DDataMapper2D::Update()
{
}

//##ModelId=3E67E285024E
void mitk::Geometry2DDataMapper2D::GenerateOutputInformation()
{
}



