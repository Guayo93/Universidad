#include <cmath>
#include <cstdlib>
#include <limits>
#include <iostream>
#include <string>
#include <sstream>

#include <itkImage.h>
#include <itkRGBPixel.h>

#include <itkImageFileReader.h>
#include <itkImageFileWriter.h>

#include <itkImageRegionConstIteratorWithIndex.h>
#include <itkImageRegionIteratorWithIndex.h>

#include <itkIdentityTransform.h>
#include <itkResampleImageFilter.h>

// Image type: 2-dimensional 1-byte rgb
const unsigned int Dim = 2;

// Types definition
typedef unsigned char                   TRGBResolution;
typedef itk::RGBPixel< TRGBResolution > TRGBPixel;
typedef itk::Image< TRGBPixel, Dim >    TColorImage;
typedef itk::ImageFileReader< TColorImage > TReader;
typedef itk::ImageRegionConstIteratorWithIndex< TColorImage > TIterator;
typedef itk::ImageRegionIteratorWithIndex< TColorImage > TColorIterator;
typedef itk::IdentityTransform<double, 2> TransformType;
typedef itk::ResampleImageFilter< TColorImage, TColorImage > ResampleImageFilterType;
typedef itk::ImageFileWriter< TColorImage > TWriter;

int main( int argc, char* argv[] )
{
  // Error pocos argumentos --------------------------------------
  if( argc < 2 )
  {
    std::cerr << "Ayuda:" << std::endl << argv[ 0 ] << " archivo_imagen" << std::endl;
    return ( -1 );
  }

  // Leer la imagen entregada -------------------------------------
  TReader::Pointer reader = TReader::New();
  reader->SetFileName( argv[ 1 ] );
  try
  {
    reader->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );
  }
  TColorImage* img = reader->GetOutput( );
  TColorImage::SizeType inputSize = img->GetLargestPossibleRegion( ).GetSize( );

  // Canal Red ----------------------------------------------
  TColorImage::Pointer rImg = TColorImage::New( );
  rImg->SetSpacing( img->GetSpacing( ) );
  rImg->SetOrigin( img->GetOrigin( ) );
  rImg->SetLargestPossibleRegion( img->GetLargestPossibleRegion( ) );
  rImg->SetRequestedRegion( img->GetRequestedRegion( ) );
  rImg->SetBufferedRegion( img->GetBufferedRegion( ) );
  rImg->Allocate( );

  // Canal Green -------------------------------------------------
  TColorImage::Pointer gImg = TColorImage::New( );
  gImg->SetSpacing( img->GetSpacing( ) );
  gImg->SetOrigin( img->GetOrigin( ) );
  gImg->SetLargestPossibleRegion( img->GetLargestPossibleRegion( ) );
  gImg->SetRequestedRegion( img->GetRequestedRegion( ) );
  gImg->SetBufferedRegion( img->GetBufferedRegion( ) );
  gImg->Allocate( );

  // Canal Blue ---------------------------------------------------
  TColorImage::Pointer bImg = TColorImage::New( );
  bImg->SetSpacing( img->GetSpacing( ) );
  bImg->SetOrigin( img->GetOrigin( ) );
  bImg->SetLargestPossibleRegion( img->GetLargestPossibleRegion( ) );
  bImg->SetRequestedRegion( img->GetRequestedRegion( ) );
  bImg->SetBufferedRegion( img->GetBufferedRegion( ) );
  bImg->Allocate( );

  // Imagen Reconstruida -----------------------------------------
  TColorImage::Pointer rgbImg = TColorImage::New( );
  rgbImg->SetSpacing( img->GetSpacing( ) );
  rgbImg->SetOrigin( img->GetOrigin( ) );
  rgbImg->SetLargestPossibleRegion( img->GetLargestPossibleRegion( ) );
  rgbImg->SetRequestedRegion( img->GetRequestedRegion( ) );
  rgbImg->SetBufferedRegion( img->GetBufferedRegion( ) );
  rgbImg->Allocate( );

  // Inicializar en Negro -----------------------------------------
  TRGBPixel black;
  black.SetRed( 0 );
  black.SetGreen( 0 );
  black.SetBlue( 0 );
  rImg->FillBuffer( black );
  gImg->FillBuffer( black );
  bImg->FillBuffer( black );
  rgbImg->FillBuffer( black );

  // Llenar los canales -------------------------------------------
  TIterator it( img, img->GetLargestPossibleRegion( ) );
  TColorIterator crIt( rImg, rImg->GetLargestPossibleRegion( ) );
  TColorIterator cgIt( gImg, gImg->GetLargestPossibleRegion( ) );
  TColorIterator cbIt( bImg, bImg->GetLargestPossibleRegion( ) );
  TColorIterator rgbIt( rgbImg, rgbImg->GetLargestPossibleRegion( ) );

  it.GoToBegin( );
  crIt.GoToBegin( );
  cgIt.GoToBegin( );
  cbIt.GoToBegin( );
  for(; !it.IsAtEnd( ) && !crIt.IsAtEnd( ) && !cgIt.IsAtEnd( ) && !cbIt.IsAtEnd( ); ++it, ++crIt, ++cgIt, ++cbIt)
  {
    TRGBPixel value, pixel;
    pixel = it.Get( );

    // Red -----------------------------
    value.SetRed( pixel.GetRed( ) );
    value.SetGreen( 0 );
    value.SetBlue( 0 );
    crIt.Set( value );

    // Green --------------------------
    value.SetRed( 0 );
    value.SetGreen( pixel.GetGreen( ) );
    value.SetBlue( 0 );
    cgIt.Set( value );

    // Blue ---------------------------
    value.SetRed( 0 );
    value.SetGreen( 0 );
    value.SetBlue( pixel.GetBlue( ) );
    cbIt.Set( value );
  }

  // Imprimir resultados parciales - Separacion -------------------
  std::stringstream ss( argv[ 1 ] );
  std::string basename;
  getline( ss, basename, '.' );

  TWriter::Pointer writer = TWriter::New( );

  // Canal Red -------------------
  writer->SetInput( rImg );
  writer->SetFileName( basename + "_R.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );
  }

  // Canal Green --------------
  writer->SetInput( gImg );
  writer->SetFileName( basename + "_G.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );
  }

  // Canal Blue ------------
  writer->SetInput( bImg );
  writer->SetFileName( basename + "_B.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );
  }

  std::cout << "Fin Separacion de Canales" << std::endl;

  // Inicia escalamiento y resescalamiento ------------------------

  TColorImage::SizeType outputSizeR;
  outputSizeR[ 0 ] = inputSize[ 0 ] * 0.75f;
  outputSizeR[ 1 ] = inputSize[ 1 ] * 0.75f;

  TColorImage::SizeType outputSizeG;
  outputSizeG[ 0 ] = inputSize[ 0 ] * 0.5f;
  outputSizeG[ 1 ] = inputSize[ 1 ] * 0.5f;

  TColorImage::SizeType outputSizeB;
  outputSizeB[ 0 ] = inputSize[ 0 ] * 0.25f;
  outputSizeB[ 1 ] = inputSize[ 1 ] * 0.25f;

  TColorImage::SpacingType outputSpacingR;
  outputSpacingR[ 0 ] = rImg->GetSpacing( )[ 0 ] * ( static_cast< double >( inputSize[ 0 ] ) / static_cast< double >( outputSizeR[ 0 ] ) );
  outputSpacingR[ 1 ] = rImg->GetSpacing( )[ 1 ] * ( static_cast< double >( inputSize[ 1 ] ) / static_cast< double >( outputSizeR[ 1 ] ) );

  TColorImage::SpacingType outputSpacingG;
  outputSpacingG[ 0 ] = gImg->GetSpacing( )[ 0 ] * ( static_cast< double >( inputSize[ 0 ] ) / static_cast< double >( outputSizeG[ 0 ] ) );
  outputSpacingG[ 1 ] = gImg->GetSpacing( )[ 1 ] * ( static_cast< double >( inputSize[ 1 ] ) / static_cast< double >( outputSizeG[ 1 ] ) );

  TColorImage::SpacingType outputSpacingB;
  outputSpacingB[ 0 ] = bImg->GetSpacing( )[ 0 ] * ( static_cast< double >( inputSize[ 0 ] ) / static_cast< double >( outputSizeB[ 0 ] ) );
  outputSpacingB[ 1 ] = bImg->GetSpacing( )[ 1 ] * ( static_cast< double >( inputSize[ 1 ] ) / static_cast< double >( outputSizeB[ 1 ] ) );

  // Scale --------------------------------------------------
  ResampleImageFilterType::Pointer resampleFilter = ResampleImageFilterType::New( );

  // Scale Red ---------------------------------------------
  resampleFilter->SetTransform( TransformType::New( ) );
  resampleFilter->SetInput( rImg );
  resampleFilter->SetSize( outputSizeR );
  resampleFilter->SetOutputSpacing( outputSpacingR );
  resampleFilter->UpdateLargestPossibleRegion( );

  writer->SetInput( resampleFilter->GetOutput( ) );
  writer->SetFileName( basename + "_sR.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );
  }

  // ReScale Red ------------------------------------------------
  rImg = resampleFilter->GetOutput( );

  inputSize = rImg->GetLargestPossibleRegion( ).GetSize( );
  outputSizeR[ 0 ] = inputSize[ 0 ] * 1.3334f;
  outputSizeR[ 1 ] = inputSize[ 1 ] * 1.3334f;
  outputSpacingR[ 0 ] = rImg->GetSpacing( )[ 0 ] * ( static_cast< double >( inputSize[ 0 ] ) / static_cast< double >( outputSizeR[ 0 ] ) );
  outputSpacingR[ 1 ] = rImg->GetSpacing( )[ 1 ] * ( static_cast< double >( inputSize[ 1 ] ) / static_cast< double >( outputSizeR[ 1 ] ) );

  // Output Red Rescaled -----------------------------------------
  resampleFilter = ResampleImageFilterType::New( );
  resampleFilter->SetTransform( TransformType::New( ) );
  resampleFilter->SetInput( rImg );
  resampleFilter->SetSize( outputSizeR );
  resampleFilter->SetOutputSpacing( outputSpacingR );
  resampleFilter->UpdateLargestPossibleRegion( );

  writer->SetInput( resampleFilter->GetOutput( ) );
  writer->SetFileName( basename + "_ssR.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );
  }

  // Scale Green ----------------------------------------------
  resampleFilter->SetTransform( TransformType::New( ) );
  resampleFilter->SetInput( gImg );
  resampleFilter->SetSize( outputSizeG );
  resampleFilter->SetOutputSpacing( outputSpacingG );
  resampleFilter->UpdateLargestPossibleRegion( );

  writer->SetInput( resampleFilter->GetOutput( ) );
  writer->SetFileName( basename + "_sG.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );
  }

  // ReScale Green ---------------------------------------------
  gImg = resampleFilter->GetOutput( );

  inputSize = gImg->GetLargestPossibleRegion( ).GetSize( );
  outputSizeG[ 0 ] = inputSize[ 0 ] * 2;
  outputSizeG[ 1 ] = inputSize[ 1 ] * 2;
  outputSpacingG[ 0 ] = gImg->GetSpacing( )[ 0 ] * ( static_cast< double >( inputSize[ 0 ] ) / static_cast< double >( outputSizeG[ 0 ] ) );
  outputSpacingG[ 1 ] = gImg->GetSpacing( )[ 1 ] * ( static_cast< double >( inputSize[ 1 ] ) / static_cast< double >( outputSizeG[ 1 ] ) );

  // Output ReScale Green ----------------------------------------
  resampleFilter = ResampleImageFilterType::New( );
  resampleFilter->SetTransform( TransformType::New( ) );
  resampleFilter->SetInput( gImg );
  resampleFilter->SetSize( outputSizeG );
  resampleFilter->SetOutputSpacing( outputSpacingG );
  resampleFilter->UpdateLargestPossibleRegion( );
  writer->SetInput( resampleFilter->GetOutput( ) );
  writer->SetFileName( basename + "_ssG.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );
  }

  // Scale Blue ------------------------------------------------
  resampleFilter->SetTransform( TransformType::New( ) );
  resampleFilter->SetInput( bImg );
  resampleFilter->SetSize( outputSizeB );
  resampleFilter->SetOutputSpacing( outputSpacingB );
  resampleFilter->UpdateLargestPossibleRegion( );

  writer->SetInput( resampleFilter->GetOutput( ) );
  writer->SetFileName( basename + "_sB.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );
  }

  // ReScale Blue ------------------------------------------------
  bImg = resampleFilter->GetOutput( );

  inputSize = bImg->GetLargestPossibleRegion( ).GetSize( );
  outputSizeB[ 0 ] = inputSize[ 0 ] * 4;
  outputSizeB[ 1 ] = inputSize[ 1 ] * 4;

  outputSpacingB[ 0 ] = bImg->GetSpacing( )[ 0 ] * ( static_cast< double >( inputSize[ 0 ] ) / static_cast< double >( outputSizeB[ 0 ] ) );
  outputSpacingB[ 1 ] = bImg->GetSpacing( )[ 1 ] * ( static_cast< double >( inputSize[ 1 ] ) / static_cast< double >( outputSizeB[ 1 ] ) );

  // Output ReScale Blue -----------------------------------------
  resampleFilter = ResampleImageFilterType::New( );
  resampleFilter->SetTransform( TransformType::New( ) );
  resampleFilter->SetInput( bImg );
  resampleFilter->SetSize( outputSizeB );
  resampleFilter->SetOutputSpacing( outputSpacingB );
  resampleFilter->UpdateLargestPossibleRegion( );

  writer->SetInput( resampleFilter->GetOutput( ) );
  writer->SetFileName( basename + "_ssB.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );
  }

  std::cout << "Fin Escalamiento y ReEscalamiento" << std::endl;

  // Imagen Compuesta ---------------------------------------------
  TColorIterator crItU( rImg, rImg->GetLargestPossibleRegion( ) );
  TColorIterator cgItU( gImg, gImg->GetLargestPossibleRegion( ) );
  TColorIterator cbItU( bImg, bImg->GetLargestPossibleRegion( ) );

  rgbIt.GoToBegin( );
  crItU.GoToBegin( );
  cgItU.GoToBegin( );
  cbItU.GoToBegin( );
  for(; !rgbIt.IsAtEnd( ) && !crItU.IsAtEnd( ) && !cgItU.IsAtEnd( ) && !cbItU.IsAtEnd( ); ++rgbIt, ++crItU, ++cgItU, ++cbItU)
  {
    TRGBPixel value, pixel;

    value = crItU.Get( );
    pixel.SetRed( value.GetRed( ) );

    value = cgItU.Get( );
    pixel.SetGreen( value.GetGreen( ) );

    value = cbItU.Get( );
    pixel.SetBlue( value.GetBlue( ) );

    rgbIt.Set( pixel );
  }

  writer->SetInput( rgbImg );
  writer->SetFileName( basename + "_rRGB.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
    return( 1 );

  }

  std::cout << "Fin Union de Canales." << std::endl;

  TColorImage::Pointer diffImg = TColorImage::New( );
  diffImg->SetSpacing( img->GetSpacing( ) );
  diffImg->SetOrigin( img->GetOrigin( ) );
  diffImg->SetLargestPossibleRegion( img->GetLargestPossibleRegion( ) );
  diffImg->SetRequestedRegion( img->GetRequestedRegion( ) );
  diffImg->SetBufferedRegion( img->GetBufferedRegion( ) );
  diffImg->Allocate( );

  diffImg->FillBuffer( black );

  TColorIterator diIt( diffImg, diffImg->GetLargestPossibleRegion( ) );

  it.GoToBegin( );
  rgbIt.GoToBegin( );
  diIt.GoToBegin( );

  for( ; !it.IsAtEnd( ), !rgbIt.IsAtEnd( ), !diIt.IsAtEnd( ); ++it, ++rgbIt, ++diIt )
  {
    TRGBPixel value, pixel, pixel2;

    pixel = it.Get( );
    pixel2 = rgbIt.Get( );

    value.SetRed( pixel.GetRed( ) - pixel2.GetRed( ) );
    value.SetGreen( pixel.GetGreen( ) - pixel2.GetGreen( ) );
    value.SetBlue( pixel.GetBlue( ) - pixel2.GetBlue( ) );

    diIt.Set( value );
  }

  writer->SetInput( diffImg );
  writer->SetFileName( basename + "_diff.png" );
  try
  {
    writer->Update( );
  }
  catch( itk::ExceptionObject& err )
  {
    std::cerr << "Error: " << err << std::endl;
  }

  std::cout << "Termina diferencia de Imagenes." << std::endl;

  return( 0 );
}
