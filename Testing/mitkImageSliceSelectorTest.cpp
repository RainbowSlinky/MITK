#include "mitkImage.h"
#include "mitkPicFileReader.h"
#include "mitkCylindricToCartesianFilter.h"
#include "mitkImageSliceSelector.h"

#include <fstream>
int mitkImageSliceSelectorTest(int argc, char* argv[])
{
	//Read pic-Image from file
	mitk::PicFileReader::Pointer reader = mitk::PicFileReader::New();
	  reader->SetFileName(argv[1]);

  //Take a slice
	mitk::ImageSliceSelector::Pointer slice = mitk::ImageSliceSelector::New();
	  slice->SetInput(reader->GetOutput());
	  slice->SetSliceNr(1);
	  slice->Update();

  std::cout << "Testing IsInitialized(): ";
  if(slice->GetOutput()->IsInitialized()==false)
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  std::cout << "Testing IsSliceSet(): ";
  if(slice->GetOutput()->IsSliceSet(0)==false)
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  try
  {
    std::cout << "Testing another, smaller (!!) input with the same slice-selector(): ";
    //Use CylindricToCartesianFilter
	  mitk::CylindricToCartesianFilter::Pointer cyl2cart = mitk::CylindricToCartesianFilter::New();
      cyl2cart->SetInput(reader->GetOutput());
      //the output size of this filter is smaller than the of the input!!
      cyl2cart->SetTargetXSize( 128 );

    //Use the same slice-selector again, this time to take a slice of the filtered image
      //which is smaller than the one of the old input!!
	  slice->SetInput(cyl2cart->GetOutput());
	    slice->SetSliceNr(1);

      //The requested region is still the old one,
      //therefore the following should result in an exception! 
	    slice->Update();

    std::cout<<"Part 1 [FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  catch ( itk::ExceptionObject & ex )
  {
    std::cout<<"Part 1 [PASSED] ";
    //after such an exception, we need to call ResetPipeline.
    slice->ResetPipeline();
  }

  try
  {
	  slice->UpdateLargestPossibleRegion();
  }
  catch ( itk::ExceptionObject & ex )
  {
    std::cout<<"Part 2 [FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"Part 2 [PASSED]"<<std::endl;

  std::cout << "Testing IsInitialized(): ";
  if(slice->GetOutput()->IsInitialized()==false)
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  std::cout << "Testing IsSliceSet(): ";
  if(slice->GetOutput()->IsSliceSet(0)==false)
  {
    std::cout<<"[FAILED]"<<std::endl;
    return EXIT_FAILURE;
  }
  std::cout<<"[PASSED]"<<std::endl;

  if(reader->GetOutput()->GetDimension(3) > 1)
  {
    int time=reader->GetOutput()->GetDimension(3)-1;

    std::cout << "Testing 3D+t: Setting time to " << time << ": ";
	  slice->SetTimeNr(time);
    if(slice->GetTimeNr()!=time)
    {
      std::cout<<"[FAILED]"<<std::endl;
      return EXIT_FAILURE;
    }
    std::cout<<"[PASSED]"<<std::endl;

    std::cout << "Testing 3D+t: Updating slice: ";
    slice->Update();
    if(slice->GetOutput()->IsInitialized()==false)
    {
      std::cout<<"[FAILED]"<<std::endl;
      return EXIT_FAILURE;
    }
    std::cout<<"[PASSED]"<<std::endl;

    std::cout << "Testing 3D+t: IsSliceSet(): ";
    if(slice->GetOutput()->IsSliceSet(0)==false)
    {
      std::cout<<"[FAILED]"<<std::endl;
      return EXIT_FAILURE;
    }
    std::cout<<"[PASSED]"<<std::endl;

    std::cout << "Testing 3D+t: First slice in reader available: ";
    if(reader->GetOutput()->IsSliceSet(0, time)==false)
    {
      std::cout<<"[FAILED]"<<std::endl;
      return EXIT_FAILURE;
    }
    std::cout<<"[PASSED]"<<std::endl;
  }

  std::cout<<"[TEST DONE]"<<std::endl;
  return EXIT_SUCCESS;
}
